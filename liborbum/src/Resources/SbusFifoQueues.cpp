#include "Resources/SbusFifoQueues.hpp"
#include "Resources/SbusRegisters.hpp"

ubyte SbusFifoQueue_Sif2::read_ubyte()
{
	auto _lock = scope_lock();

	ubyte data = DmaFifoQueue::read_ubyte();

	// Check if the FIFO queue is empty.
	if (is_empty())
		sbus_f300->write_uword(sbus_f300->read_uword() | 0x04000000);
	else
		sbus_f300->write_uword(sbus_f300->read_uword() & (~0x04000000));
		
	return data;
}

void SbusFifoQueue_Sif2::write_ubyte(const ubyte data)
{
	auto _lock = scope_lock();

	DmaFifoQueue::write_ubyte(data);

	// Signal data is available.
	sbus_f300->write_uword(sbus_f300->read_uword() & (~0x04000000));
}