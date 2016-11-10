#include "stdafx.h"

#include "Common/Types/Registers/LinkRegister32_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"

LinkRegister32_t::LinkRegister32_t(const std::shared_ptr<PCRegister32_t> & pcRegister) :
	mPCRegister(pcRegister)
{
}

void LinkRegister32_t::setLinkAddress()
{
	writeWordU(mPCRegister->getPCValue() + 8);
}
