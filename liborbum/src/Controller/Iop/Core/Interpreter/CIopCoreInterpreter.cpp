#include <boost/format.hpp>

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Core.hpp"
#include "Resources/RResources.hpp"

CIopCoreInterpreter::CIopCoreInterpreter(Core* core) :
    CIopCore(core)
{
}

int CIopCoreInterpreter::time_step(const int ticks_available)
{
    auto& r = core->get_resources();

    // Check if any external interrupts are pending and immediately handle exception if there is one.
    handle_interrupt_check();

    // Set the instruction holder to the instruction at the current PC, and get instruction details.
    const uptr pc_address = r.iop.core.r3000.pc.read_uword();
    uptr physical_address = translate_address_inst(pc_address).value();
    uword raw_inst = r.iop.bus.read_uword(BusContext::Iop, physical_address);
    IopCoreInstruction inst = IopCoreInstruction(raw_inst);

#if defined(BUILD_DEBUG)
    static size_t DEBUG_LOOP_BREAKPOINT = 0x1000000000000000;
    static uptr DEBUG_PC_BREAKPOINT = 0xFFFF86D0;
    static uword DEBUG_INST_VAL_BREAKPOINT = 0x42000010; // COP0 RFE

    if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
    {
        // Debug print details.
        BOOST_LOG(Core::get_logger()) << boost::format("IopCore cycle = 0x%llX: PC = 0x%08X, BD = %d, IntEn = %d, Instruction = %s")
                                             % DEBUG_LOOP_COUNTER
                                             % pc_address
                                             % r.iop.core.r3000.bdelay.is_branch_pending()
                                             % !r.iop.core.cop0.status.interrupts_masked
                                             % ((!inst.value) ? "SLL (NOP)" : inst.get_info()->mnemonic);
    }

    if (DEBUG_LOOP_COUNTER == (DEBUG_LOOP_BREAKPOINT + 0x100))
    {
        BOOST_LOG(Core::get_logger()) << boost::format("IOPCore loop breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.") % DEBUG_LOOP_COUNTER % pc_address;
    }

    if (pc_address == DEBUG_PC_BREAKPOINT || pc_address == 0x0)
    {
        BOOST_LOG(Core::get_logger()) << boost::format("IOPCore PC breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.") % DEBUG_LOOP_COUNTER % pc_address;
    }

    // Special hook into ksprintf @ PC = 0x86D0, we can print to emulator log directly.
    debug_print_ksprintf();
#endif

    // Run the instruction.
    auto impl_index = inst.get_info()->impl_index;
    (this->*IOP_INSTRUCTION_TABLE[impl_index])(inst);

    // Increment PC.
    r.iop.core.r3000.bdelay.advance_pc(r.iop.core.r3000.pc);

#if defined(BUILD_DEBUG)
    // Debug increment loop counter.
    DEBUG_LOOP_COUNTER++;
#endif

    // Return the number of cycles completed.
    return 3; // TODO: fix CPI's. inst.get_info()->cpi;
}

void CIopCoreInterpreter::INSTRUCTION_UNKNOWN(const IopCoreInstruction inst)
{
    // Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 instruction encountered! (%s)")
                                         % __FILENAME__ % __LINE__ % const_cast<IopCoreInstruction*>(&inst)->get_info()->mnemonic;
#endif
}
