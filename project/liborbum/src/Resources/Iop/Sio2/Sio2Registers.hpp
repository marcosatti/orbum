#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/ByteRegister.hpp"

/// SIO2 CTRL Register.
/// RESET_DIR is a reset SIO2 or SIO flag in TX/RX direction (?). 
/// This seems like a bit of magic to me, no documentation really.
/// Looking into the bios, it changes between OR'ing 0xC or 0x1 with 0x3BC, which works with what PCSX2 says.
/// (ie: 0xC OR'd has no effect, 0x1 OR'd makes it 0x3BD.)
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

/// Data fifo port register.
/// Used as an interface by the SIO2 to transmit data.
class Sio2Register_Data : public ByteRegister
{
public:
	Sio2Register_Data();

	void initialise() override;

	/// Reads and writes to the data fifo queue.
	ubyte read_ubyte() override;
	void write_ubyte(const ubyte value) override;

	/// Reference to the data fifo queue.
	DmaFifoQueue<> * data_fifo;
};
