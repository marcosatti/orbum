#include "stdafx.h"

#include "Resources/CDVD/Types/CDVDRegisters_t.h"

CDVDRegister_NS_COMMAND_t::CDVDRegister_NS_COMMAND_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register8_t(mnemonic, debugReads, debugWrites),
	mPendingCommand(false)
{
}

void CDVDRegister_NS_COMMAND_t::writeByte(const System_t context, u8 value)
{
	if (mPendingCommand)
		throw std::runtime_error("CDVDRegister_NS_COMMAND_t already had pending command set... Oops!");

	mPendingCommand = true;
	Register8_t::writeByte(context, value);
}


CDVDRegister_NS_RDY_DIN_t::CDVDRegister_NS_RDY_DIN_t(const char * mnemonic_READY, const char * mnemonic_DATA_IN, bool debugReads, bool debugWrites, const size_t fifoQueueSize) :
	Register8_t("NOT USED", false, false),
	READY(std::make_shared<Register8_t>(mnemonic_READY, debugReads, debugWrites)),
	DATA_IN(std::make_shared<FIFOQueue8_t>(mnemonic_DATA_IN, debugReads, debugWrites, fifoQueueSize))
{
}

u8 CDVDRegister_NS_RDY_DIN_t::readByte(const System_t context)
{
	if (context == System_t::IOPCore)
		return READY->readByte(context);
	else
		throw std::runtime_error("CDVDRegister_NS_RDY_DIN readByte called but not from IOPCore - what are you trying to do??");
}

void CDVDRegister_NS_RDY_DIN_t::writeByte(const System_t context, u8 value)
{
	if (context == System_t::IOPCore)
		DATA_IN->writeByte(context, value);
	else
		throw std::runtime_error("CDVDRegister_NS_RDY_DIN readByte called but not from IOPCore - what are you trying to do??");
}
