#pragma once

#include <cstddef>

#include <boost/lockfree/spsc_queue.hpp>

#include "Common/Types/FifoQueue/FifoQueue.hpp"

/// SPSC-backed FIFO queue.
class SpscFifoQueue : public FifoQueue
{
public:
	SpscFifoQueue(const size_t size);

	/// Initialise FIFO queue (set to empty).
	void initialise() override;

	/// Reads byte(s) from the FIFO queue (pop).
	/// Returns true on a successful read.
	bool read_ubyte(ubyte & data) override;

	/// Writes push bytes(s) to the end of the FIFO queue.
	/// Returns true on a successful writes.
	bool write_ubyte(const ubyte data) override;

	/// Returns the number of bytes remaining in the queue available for reading.
	/// Use only from a consumer thread (Boost requirement).
	size_t read_available() const override;

	/// Returns the number of bytes free in the queue available for writing.
	/// Use only from a producer thread (Boost requirement).
	size_t write_available() const override;

	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override;

private:
	/// The backend for the FIFO queue.
	boost::lockfree::spsc_queue<ubyte> fifo_queue;
};

