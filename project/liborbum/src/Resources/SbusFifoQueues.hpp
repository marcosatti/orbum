#pragma once

#include "Common/Types/ScopeLock.hpp"
#include "Common/Types/FifoQueue/SpscFifoQueue.hpp"

class SbusRegister_F300;

/*
A custom FIFO for the SIF2 DMA interface to trigger updates to the sbus_f300 register (magic values).
*/
class SbusFifoQueue_Sif2 : public SpscFifoQueue, public ScopeLock
{
public:
	SbusFifoQueue_Sif2(const size_t size);

	/*
	Trigger updates to the SBUS_F300 register (magic values).
	Scope locked for the entire duration as the F300 register is updated.
	Based upon PCSX2's "sif2.cpp".
	*/
	bool read_ubyte(ubyte & data) override;
	bool write_ubyte(const ubyte data) override;

	/*
	Reference to the SBUS_F300 register.
	*/
	SbusRegister_F300 * sbus_f300;
};