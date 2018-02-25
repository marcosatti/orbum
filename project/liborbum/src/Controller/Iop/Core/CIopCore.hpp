#pragma once

#include <optional>
#include <Caches.hpp>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Mips/MmuAccess.hpp"
#include "Common/Types/TranslationCache/TranslationCache.hpp"

#include "Controller/CController.hpp"

#include "Resources/Iop/Core/IopCoreException.hpp"

class Core;

/// Common functionality to the IopCore controller.
class CIopCore : public CController
{
public:
    CIopCore(Core * core);
    virtual ~CIopCore();

	void handle_event(const ControllerEvent & event) override;

protected:
#if defined(BUILD_DEBUG)
	// Debug loop counter 
	size_t DEBUG_LOOP_COUNTER = 0;

	// Debug for counting the number of exceptions handled.
	size_t DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

    /// Steps through the IOP Core state, executing instructions.
	virtual int time_step(const int ticks_available) = 0;

	/// Handles a given exception by running the general exception handler based on the exception properties defined.
	void handle_exception(const IopCoreException exception);

	/// Helper functions to check for: 
	///  - The usability conditions of COP0.
	///  - No over or underflow will occur for signed 32 bit integers.
	/// Returns a bool indicating if the instruction should return early because of unavailablity.
	/// Return early from instruction = true, proceed with instruction = false.
	/// They will automatically set the exception state as well.
	bool handle_cop0_usable();
	bool handle_no_over_or_underflow_32_check(const sword x, const sword y);

	/// Checks if any of the interrupt lines have an IRQ pending, and raises an interrupt exception.
	void handle_interrupt_check();

#if defined(BUILD_DEBUG)
	/// Prints debug information about interrupt sources.
	void debug_print_interrupt_info();
#endif

	/// Performs a cached translation lookup from the given virtual address 
	/// and access type, and returns the physical address. If the address is not
	/// found within the cache the full lookup process will be invoked.
	/// This should always be valid as the IOP has no TLB...
	std::optional<uptr> translate_address(const uptr virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access);

private:
    /// Address translation cache, see translate_address().
    TranslationCache<8, uptr, 0xFFF, TimestampedArrayLruCache> translation_cache;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);

	/// Address translation fallback lookup function, runs through the full lookup process.
	/// The IOP Core has no TLB - all virtual addresses are directly converted to
    /// physical addresses based on kernel segments. Currently if the CPU is not 
    /// in a kernel context or an MMU error occurs, a runtime_error exception will be thrown.
	std::optional<uptr> translate_address_fallback(const uptr virtual_address, const MmuRwAccess rw_access, const MmuIdAccess id_access);
};