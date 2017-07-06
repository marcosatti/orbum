#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

FIFOQueue_t::FIFOQueue_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	mSize(maxByteSize),
	mFIFOQueue(maxByteSize)
{
}

void FIFOQueue_t::initialise()
{
	// Clear the FIFO queue.
	mFIFOQueue.reset();
}

bool FIFOQueue_t::readByte(const Context_t context, u8 & data)
{
	bool success = mFIFOQueue.pop(data);

#if DEBUG_LOG_FIFOQUEUE_READ_WRITE
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8 (Ok = %d), Used Size = %d, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), success, getReadAvailable(), data);
#else
		log(Debug, "%s: %s Read u8 (Ok = %d), Used Size = %d, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), success, getReadAvailable(), data);
#endif
	}
#endif

	if (!success)
		log(Debug, "FIFOQueue_t: Failed to read a byte to the FIFO queue. This **might** be ok, but you have been warned...");

	return success;
}

bool FIFOQueue_t::writeByte(const Context_t context, const u8 data)
{
	bool success = mFIFOQueue.push(data);

#if DEBUG_LOG_FIFOQUEUE_READ_WRITE
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8 (Ok = %d), Used Size = %d, Value = 0x%X.", DEBUG_CONTEXT_STRINGS[context], mMnemonic.c_str(), success, getReadAvailable(), data);
#else
		log(Debug, "%s: %s Write u8 (Ok = %d), Used Size = %d, Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), success, getReadAvailable(), data);
#endif
	}
#endif

	if (!success)
		log(Debug, "FIFOQueue_t: Failed to push a byte to the FIFO queue. This **might** be ok, but you have been warned...");

	return success;
}

bool FIFOQueue_t::read(const Context_t context, u8* buffer, const size_t length)
{
	if (mFIFOQueue.read_available() < length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (!readByte(context, buffer[i]))
			throw std::runtime_error("FIFOQueue_t::read() failed while in loop. Please debug.");
	}

	return true;
}

bool FIFOQueue_t::write(const Context_t context, const u8* buffer, const size_t length)
{
	if (mFIFOQueue.write_available() < length)
		return false;

	for (size_t i = 0; i < length; i++)
	{
		if (!writeByte(context, buffer[i]))
			throw std::runtime_error("FIFOQueue_t::read() failed while in loop. Please debug.");
	}

	return true;
}

size_t FIFOQueue_t::getReadAvailable() const
{
	return mFIFOQueue.read_available();
}

size_t FIFOQueue_t::getWriteAvailable() const
{
	return mFIFOQueue.write_available();
}

size_t FIFOQueue_t::getSize() const
{
	return mSize;
}