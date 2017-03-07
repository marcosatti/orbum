#include "stdafx.h"

#include "Common/Types/Registers/MIPS/LinkRegister128_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

LinkRegister128_t::LinkRegister128_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister128_t::setLinkAddress()
{
	writeDword(RAW, 0, mPCRegister->readWord(RAW) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
}
