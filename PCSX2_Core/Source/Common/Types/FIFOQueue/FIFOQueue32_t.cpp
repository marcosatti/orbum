#include "stdafx.h"

#include "Common/Types/FIFOQueue/FIFOQueue32_t.h"

FIFOQueue32_t::FIFOQueue32_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	mMaxByteSize(maxByteSize)
{
}

void FIFOQueue32_t::initalise()
{
	// Reset (clear) FIFO queue.
	std::queue<u32>().swap(mFIFOQueue);
}

u32 FIFOQueue32_t::readWord(const System_t context)
{
	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();

#if defined(DEBUG_LOG_FIFOQUEUE_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32, Size = %d, Value = 0x%08X.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), temp);
#else
		log(Debug, "%s: %s Read u32, Size = %d, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), temp);
#endif
	}
#endif

	return temp;
}

u128 FIFOQueue32_t::readQword(const System_t context)
{
	u128 data;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		data.UW[i] = readWord(context);
	
	return data;
}

void FIFOQueue32_t::writeWord(const System_t context, const u32 data)
{
	if ((getCurrentSize() + 1) > mMaxByteSize)
		throw std::runtime_error("FIFO Queue overloaded. Please fix.");

	mFIFOQueue.push(data);

#if defined(DEBUG_LOG_FIFOQUEUE_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32, Size = %d, Value = 0x%08X.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), data);
#else
		log(Debug, "%s: %s Write u32 @ 0x%08X, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), data);
#endif
	}
#endif
}

void FIFOQueue32_t::writeQword(const System_t context, const u128 data)
{
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
		writeWord(context, data.UW[i]); 
}

void FIFOQueue32_t::read(const System_t context, u32* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		buffer[i] = readWord(context);
}

void FIFOQueue32_t::write(const System_t context, const u32* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		writeWord(context, buffer[i]);
}

size_t FIFOQueue32_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue32_t::getMaxSize() const
{
	return mMaxByteSize;
}