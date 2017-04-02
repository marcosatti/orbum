#include "stdafx.h"

#include "Common/Types/Registers/Wrapper/WrapperF32Register32_t.h"
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

u8 WrapperF32Register32_t::readByte(const System_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u16 WrapperF32Register32_t::readHword(const System_t context, size_t arrayIndex)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

void WrapperF32Register32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	throw std::runtime_error("Only Word R/W wrapper calls to FPRegister32_t are allowed.");
}

u32 WrapperF32Register32_t::readWord(const System_t context)
{
	return mFPRegister32->readWord(context);
}

void WrapperF32Register32_t::writeWord(const System_t context, u32 value)
{
	mFPRegister32->writeWord(context, value);
}

void WrapperF32Register32_t::initalise()
{
	mFPRegister32->initalise();
}
