#pragma once

#include <queue>

#include "Common/Global/Globals.h"
#include "Common/Types/System_t.h"
#include "Common/Types/DebugBaseObject_t.h"

/*
Represents a FIFO queue used in (for example) the EE/IOP DMAC channels.
The minimum sized data unit that can be read/written to the queue is 32-bit, however 128-bit read/writes are also allowed.
TODO: test perf (use std::queue or own?), add in thread safety.
*/
class FIFOQueue32_t : public DebugBaseObject_t
{
public:
	FIFOQueue32_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize);
	virtual ~FIFOQueue32_t() = default;

	/*
	Read 32-bits of data out of the FIFO queue, and removes it.
	*/
	virtual u32 readWord(const System_t context);

	/*
	Read 128-bits of data out of the FIFO queue, and remove them (uses 4 x 32-bit reads stored in a u128).
	*/
	virtual u128 readQword(const System_t context);

	/*
	Writes 32-bits of data to the FIFO queue.
	*/
	virtual void writeWord(const System_t context, const u32 data);

	/*
	Write 128-bits of data to the FIFO queue (splits the u128 into 4 x 32-bit).
	*/
	virtual void writeQword(const System_t context, const u128 data);

	/*
	Gets the current number of 32-bit data elements in the queue.
	*/
	size_t getCurrentSize() const;

	/*
	Gets the max allowable number of 32-bit data elements this FIFO queue can hold.
	*/
	size_t getMaxSize() const;

private:
	/*
	The max number of 32-bit data elements allowed in the queue, set to the constructor paramter.
	*/
	size_t mMaxByteSize;

	/*
	The backend for the FIFO queue.
	*/
	std::queue<u32> mFIFOQueue;
};

