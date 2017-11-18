#include "Resources/SbusFifoQueues.hpp"
#include "Resources/SbusRegisters.hpp"

SbusFifoQueue_Sif2::SbusFifoQueue_Sif2(const size_t size) :
	SpscFifoQueue(size)
{
}

bool SbusFifoQueue_Sif2::read_ubyte(ubyte & data)
{
	auto _lock = scope_lock();

	if (SpscFifoQueue::read_ubyte(data))
	{
		// Check if the FIFO queue is empty.
		if (read_available() == 0)
			sbus_f300->write_uword(sbus_f300->read_uword() | 0x04000000);
		else
			sbus_f300->write_uword(sbus_f300->read_uword() & (~0x04000000));
		
		return true;
	}

	return false;
}

bool SbusFifoQueue_Sif2::write_ubyte(const ubyte data)
{
	auto _lock = scope_lock();

	if (SpscFifoQueue::write_ubyte(data))
	{
		// We are writing data - there is no need to check for data available == 0.
		sbus_f300->write_uword(sbus_f300->read_uword() & (~0x04000000));
		return true;
	}

	return false;
}