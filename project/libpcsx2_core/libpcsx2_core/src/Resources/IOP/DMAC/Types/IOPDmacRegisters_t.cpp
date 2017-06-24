#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"

constexpr int IOPDmacRegister_PCR0_t::Fields::CHANNEL_PRIORITY_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_ICR0_t::Fields::CHANNEL_IRM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_PCR1_t::Fields::CHANNEL_PRIORITY_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_ICR1_t::Fields::CHANNEL_IQE_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS];
constexpr int IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCM_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];
constexpr int IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[Constants::IOP::DMAC::NUMBER_DMAC_CHANNELS / 2];

IOPDmacRegister_PCR0_t::IOPDmacRegister_PCR0_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::Priority0, "Priority0", 0, 3, 0);
	registerField(Fields::Enable0, "Enable0", 3, 1, 0);
	registerField(Fields::Priority1, "Priority1", 4, 3, 0);
	registerField(Fields::Enable1, "Enable1", 7, 1, 0);
	registerField(Fields::Priority2, "Priority2", 8, 3, 0);
	registerField(Fields::Enable2, "Enable2", 11, 1, 0);
	registerField(Fields::Priority3, "Priority3", 12, 3, 0);
	registerField(Fields::Enable3, "Enable3", 15, 1, 0);
	registerField(Fields::Priority4, "Priority4", 16, 3, 0);
	registerField(Fields::Enable4, "Enable4", 19, 1, 0);
	registerField(Fields::Priority5, "Priority5", 20, 3, 0);
	registerField(Fields::Enable5, "Enable5", 23, 1, 0);
	registerField(Fields::Priority6, "Priority6", 24, 3, 0);
	registerField(Fields::Enable6, "Enable6", 27, 1, 0);
	registerField(Fields::PriorityCPU, "PriorityCPU", 28, 3, 0);
	registerField(Fields::EnableCPU, "EnableCPU", 31, 1, 0);

}

IOPDmacRegister_ICR0_t::IOPDmacRegister_ICR0_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::IRM0, "IRM0", 0, 1, 0);
	registerField(Fields::IRM1, "IRM1", 1, 1, 0);
	registerField(Fields::IRM2, "IRM2", 2, 1, 0);
	registerField(Fields::IRM3, "IRM3", 3, 1, 0);
	registerField(Fields::IRM4, "IRM4", 4, 1, 0);
	registerField(Fields::IRM5, "IRM5", 5, 1, 0);
	registerField(Fields::IRM6, "IRM6", 6, 1, 0);
	registerField(Fields::Error, "Error", 15, 1, 0);
	registerField(Fields::TCM0, "TCM0", 16, 1, 0);
	registerField(Fields::TCM1, "TCM1", 17, 1, 0);
	registerField(Fields::TCM2, "TCM2", 18, 1, 0);
	registerField(Fields::TCM3, "TCM3", 19, 1, 0);
	registerField(Fields::TCM4, "TCM4", 20, 1, 0);
	registerField(Fields::TCM5, "TCM5", 21, 1, 0);
	registerField(Fields::TCM6, "TCM6", 22, 1, 0);
	registerField(Fields::MasterEnable, "MasterEnable", 23, 1, 0);
	registerField(Fields::TCI0, "TCI0", 24, 1, 0);
	registerField(Fields::TCI1, "TCI1", 25, 1, 0);
	registerField(Fields::TCI2, "TCI2", 26, 1, 0);
	registerField(Fields::TCI3, "TCI3", 27, 1, 0);
	registerField(Fields::TCI4, "TCI4", 28, 1, 0);
	registerField(Fields::TCI5, "TCI5", 29, 1, 0);
	registerField(Fields::TCI6, "TCI6", 30, 1, 0);
	registerField(Fields::MasterInterrupt, "MasterInterrupt", 31, 1, 0);
}

void IOPDmacRegister_ICR0_t::writeWord(const Context_t context, const u32 value)
{
	// Preprocessing for IOP: reset (clear) the FL bits if 1 is written to them (taken from PCSX2 "IopHwWrite.cpp").
	u32 temp = value;
	if (context == Context_t::IOPCore)
		temp = ((readWord(context) & 0xFF000000) | (value & 0xFFFFFF)) & ~(value & 0x7F000000);
		
	BitfieldRegister32_t::writeWord(context, temp);
}

bool IOPDmacRegister_ICR0_t::isInterruptPending(const Context_t context)
{
	u32 regValue = readWord(context);
	u32 TCM = (regValue & 0x7F0000) >> 16;
	u32 TCI = (regValue & 0x7F000000) >> 24;
	
	// Check for channel interrupts or error interrupt. Set the master interrupt bit if any of the conditions are true.
	if (((TCM & TCI) && getFieldValue(context, Fields::MasterEnable)) || getFieldValue(context, Fields::Error))
	{
		setFieldValue(context, Fields::MasterInterrupt, 1);
		return true;
	}
	
	return false;
}

