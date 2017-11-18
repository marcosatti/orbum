#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// SIO2 CTRL Register.
///
/// TODO: notes so far:
/// Bit 0 is a reset SIO2 or SIO flag in TX/RX direction (?). Cleared once reset complete???
/// PCSX2 probably not proper - doesn't seem right that things like this exist: "sio2.ctrl &= ~1;"
/// Fuck it, its magic.
class Sio2Register_Ctrl : public SizedWordRegister, public ScopeLock
{
public:
	static constexpr Bitfield RESET_DIR = Bitfield(0, 1);

	Sio2Register_Ctrl();

	/// Scope locked for entire duration.
	/// Sets the write latch on bus write, throws error when it has already been set.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Write latch.
	/// Set to true on write, cleared by the system logic when the command has been processed.
	bool write_latch;
};
