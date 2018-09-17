#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CVuInterpreter::CVuInterpreter(Core* core) :
    CVu(core)
{
}

int CVuInterpreter::time_step(const int ticks_available)
{
#if defined(BUILD_DEBUG)
    DEBUG_LOOP_COUNTER++;
#endif

    RResources& r = core->get_resources();

    int cycles_consumed[2] = { 1, 1 };

    // The priority of register writing is: COP2 Transfer > Upper Inst > Lower Inst

    for (auto* unit : r.ee.vpu.vu.units)
    {
        // Move on if the unit is not running and the delay slot is empty
        if (unit->operation_state != VuOperationState::Run && !unit->bdelay.is_branch_pending())
        {
            continue;
        }

        // PC & Instructions stuff...
        const uword pc = unit->pc.read_uword() & 0x0FFF;
        const udword raw_inst = r.ee.bus.read_uword(BusContext::Vu, 0x11000000 | (0x8000 * unit->core_id + pc));

        const uword upper_raw_inst = (raw_inst >> 32) & 0xFFFFFFFF;
        const VuInstruction upper_inst = VuInstruction(upper_raw_inst);

        const uword lower_raw_inst = raw_inst & 0xFFFFFFFF;
        const VuInstruction lower_inst = VuInstruction(lower_raw_inst);

        // If I (bit 63) is set, execute UpperInst and LOI (using LowerInst as an immediate)
        if ((raw_inst >> 63) & 1)
        {
            execute_upper_instruction(unit, upper_inst);
            this->LOI(unit, lower_inst);

            // Advance PC and onto the next unit
            unit->bdelay.advance_pc(unit->pc);
            continue;
        }

        // If E (bit 62) is set, execute current and next instruction, and
        // terminate the current micro subroutine
        // Here we setup a delay slot for the next instruction
        if ((raw_inst >> 62) & 1)
        {
            if (unit->bdelay.is_branch_pending())
            {
                BOOST_LOG(Core::get_logger()) << "Found E-bit in branch delay slot";
            }

            // Don't actually branch
            unit->bdelay.set_branch_itype(unit->pc, 0);

            // Change the state of the VU
            unit->operation_state = VuOperationState::Ready;
        }

        // If M (bit 61) is set, then execute QMTC2 or CTC2 without interlocking
        // (VU0 only)
        if (((raw_inst >> 61) & 1) && unit->core_id == 0)
        {
            // TODO
        }

        // If D (bit 60) and DE (in FBRST) is set, terminate the micro subroutine and interrupt
        if ((raw_inst >> 60) & 1)
        {
            if (r.ee.vpu.vu.fbrst.de(unit->core_id))
            {
                auto _lock = r.ee.intc.stat.scope_lock();
                r.ee.intc.stat.insert_field(EeIntcRegister_Stat::VU_KEYS[unit->core_id], 1);
                unit->operation_state = VuOperationState::Stop;
            }
        }

        // If T (bit 59) and TE (in FBRST) is set, terminate the micro subroutine and interrupt
        if ((raw_inst >> 59) & 1)
        {
            if (r.ee.vpu.vu.fbrst.te(unit->core_id))
            {
                auto _lock = r.ee.intc.stat.scope_lock();
                r.ee.intc.stat.insert_field(EeIntcRegister_Stat::VU_KEYS[unit->core_id], 1);
                unit->operation_state = VuOperationState::Stop;
            }
        }

        execute_lower_instruction(unit, lower_inst);
        execute_upper_instruction(unit, upper_inst);

        // Advance the PC
        unit->bdelay.advance_pc(unit->pc);
    }

    // TODO: Correct CPI
    return 1;
}

