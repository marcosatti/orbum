#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/Common/Types/SBUSFIFOQueues_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"

SBUSFIFOQueue_SIF2_t::SBUSFIFOQueue_SIF2_t(const size_t& maxSize, const std::shared_ptr<SBUSRegister_F300_t> & sbusF300) :
	FIFOQueue32_t("FIFO: SIF2", maxSize),
	mSBUSF300(sbusF300)
{
}

u32 SBUSFIFOQueue_SIF2_t::readWord(const Context_t context)
{
	u32 temp = FIFOQueue32_t::readWord(context);
	handleSBUSUpdate();
	return temp;
}

u128 SBUSFIFOQueue_SIF2_t::readQword(const Context_t context)
{
	u128 temp = FIFOQueue32_t::readQword(context);
	handleSBUSUpdate();
	return temp;
}

void SBUSFIFOQueue_SIF2_t::writeWord(const Context_t context, const u32 data)
{
	FIFOQueue32_t::writeWord(context, data);
	handleSBUSUpdate();
}

void SBUSFIFOQueue_SIF2_t::writeQword(const Context_t context, const u128 data)
{
	FIFOQueue32_t::writeQword(context, data);
	handleSBUSUpdate();
}

void SBUSFIFOQueue_SIF2_t::handleSBUSUpdate() const
{
	if (getCurrentSize() == 0)
		mSBUSF300->writeWord(RAW, mSBUSF300->readWord(RAW) | 0x04000000);
	else
		mSBUSF300->writeWord(RAW, mSBUSF300->readWord(RAW) & (~0x04000000));
}
