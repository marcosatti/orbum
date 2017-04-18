#include "stdafx.h"

#include "Common/Types/FIFOQueue/FIFOQueue8_t.h"

FIFOQueue8_t::FIFOQueue8_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	mMaxByteSize(maxByteSize)
{
}

void FIFOQueue8_t::initalise()
{
	// Reset (clear) FIFO queue.
	std::queue<u8>().swap(mFIFOQueue);
}

u8 FIFOQueue8_t::readByte(const System_t context)
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();

#if defined(DEBUG_LOG_FIFOQUEUE_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8, Size = %d, Value = 0x%08X.", getSystemStr(context), mMnemonic.c_str(), mFIFOQueue.size(), temp);
#else
		log(Debug, "%s: %s Read u8, Size = %d, Value = %d.", getSystemStr(context), mMnemonic.c_str(), mFIFOQueue.size(), temp);
#endif
	}
#endif

	return temp;
}

void FIFOQueue8_t::writeByte(const System_t context, const u8 data)
{
	if ((getCurrentSize() + 1) > mMaxByteSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);

#if defined(DEBUG_LOG_FIFOQUEUE_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8, Size = %d, Value = 0x%08X.", getSystemStr(context), mMnemonic.c_str(), mFIFOQueue.size(), data);
#else
		log(Debug, "%s: %s Write u8 @ 0x%08X, Value = %d.", getSystemStr(context), mMnemonic.c_str(), mFIFOQueue.size(), data);
#endif
	}
#endif
}

size_t FIFOQueue8_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue8_t::getMaxSize() const
{
	return mMaxByteSize;
}