int CVuInterpreter::execute_lower_instruction(VuUnit_Base* unit, VuInstruction inst)
{
    const MipsInstructionInfo info = inst.lower_lookup();

    switch (info.pipeline)
    {
    case VuPipeline::FDIV:
    {
        if (!unit->fdiv.is_running())
        {
            // FDIV is not responsible for the first 2 cycles (fetch instruction
            // and read registers)
            unit->fdiv = FdivPipeline(info.cpi - 2);
            
            // Temporarily save current Q in new_q, and swap it later
            // (needed because the instructions operate on unit->q)
            unit->fdiv.new_q = unit->q;
            (this->*VU_INSTRUCTION_TABLE[info.impl_index])(unit, inst);
            std::swap(unit->q, unit->fdiv.new_q);

            break;
        }
        else
        {
            // Run the pipelines, and use the new registers if the pipeline is finished
            // Same for EFU etc
            unit->fdiv.consume_cycle(1);
            if (!unit->fdiv.is_running()) unit->q = unit->fdiv.new_q;
        }
    };

    case VuPipeline::EFU:
    {
        if (!unit->efu.is_running())
        {
            // The 3 cycles are for instruction fetching, and registers read/write.
            // EFU is responsible for the execution stages only.
            unit->efu = EfuPipeline(info.cpi - 3);
            
            // Temporarily save current P in new_p, and swap it later
            // (needed because the instructions operate on unit->p)
            unit->efu.new_p = unit->p;
            (this->*VU_INSTRUCTION_TABLE[info.impl_index])(unit, inst);
            std::swap(unit->p, unit->efu.new_p);

            break;
        }
        else
        {
            unit->efu.consume_cycle(1);
            if (!unit->efu.is_running()) unit->p = unit->efu.new_p;
        }
    };

    case VuPipeline::IALU:
    {
        // See case EFU for the 3 cycles.
        // TODO: if an integer register is used during store/load data hazard is generated
        unit->ialu = IaluPipeline(info.cpi - 3);
        
        (this->*VU_INSTRUCTION_TABLE[info.impl_index])(unit, inst);

        unit->ialu.consume_cycle(1);
        break;
    };

    case VuPipeline::Basic:
    {
        (this->*VU_INSTRUCTION_TABLE[info.impl_index])(unit, inst);

        break;
    };

    default:
        throw std::runtime_error("VU: Found instruction of unsupported pipeline");
    }

    // Every step runs only 1 cycle except when the pipeline stalls
    return 1;
}

int CVuInterpreter::execute_upper_instruction(VuUnit_Base* unit, VuInstruction inst)
{
    const MipsInstructionInfo info = inst.upper_lookup();

    for (FmacPipeline& fmac : unit->fmac)
    {
        // TODO: Data hazards occur when a register is being used by two 
        // units/pipelines, but the current implementation tracks only 

        bool is_type_3 = (inst.opcode() >> 2) == 0b1111;

        // If the VF register is being used, stall FMAC
        {
            // Upper Instruction field type 3 specifies only 2 registers, fs and ft,
            // while the others specifies 3 registers, fd, fs and ft.
            // (type 3 has the opcode 1111__)
            if (is_type_3)
            {
                if (fmac.is_using_register(inst.ft(), inst.dest()) || 
                    fmac.is_using_register(inst.fs(), inst.dest()))
                {
                    fmac.consume_cycle(1);
                    continue;
                }
            }
            else
            {
                if (fmac.is_using_register(inst.fd(), inst.dest()) ||
                    fmac.is_using_register(inst.fs(), inst.dest()) ||
                    fmac.is_using_register(inst.ft(), inst.dest()))
                {
                    fmac.consume_cycle(1);
                    continue;
                }
            }
        }

        if (!fmac.is_running())
        {
            // FMAC has three execution stages, fixed for all the FMAC instructions
            if (is_type_3)
                fmac = FmacPipeline(3, inst.ft(), inst.dest());
            else
                fmac = FmacPipeline(3, inst.fd(), inst.dest());
            (this->*VU_INSTRUCTION_TABLE[info.impl_index])(unit, inst);
        }
        else
        {
            fmac.consume_cycle(1);
        }
    }

    // Every step runs only 1 cycle except when the pipeline stalls
    return 1;
}
