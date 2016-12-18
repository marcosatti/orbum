#pragma once

#include <queue>

#include "Common/Global/Globals.h"

/*
Represents a FIFO queue used in (for example) the EE/IOP DMAC channels.
User is able to read or write 128-bit data to the queue.
TODO: test perf (use std::queue or own?), add in thread safety.
*/
class FIFOQueue_t
{
public:
	explicit FIFOQueue_t(const size_t & maxSize);
	explicit FIFOQueue_t(const char * mnemonic, const size_t & maxSize);
	~FIFOQueue_t();

	/*
	Read 128-bits of data out of the FIFO queue, and removes it.
	*/
	u128 read();

	/*
	Writes 128-bits of data to the FIFO queue.
	*/
	void write(const u128 & data);

	/*
	Gets the current number of 128-bit data elements in the queue.
	*/
	size_t getCurrentSize() const;

	/*
	Gets the max allowable number of 128-bit data elements this FIFO queue can hold.
	*/
	size_t getMaxSize() const;

	/*
	Gets the mnemonic of this register. Used for debug/logging.
	*/
	const char * getMnemonic() const;

private:
	/*
	The mnemonic.
	*/
	const std::string mMnemonic;

	/*
	The max number of 128-bit data elements allowed in the queue, set to the constructor paramter.
	*/
	size_t mMaxSize;

	/*
	The backend for the FIFO queue.
	*/
	std::queue<u128> mFIFOQueue;
};

