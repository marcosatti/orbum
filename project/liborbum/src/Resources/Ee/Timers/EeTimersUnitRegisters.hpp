#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "Controller/ControllerEvent.hpp"

using ControllerEventType = ControllerEvent::Type;

/// The Timer Count register type. See EE Users Manual page 37.
/// Provides the increment function, which also wraps the uword value around once overflow (> uhword) happens (an internal flag is set).
/// This register is only accessed by the Timers controller, it doesn't need any sync support.
class EeTimersUnitRegister_Count : public SizedWordRegister
{
public:
	EeTimersUnitRegister_Count();

	/// Increments the timer by the amount specified (controlling prescalling when required).
	/// Updates the overflow status. If it overflows, the flag is set.
	void increment(const uhword value);
	
	/// Returns if the register has overflowed or not, and resets the flag.
	bool is_overflowed_and_reset();

	/// Reset the count with the specified prescale.
	void reset_prescale(const int prescale_target);

private:
	/// Internal overflow flag. Use/see is_overflowed_and_reset().
	bool is_overflowed;

	/// Prescale functionality, see increment().
	/// (ie: needs x amount before 1 is added to the count).
    int prescale_target;
	int prescale_count;
};

/// The Timer Mode register type. See EE Users Manual page 36.
/// Writing 1 to the Equal flag or Overflow flag (bits 10 and 11) will trigger a timer unit reset.
class EeTimersUnitRegister_Mode : public SizedWordRegister, public ScopeLock
{
public:
	static constexpr Bitfield CLKS = Bitfield(0, 2);
	static constexpr Bitfield GATE = Bitfield(2, 1);
	static constexpr Bitfield GATS = Bitfield(3, 1);
	static constexpr Bitfield GATM = Bitfield(4, 2);
	static constexpr Bitfield ZRET = Bitfield(6, 1);
	static constexpr Bitfield CUE  = Bitfield(7, 1);
	static constexpr Bitfield CMPE = Bitfield(8, 1);
	static constexpr Bitfield OVFE = Bitfield(9, 1);
	static constexpr Bitfield EQUF = Bitfield(10, 1);
	static constexpr Bitfield OVFF = Bitfield(11, 1);

	EeTimersUnitRegister_Mode();

	/// Scope locked for the entire duration.
	/// When written to, caches the timer event source, and sets the write latch.
	/// Writing 1 to the EQUF or OVFF flags resets them.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Returns if CLKS and GATS are both set to H-BLNK, which is used as a special condition.
	bool is_gate_hblnk_special();

	/// Bus write latch. Signifies that the timer unit should be reset (ie: reset count with the prescale below).
	bool write_latch;

	/// Calculates unit parameters including:
	/// - Internally sets the event source this timer follows.
	/// - Returns the prescale that should be set on the count register.
	uword calculate_prescale_and_set_event();
	
	/// Holds the cached result of which event type this timer is following.
	ControllerEventType event_type;
};

