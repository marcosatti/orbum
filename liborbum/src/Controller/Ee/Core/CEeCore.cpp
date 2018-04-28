#include <sstream>
#include <boost/format.hpp>
#include <Console.hpp>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/CEeCore.hpp"

#include "Resources/RResources.hpp"
#include "Resources/Ee/Dmac/EeDmacConstants.hpp"
#include "Resources/Ee/Intc/EeIntcConstants.hpp"

#if defined(BUILD_DEBUG)
std::atomic_bool DEBUG_IN_CONTROLLER_EECORE = false;
#endif

CEeCore::CEeCore(Core * core) :
	CController(core)
{
}

CEeCore::~CEeCore()
{
#if defined(BUILD_DEBUG)
	auto& r = core->get_resources();
	BOOST_LOG(Core::get_logger()) << 
		boost::format("EE Core exiting @ Cycle = 0x%llX, PC = 0x%08X.") 
		% DEBUG_LOOP_COUNTER 
		% r.ee.core.r5900.pc.read_uword();
#endif
}

void CEeCore::handle_event(const ControllerEvent & event)
{
#if defined(BUILD_DEBUG)
    if (DEBUG_IN_CONTROLLER_EECORE)
        throw std::runtime_error("EeCore controller is already running!");
    DEBUG_IN_CONTROLLER_EECORE = true;
	static size_t DEBUG_COUNTER = 0;
#endif

#if defined(BUILD_DEBUG)
	static std::chrono::high_resolution_clock::time_point DEBUG_OVERHEAD = std::chrono::high_resolution_clock::now();
	const std::chrono::high_resolution_clock::time_point DEBUG_T1 = std::chrono::high_resolution_clock::now();
#endif

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
		throw std::runtime_error("CEeCore event handler not implemented - please fix!");
	}
	}

#if defined(BUILD_DEBUG)
	const std::chrono::high_resolution_clock::time_point DEBUG_T2 = std::chrono::high_resolution_clock::now();

	const std::chrono::duration<double, std::micro> run_duration = DEBUG_T2 - DEBUG_T1;
	const std::chrono::duration<double, std::micro> overhead_duration = DEBUG_T1 - DEBUG_OVERHEAD;
	const std::chrono::duration<double, std::micro> total_duration = run_duration + overhead_duration;

	DEBUG_OVERHEAD = std::chrono::high_resolution_clock::now();

	const std::string info = str(boost::format("EE Core benchmark; total: %.3f us, run: %.3f us (%.1f%%), overhead: %.3f us (%.1f%%)")
		% total_duration.count()
		% run_duration.count()
		% ((run_duration / total_duration) * 100.0)
		% overhead_duration.count()
		% ((overhead_duration / total_duration) * 100.0));

	//BOOST_LOG(core->get_logger()) << info;

	if (DEBUG_COUNTER % 100 == 0)
		print_title(info);

#endif

#if defined(BUILD_DEBUG)
	DEBUG_COUNTER++;
    DEBUG_IN_CONTROLLER_EECORE = false;
#endif
}

