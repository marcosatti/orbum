#include "stdafx.h"

#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

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

bool EEDmacChannel_t::isEnabled() const
{
	if (CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::STR) > 0)
		return true;
	
	return false;
}

bool EEDmacChannel_t::isChainInDrainStallControlTag() const
{
	return ((CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x4;
}

bool EEDmacChannel_t::isChainInSourceStallControlTag() const
{
	return ((CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) >> 12) & 0x7) == 0x0;
}

bool EEDmacChannel_t::isChainInInterruptTag() const
{
	if (CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TIE) != 0 
		&& (CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::TAG) & 0x8000) != 0)
	{
		return true;
	}
	
	return false;
}

bool EEDmacChannel_t::isChainInExitTag() const
{
	if (mChainExitState)
		return true;

	return false;
}

bool EEDmacChannel_t::isChainSourceInFirstCycle() const
{
	if (mChainSrcFirstRun)
		return true;

	return false;
}

bool EEDmacChannel_t::isChainStackOverflowed() const
{
	if (mChainStackLevelState >= 2) // Remember: 0 indexed!
		return true;

	return false;
}

bool EEDmacChannel_t::isChainStackUnderflowed() const
{
	if (mChainStackLevelState == 0)
		return true;

	return false;
}

bool EEDmacChannel_t::isInterleaveInSkipMode() const
{
	if (mInterleavedInSkipBlock)
		return true;
	
	return false;
}

LogicalMode_t EEDmacChannel_t::getRuntimeLogicalMode() const
{
	return static_cast<LogicalMode_t>(CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::MOD));
}

Direction_t EEDmacChannel_t::getRuntimeDirection() const
{
	Direction_t direction = getChannelProperties()->Direction;
	if (direction == Direction_t::BOTH)
		direction = static_cast<Direction_t>(CHCR->getFieldValue(EEDmacChannelRegister_CHCR_t::Fields::DIR));

	return direction;
}

u32 EEDmacChannel_t::getInterleavedCount() const
{
	return mInterleavedBlockCount;
}

void EEDmacChannel_t::setChainSourceFirstCycle()
{
	// Set TADR to (MADR + (QWC * 0x10)) as the next tag address on first run.
	u32 ADDR = MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::ADDR);
	u32 SPRFlag = MADR->getFieldValue(EEDmacChannelRegister_MADR_t::Fields::SPR);
	u32 QWCValue = QWC->getFieldValue(EEDmacChannelRegister_QWC_t::Fields::QWC);
	TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, ADDR + (QWCValue * 0x10));
	TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR, SPRFlag);

	mChainSrcFirstRun = false;
}

void EEDmacChannel_t::setChainExitStateReset()
{
	mChainSrcFirstRun = true;
	mChainExitState = false;
	mChainStackLevelState = 0;
}

void EEDmacChannel_t::setChainExitStateTrue()
{
	mChainExitState = true;
}

void EEDmacChannel_t::setInterleaveModeToggle()
{
	// Toggle mode and reset the count.
	mInterleavedInSkipBlock = !mInterleavedInSkipBlock;
	mInterleavedBlockCount = 0;
}

void EEDmacChannel_t::setInterleaveCountIncrement()
{
	mInterleavedBlockCount += 1;
}

void EEDmacChannel_t::setInterleaveSkipDataCycle() const
{
	MADR->increment();
}

void EEDmacChannel_t::pushChainStack()
{
	ASR[mChainStackLevelState]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR, TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR) + 0x10);
	ASR[mChainStackLevelState]->setFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR, TADR->getFieldValue(EEDmacChannelRegister_TADR_t::Fields::SPR));
	mChainStackLevelState += 1;
}

void EEDmacChannel_t::popChainStack()
{
	TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, ASR[mChainStackLevelState]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::ADDR));
	TADR->setFieldValue(EEDmacChannelRegister_TADR_t::Fields::ADDR, ASR[mChainStackLevelState]->getFieldValue(EEDmacChannelRegister_ASR_t::Fields::SPR));
	mChainStackLevelState -= 1;
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
