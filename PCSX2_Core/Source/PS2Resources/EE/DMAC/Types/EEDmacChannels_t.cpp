#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

EEDmacChannel_t::EEDmacChannel_t(const u32& channelID) :
	mChannelID(channelID),
	CHCR(std::make_shared<EEDmacChannelRegister_CHCR_t>()),
	MADR(std::make_shared<EEDmacChannelRegister_MADR_t>()),
	QWC(std::make_shared<EEDmacChannelRegister_QWC_t>()),
	TADR(nullptr),
	ASR0(nullptr),
	ASR1(nullptr),
	SADR(nullptr),
	ASR{ ASR0, ASR1 },
	mFIFOQueue(nullptr),
	mSliceCountState(0),
	mChainSrcFirstRun(true),
	mChainExitState(false),
	mChainStackLevelState(0),
	mInterleavedInSkipBlock(false),
	mInterleavedBlockCount(0)
{
}

EEDmacChannel_t::EEDmacChannel_t(const u32& channelID, std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	mChannelID(channelID),
	CHCR(std::make_shared<EEDmacChannelRegister_CHCR_t>()),
	MADR(std::make_shared<EEDmacChannelRegister_MADR_t>()),
	QWC(std::make_shared<EEDmacChannelRegister_QWC_t>()),
	TADR(nullptr),
	ASR0(nullptr),
	ASR1(nullptr),
	SADR(nullptr),
	ASR{ ASR0, ASR1 },
	mFIFOQueue(fifoQueue),
	mSliceCountState(0),
	mChainSrcFirstRun(true),
	mChainExitState(false),
	mChainStackLevelState(0),
	mInterleavedInSkipBlock(false),
	mInterleavedBlockCount(0)
{
}

const ChannelProperties_t * EEDmacChannel_t::getChannelProperties() const
{
	return EEDmacChannelTable::getChannelInfo(mChannelID);
}

EEDmacChannel_VIF0_t::EEDmacChannel_VIF0_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_8060(std::make_shared<ConstantMemory_t>(0xFA0, "EE DMAC VIF0 Reserved Memory"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_VIF1_t::EEDmacChannel_VIF1_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_9060(std::make_shared<ConstantMemory_t>(0xFA0, "EE DMAC VIF1 Reserved Memory"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_GIF_t::EEDmacChannel_GIF_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_A060(std::make_shared<ConstantMemory_t>(0xFA0, "EE DMAC GIF Reserved Memory"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>();
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>();
}

EEDmacChannel_fromIPU_t::EEDmacChannel_fromIPU_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_B030(std::make_shared<ConstantMemory_t>(0x3D0, "EE DMAC fromIPU Reserved Memory"))
{
}

EEDmacChannel_toIPU_t::EEDmacChannel_toIPU_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_B440(std::make_shared<ConstantMemory_t>(0xBC0, "EE DMAC toIPU Reserved Memory"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF0_t::EEDmacChannel_SIF0_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C030(std::make_shared<ConstantMemory_t>(0x3D0, "EE DMAC SIF0 Reserved Memory"))
{
}

EEDmacChannel_SIF1_t::EEDmacChannel_SIF1_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C440(std::make_shared<ConstantMemory_t>(0x3C0, "EE DMAC SIF1 Reserved Memory"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
}

EEDmacChannel_SIF2_t::EEDmacChannel_SIF2_t(std::shared_ptr<FIFOQueue_t>& fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C830(std::make_shared<ConstantMemory_t>(0x7D0, "EE DMAC SIF2 Reserved Memory"))
{
}

EEDmacChannel_fromSPR_t::EEDmacChannel_fromSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	MEMORY_D030(std::make_shared<ConstantMemory_t>(0x50, "EE DMAC fromSPR Reserved Memory0")),
	MEMORY_D090(std::make_shared<ConstantMemory_t>(0x370, "EE DMAC fromSPR Reserved Memory1"))
{
	SADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}

EEDmacChannel_toSPR_t::EEDmacChannel_toSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	MEMORY_D440(std::make_shared<ConstantMemory_t>(0x40, "EE DMAC toSPR Reserved Memory0")),
	MEMORY_D490(std::make_shared<ConstantMemory_t>(0xB70, "EE DMAC fromSPR Reserved Memory1"))
{
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>();
	SADR = std::make_shared<EEDmacChannelRegister_SADR_t>();
}
