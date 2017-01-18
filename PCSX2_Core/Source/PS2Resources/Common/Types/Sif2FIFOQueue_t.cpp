#include "stdafx.h"

#include "Common/Types/Registers/Register32_t.h"

#include "PS2Resources/Common/Types/Sif2FIFOQueue_t.h"

Sif2FIFOQueue_t::Sif2FIFOQueue_t(const size_t& maxSize, std::shared_ptr<Register32_t> & sbusF300) :
	FIFOQueue_t(maxSize),
	mSbusF300(sbusF300)
{
}

Sif2FIFOQueue_t::Sif2FIFOQueue_t(const char* mnemonic, const size_t& maxSize, std::shared_ptr<Register32_t> & sbusF300) :
	FIFOQueue_t(mnemonic, maxSize),
	mSbusF300(sbusF300)
{
}

u32 Sif2FIFOQueue_t::readWord(const Context_t& context)
{
	u32 temp = FIFOQueue_t::readWord(context);
	handleSBUSUpdate();
	return temp;
}

u128 Sif2FIFOQueue_t::readQword(const Context_t& context)
{
	u128 temp = FIFOQueue_t::readQword(context);
	handleSBUSUpdate();
	return temp;
}

void Sif2FIFOQueue_t::writeWord(const Context_t& context, const u32& data)
{
	FIFOQueue_t::writeWord(context, data);
	handleSBUSUpdate();
}

void Sif2FIFOQueue_t::writeQword(const Context_t& context, const u128& data)
{
	FIFOQueue_t::writeQword(context, data);
	handleSBUSUpdate();
}

void Sif2FIFOQueue_t::handleSBUSUpdate() const
{
	if (getCurrentSize() == 0)
		mSbusF300->writeWord(Context_t::RAW, mSbusF300->readWord(Context_t::RAW) | 0x04000000);
	else
		mSbusF300->writeWord(Context_t::RAW, mSbusF300->readWord(Context_t::RAW) & (~0x04000000));
}
