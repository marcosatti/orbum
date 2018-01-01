#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

class SbusRegister_F300;

/// A custom FIFO for the SIF2 DMA interface to trigger updates to the sbus_f300 register (magic values).
class SbusFifoQueue_Sif2 : public DmaFifoQueue<>, public ScopeLock
{
public:
	/// Trigger updates to the SBUS_F300 register (magic values).
	/// Scope locked for the entire duration as the F300 register is updated.
	/// Based upon PCSX2's "sif2.cpp".
	ubyte read_ubyte() override;
	void write_ubyte(const ubyte data) override;

	/// Reference to the SBUS_F300 register.
	SbusRegister_F300 * sbus_f300;
};