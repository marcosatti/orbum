#include <sstream>
#include <algorithm>
#include <boost/format.hpp>

#include "Core.hpp"
#include "Common/Options.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"
#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Ee/Dmac/EeDmacConstants.hpp"
#include "Resources/Ee/Intc/EeIntcConstants.hpp"

CEeCoreInterpreter::CEeCoreInterpreter(Core * core) :
	CController(core),
	c_vu_interpreter(core)
{
}

CEeCoreInterpreter::~CEeCoreInterpreter()
{
	auto& r = core->get_resources();
	BOOST_LOG(Core::get_logger()) << 
		boost::format("EE Core exiting @ Cycle = 0x%llX, PC = 0x%08X.") 
		% DEBUG_LOOP_COUNTER 
		% r.ee.core.r5900.pc.read_uword();
}

void CEeCoreInterpreter::handle_event(const ControllerEvent & event) const
{
	switch (event.type)
	{
	case ControllerEvent::Type::Time:
	{
		int ticks_remaining = time_to_ticks(event.data.time_us);
		while (ticks_remaining > 0)
			ticks_remaining -= time_step(ticks_remaining);
		break;
	}
	default:
	{
		throw std::runtime_error("CEeCoreInterpreter event handler not implemented - please fix!");
	}
	}
}

int CEeCoreInterpreter::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::EeCore]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "EeCore ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CEeCoreInterpreter::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	// Check if any external interrupts are pending and immediately handle exception if there is one.
	handle_interrupt_check();
	
	// Set the instruction holder to the instruction at the current PC, and get instruction details.
	const uptr pc_address = r.ee.core.r5900.pc.read_uword();
	uptr physical_address;
	bool mmu_error = translate_vaddress(pc_address, READ, physical_address); // TODO: Add error checking for address bus error.
	EeCoreInstruction inst = EeCoreInstruction(r.ee.bus.read_uword(BusContext::Ee, physical_address));

#if defined(BUILD_DEBUG)
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
			% !r.ee.core.cop0.status.is_interrupts_masked()
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
	(this->*EECORE_INSTRUCTION_TABLE[inst.get_info()->impl_index])(inst);

	// Increment PC.
	r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc);

	// Update the COP0.Count register, and check for interrupt. See EE Core Users Manual page 70.
	r.ee.core.cop0.count.offset(inst.get_info()->cpi);
	handle_count_event_check();

#if defined(BUILD_DEBUG)
	// Debug increment loop counter.
	DEBUG_LOOP_COUNTER++;
#endif

	// Return the number of cycles completed.
	return 1; // TODO: fix CPI's. inst.get_info()->cpi;
}

void CEeCoreInterpreter::handle_interrupt_check() const
{
	auto& r = core->get_resources();

	auto& cop0 = r.ee.core.cop0;

	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (!cop0.status.is_interrupts_masked())
	{
		uword ip_cause = cop0.cause.extract_field(EeCoreCop0Register_Cause::IP);
		uword im_status = cop0.status.extract_field(EeCoreCop0Register_Status::IM);
		if (ip_cause & im_status)
		{
#if DEBUG_LOG_EE_INTERRUPTS
			// Debug: print interrupt sources.
			debug_print_interrupt_info();
#endif
			// Handle the interrupt immediately.
			handle_exception(EeCoreException::EX_INTERRUPT);
		}
	}
}

