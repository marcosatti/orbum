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
    RResources& r = core->get_resources();

    // TODO: Not yet implemented.
#if defined(BUILD_DEBUG)
    DEBUG_LOOP_COUNTER++;
#endif

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
        const udword raw_inst = r.ee.bus.read_uword(BusContext::Vu, 0x11000000 + 0x8000 * unit->core_id + pc);

        const uword upper_raw_inst = (raw_inst >> 31) & 0xFFFFFFFF;
        const VuInstruction upper_inst = VuInstruction(upper_raw_inst);
        const MipsInstructionInfo upper_info = upper_inst.upper_lookup();

        const uword lower_raw_inst = raw_inst & 0xFFFFFFFF;
        const VuInstruction lower_inst = VuInstruction(lower_raw_inst);
        const MipsInstructionInfo lower_info = lower_inst.lower_lookup();

        // If I (bit 63) is set, execute UpperInst and LOI (using LowerInst as an immediate)
        if ((raw_inst >> 63) & 1)
        {
            (this->*VU_INSTRUCTION_TABLE[upper_inst.upper_lookup().impl_index])(unit, upper_inst);
            this->LOI(unit, lower_inst);

            // Onto the next unit
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

        (this->*VU_INSTRUCTION_TABLE[lower_inst.lower_lookup().impl_index])(unit, lower_inst);
        (this->*VU_INSTRUCTION_TABLE[upper_inst.upper_lookup().impl_index])(unit, upper_inst);

        // Advance the PC
        unit->bdelay.advance_pc(unit->pc);
    }

    // TODO: Correct CPI
    return 1;
}
