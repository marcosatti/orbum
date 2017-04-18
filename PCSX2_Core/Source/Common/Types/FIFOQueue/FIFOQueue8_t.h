#pragma once

#include <queue>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/DebugBaseObject_t.h"

/*
Represents a FIFO queue used in (for example) the CDVD parameter/response FIFO's.
The minimum sized data unit that can be read/written to the queue is 8-bits.
TODO: test perf (use std::queue or own?), add in thread safety.
*/
class FIFOQueue8_t : public DebugBaseObject_t
{
public:
	FIFOQueue8_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize);
	virtual ~FIFOQueue8_t() = default;

	/*
	Initalise FIFO queue (set to empty).
	*/
	virtual void initalise();

	/*
	Read 8-bits of data out of the FIFO queue, and removes it.
	*/
	virtual u8 readByte(const System_t context);

	/*
	Writes 8-bits of data to the FIFO queue.
	*/
	virtual void writeByte(const System_t context, const u8 data);

	/*
	Gets the current number of 8-bit data elements in the queue.
	*/
	size_t getCurrentSize() const;

	/*
	Gets the max allowable number of 8-bit data elements this FIFO queue can hold.
	*/
	size_t getMaxSize() const;

private:
	/*
	The max number of 8-bit data elements allowed in the queue, set to the constructor paramter.
	*/
	size_t mMaxByteSize;

	/*
	The backend for the FIFO queue.
	*/
	std::queue<u8> mFIFOQueue;
};

