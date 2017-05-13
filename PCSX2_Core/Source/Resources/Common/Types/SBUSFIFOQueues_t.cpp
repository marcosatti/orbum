#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

SBUSFIFOQueue_SIF2_t::SBUSFIFOQueue_SIF2_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxSize, const std::shared_ptr<SBUSRegister_F300_t> & sbusF300) :
	FIFOQueue_t(mnemonic, debugReads, debugWrites, maxSize),
	mSBUSF300(sbusF300)
{
}

u32 SBUSFIFOQueue_SIF2_t::readWord(const System_t context)
{
	u32 temp = FIFOQueue_t::readWord(context);
	handleSBUSUpdate(context);
	return temp;
}

u128 SBUSFIFOQueue_SIF2_t::readQword(const System_t context)
{
	u128 temp = FIFOQueue_t::readQword(context);
	handleSBUSUpdate(context);
	return temp;
}

void SBUSFIFOQueue_SIF2_t::writeWord(const System_t context, const u32 data)
{
	FIFOQueue_t::writeWord(context, data);
	handleSBUSUpdate(context);
}

void SBUSFIFOQueue_SIF2_t::writeQword(const System_t context, const u128 data)
{
	FIFOQueue_t::writeQword(context, data);
	handleSBUSUpdate(context);
}

void SBUSFIFOQueue_SIF2_t::handleSBUSUpdate(const System_t context) const
{
	if (getCurrentSize() == 0)
		mSBUSF300->writeWord(context, mSBUSF300->readWord(context) | 0x04000000);
	else
		mSBUSF300->writeWord(context, mSBUSF300->readWord(context) & (~0x04000000));
}
