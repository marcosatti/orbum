#include "stdafx.h"

#include "Common/Types/Register/PairRegister16_t.h"

PairRegister16_t::PairRegister16_t(const char* mnemonic, bool debugReads, bool debugWrites, const std::shared_ptr<Register16_t>& highRegister16):
	Register16_t(mnemonic, debugReads, debugWrites),
	mHighRegister16(highRegister16)
{
}

u32 PairRegister16_t::readPairWord(const System_t context)
{
	return (mHighRegister16->readHword(context) << 16) | readHword(context);
}

void PairRegister16_t::writePairWord(const System_t context, u32 value)
{
	mHighRegister16->writeHword(context, static_cast<u16>(value >> 16));
	writeHword(context, static_cast<u16>(value));
}