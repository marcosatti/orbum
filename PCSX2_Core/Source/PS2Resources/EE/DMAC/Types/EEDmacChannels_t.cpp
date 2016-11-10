#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

EEDmacChannel_t::EEDmacChannel_t(const u32 & channelID) :
	mChannelID(channelID),
	mCHCR(std::make_shared<EEDmacChannelRegister_CHCR_t>(mSliceCountState)),
	mMADR(std::make_shared<EEDmacChannelRegister_MADR_t>()),
	mQWC(std::make_shared<EEDmacChannelRegister_QWC_t>()),
	mTADR(nullptr),
	mASR0(nullptr),
	mASR1(nullptr),
	mSADR(nullptr),
	mASR{ mASR0, mASR1 },
	mSliceCountState(0),
	mChainExitState(false),
	mChainStackLevelState(0),
	mInterleavedSkipState(false),
	mInterleavedCountState(0)
{
}

const ChannelProperties_t * EEDmacChannel_t::getChannelProperties() const
{
	return EEDmacTable::getChannelInfo(mChannelID);
}

EEDmacChannel_VIF0_t::EEDmacChannel_VIF0_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_VIF1_t::EEDmacChannel_VIF1_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_GIF_t::EEDmacChannel_GIF_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_fromIPU_t::EEDmacChannel_fromIPU_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
}

EEDmacChannel_toIPU_t::EEDmacChannel_toIPU_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF0_t::EEDmacChannel_SIF0_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
}

EEDmacChannel_SIF1_t::EEDmacChannel_SIF1_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF2_t::EEDmacChannel_SIF2_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
}

EEDmacChannel_fromSPR_t::EEDmacChannel_fromSPR_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mSADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}

EEDmacChannel_toSPR_t::EEDmacChannel_toSPR_t() :
	EEDmacChannel_t(CHANNEL_ID)
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mSADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}