#if defined(BUILD_DEBUG)
void CEeCoreInterpreter::debug_print_interrupt_info() const
{
	auto& r = core->get_resources();

	auto& cop0 = r.ee.core.cop0;
	uword ip_cause = cop0.cause.extract_field(EeCoreCop0Register_Cause::IP);
	uword im_status = cop0.status.extract_field(EeCoreCop0Register_Status::IM);

	BOOST_LOG(Core::get_logger()) << 
		boost::format("EeCore IntEx @ cycle = 0x%llX, PC = 0x%08X, BD = %d.")
		 % DEBUG_LOOP_COUNTER
		 % r.ee.core.r5900.pc.read_uword()
		 % r.ee.core.r5900.bdelay.is_branch_pending();

	std::stringstream sources;

	// Check the INTC.
	if ((ip_cause & im_status) & 0x4)
	{
		const Bitfield FILTER[] = 
		{
			Bitfield(0, 0)
			//EeIntcRegister_Stat::VBON, 
			//EeIntcRegister_Stat::VBOF 
		};

		auto& stat = r.ee.intc.stat;
		auto& mask = r.ee.intc.mask;
		bool source_triggered = false;

		for (auto& irq_field : EeIntcRegister_Stat::IRQ_KEYS)
		{
			if (stat.extract_field(irq_field) & mask.extract_field(irq_field))
			{
				source_triggered = true;
				
				if (std::end(FILTER) != std::find(std::begin(FILTER), std::end(FILTER), irq_field))
					continue;

				sources << "INTC source " << EeIntcConstants::MNEMONICS[irq_field.start] << ", ";
			}
		}

		if (!source_triggered)
			sources << "No INTC sources (?), ";
	}

	// Check the DMAC.
	if ((ip_cause & im_status) & 0x8)
	{
		const int FILTER[] = 
		{ 
			-1
			// 5,
			// 6,
		};

		auto& stat = r.ee.dmac.stat;
		bool source_triggered = false;

		// Check through STAT for triggered channels.
		for (int i = 0; i < Constants::EE::DMAC::NUMBER_DMAC_CHANNELS; i++)
		{
			if (stat.extract_field(EeDmacRegister_Stat::CHANNEL_CIS_KEYS[i])
				&& stat.extract_field(EeDmacRegister_Stat::CHANNEL_CIM_KEYS[i]))
			{
				source_triggered = true;

				if (std::end(FILTER) != std::find(std::begin(FILTER), std::end(FILTER), i))
					continue;

				sources << "DMAC channel " << EeDmacConstants::MNEMONICS[i] << ", ";
			}
		}

		if (!source_triggered)
			sources << "No DMAC channels (?), ";
	}

	if (sources.tellp())
		BOOST_LOG(core->get_logger()) << "EeCore Interrupt sources: " << sources.str();
}
#endif

void CEeCoreInterpreter::handle_count_event_check() const
{
	auto& r = core->get_resources();
	auto& count = r.ee.core.cop0.count;
	auto& cause = r.ee.core.cop0.cause;
	auto& compare = r.ee.core.cop0.compare;

	// Check the COP0.Count register against the COP0.Compare register. See EE Core Users Manual page 72 for details.
	// The docs specify that an interrupt (IP[7]) is raised when the two values are equal.
	if (count.read_uword() == compare.read_uword())
		cause.set_irq_line(7);
	else
		cause.clear_irq_line(7);
}

