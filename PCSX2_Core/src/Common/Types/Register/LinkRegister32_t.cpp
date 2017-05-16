#include "Common/Types/Register/LinkRegister32_t.h"
#include "Common/Types/Register/PCRegister32_t.h"

LinkRegister32_t::LinkRegister32_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<PCRegister32_t> & pcRegister) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mPCRegister(pcRegister)
{
}

void LinkRegister32_t::setLinkAddress(const System_t context)
{
	writeWord(context, mPCRegister->readWord(context) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
}
