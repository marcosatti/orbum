#include "Resources/IOP/SIO2/Types/SIO2Registers_t.h"

SIO2Register_CTRL_t::SIO2Register_CTRL_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites),
	mPendingCommand(false)
{
	registerField(Fields::Reset, "Reset", 0, 1, 0);
}

void SIO2Register_CTRL_t::writeWord(const Context_t context, const u32 value)
{
	if (mPendingCommand)
		throw std::runtime_error("SIO2Register_CTRL_t already had pending command set... Oops!");

	mPendingCommand = true;
	BitfieldRegister32_t::writeWord(context, value);
}