IOPDmacRegister_PCR1_t::IOPDmacRegister_PCR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites)
{
	registerField(Fields::Priority7, "Priority7", 0, 3, 0);
	registerField(Fields::Enable7, "Enable7", 3, 1, 0);
	registerField(Fields::Priority8, "Priority8", 4, 3, 0);
	registerField(Fields::Enable8, "Enable8", 7, 1, 0);
	registerField(Fields::Priority9, "Priority9", 8, 3, 0);
	registerField(Fields::Enable9, "Enable9", 11, 1, 0);
	registerField(Fields::Priority10, "Priority10", 12, 3, 0);
	registerField(Fields::Enable10, "Enable10", 15, 1, 0);
	registerField(Fields::Priority11, "Priority11", 16, 3, 0);
	registerField(Fields::Enable11, "Enable11", 19, 1, 0);
	registerField(Fields::Priority12, "Priority12", 20, 3, 0);
	registerField(Fields::Enable12, "Enable12", 23, 1, 0);
	registerField(Fields::Priority13, "Priority13", 24, 3, 0);
	registerField(Fields::Enable13, "Enable13", 27, 1, 0);
}

IOPDmacRegister_ICR1_t::IOPDmacRegister_ICR1_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const std::shared_ptr<IOPDmacRegister_ICR0_t>& ICR0) :
	BitfieldRegister32_t(mnemonic, debugReads, debugWrites),
	mICR0(ICR0)
{
	registerField(Fields::IQE0, "IQE0", 0, 1, 0);
	registerField(Fields::IQE1, "IQE1", 1, 1, 0);
	registerField(Fields::IQE2, "IQE2", 2, 1, 0);
	registerField(Fields::IQE3, "IQE3", 3, 1, 0);
	registerField(Fields::IQE4, "IQE4", 4, 1, 0);
	registerField(Fields::IQE5, "IQE5", 5, 1, 0);
	registerField(Fields::IQE6, "IQE6", 6, 1, 0);
	registerField(Fields::IQE7, "IQE7", 7, 1, 0);
	registerField(Fields::IQE8, "IQE8", 8, 1, 0);
	registerField(Fields::IQE9, "IQE9", 9, 1, 0);
	registerField(Fields::IQE10, "IQE10", 10, 1, 0);
	registerField(Fields::IQE11, "IQE11", 11, 1, 0);
	registerField(Fields::IQE12, "IQE12", 12, 1, 0);
	registerField(Fields::IQE13, "IQE13", 13, 1, 0);
	registerField(Fields::TCM7, "TCM7", 16, 1, 0);
	registerField(Fields::TCM8, "TCM8", 17, 1, 0);
	registerField(Fields::TCM9, "TCM9", 18, 1, 0);
	registerField(Fields::TCM10, "TCM10", 19, 1, 0);
	registerField(Fields::TCM11, "TCM11", 20, 1, 0);
	registerField(Fields::TCM12, "TCM12", 21, 1, 0);
	registerField(Fields::TCM13, "TCM13", 22, 1, 0);
	registerField(Fields::TCI7, "TCI7", 24, 1, 0);
	registerField(Fields::TCI8, "TCI8", 25, 1, 0);
	registerField(Fields::TCI9, "TCI9", 26, 1, 0);
	registerField(Fields::TCI10, "TCI10", 27, 1, 0);
	registerField(Fields::TCI11, "TCI11", 28, 1, 0);
	registerField(Fields::TCI12, "TCI12", 29, 1, 0);
	registerField(Fields::TCI13, "TCI13", 30, 1, 0);
}

void IOPDmacRegister_ICR1_t::writeWord(const Context_t context, const u32 value)
{
	// Preprocessing for IOP: reset (clear) the FL bits if 1 is written to them (taken from PCSX2 "IopHwWrite.cpp").
	u32 temp = value;
	if (context == Context_t::IOPCore)
		temp = ((readWord(context) & 0xFF000000) | (value & 0xFFFFFF)) & ~(value & 0x7F000000);

	BitfieldRegister32_t::writeWord(context, temp);
}

bool IOPDmacRegister_ICR1_t::isInterruptPending(const Context_t context)
{
	u32 regValue = readWord(context);
	u32 TCM = (regValue & 0x7F0000) >> 16;
	u32 TCI = (regValue & 0x7F000000) >> 24;

	// Check for channel interrupts or error interrupt. Set the master interrupt bit if any of the conditions are true.
	if ((TCM & TCI) && mICR0->getFieldValue(context, IOPDmacRegister_ICR0_t::Fields::MasterEnable))
	{
		mICR0->setFieldValue(context, IOPDmacRegister_ICR0_t::Fields::MasterInterrupt, 1);
		return true;
	}

	return false;
}

IOPDmacRegister_PCRW_t::IOPDmacRegister_PCRW_t(const std::shared_ptr<IOPDmacRegister_PCR0_t> & pcr0, const std::shared_ptr<IOPDmacRegister_PCR1_t> & pcr1) :
	mPCR0(pcr0),
	mPCR1(pcr1)
{
}

