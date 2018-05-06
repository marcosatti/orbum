#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// SIO2 CTRL Register.
/// Usual value is 0x3BC (initial BIOS value) OR'd with either 0xC (no effect) or 0x1.
/// Basically no documentation from PCSX2 or by RE'ing the BIOS, however,
/// the BIOS always reuses the previous value when writing to it. This suggests
/// that bit 0 (aka DIR_RESET below) is a write only field that toggles the 
/// internal direction of the SIO2, and is always zero on reads. Doesn't explain why
/// 0xC is OR'd instead of zero though... maybe 0xC is a write only field too.
/// TODO: would love to hardware test this theory.
class Sio2Register_Ctrl : public SizedWordRegister, public ScopeLock
{
public:
	/// SIO2 transfer direction to/from SIO0.
	enum class Direction
	{
		TX, 
		RX,
	};

	static constexpr Bitfield DIR_RESET = Bitfield(0, 1); // Resets the SIO if 0, and sets in TX direction, RX otherwise. Writes only.

	Sio2Register_Ctrl();

	/// Upon writes, sets the current direction based on DIR_RESET then clears that bit.
	void write_uword(const uword value);

	/// Scope locked for entire duration.
	/// Sets the write latch on bus write, throws error when it has already been set.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;

	/// Current transfer direction, set upon writes. Defaults to TX.
	Direction direction;

	/// Current transfer status to/from SIO0.
	bool started;
	size_t transfer_port;
	size_t transfer_count;

	/// Write latch, set to true on bus write, cleared by the controller.
	bool write_latch;
};
