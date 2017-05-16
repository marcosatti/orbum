#include "Common/Global/Globals.h"

#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

SBUSFIFOQueue_SIF2_t::SBUSFIFOQueue_SIF2_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxSize, const std::shared_ptr<SBUSRegister_F300_t> & sbusF300) :
	FIFOQueue_t(mnemonic, debugReads, debugWrites, maxSize),
	mSBUSF300(sbusF300)
{
}

u8 SBUSFIFOQueue_SIF2_t::readByte(const System_t context)
{
	// Must read from the FIFO first - SBUS update calls FIFOQueue::getCurrentSize().
	u32 temp = FIFOQueue_t::readByte(context);
	handleSBUSUpdate(context);
	return temp;
}

void SBUSFIFOQueue_SIF2_t::writeByte(const System_t context, const u8 data)
{
	FIFOQueue_t::writeByte(context, data);
	handleSBUSUpdate(context);
}

void SBUSFIFOQueue_SIF2_t::handleSBUSUpdate(const System_t context) const
{
	if (getCurrentSize() == 0)
		mSBUSF300->writeWord(context, mSBUSF300->readWord(context) | 0x04000000);
	else
		mSBUSF300->writeWord(context, mSBUSF300->readWord(context) & (~0x04000000));
}
