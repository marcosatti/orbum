#pragma once

#include <cstddef>
#include <stdexcept>

#include <Queues.hpp>

#include "Common/Types/FifoQueue/FifoQueue.hpp"

/// SPSC-backed DMA FIFO queue.
template <size_t Size = 1024>
class DmaFifoQueue : public FifoQueue
{
public:
    using QueueTy = SpscQueue<ubyte, Size>;

    /// Initialise FIFO queue (set to empty).
    void initialise() override
    {
        fifo_queue.reset();
    }

    /// Reads byte(s) from the FIFO queue (pop).
    ubyte read_ubyte() override
    {
        ubyte data;
        if (!fifo_queue.try_pop(data))
            throw std::runtime_error("Could not pop from DMA fifo queue.");
        return data;
    }

    /// Writes push bytes(s) to the end of the FIFO queue.
    void write_ubyte(const ubyte data) override
    {
        if (!fifo_queue.try_push(data))
            throw std::runtime_error("Could not push to DMA fifo queue.");
    }

    /// Returns if there are at least the specified number of bytes
    /// remaining in the queue available for reading.
    /// Use only from a consumer thread (Boost requirement).
    bool has_read_available(const size_t n_bytes) const override
    {
        return fifo_queue.has_read_available(n_bytes);
    }

    /// Returns if there are at least the specified number of bytes
    /// available in the queue available for writing.
    /// Use only from a producer thread (Boost requirement).
    bool has_write_available(const size_t n_bytes) const override
    {
        return fifo_queue.has_write_available(n_bytes);
    }

    template<class Archive>
    void serialize(Archive & archive)
    {
        archive(
            CEREAL_NVP(fifo_queue)
        );
    }

private:
    /// The backend for the FIFO queue.
    QueueTy fifo_queue;
};
