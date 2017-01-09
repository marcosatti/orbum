#include "stdafx.h"

#include "Common/Types/Registers/MIPS/LinkRegister32_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

LinkRegister32_t::LinkRegister32_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister32_t::setLinkAddress()
{
	writeWord(Context_t::RAW, mPCRegister->readWord(Context_t::RAW) + 8);
}