int CEeCore::time_to_ticks(const double time_us)
{
	int ticks = static_cast<int>(time_us / 1.0e6 * Constants::EE::EECore::EECORE_CLK_SPEED * core->get_options().system_biases[ControllerType::Type::EeCore]);
	
	if (ticks < 16)
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

void CEeCore::handle_interrupt_check()
{
	auto& r = core->get_resources();

	auto& cop0 = r.ee.core.cop0;

	// Interrupt exceptions are only taken when conditions are correct.
	// Interrupt exception checking follows the process on page 74 of the EE Core Users Manual.
	if (!cop0.status.interrupts_masked)
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
void CEeCore::debug_print_interrupt_info()
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

void CEeCore::handle_count_update(const int cpi)
{
	auto& r = core->get_resources();
	auto& count = r.ee.core.cop0.count;
	auto& status = r.ee.core.cop0.status;

	count.offset(cpi);

	// Only bother checking for interrupts if the counting is enabled.
	if (status.count_interrupts_enabled)
	{
		auto& cause = r.ee.core.cop0.cause;
		auto& compare = r.ee.core.cop0.compare;

		// Check the COP0.Count register against the COP0.Compare register. 
		// See EE Core Users Manual page 72 for details. The docs specify 
		// that an interrupt (IP[7]) is raised when the two values are equal.
		// We kind of cheat here a little - abusing the fact that if an
		// interrupt is raised, writing to the compare register will clear
		// the interrupt (which should be done in the ISR), so we can get
		// away with a GTE comparison.
		auto count_value = count.read_uword();
		auto compare_value = compare.read_uword();
		if (count_value >= compare_value)
			cause.set_irq_line(7);
	}
}

bool CEeCore::handle_cop0_usable()
{
	auto& r = core->get_resources();

	if (!r.ee.core.cop0.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 0);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool CEeCore::handle_cop1_usable()
{
	auto& r = core->get_resources();

	if (!r.ee.core.fpu.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 1);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool CEeCore::handle_cop2_usable()
{
	auto& r = core->get_resources();

	if (!r.ee.vpu.vu.unit_0.is_usable())
	{
		// Coprocessor was not usable. Raise an exception.
		r.ee.core.cop0.cause.insert_field(EeCoreCop0Register_Cause::CE, 2);
		handle_exception(EeCoreException::EX_COPROCESSOR_UNUSABLE);
		return false;
	}

	// Coprocessor is usable, proceed.
	return true;
}

bool CEeCore::handle_no_over_or_underflow_32_check(const sword x, const sword y)
{
	if (test_over_or_underflow_32(x, y))
	{
		// Over/Under flow occured.
		handle_exception(EeCoreException::EX_OVERFLOW);
		return false;
	}

	// No error occured.
	return true;
}

bool CEeCore::handle_no_over_or_underflow_64_check(const sdword x, const sdword y)
{
	if (test_over_or_underflow_64(x, y))
	{
		// Over/Under flow occured.
		handle_exception(EeCoreException::EX_OVERFLOW);
		return false;
	}

	// No error occured.
	return true;
}

void CEeCore::handle_exception(const EeCoreException exception)
{
	auto& r = core->get_resources();
	auto& cop0 = r.ee.core.cop0;
	auto& pc = r.ee.core.r5900.pc;
	auto& bdelay = r.ee.core.r5900.bdelay;

#if defined(BUILD_DEBUG)
	DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif

#if 0 // defined(BUILD_DEBUG)
	// Debug print exception type.
	BOOST_LOG(Core::get_logger()) << boost::format("EECore ExceptionHandler called! EXCCODE = %d") % static_cast<int>(exception);
#endif

	const bool is_level2 = static_cast<int>(exception) >= 100;
	const uword exccode = is_level2 ? static_cast<uword>(exception) - 100 :  static_cast<uword>(exception);

	// Sets the EPC and BD fields.
	auto set_error_address = [&]()
	{
		// Note that the (Error)EPC register should point to the instruction that caused the exception.
		// If we are in a branch delay slot, need to flush it (reset) so we dont jump after this exits.
		if (bdelay.is_branch_pending())
		{
			uptr pc_address = pc.read_uword() - Constants::MIPS::SIZE_MIPS_INSTRUCTION;
			is_level2 ? cop0.errorepc.write_uword(pc_address) : cop0.epc.write_uword(pc_address);
			cop0.cause.insert_field(is_level2 ? EeCoreCop0Register_Cause::BD2 : EeCoreCop0Register_Cause::BD, 1);
			bdelay.stop_branch(); // Reset branch delay slot.
		}
		else
		{
			uptr pc_address = pc.read_uword();
			is_level2 ? cop0.errorepc.write_uword(pc_address) : cop0.epc.write_uword(pc_address);
			cop0.cause.insert_field(is_level2 ? EeCoreCop0Register_Cause::BD2 : EeCoreCop0Register_Cause::BD, 0);
		}
	};

	// Set the error level.
	cop0.status.insert_field(EeCoreCop0Register_Status::ERL, is_level2 ? 1 : 0);
	cop0.cause.insert_field(is_level2 ? EeCoreCop0Register_Cause::EXC2 : EeCoreCop0Register_Cause::EXCCODE, exccode);
	
	// For Reset and NMI's, handle these through specific process.
	if (exception == EeCoreException::EX_RESET || exception == EeCoreException::EX_NMI)
	{
		set_error_address();
		pc.write_uword(Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_V_RESET_NMI);
		return;
	}

	// Calculate exception handler vector base.
	uptr exception_vector_base;
	if (cop0.status.extract_field(EeCoreCop0Register_Status::DEV) || cop0.status.extract_field(EeCoreCop0Register_Status::BEV))
		exception_vector_base = Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A1;
	else
		exception_vector_base = Constants::MIPS::Exceptions::Imp46::VADDRESS_EXCEPTION_BASE_A0;

	// Calculate exception handler vector base. 
	uptr exception_vector_offset;
	if (cop0.status.extract_field(EeCoreCop0Register_Status::EXL))
	{
		// Already in exception handler - use the general ISR.
		exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
	}
	else
	{
		// Update the error context.
		set_error_address();
		cop0.status.insert_field(EeCoreCop0Register_Status::EXL, 1);

		// Select the appropriate ISR offset.
		if (exception == EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD 
			|| exception == EeCoreException::EX_TLB_REFILL_INVALID_STORE)
		{
			exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_TLB_REFILL;
		}
		else if (exception == EeCoreException::EX_INTERRUPT)
		{
			exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_INTERRUPT;
		}
		else if (exception == EeCoreException::EX_PERFORMANCE_COUNTER)
		{
			exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COUNTER;
		}
		else if (exception == EeCoreException::EX_DEBUG)
		{
			exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_DEBUG;
		}
		else
		{
			exception_vector_offset = Constants::MIPS::Exceptions::Imp46::OADDRESS_EXCEPTION_VECTOR_V_COMMON;
		}
	}

	// Update the PC with the final exception handler vector address.
	pc.write_uword(exception_vector_base + exception_vector_offset);

	// TODO: Extra code to make sure the PC is correct. Currently an external exception (eg: interrupt) is run before the instruction is executed, so the PC is correct.
	//       But for an internal interrupt (eg: syscall), the instruction has already run and so the PC will get incremented upon this function's return, which leads to a skipped instruction.
	//       This is the easiest way to fix this, not sure how to properly do it (just need to play around with the code structure).
	//       Reset and NMI's are handled above, no need to check for them here.
	if (exception != EeCoreException::EX_INTERRUPT)
		pc.offset(-static_cast<sword>(Constants::MIPS::SIZE_MIPS_INSTRUCTION));
}

std::optional<uptr> CEeCore::translate_address(const uptr virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access)
{
#if defined(BUILD_DEBUG)
	auto& r = core->get_resources();

	static const std::pair<uptr, uptr> DEBUG_VA_BREAKPOINT_RANGES[] = 
	{
		std::make_pair(0x1F402000, 0x1F402040)
	};

	for (const auto& range : DEBUG_VA_BREAKPOINT_RANGES)
	{
		if (virtual_address >= range.first && virtual_address <= range.second)
		{
			BOOST_LOG(Core::get_logger()) << 
				boost::format("EE MMU breakpoint hit @ cycle = 0x%llX, PC = 0x%08X, VA = 0x%08X (%s).") 
				% DEBUG_LOOP_COUNTER 
				% r.ee.core.r5900.pc.read_uword() 
				% virtual_address
				% ((rw_access == READ) ? "READ" : "WRITE");
		}
	}
#endif

    auto fallback_fn = [this](const uptr virtual_address, const MmuRwAccess rw_access) -> std::optional<uptr>
	{ 
		return translate_address_fallback(virtual_address, rw_access); 
	};

	std::optional<uptr> result;
	switch (id_access)
	{
	case INSTRUCTION:
		result = translation_cache_inst.lookup(virtual_address, rw_access, fallback_fn);
		break;
	case DATA:
		result = translation_cache_data.lookup(virtual_address, rw_access, fallback_fn);
		break;
	default:
		throw std::runtime_error("Unrecognised id_access");
	}

	return result;
}

std::optional<uptr> CEeCore::translate_address_fallback(const uptr virtual_address, const MmuRwAccess rw_access)
{
    // This process follows the information and diagram given on page 121 & 122
    // of the EE Core Users Manual. 

    auto& r = core->get_resources();
    auto& cop0 = r.ee.core.cop0;
    auto& tlb = r.ee.core.tlb;

    auto handle_mmu_error = [&](const uptr address, const EeCoreException exception, const sword tlb_entry_index)
    {
        // Set COP0 information. TODO: check if correct.
        const Bitfield high_19 = Bitfield(13, 19);
        cop0.badvaddr.write_uword(address);
        cop0.context.insert_field(EeCoreCop0Register_System::BADVPN2, high_19.extract_from(address));
        cop0.entryhi.insert_field(EeCoreCop0Register_EntryHi::VPN2, high_19.extract_from(address));
        cop0.random.insert_field(EeCoreCop0Register_Random::RANDOM, tlb.generate_new_tlb_index());

        // Set only if tlb entry index valid.
        if (tlb_entry_index > 0) 
            cop0.entryhi.insert_field(EeCoreCop0Register_EntryHi::ASID, tlb.tlb_entry_at(tlb_entry_index).asid); 

        // Pass exception to handler.
        handle_exception(exception);
    };

    uptr physical_address = 0x0;

    // Stage 1 - determine which CPU context we are in (user, supervisor or kernel) and check address bounds.
    // Note that a VA is valid over the full address space in kernel mode - there is no need to check bounds.
    auto context = cop0.operating_context();
    if (context == MipsCoprocessor0::OperatingContext::User)
    {
        // Operating in user mode.
        if (!(virtual_address <= Constants::MIPS::MMU::VADDRESS_USER_UPPER_BOUND))
        {
            handle_mmu_error(
                virtual_address,
                rw_access == READ ? EeCoreException::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD : EeCoreException::EX_ADDRESS_ERROR_STORE, 
                -1
            );
            return std::nullopt;
        }
    }
    else if (context == MipsCoprocessor0::OperatingContext::Supervisor)
    {
        // Operating in supervisor mode.
        if (!((virtual_address >= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_LOWER_BOUND_2 && virtual_address <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_1)
            || (virtual_address <= Constants::MIPS::MMU::VADDRESS_SUPERVISOR_UPPER_BOUND_2)))
        {
            handle_mmu_error(
                virtual_address,
                rw_access == READ ? EeCoreException::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD : EeCoreException::EX_ADDRESS_ERROR_STORE, 
                -1
            );
            return std::nullopt;
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
            return std::make_optional(physical_address);
        }

        // Test for kseg1
        if (virtual_address >= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3 && virtual_address <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_3)
        {
            // We are in kseg1, so to get the physical address we just minus the kseg1 base address of 0xA0000000.
            physical_address = (virtual_address - Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_LOWER_BOUND_3);
            return std::make_optional(physical_address);
        }

        // Test for Status.ERL = 1 (indicating kuseg is unmapped). Note that the VA still has to be within the segment bounds for this to work.
        if (cop0.status.extract_field(EeCoreCop0Register_Status::ERL) == 1)
        {
            if (virtual_address <= Constants::MIPS::MMU::MMU::VADDRESS_KERNEL_UPPER_BOUND_1)
            {
                // We are in kuseg unmapped region, so just return the VA.
                physical_address = virtual_address;
                return std::make_optional(physical_address);
            }
        }
    }

    // Check if its in the TLB and get the information.
    int tlb_index = tlb.find_tlb_entry_index(virtual_address);
    if (tlb_index == -1)
    {
        handle_mmu_error(
            virtual_address,
            rw_access == READ ? EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD : EeCoreException::EX_TLB_REFILL_INVALID_STORE, 
            -1
        );
        return std::nullopt;
    }
    const auto& tlb_entry = tlb.tlb_entry_at(tlb_index);

    // Check the global bit, and check ASID if needed (against the ASID value in the EntryHi COP0 register).
    // TODO: Check if ASID checking is correct.
    if (!tlb_entry.g)
    {
        // Not a global page map, need to make sure ASID's are the same.
        if (cop0.entryhi.extract_field(EeCoreCop0Register_EntryHi::ASID) != tlb_entry.asid)
        {
            handle_mmu_error(
                virtual_address,
                rw_access == READ ? EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD : EeCoreException::EX_TLB_REFILL_INVALID_STORE, 
                -1
            );
            return std::nullopt;
        }
    }

    // Stage 3 - Assess if the page is valid and it is marked dirty. Also check for the scratchpad ram access.
    // Need to check now before continuing if the VPN is for a even or odd page (0 = Even, 1 = Odd). 
    // This is done by checking the LSB of the VPN from the original address accessed.
    ubyte tlb_even_odd_index = (virtual_address & tlb_entry.mask.evenodd_mask) ? 1 : 0;

    // Check if the entry is valid (V bit)
    if (!tlb_entry.physical_info[tlb_even_odd_index].v)
    {
        handle_mmu_error(
            virtual_address,
            rw_access == READ ? EeCoreException::EX_TLB_REFILL_INVALID_INSTRUCTION_FETCH_LOAD : EeCoreException::EX_TLB_REFILL_INVALID_STORE, 
            -1
        );
        return std::nullopt;
    }

    // Check if entry is allowed writes (dirty flag) and raise TLB modified exception if writing occurs.
    if (!tlb_entry.physical_info[tlb_even_odd_index].d && rw_access == WRITE)
    {
        handle_mmu_error(
            virtual_address,
            EeCoreException::EX_TLB_MODIFIED, 
            -1
        );
        return std::nullopt;
    }
    
    // Check if accessing scratchpad.
    if (tlb_entry.s)
    {
        // As mentioned in the TLB implementation (see the class EeCoreTlb), the scratchpad ram is allocated in the TLB as a continuous block of 4 x 4KB pages (16KB).
        // This means that the VPN occupies the upper 18 bits, with the 2 next lower bits selecting which 4KB page we are in (0 -> 3).
        physical_address = 0x70000000 + (virtual_address & Constants::MASK_16KB);
        return std::make_optional(physical_address);
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
    uword offset_mask = (tlb_entry.mask.pagemask << 12) | 0xFFF;
    physical_address = ((tlb_entry.physical_info[tlb_even_odd_index].pfn << 12) | (virtual_address & offset_mask));
    return std::make_optional(physical_address);
}
