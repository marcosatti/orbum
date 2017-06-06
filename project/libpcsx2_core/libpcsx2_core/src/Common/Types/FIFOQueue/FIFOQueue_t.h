#pragma once

#include <boost/lockfree/spsc_queue.hpp>

#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"
#include "Common/Types/Util/DebugBaseObject_t.h"

/*
Represents a FIFO queue used in, for example, the DMA transfer paths and the CDVD parameter/response FIFO's.
The minimum sized data unit that can be read/written to the queue is a byte.
Other sizes can be read/write, with an optional buffer to perform operations directly on.
Uses a thread-safe ring buffer (boost::lock_free::spsc_queue) as the backend, which allows only one producer & one consumer at any one time.
*/
class FIFOQueue_t : public DebugBaseObject_t
{
public:
	FIFOQueue_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize);
	virtual ~FIFOQueue_t() = default;

	/*
	Initialise FIFO queue (set to empty).
	*/
	virtual void initialise();

	/*
	Reads byte(s) from the FIFO queue (pop).
	Returns true on a successful read.
	*/
	virtual bool readByte(const Context_t context, u8 & data);

	/*
	Writes push bytes(s) to the end of the FIFO queue.
	Returns true on a successful writes.
	*/
	virtual bool writeByte(const Context_t context, const u8 data);
	
	/*
	Reads bytes to the buffer given.
	This is a wrapper around the readByte function, and should not be treated as a separate interface (not made virtual).
	Before reading from the queue, first checks that there are 'length' elements available. 
	Returns true if this check passed and bytes were read into 'buffer', false otherwise.
	*/
	bool read(const Context_t context, u8 * buffer, const size_t length);

	/*
	Writes bytes from the buffer given.
	This is a wrapper around the writeByte function, and should not be treated as a separate interface (not made virtual).
	Before writing to the queue, first checks that there are 'length' spaces available. 
	Returns true if this check passed and bytes were written from 'buffer', false otherwise.
	*/
	bool write(const Context_t context, const u8 * buffer, const size_t length);

	/*
	Returns the number of bytes remaining in the queue available for reading.
	Use only from a consumer thread (Boost requirement).
	*/
	size_t getReadAvailable() const;

	/*
	Returns the number of bytes free in the queue available for writing.
	Use only from a producer thread (Boost requirement).
	*/
	size_t getWriteAvailable() const;

	/*
	Returns the maximum amount of data this queue can hold, set at construction.
	*/
	size_t getSize() const;

private:
	/*
	Maximum size of the FIFO queue.
	*/
	size_t mSize;

	/*
	The backend for the FIFO queue.
	Note: The docs might be a little confusing, in that while it says only one producer and one consumer, that is only when it is simultaneously accessed.
	      This means multiple threads can produce & consume, but there can only be one producer & consumer of those threads active at a time.
	*/
	boost::lockfree::spsc_queue<u8> mFIFOQueue;
};

