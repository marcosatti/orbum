#include "Common/Global/Globals.h"

#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

SBUSFIFOQueue_SIF2_t::SBUSFIFOQueue_SIF2_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxSize, const std::shared_ptr<SBUSRegister_F300_t> & sbusF300) :
	FIFOQueue_t(mnemonic, debugReads, debugWrites, maxSize),
	mSBUSF300(sbusF300)
{
}

bool SBUSFIFOQueue_SIF2_t::readByte(const Context_t context, u8 & data)
{
	if (FIFOQueue_t::readByte(context, data))
	{
		// Check if the FIFO queue is empty.
		if (getReadAvailable() == 0)
			mSBUSF300->writeWord(context, mSBUSF300->readWord(context) | 0x04000000);
		else
			mSBUSF300->writeWord(context, mSBUSF300->readWord(context) & (~0x04000000));
		
		return true;
	}

	return false;
}

bool SBUSFIFOQueue_SIF2_t::writeByte(const Context_t context, const u8 data)
{
	if (FIFOQueue_t::writeByte(context, data))
	{
		// We are writing data - there is no need to check for data available == 0.
		mSBUSF300->writeWord(context, mSBUSF300->readWord(context) & (~0x04000000));
		return true;
	}

	return false;
}