#include "Resources/Cdvd/CdvdFifoQueues.hpp"
#include "Resources/Cdvd/CdvdRegisters.hpp"

CdvdFifoQueue_Ns_Data_Out::CdvdFifoQueue_Ns_Data_Out(const size_t size) :
	SpscFifoQueue(size)
{
}

bool CdvdFifoQueue_Ns_Data_Out::read_ubyte(ubyte & data)
{
	auto _lock = scope_lock();

	bool success = SpscFifoQueue::read_ubyte(data);

	// Check if FIFO is empty.
	if (read_available() == 0)
		ns_rdy_din->ready.write_ubyte(ns_rdy_din->ready.read_ubyte() | 0x40);

	return success;
}

bool CdvdFifoQueue_Ns_Data_Out::write_ubyte(const ubyte data)
{
	auto _lock = scope_lock();
	
	bool success = SpscFifoQueue::write_ubyte(data);

	// Check if FIFO is empty (write could fail).
	if (read_available() > 0)
		ns_rdy_din->ready.write_ubyte(ns_rdy_din->ready.read_ubyte() & (~0x40));

	return success;
}
