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

u8 WrapperF32Register32_t::readByte(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeByte(u32 arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u16 WrapperF32Register32_t::readHword(u32 arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeHword(u32 arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u32 WrapperF32Register32_t::readWord()
{
	return mFPRegister32->readWord();
}

void WrapperF32Register32_t::writeWord(u32 value)
{
	mFPRegister32->writeWord(value);
}