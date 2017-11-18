#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/Register/SizedByteRegister.hpp"
#include "Common/Types/FifoQueue/SpscFifoQueue.hpp"

/// CDVD Register N/S_COMMAND.
/// Sets an internal variable to true if there is a pending command to be processed.
/// Needs to be scope locked by the CDVD controller.
class CdvdRegister_Ns_Command : public SizedByteRegister, public ScopeLock
{
public:
	CdvdRegister_Ns_Command();

	/// Sets the write latch, indicates a pending command to be processed by controller.
	/// TODO: currently throws error when it has already been set - what is meant to happen?
	void byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value) override;

	/// Write latch, needs to be cleared after processing a command by the controller.
	bool write_latch;
};

/// CDVD register / FIFO queue hybrid "register".
/// Read: SizedByteRegister: {N/S}_READY.
/// Write: SpscFifoQueue: {N/S}_DATA_IN.
/// CdvdFifoQueue_Ns_Data_Out (see CdvdFifoQueues.hpp) uses the internal members directly.
class CdvdRegister_Ns_Rdy_Din : public ByteRegister
{
public:
	CdvdRegister_Ns_Rdy_Din(const size_t size);

	void initialise() override;

	ubyte read_ubyte() override;
	void write_ubyte(const ubyte value) override;

	usize byte_bus_map_size() const override;

	/// Resources.
	SizedByteRegister ready;
	SpscFifoQueue data_in;
};