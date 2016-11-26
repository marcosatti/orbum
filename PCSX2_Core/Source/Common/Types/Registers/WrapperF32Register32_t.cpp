#include "stdafx.h"

#include "Common/Types/Registers/WrapperF32Register32_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

WrapperF32Register32_t::WrapperF32Register32_t(const std::shared_ptr<FPRegister32_t>& fpRegister32) :
	mFPRegister32(fpRegister32)
{
}

WrapperF32Register32_t::WrapperF32Register32_t(const char* mnemonic, const std::shared_ptr<FPRegister32_t>& fpRegister32) :
	Register32_t(mnemonic),
	mFPRegister32(fpRegister32)
{
}

WrapperF32Register32_t::~WrapperF32Register32_t()
{
}

u8 WrapperF32Register32_t::readByteU(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeByteU(u32 arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

s8 WrapperF32Register32_t::readByteS(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeByteS(u32 arrayIndex, s8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u16 WrapperF32Register32_t::readHwordU(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeHwordU(u32 arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

s16 WrapperF32Register32_t::readHwordS(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeHwordS(u32 arrayIndex, s16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u32 WrapperF32Register32_t::readWordU()
{
	return mFPRegister32->readWordU();
}

void WrapperF32Register32_t::writeWordU(u32 value)
{
	mFPRegister32->writeWordU(value);
}

s32 WrapperF32Register32_t::readWordS()
{
	return mFPRegister32->readWordS();
}

void WrapperF32Register32_t::writeWordS(s32 value)
{
	mFPRegister32->writeWordS(value);
}