u32 IOPDmacRegister_PCRW_t::getChannelPriority(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		return mPCR0->getFieldValue(context, IOPDmacRegister_PCR0_t::Fields::CHANNEL_PRIORITY_KEYS[channel->getChannelID()]);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		return mPCR1->getFieldValue(context, IOPDmacRegister_PCR1_t::Fields::CHANNEL_PRIORITY_KEYS[channel->getChannelID() % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get priority index.");
}

void IOPDmacRegister_PCRW_t::setChannelPriority(const Context_t context, const IOPDmacChannel_t * channel, const u32 value)
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		mPCR0->setFieldValue(context, IOPDmacRegister_PCR0_t::Fields::CHANNEL_PRIORITY_KEYS[channel->getChannelID()], value);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		mPCR1->setFieldValue(context, IOPDmacRegister_PCR1_t::Fields::CHANNEL_PRIORITY_KEYS[channel->getChannelID() % 7], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set priority index.");
}

bool IOPDmacRegister_PCRW_t::isChannelEnabled(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		return (mPCR0->getFieldValue(context, IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[channel->getChannelID()]) > 0);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		return (mPCR1->getFieldValue(context, IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[channel->getChannelID() % 7]) > 0);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get enabled index.");
}

void IOPDmacRegister_PCRW_t::setChannelEnabled(const Context_t context, const IOPDmacChannel_t * channel, const bool value)
{
	// Channels 0-6 belong to PCR0, channels 7-13 belong to PCR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		mPCR0->setFieldValue(context, IOPDmacRegister_PCR0_t::Fields::CHANNEL_ENABLE_KEYS[channel->getChannelID()], (value ? 1 : 0));
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		mPCR1->setFieldValue(context, IOPDmacRegister_PCR1_t::Fields::CHANNEL_ENABLE_KEYS[channel->getChannelID() % 7], (value ? 1: 0));
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set enabled index.");
}

IOPDmacRegister_ICRW_t::IOPDmacRegister_ICRW_t(const std::shared_ptr<IOPDmacRegister_ICR0_t> & icr0, const std::shared_ptr<IOPDmacRegister_ICR1_t> & icr1) :
	mICR0(icr0),
	mICR1(icr1)
{
}

u32 IOPDmacRegister_ICRW_t::getChannelIRM(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-6 belong to ICR0.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		return mICR0->getFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_IRM_KEYS[channel->getChannelID()]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get IRM index.");
}

void IOPDmacRegister_ICRW_t::setChannelIRM(const Context_t context, const IOPDmacChannel_t * channel, const u32 value)
{
	// Channels 0-6 belong to ICR0.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		mICR0->setFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_IRM_KEYS[channel->getChannelID()], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set IRM index.");
}

u32 IOPDmacRegister_ICRW_t::getChannelIQE(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 14)
		return mICR1->getFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_IQE_KEYS[channel->getChannelID()]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get IQE index.");
}

void IOPDmacRegister_ICRW_t::setChannelIQE(const Context_t context, const IOPDmacChannel_t * channel, const u32 value)
{
	// Channels 0-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 14)
		mICR1->setFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_IQE_KEYS[channel->getChannelID()], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set IQE index.");
}

u32 IOPDmacRegister_ICRW_t::getChannelTCM(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		return mICR0->getFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCM_KEYS[channel->getChannelID()]);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		return mICR1->getFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCM_KEYS[channel->getChannelID() % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get TCM index.");
}

void IOPDmacRegister_ICRW_t::setChannelTCM(const Context_t context, const IOPDmacChannel_t * channel, const u32 value)
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		mICR0->setFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCM_KEYS[channel->getChannelID()], value);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		mICR1->setFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCM_KEYS[channel->getChannelID() % 7], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set TCM index.");
}

u32 IOPDmacRegister_ICRW_t::getChannelTCI(const Context_t context, const IOPDmacChannel_t * channel)
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		return mICR0->getFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[channel->getChannelID()]);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		return mICR1->getFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[channel->getChannelID() % 7]);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel get TCI index.");
}

void IOPDmacRegister_ICRW_t::setChannelTCI(const Context_t context, const IOPDmacChannel_t * channel, const u32 value)
{
	// Channels 0-6 belong to ICR0, channels 7-13 belong to ICR1.
	if (channel->getChannelID() >= 0 && channel->getChannelID() < 7)
		mICR0->setFieldValue(context, IOPDmacRegister_ICR0_t::Fields::CHANNEL_TCI_KEYS[channel->getChannelID()], value);
	else if (channel->getChannelID() >= 7 && channel->getChannelID() < 14)
		mICR1->setFieldValue(context, IOPDmacRegister_ICR1_t::Fields::CHANNEL_TCI_KEYS[channel->getChannelID() % 7], value);
	else
		throw std::runtime_error("IOP DMAC PCRW could not determine channel set TCI index.");
}

bool IOPDmacRegister_ICRW_t::isInterruptPending(const Context_t context) const
{
	return (mICR0->isInterruptPending(context) || mICR1->isInterruptPending(context));
}