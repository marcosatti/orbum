#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/DebugBitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

DebugBitfieldRegister32_t::DebugBitfieldRegister32_t(const char* mnemonic) :
	DebugRegister32_t(mnemonic)
{
}

DebugBitfieldRegister32_t::~DebugBitfieldRegister32_t()
{
}

u32 DebugBitfieldRegister32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	return MathUtil::extractMaskedValue32(UW, startPosition, bitLength);
}

void DebugBitfieldRegister32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	UW = MathUtil::insertMaskedValue32(UW, value, startPosition, bitLength);
}

void DebugBitfieldRegister32_t::writeWordU(u32 value)
{
	Register32_t::writeWordU(value);
	BitfieldMap32_t::syncMapFromMemory();
}

void DebugBitfieldRegister32_t::writeWordS(s32 value)
{
	writeWordU(static_cast<u32>(value));
}