bool CEeCoreInterpreter::handle_cop0_usable() const
{
	auto& r = core->get_resources();

	if (!r.ee.core.cop0.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 0);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool CEeCoreInterpreter::handle_cop1_usable() const
{
	auto& r = core->get_resources();

	if (!r.ee.core.fpu.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 1);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool CEeCoreInterpreter::handle_cop2_usable() const
{
	auto& r = core->get_resources();

	if (!r.ee.vpu.vu.unit_0.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 2);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}

bool CEeCoreInterpreter::handle_over_or_underflow_32(const sword& x, const sword& y) const
{
	if (test_over_or_underflow_32(x, y))
	{
		// Over/Under flow occured.
		handle_exception(EeCoreException::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

bool CEeCoreInterpreter::handle_over_or_underflow_64(const sdword& x, const sdword& y) const
{
	if (test_over_or_underflow_64(x, y))
	{
		// Over/Under flow occured.
		handle_exception(EeCoreException::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

void CEeCoreInterpreter::INSTRUCTION_UNKNOWN(const EeCoreInstruction inst) const
{
	// Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R5900 instruction encountered! (%s)") 
	 	% __FILENAME__ % __LINE__ % const_cast<EeCoreInstruction*>(&inst)->get_info()->mnemonic;
#endif
}

void CEeCoreInterpreter::handle_exception(const EeCoreException exception) const
{
	auto& r = core->get_resources();
	auto& cop0 = r.ee.core.cop0;

#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	BOOST_LOG(Core::get_logger()) << boost::format("EECore ExceptionHandler called! EXCCODE = %d") % static_cast<int>(exception);
#endif

	// For Reset and NMI's, need some additional processing before calling the general handlers.
	// if (exception == EeCoreException::EX_RESET)
	// {
	// 	cop0.initialise();
	// }
	// else if (exception == EeCoreException::EX_NMI)
	// {
	// 	cop0.status.insert_field(EeCoreCop0Register_Status::ERL, 1);
	// 	cop0.status.insert_field(EeCoreCop0Register_Status::BEV, 1);
	// }

	// Call the Level 1 or Level 2 exception handler based on the exception.
	if (static_cast<int>(exception) < 100)
		handle_exception_l1(exception);
	else
		handle_exception_l2(exception);
}

void CEeCoreInterpreter::handle_exception_l1(const EeCoreException exception) const
{
	auto& r = core->get_resources();

	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.
	auto& cop0 = r.ee.core.cop0;
	auto& pc = r.ee.core.r5900.pc;
	auto& bdelay = r.ee.core.r5900.bdelay;

	// Vector offset value, used to set final vector address.
	uword vector_offset = 0x0;

	// Set Cause.ExeCode value.
	cop0.cause.insert_field(EeCoreCop0Register_Cause::EXCCODE, static_cast<uword>(exception));

	// If already in exception handler (EXL == 1), do not update EPC and Cause.BD, and use general exception handler vector. Else perform normal exception processing.
	if (cop0.status.extract_field(EeCoreCop0Register_Status::EXL) == 1)
	{
		vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	else
	{
		// Set EPC and Cause.BD fields.
		// Note that the EPC register should point to the instruction that caused the exception.
		// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
		if (bdelay.is_branch_pending())
		{
			uptr pc_address = pc.read_uword() - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
			cop0.epc.write_uword(pc_address);
			cop0.cause.insert_field(EeCoreCop0Register_Cause::BD, 1);
			bdelay.stop_branch(); // Reset branch delay slot.
		}
		else
		{
			uptr pc_address = pc.read_uword();
			cop0.epc.write_uword(pc_address);
			cop0.cause.insert_field(EeCoreCop0Register_Cause::BD, 0);
		}

		// Set to kernel mode and disable interrupts.
		cop0.status.insert_field(EeCoreCop0Register_Status::EXL, 1);

		// Select the vector to use (set vector_offset).
		if (exception == EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD
			|| exception == EeCoreException::EX_TLB_REFILL_INVALID_STORE)
		{
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (exception == EeCoreException::EX_INTERRUPT)
		{
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else
		{
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}
	}

	// Select vector base to use and set PC to use the specified vector.
	if (cop0.status.extract_field(EeCoreCop0Register_Status::BEV) == 1)
	{
		pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vector_offset);
	}
	else
	{
		pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vector_offset);
	}

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (exception != EeCoreException::EX_INTERRUPT)
	{
		pc.offset(-static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

void CEeCoreInterpreter::handle_exception_l2(const EeCoreException exception) const
{
	auto& r = core->get_resources();

	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.
	auto& cop0 = r.ee.core.cop0;
	auto& pc = r.ee.core.r5900.pc;
	auto& bdelay = r.ee.core.r5900.bdelay;

	// Vector offset value, used to set final vector address.
	uword vector_offset = 0x0;

	// Set Cause.EXC2 value.
	cop0.cause.insert_field(EeCoreCop0Register_Cause::EXC2, static_cast<uword>(exception) - 100);

	// Set EPC and Cause.BD fields.
	// Note that the EPC register should point to the instruction that caused the exception.
	// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
	if (bdelay.is_branch_pending())
	{
		// TODO: no idea if this code works, yet to encounter a branch delay exception.
		uptr pc_address = pc.read_uword() - Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2;
		cop0.errorepc.write_uword(pc_address);
		cop0.cause.insert_field(EeCoreCop0Register_Cause::BD2, 1);
		bdelay.stop_branch(); // Reset branch delay slot.
	}
	else
	{
		uptr pc_address = pc.read_uword() - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
		cop0.errorepc.write_uword(pc_address);
		cop0.cause.insert_field(EeCoreCop0Register_Cause::BD2, 0);
	}

	// Set to kernel mode and disable interrupts.
	cop0.status.insert_field(EeCoreCop0Register_Status::ERL, 1);

	// Select vector to use and set PC to use it.
	if (exception == EeCoreException::EX_NMI
		|| exception == EeCoreException::EX_RESET)
	{
		pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	}
	else
	{
		if (exception == EeCoreException::EX_PERFORMANCE_COUNTER)
		{
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (exception == EeCoreException::EX_DEBUG)
		{
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			// Use V_TLB_REFIL (offset 0x00000000) (should get optimised out).
			vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}

		// Select vector base to use and set PC to use the specified vector.
		if (cop0.status.extract_field(EeCoreCop0Register_Status::DEV) == 1)
		{
			pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1 + vector_offset);
		}
		else
		{
			pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0 + vector_offset);
		}
	}

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (exception != EeCoreException::EX_RESET
		&& exception != EeCoreException::EX_NMI)
	{
		pc.offset(-static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

void CEeCoreInterpreter::handle_mmu_error(const uptr address, const MmuAccess access, const MmuError error, const sword tlb_entry_index) const
{
	auto& r = core->get_resources();

	auto& cop0 = r.ee.core.cop0;
	auto& tlb = r.ee.core.tlb;
	EeCoreException exception;

	// Set COP0 information. TODO: check if correct.
	Bitfield high_19 = Bitfield(13, 19);
	cop0.badvaddr.write_uword(address);
	cop0.context.insert_field(EeCoreCop0Register_System::BADVPN2, high_19.extract_from(address));
	cop0.entryhi.insert_field(EeCoreCop0Register_EntryHi::VPN2, high_19.extract_from(address));
	cop0.random.insert_field(EeCoreCop0Register_Random::RANDOM, tlb.generate_new_tlb_index());

	if (tlb_entry_index > 0) 
		cop0.entryhi.insert_field(EeCoreCop0Register_EntryHi::ASID, tlb.tlb_entry_at(tlb_entry_index).asid); // Set only if tlb entry index valid.

	// Find the right exception to process...
	if (access == READ)
	{
		switch (error)
		{
		case ADDRESS:
			exception = EeCoreException::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD; break;
		case TLB_REFILL:
			exception = EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD; break;
		case TLB_INVALID:
			exception = EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD; break;
		case TLB_MODIFIED:
			exception = EeCoreException::EX_TLB_MODIFIED; break;
		}
	}
	else
	{
		switch (error)
		{
		case ADDRESS:
			exception = EeCoreException::EX_ADDRESS_ERROR_STORE; break;
		case TLB_REFILL:
			exception = EeCoreException::EX_TLB_REFILL_INVALID_STORE; break;
		case TLB_INVALID:
			exception = EeCoreException::EX_TLB_REFILL_INVALID_STORE; break;
		case TLB_MODIFIED:
			exception = EeCoreException::EX_TLB_MODIFIED; break;
		}
	}

	// Pass exception to handler.
	handle_exception(exception);
}

bool CEeCoreInterpreter::translate_vaddress(const uptr virtual_address, const MmuAccess access, uptr & physical_address) const
{
	auto& r = core->get_resources();

	// This process follows the information and diagram given on page 121 & 122 of the EE Core Users Manual. 
	// I am unsure if this is exactly what happens, as the information is a bit vague on how to obtain the page mask and ASID, 
	//  but I'm confident this is what it meant (I also dont see another way to do it).
	// TODO: try to reduce the spaghetti code-ness of this... however the lookup process is complicated and error propogation is needed, so may not be able to do much.
	auto& cop0 = r.ee.core.cop0;
	auto& tlb = r.ee.core.tlb;

#if defined(BUILD_DEBUG)
	static uword DEBUG_VA_BREAKPOINT = 0xFFFFFFFF;
	if (virtual_address == DEBUG_VA_BREAKPOINT)
	{
		BOOST_LOG(Core::get_logger()) << boost::format("EE MMU breakpoint hit @ cycle = 0x%llX, PC = 0x%08X, VA = 0x%08X (%s).") 
		 	% DEBUG_LOOP_COUNTER % r.ee.core.r5900.pc.read_uword() % DEBUG_VA_BREAKPOINT % (access == READ) ? "READ" : "WRITE";
	}
#endif

	// Stage 1 - determine which CPU context we are in (user, supervisor or kernel) and check address bounds.
	// Note that a VA is valid over the full address space in kernel mode - there is no need to check bounds.
	auto context = cop0.operating_context();
	if (context == MipsCoprocessor0::OperatingContext::User)
	{
		// Operating in user mode.
		if (!(virtual_address <= Constants::MIPS::MMU::VADDRESS_USER_UPPER_BOUND))
		{
			handle_mmu_error(virtual_address, access, ADDRESS, -1);
			return true;
		}
	}
	else if (context == MipsCoprocessor0::OperatingContext::Supervisor)
	{
		// Operating in supervisor mode.
		if (!((virtual_address >= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2 && virtual_address <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1)
			|| (virtual_address <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2)))
		{
			handle_mmu_error(virtual_address, access, ADDRESS, -1);
			return true;
		}
	}

	// Stage 2 - perform TLB lookup and perform checks.
	// If we are operating in kernel mode, then SOME addreses are unmapped, and we do not need to perform a TLB lookup.
	if (context == MipsCoprocessor0::OperatingContext::Kernel)
	{
		// Test for kseg0
		if (virtual_address >= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && virtual_address <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			physical_address = (virtual_address - Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return false;
		}

		// Test for kseg1
		if (virtual_address >= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && virtual_address <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			physical_address = (virtual_address - Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return false;
		}

		// Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
		if (cop0.status.extract_field(EeCoreCop0Register_Status::ERL) == 1) 
		{
			if (virtual_address <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
			{
				// We are in kuseg unmapped region, so just return the VA.
				physical_address = virtual_address;
				return false;
			}
		}
	}

	// Check if its in the TLB and get the information.
	int tlb_index = tlb.find_tlb_entry_index(virtual_address);
	if (tlb_index == -1)
	{
		handle_mmu_error(virtual_address, access, TLB_REFILL, tlb_index);
		return true;
	}
	auto& tlb_entry = tlb.tlb_entry_at(tlb_index);

	// Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
	// TODO: Check if ASID checking is correct.
	if (tlb_entry.g == 0)
	{
		// Not a global page map, need to make sure ASID's are the same.
		if (cop0.entryhi.extract_field(EeCoreCop0Register_EntryHi::ASID) != tlb_entry.asid)
		{
			handle_mmu_error(virtual_address, access, TLB_REFILL, tlb_index);
			return true;
		}
	}

	// Stage 3 - Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access.
	// Check if accessing scratchpad.
	if (tlb_entry.s)
	{
		// As mentioned in the TLB implementation (see the class EeCoreTlb), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
		// This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).
		physical_address = 0x70000000 + (virtual_address & Constants::MASK_16KB);
		return false;
	}

	// Need to check now before continuing if the VPN is for a even or odd page (0 = Even, 1 = Odd). 
	// This is done by checking the LSB of the VPN from the original address accessed.
	// Neat trick: +1 to the TLB mask to get the mask for the LSB of the VPN. Note that this mask is always equal to or greater than 4KB.
	uword index_even_odd_mask = ((tlb_entry.mask << 12) | 0xFFF) + 1;
	ubyte tlb_even_odd_index = (virtual_address & index_even_odd_mask) ? 1 : 0;

	// Check if the entry is valid (V bit)
	if (!tlb_entry.physical_info[tlb_even_odd_index].v)
	{
		handle_mmu_error(virtual_address, access, TLB_INVALID, tlb_index);
		return true;
	}

	// Check if entry is allowed writes (dirty flag) and raise TLB modified exception if writing occurs.
	if (!tlb_entry.physical_info[tlb_even_odd_index].d && access == WRITE)
	{
		handle_mmu_error(virtual_address, access, TLB_MODIFIED, tlb_index);
		return true;
	}

	// Stage 4 - calculate final physical address from TLB entry.
	// Cache access?
	// TODO: Left unimplemented for now. The location is still refering to main memory.
	/*
	if (tlbEntry.physical_info[mIndexEvenOdd].mC > 0)
	{
	}
	*/

	// We are accessing main memory - combine PFN with offset using the TLB entry mask, to get the physical address (PhyAddr = PFN (shifted) | Offset).
	uword offset_mask = (tlb_entry.mask << 12) | 0xFFF;
	physical_address = ((tlb_entry.physical_info[tlb_even_odd_index].pfn << 12) | (virtual_address & offset_mask));
	return false;
}