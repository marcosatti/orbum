#pragma once

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/ByteRegister.hpp"
#include "Common/Types/Register/SizedByteRegister.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

/// CDVD register / FIFO queue hybrid "register".
/// Read: SizedByteRegister: {N/S}_READY.
/// Write: DmaFifoQueue: {N/S}_DATA_IN.
/// CdvdFifoQueue_Ns_Data_Out (see CdvdFifoQueues.hpp) uses the internal members directly.
class CdvdRegister_Ns_Rdy_Din : public ByteRegister
{
public:
	static constexpr Bitfield READY_EMPTY = Bitfield(6, 1); // FIFO empty flag (from PCSX2 / bios).
	static constexpr Bitfield READY_BUSY  = Bitfield(7, 1); // Busy / command pending flag (from bios).

	void initialise() override;

	ubyte read_ubyte() override;
	void write_ubyte(const ubyte value) override;

	/// Resources.
	SizedByteRegister ready;
	DmaFifoQueue<> data_in;
};

/// CDVD N/S command FIFO register.
class CdvdRegister_Ns_Command : public SizedByteRegister
{
public:
	CdvdRegister_Ns_Command();

	/// Sets the write latch and the ns_rdy_din->ready.busy flag when this is written to.
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;
		
	/// Bus write latch, used for checking if a command is pending.
	/// TODO: probably don't need this (can get status from ready register), but just do it to be safe.
	bool write_latch;

	/// Reference to the ready register.
	CdvdRegister_Ns_Rdy_Din * ns_rdy_din;
};