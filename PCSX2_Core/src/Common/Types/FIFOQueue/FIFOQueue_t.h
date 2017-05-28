#pragma once

#include <queue>

#include "Common/Global/Globals.h"
#include "Common/Types/System/Context_t.h"
#include "Common/Types/Util/DebugBaseObject_t.h"

/*
Represents a FIFO queue used in, for example, the DMA transfer paths and the CDVD parameter/response FIFO's.
The minimum sized data unit that can be read/written to the queue is 8-bits.
Other sizes can be read/write, with an optional buffer to perform operations directly on.
TODO: Test performance... probably migrate to using a ring buffer.
TODO: Add in thread safety - trivial task, just put in locks on every read/write function.
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
	Read/write functions to access the FIFO queue, with subclassed functionality.
	Reads pop byte(s) from the FIFO queue, and cannot be accessed again.
	Writes push bytes(s) to the end of the FIFO queue.
	Upon reading or writing to the queue when there is no data left or it is full, a runtime error is thrown.
	The provided hword/word/dword/qword functions are wrappers around the byte functions, and should not be treated as separate interfaces (not made virtual).
	*/
	virtual u8 readByte(const Context_t context);
	virtual void writeByte(const Context_t context, const u8 data);
	u16 readHword(const Context_t context);
	void writeHword(const Context_t context, const u16 data);
	u32 readWord(const Context_t context);
	void writeWord(const Context_t context, const u32 data);
	u64 readDword(const Context_t context);
	void writeDword(const Context_t context, const u64 data);
	u128 readQword(const Context_t context);
	void writeQword(const Context_t context, const u128 data);
	
	/*
	Reads bytes to the buffer given.
	This is a wrapper around the readByte function, and should not be treated as a separate interface (not made virtual).
	*/
	void read(const Context_t context, u8 * buffer, const size_t length);

	/*
	Writes bytes from the buffer given.
	This is a wrapper around the writeByte function, and should not be treated as a separate interface (not made virtual).
	*/
	void write(const Context_t context, const u8 * buffer, const size_t length);

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
	The max number of 8-bit data elements allowed in the queue, set to the constructor parameter.
	*/
	size_t mMaxByteSize;

	/*
	The backend for the FIFO queue.
	*/
	std::queue<u8> mFIFOQueue;
};

