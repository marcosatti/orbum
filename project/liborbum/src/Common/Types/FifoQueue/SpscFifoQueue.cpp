#include "Common/Types/FifoQueue/SpscFifoQueue.hpp"

SpscFifoQueue::SpscFifoQueue(const size_t size) :
	fifo_queue(size)
{
}

void SpscFifoQueue::initialise()
{
	// Clear the FIFO queue.
	fifo_queue.reset();
}

bool SpscFifoQueue::read_ubyte(ubyte & data)
{
	return fifo_queue.pop(data);
}

bool SpscFifoQueue::write_ubyte(const ubyte data)
{
	return fifo_queue.push(data);
}

size_t SpscFifoQueue::read_available() const
{
	return fifo_queue.read_available();
}

size_t SpscFifoQueue::write_available() const
{
	return fifo_queue.write_available();
}

usize SpscFifoQueue::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_QWORD);
}