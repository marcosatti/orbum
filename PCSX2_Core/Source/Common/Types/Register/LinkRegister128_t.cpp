#include "stdafx.h"

#include "Common/Types/Register/LinkRegister128_t.h"
#include "Common/Types/Register/PCRegister32_t.h"

LinkRegister128_t::LinkRegister128_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister128_t::setLinkAddress(const System_t context)
{
	writeDword(context, 0, mPCRegister->readWord(context) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
}
