#include <utility>
#include <algorithm>
#include <sstream>
#include <boost/format.hpp>

#include "Core.hpp"
#include "Common/Options.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Iop/Dmac/IopDmacConstants.hpp"
#include "Resources/Iop/Intc/IopIntcConstants.hpp"

CIopCoreInterpreter::CIopCoreInterpreter(Core * core) :
	CController(core)
{
}

CIopCoreInterpreter::~CIopCoreInterpreter()
{
	auto& r = core->get_resources();
	BOOST_LOG(Core::get_logger()) << 
		boost::format("IOP Core exiting @ Cycle = 0x%llX, PC = 0x%08X.") 
		% DEBUG_LOOP_COUNTER 
		% r.iop.core.r3000.pc.read_uword();
}

void CIopCoreInterpreter::handle_event(const ControllerEvent & event) const
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
		throw std::runtime_error("CIopCoreInterpreter event handler not implemented - please fix!");
	}
	}
}

int CIopCoreInterpreter::time_to_ticks(const double time_us) const
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::IOP::IOPCore::IOPCORE_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::IopCore]);
	
	if (ticks < 10)
	{
		static bool warned = false;
		if (!warned)
		{
			BOOST_LOG(Core::get_logger()) << "IopCore ticks too low - increase time delta";
			warned = true;
		}
	}

	return ticks;
}

