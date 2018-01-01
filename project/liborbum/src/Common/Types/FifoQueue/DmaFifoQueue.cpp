#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

void DmaFifoQueue::initialise()
{
	// Clear the FIFO queue.
	fifo_queue.reset();
}

bool DmaFifoQueue::read_ubyte(ubyte & data)
{
	return fifo_queue.try_pop(data);
}

bool DmaFifoQueue::write_ubyte(const ubyte data)
{
	return fifo_queue.try_push(data);
}

bool DmaFifoQueue::is_empty() const
{
	return fifo_queue.is_empty();
}

bool DmaFifoQueue::is_full() const
{
	return fifo_queue.is_full();
}
