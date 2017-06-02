#include "Common/Types/Register/LinkRegister128_t.h"
#include "Common/Types/Register/PCRegister32_t.h"

LinkRegister128_t::LinkRegister128_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<PCRegister32_t> & pcRegister) :
	Register128_t(mnemonic, debugReads, debugWrites),
	mPCRegister(pcRegister)
{
}

void LinkRegister128_t::setLinkAddress(const Context_t context)
{
	writeDword(context, 0, mPCRegister->readWord(context) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
}