int CIopCoreInterpreter::time_step(const int ticks_available) const
{
	auto& r = core->get_resources();

	// Check if any external interrupts are pending and immediately handle exception if there is one.
	handle_interrupt_check();
	
	// Set the instruction holder to the instruction at the current PC, and get instruction details.
	const uptr pc_address = r.iop.core.r3000.pc.read_uword();
	uptr physical_address;
	bool mmu_error = translate_vaddress(pc_address, READ, physical_address); // TODO: Add error checking for address bus error.
	IopCoreInstruction inst = IopCoreInstruction(r.iop.bus.read_uword(BusContext::Iop, physical_address));

#if defined(BUILD_DEBUG)
	static size_t DEBUG_LOOP_BREAKPOINT = 0x10000000042C36;
	static uptr DEBUG_PC_BREAKPOINT = 0x0;
	static uword DEBUG_INST_VAL_BREAKPOINT = 0x42000010; // COP0 RFE

	if (DEBUG_LOOP_COUNTER >= DEBUG_LOOP_BREAKPOINT)
	{
		// Debug print details.
		BOOST_LOG(Core::get_logger()) << 
			boost::format("IopCore cycle = 0x%llX: PC = 0x%08X, BD = %d, IntEn = %d, Instruction = %s")
			% DEBUG_LOOP_COUNTER
			% pc_address
			% r.iop.core.r3000.bdelay.is_branch_pending() 
			% !r.iop.core.cop0.status.is_interrupts_masked()
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
	return inst.get_info()->cpi;
}

void CIopCoreInterpreter::handle_interrupt_check() const
{
	auto& r = core->get_resources();

	auto& cop0 = r.iop.core.cop0;

	// Interrupt exceptions are only taken when conditions are correct.
	if (!cop0.status.is_interrupts_masked())
	{
		uword ip_cause = cop0.cause.extract_field(IopCoreCop0Register_Cause::IP);
		uword im_status = cop0.status.extract_field(IopCoreCop0Register_Status::IM);
		if (ip_cause & im_status)
		{
#if DEBUG_LOG_IOP_INTERRUPTS
			// Debug: print interrupt sources.
			debug_print_interrupt_info();
#endif
			// Handle the interrupt immediately.
			handle_exception(IopCoreException::EX_INTERRUPT);
		}
	}
}

#if defined(BUILD_DEBUG)
void CIopCoreInterpreter::debug_print_interrupt_info() const
{
	auto& r = core->get_resources();
	auto& stat = r.iop.intc.stat;
	auto& mask = r.iop.intc.mask;

	BOOST_LOG(Core::get_logger()) << 
		boost::format("IOPCore IntEx @ cycle = 0x%llX, PC = 0x%08X, BD = %d.")
		% DEBUG_LOOP_COUNTER
		% r.iop.core.r3000.pc.read_uword()
		% r.iop.core.r3000.bdelay.is_branch_pending();

	std::stringstream sources;

	// Check the INTC.
	{
		const Bitfield FILTER[] = 
		{ 
			IopIntcRegister_Stat::VBLANK, 
			IopIntcRegister_Stat::EVBLANK 
		};

		bool source_triggered = false;

		for (auto& irq_field : IopIntcRegister_Stat::IRQ_KEYS)
		{
			if (stat.extract_field(irq_field) & mask.extract_field(irq_field))
			{
				source_triggered = true;

				if (std::end(FILTER) != std::find(std::begin(FILTER), std::end(FILTER), irq_field))
					continue;

				sources << "INTC source " << IopIntcConstants::MNEMONICS[irq_field.start] << ", ";
			}
		}
		
		if (!source_triggered)
			sources << "No INTC sources (?), ";
	}

	// Print DMAC sources if it was a source.
	if (stat.extract_field(IopIntcRegister_Stat::DMAC) 
		& mask.extract_field(IopIntcRegister_Mask::DMAC))
	{
		const int half = Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2;
		const int FILTER[] = 
		{ 
			-1
			// 9,
			// 10
		};

		auto& icr0 = r.iop.dmac.icr0;
		auto& icr1 = r.iop.dmac.icr1;
		bool source_triggered = false;

		// Check first half of channels (ICR0).
		for(int i = 0; i < half; i++)
		{
			if (icr0.extract_field(IopDmacRegister_Icr0::CHANNEL_TCI_KEYS[i])
				&& icr0.extract_field(IopDmacRegister_Icr0::CHANNEL_TCM_KEYS[i]))
			{
				source_triggered = true;
				
				if (std::end(FILTER) != std::find(std::begin(FILTER), std::end(FILTER), i))
					continue;

				sources << "DMAC ICR0 channel " << IopDmacConstants::MNEMONICS[i] << ", ";
			}
		}
		// Check second half of channels (ICR1).
		for (int i = 0; i < half; i++)
		{
			if (icr1.extract_field(IopDmacRegister_Icr1::CHANNEL_TCI_KEYS[i])
				&& icr1.extract_field(IopDmacRegister_Icr1::CHANNEL_TCM_KEYS[i]))
			{
				source_triggered = true;
				
				if (std::end(FILTER) != std::find(std::begin(FILTER), std::end(FILTER), i))
					continue;

				sources << "DMAC ICR1 channel " << IopDmacConstants::MNEMONICS[half + i] << ", ";
			}
		}

		// Maybe we missed it? :(
		// This is probably ok - the DMAC might have finished a transfer during
		// the ISR of the IOP (ie: INTC DMAC stat bit is set after it has been
		// ack'd), but the IOP doesn't seem to care. It simply returns without 
		// doing anything harmful.
		if (!source_triggered)
			sources << "No DMAC channels (?), ";
	}

	if (sources.tellp())
		BOOST_LOG(core->get_logger()) << "IopCore Interrupt sources: " << sources.str();
}
#endif

bool CIopCoreInterpreter::handle_cop0_usable() const
{
	auto& r = core->get_resources();
	
	if (!r.iop.core.cop0.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.iop.core.cop0.cause.insert_field(IopCoreCop0Register_Cause::CE, 0);
		handle_exception(IopCoreException::EX_COPROCESSOR_UNUSABLE);
		return true;
	}

	// Coprocessor is usable, proceed.
	return false;
}


bool CIopCoreInterpreter::handle_over_or_underflow_32(const sword& x, const sword& y) const
{
	if (test_over_or_underflow_32(x, y))
	{
		// Over/Under flow occured.
		handle_exception(IopCoreException::EX_OVERFLOW);
		return true;
	}

	// No error occured.
	return false;
}

void CIopCoreInterpreter::INSTRUCTION_UNKNOWN(const IopCoreInstruction inst) const
{
	// Unknown instruction, log if debug is enabled.
#if defined(BUILD_DEBUG)
	BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) Unknown R3000 instruction encountered! (%s)")
		% __FILENAME__ % __LINE__ % const_cast<IopCoreInstruction*>(&inst)->get_info()->mnemonic;
#endif
}

