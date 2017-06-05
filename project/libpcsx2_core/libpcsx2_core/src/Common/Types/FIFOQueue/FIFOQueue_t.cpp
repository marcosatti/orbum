#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

FIFOQueue_t::FIFOQueue_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	mMaxByteSize(maxByteSize)
{
}

void FIFOQueue_t::initialise()
{
	// Reset (clear) FIFO queue.
	std::queue<u8>().swap(mFIFOQueue);
}

u8 FIFOQueue_t::readByte(const Context_t context)
{
	if (getCurrentSize() == 0)
		throw std::runtime_error("FIFO Queue empty, but tried to read. Please fix.");

	auto temp = mFIFOQueue.front();
	mFIFOQueue.pop();

#if DEBUG_LOG_FIFOQUEUE_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8, Size = %d, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), mFIFOQueue.size(), temp);
#else
		log(Debug, "%s: %s Read u8, Size = %d, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), temp);
#endif
	}
#endif

	return temp;
}

void FIFOQueue_t::writeByte(const Context_t context, const u8 data)
{
	if (getCurrentSize() == mMaxByteSize)
		throw std::runtime_error("FIFO Queue full, but tried to write. Please fix.");

	mFIFOQueue.push(data);

#if DEBUG_LOG_FIFOQUEUE_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8, Size = %d, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), mFIFOQueue.size(), data);
#else
		log(Debug, "%s: %s Write u8, Size = %d, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), mFIFOQueue.size(), data);
#endif
	}
#endif
}

u16 FIFOQueue_t::readHword(const Context_t context)
{
	u16 buffer;
	read(context, reinterpret_cast<u8*>(&buffer), Constants::NUMBER_BYTES_IN_HWORD);
	return buffer;
}

void FIFOQueue_t::writeHword(const Context_t context, const u16 data)
{
	write(context, reinterpret_cast<const u8*>(&data), Constants::NUMBER_BYTES_IN_HWORD);
}

u32 FIFOQueue_t::readWord(const Context_t context)
{
	u32 buffer;
	read(context, reinterpret_cast<u8*>(&buffer), Constants::NUMBER_BYTES_IN_WORD);
	return buffer;
}

void FIFOQueue_t::writeWord(const Context_t context, const u32 data)
{
	write(context, reinterpret_cast<const u8*>(&data), Constants::NUMBER_BYTES_IN_WORD);
}

u64 FIFOQueue_t::readDword(const Context_t context)
{
	u64 buffer;
	read(context, reinterpret_cast<u8*>(&buffer), Constants::NUMBER_BYTES_IN_DWORD);
	return buffer;
}

void FIFOQueue_t::writeDword(const Context_t context, const u64 data)
{
	write(context, reinterpret_cast<const u8*>(&data), Constants::NUMBER_BYTES_IN_DWORD);
}

u128 FIFOQueue_t::readQword(const Context_t context)
{
	u128 buffer;
	read(context, reinterpret_cast<u8*>(&buffer), Constants::NUMBER_BYTES_IN_QWORD);
	return buffer;
}

void FIFOQueue_t::writeQword(const Context_t context, const u128 data)
{
	write(context, reinterpret_cast<const u8*>(&data), Constants::NUMBER_BYTES_IN_QWORD);
}

void FIFOQueue_t::read(const Context_t context, u8* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		buffer[i] = readByte(context);
}

void FIFOQueue_t::write(const Context_t context, const u8* buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		writeByte(context, buffer[i]);
}

size_t FIFOQueue_t::getCurrentSize() const
{
	return mFIFOQueue.size();
}

size_t FIFOQueue_t::getMaxSize() const
{
	return mMaxByteSize;
}