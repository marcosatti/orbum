#include "stdafx.h"

#include "Resources/CDVD/Types/CDVDRegisters_t.h"

CDVDRegister_N_2005_t::CDVDRegister_N_2005_t(const char * mnemonic_N_READY, const char * mnemonic_N_DATA_IN, bool debugReads, bool debugWrites) :
	Register8_t("NOT USED", false, false),
	N_READY(std::make_shared<Register8_t>(mnemonic_N_READY, debugReads, debugWrites)),
	N_DATA_IN(std::make_shared<FIFOQueue8_t>(mnemonic_N_DATA_IN, debugReads, debugWrites))
{
}

u8 CDVDRegister_N_2005_t::readByte(const System_t context)
{
	if (context == System_t::IOPCore)
		return N_READY->readByte(context);
	else
		throw std::runtime_error("CDVDRegister_N_2005 readByte called but not from IOPCore - what are you trying to do??");
}

void CDVDRegister_N_2005_t::writeByte(const System_t context, u8 value)
{
	if (context == System_t::IOPCore)
		N_DATA_IN->writeByte(context, value);
	else
		throw std::runtime_error("CDVDRegister_N_2005 readByte called but not from IOPCore - what are you trying to do??");
}
