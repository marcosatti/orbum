#pragma once

#include <optional>
#include <Caches.hpp>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"
#include "Common/Types/TranslationCache/TranslationCache.hpp"

#include "Controller/CController.hpp"

#include "Resources/Ee/Core/EeCoreException.hpp"

class Core;

/// Common functionality to the EeCore controller.
class CEeCore : public CController
{
public:
	CEeCore(Core * core);
	virtual ~CEeCore();

	void handle_event(const ControllerEvent & event) override;

protected:
#if defined(BUILD_DEBUG)
	/// Debug loop counter.
	size_t DEBUG_LOOP_COUNTER = 0;

	/// Debug for counting the number of exceptions handled.
	size_t DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

    /// Steps through the EE Core state, executing instructions.
	virtual int time_step(const int ticks_available) = 0;

	/// Handles a given exception by running the general exception handler (level 1 or 2) based on the exception properties defined.
	void handle_exception(const EeCoreException exception);
	
	/// Helper functions to check:
	///  - The usability conditions of COP0, 1, 2 (VU0).
	///  - No over or underflow will occur for signed 32/64 bit integers.
	/// They will automatically set the exception state on their failure condition.
	bool handle_cop0_usable();
	bool handle_cop1_usable();
	bool handle_cop2_usable();
	bool handle_no_over_or_underflow_32_check(const sword x, const sword y);
	bool handle_no_over_or_underflow_64_check(const sdword x, const sdword y);

	/// Increments the count register by the number of cycles and checks the 
	/// COP0.Count register against the COP0.Compare register.
	/// If the Count value == Compare value, an interrupt is generated.
	void handle_count_update(const int cycles);

	/// Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	void handle_interrupt_check();

#if defined(BUILD_DEBUG)
	/// Prints debug information about interrupt sources.
	void debug_print_interrupt_info();
#endif

	/// Performs a cached translation lookup from the given virtual address 
	/// and access type, and returns the physical address. If the address is not
	/// found within the cache the full lookup process will be invoked.
	/// If the EE Core's TLB is modified, the whole cache is flushed.
	std::optional<uptr> translate_address(const uptr virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access);

private:
	/// Cached TLB write count - indicates the translation cache is valid
	/// for this "timestamp".
	size_t translation_cache_tlb_write_count;

    /// Address translation cache, see translate_address().
    TranslationCache<1, 2, 1, 1, 1, 4, uptr, 0xFFF, ArrayLruCache> translation_cache;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);

	/// Address translation fallback lookup function, runs through the full lookup process.
	/// There are 4 associated stages (see diagram on EE Core Users Manual page 122):
	/// Stage 1 tests the operating context of the CPU and checks if the address is invalid.
	/// Stage 2 performs a TLB lookup and checks the ASID and G bits.
	/// Stage 3 tests the valid and dirty flags, and determines if the VPN is for the even or odd PFN.
	/// Stage 4 calculates the final physical address.
	std::optional<uptr> translate_address_fallback(const uptr virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access);
};