void CIopCoreInterpreter::handle_exception(const IopCoreException exception) const
{
	auto& r = core->get_resources();
	
#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

	auto& cop0 = r.iop.core.cop0;
	auto& pc = r.iop.core.r3000.pc;
	auto& bdelay = r.iop.core.r3000.bdelay;

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	BOOST_LOG(Core::get_logger()) << boost::format("IOPCore ExceptionHandler called! Type = %s") % exceptionProperties->mMnemonic);
#endif

	// If its a reset exception, initialise COP0 registers and set PC to reset vector then return.
	// if (exception == IopCoreException::EX_RESET)
	// {
	//	cop0.initialise();
	//	pc.write_uword(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
	//	return;
	// }

	// Perform general exception handler code.
	// Vector offset value, used to set final vector address.
	usize ex_vector_offset = 0x0;

	// Set Cause.ExeCode value.
	cop0.cause.insert_field(IopCoreCop0Register_Cause::EXCCODE, static_cast<uword>(exception));

	// Set EPC and Cause.BD fields, based on if we are in the branch delay slot.
	// Note that the EPC register should point to the instruction that caused the exception.
	// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
	if (bdelay.is_branch_pending())
	{
		uword pc_addr = pc.read_uword() - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
		cop0.epc.write_uword(pc_addr);
		cop0.cause.insert_field(IopCoreCop0Register_Cause::BD, 1);
		bdelay.stop_branch();
	}
	else
	{
		uword pc_addr = pc.read_uword();
		cop0.epc.write_uword(pc_addr);
		cop0.cause.insert_field(IopCoreCop0Register_Cause::BD, 0);
	}

	// Select the vector to use (set ex_vector_offset).
	if (exception == IopCoreException::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD || exception == IopCoreException::EX_TLB_REFILL_STORE)
		ex_vector_offset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
	else
		ex_vector_offset = Constants::MIPS::Exceptions::Imp0::OADDRESS_EXCEPTION_VECTOR_V_COMMON;

	// Select vector base to use and set PC to use the specified vector.
	if (cop0.status.extract_field(IopCoreCop0Register_Status::BEV) == 1)
		pc.write_uword(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A1 + ex_vector_offset);
	else
		pc.write_uword(Constants::MIPS::Exceptions::Imp0::VADDRESS_EXCEPTION_BASE_A0 + ex_vector_offset);

	// Push the exception state within the COP0.Status register (will cause IEc and KUc to switch to interrupts disabled and kernel mode respectively).
	cop0.status.push_exception_stack();

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	if (exception != IopCoreException::EX_INTERRUPT 
		&& exception != IopCoreException::EX_RESET)
	{
		pc.offset(-static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
	}
}

bool CIopCoreInterpreter::translate_vaddress(const uptr virtual_address, const MmuAccess access, uptr & physical_address) const
{
	auto& r = core->get_resources();
	auto& cop0 = r.iop.core.cop0;

#if defined(BUILD_DEBUG)
	static const std::pair<uptr, uptr> DEBUG_VA_BREAKPOINT_RANGES[] = 
	{
		std::make_pair(0xBF801040, 0xBF801050),
		std::make_pair(0xBF808200, 0xBF808300)
	};

	for (const auto& range : DEBUG_VA_BREAKPOINT_RANGES)
	{
		if (virtual_address >= range.first && virtual_address <= range.second)
		{
			BOOST_LOG(Core::get_logger()) << 
				boost::format("IOP MMU breakpoint hit @ cycle = 0x%llX, PC = 0x%08X, VA = 0x%08X (%s).") 
				% DEBUG_LOOP_COUNTER 
				% r.iop.core.r3000.pc.read_uword() 
				% virtual_address
				% ((access == READ) ? "READ" : "WRITE");
		}
	}
#endif

	// If in kernel mode, perform a direct translation if VA is within kernel segments.
	auto context = cop0.operating_context();
	if (context == MipsCoprocessor0::OperatingContext::Kernel)
	{
		// Test for kseg0
		if (virtual_address >= Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2 && virtual_address <= Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_2)
		{
			// We are in kseg0, so to get the physical address we just minus the kseg0 base address of 0x80000000.
			// We also do not test for the Config.K0 status, as we do not involve caches unless it is an explicit request.
			physical_address = (virtual_address - Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_2);
			return false;
		}

		// Test for kseg1
		if (virtual_address >= Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && virtual_address <= Constants::MIPS::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
		{
			// We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
			physical_address = (virtual_address - Constants::MIPS::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
			return false;
		}

		// Undocumented: the IOP seems to access the addresses 0xFFC00000 - 0xFFFFFFFF as if it was trying to access the BIOS (0x1FC00000)... probably related to cache modes.
		// The IOP's MMU has an image mapping to handle this address. From PCSX2 code.
		if (virtual_address >= Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_2_LOWER_BOUND)
		{
			physical_address = virtual_address;
			return false;
		}

		// Undocumented: the IOP accesses addresses 0x00000000 - 0x001FFFFF as if it was trying to access the main memory (2MB).
		// This is not TLB mapped. From PCSX2 code.
		if (virtual_address <= Constants::IOP::IOPCore::MMU::VADDRESS_SPECIAL_1_UPPER_BOUND)
		{
			// Check if a write is being performed with isolate cache turned on.
			if (cop0.status.extract_field(IopCoreCop0Register_Status::ISC) && access == WRITE)
			{
				// Return that an error has occurred but dont invoke the exception handler (doesn't change any instructions behaviour).
				return true;
			}

			physical_address = virtual_address;
			return false;
		}
	}

	// Throw runtime error as anything else is not implemented.
	throw std::runtime_error("IOPCore MMU: VA or COP0 was not in kernel context (not implemented). Needs debugging!");
}