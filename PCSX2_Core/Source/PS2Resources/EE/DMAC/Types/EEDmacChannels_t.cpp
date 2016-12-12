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
	return EEDmacChannelTable::getChannelInfo(mChannelID);
}

EEDmacChannel_VIF0_t::EEDmacChannel_VIF0_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0xFA0, "EE DMAC VIF0 Reserved Memory"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_VIF1_t::EEDmacChannel_VIF1_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0xFA0, "EE DMAC VIF1 Reserved Memory"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_GIF_t::EEDmacChannel_GIF_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0xFA0, "EE DMAC GIF Reserved Memory"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	mASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_fromIPU_t::EEDmacChannel_fromIPU_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0x3D0, "EE DMAC fromIPU Reserved Memory"))
{
}

EEDmacChannel_toIPU_t::EEDmacChannel_toIPU_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0xBC0, "EE DMAC toIPU Reserved Memory"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF0_t::EEDmacChannel_SIF0_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0x3D0, "EE DMAC SIF0 Reserved Memory"))
{
}

EEDmacChannel_SIF1_t::EEDmacChannel_SIF1_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0x3C0, "EE DMAC SIF1 Reserved Memory"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF2_t::EEDmacChannel_SIF2_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED(std::make_shared<ZeroMemory_t>(0x7D0, "EE DMAC SIF2 Reserved Memory"))
{
}

EEDmacChannel_fromSPR_t::EEDmacChannel_fromSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED0(std::make_shared<ZeroMemory_t>(0x50, "EE DMAC fromSPR Reserved Memory0")),
	mRESERVED1(std::make_shared<ZeroMemory_t>(0x370, "EE DMAC fromSPR Reserved Memory1"))
{
	mSADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}

EEDmacChannel_toSPR_t::EEDmacChannel_toSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	mRESERVED0(std::make_shared<ZeroMemory_t>(0x40, "EE DMAC toSPR Reserved Memory0")),
	mRESERVED1(std::make_shared<ZeroMemory_t>(0xB70, "EE DMAC fromSPR Reserved Memory1"))
{
	mTADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	mSADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}
