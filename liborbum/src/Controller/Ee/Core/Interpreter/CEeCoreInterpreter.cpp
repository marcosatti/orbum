#include <boost/format.hpp>

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"

CEeCoreInterpreter::CEeCoreInterpreter(Core* core) :
    CEeCore(core),
    c_vu_interpreter(core)
{
}

int CEeCoreInterpreter::time_step(const int ticks_available)
{
    auto& r = core->get_resources();

    // Check if any external interrupts are pending and immediately handle exception if there is one.
    if (ticks_available % 16 == 0)
        handle_interrupt_check();

    // Set the instruction holder to the instruction at the current PC, and get instruction details.
    const uptr pc_address = r.ee.core.r5900.pc.read_uword();
    uptr physical_address = translate_address_inst(pc_address).value();
    uword raw_inst = r.ee.bus.read_uword(BusContext::Ee, physical_address);
    EeCoreInstruction inst = EeCoreInstruction(raw_inst);

#if 0 //defined(BUILD_DEBUG)
	static size_t DEBUG_LOOP_BREAKPOINT = 0x1000000143DE40;
	static uptr DEBUG_PC_BREAKPOINT = 0x0;
	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		BOOST_LOG(Core::get_logger()) << 
			boost::format("EeCore cycle = 0x%llX: PC = 0x%08X, BD = %d, IntEn = %d, Instruction = %s")
			% DEBUG_LOOP_COUNTER
			% pc_address
			% r.ee.core.r5900.bdelay.is_branch_pending() 
			% !r.ee.core.cop0.status.interrupts_masked
			% ((!inst.value) ? "SLL (NOP)" : inst.get_info()->mnemonic);
	}

	if (DEBUG_LOOP_COUNTER >= (DEBUG_LOOP_BREAKPOINT + 0x1000))
	{
		BOOST_LOG(Core::get_logger()) << boost::format("EeCore loop breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.") % DEBUG_LOOP_COUNTER % pc_address;
	}

	if (pc_address == DEBUG_PC_BREAKPOINT || pc_address == 0x0)
	{
		BOOST_LOG(Core::get_logger()) << boost::format("EeCore pc breakpoint hit @ cycle = 0x%llX, PC = 0x%08X.") % DEBUG_LOOP_COUNTER % pc_address;
	}
#endif

    // Run the instruction, which is based on the implementation index.
    const int impl_index = inst.get_info()->impl_index;
    (this->*EECORE_INSTRUCTION_TABLE[impl_index])(inst);

    // Increment PC.
    r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc);

    // Update the COP0.Count register, and check for interrupt.
    // See EE Core Users Manual page 70.
    if (ticks_available % 16 == 0)
        handle_count_update(inst.get_info()->cpi * 16);

#if defined(BUILD_DEBUG)
    // Debug increment loop counter.
    DEBUG_LOOP_COUNTER++;
#endif

    // Return the number of cycles completed.
    return 3; // TODO: fix CPI's. inst.get_info()->cpi;
}

void CEeCoreInterpreter::INSTRUCTION_UNKNOWN(const EeCoreInstruction inst)
{
    // Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R5900 instruction encountered! (%s)")
                                         % __FILENAME__ % __LINE__ % const_cast<EeCoreInstruction*>(&inst)->get_info()->mnemonic;
#endif
}
