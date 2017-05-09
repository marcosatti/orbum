#include "stdafx.h"

#include "Common/Types/Memory/ConstantByteMemory_t.h"

#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"

EEDmacChannel_t::EEDmacChannel_t(const int channelID) :
	CHCR(nullptr),
	MADR(nullptr),
	QWC(nullptr),
	TADR(nullptr),
	ASR0(nullptr),
	ASR1(nullptr),
	SADR(nullptr),
	ASR{ },
	FIFOQueue(nullptr),
	mChannelID(channelID)
{
	// Perform lookup for constant channel info.
	mInfo = EEDmacChannelTable::getInfo(this);
}

EEDmacChannel_t::EEDmacChannel_t(const int channelID, const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	CHCR(nullptr),
	MADR(nullptr),
	QWC(nullptr),
	TADR(nullptr),
	ASR0(nullptr),
	ASR1(nullptr),
	SADR(nullptr),
	ASR{ },
	FIFOQueue(fifoQueue),
	mChannelID(channelID)
{
	// Perform lookup for constant channel info.
	mInfo = EEDmacChannelTable::getInfo(this);
}

int EEDmacChannel_t::getChannelID() const
{
	return mChannelID;
}

const EEDmacChannelTable::EEDmacChannelInfo_t * EEDmacChannel_t::getInfo() const
{
	return mInfo;
}

EEDmacChannel_VIF0_t::EEDmacChannel_VIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_8060(std::make_shared<ConstantByteMemory_t>("EE DMAC 8060", false, false, 0xFA0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_TO_CHCR_t>("EE DMAC CH_VIF0 CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_VIF0 MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_VIF0 QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_VIF0 TADR", false, false);
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_VIF0 ASR0", false, false);
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_VIF0 ASR1", false, false);
	ASR[0] = ASR0;
	ASR[1] = ASR1;
}

EEDmacChannel_VIF1_t::EEDmacChannel_VIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_9060(std::make_shared<ConstantByteMemory_t>("EE DMAC 9060", false, false, 0xFA0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_CHCR_t>("EE DMAC CH_VIF1 CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_VIF1 MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_VIF1 QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_VIF1 TADR", false, false);
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_VIF1 ASR0", false, false);
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_VIF1 ASR1", false, false);
	ASR[0] = ASR0;
	ASR[1] = ASR1;
}

EEDmacChannel_GIF_t::EEDmacChannel_GIF_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_A060(std::make_shared<ConstantByteMemory_t>("EE DMAC A060", false, false, 0xFA0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_TO_CHCR_t>("EE DMAC CH_GIF CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_GIF MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_GIF QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_GIF TADR", false, false);
	ASR0 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_GIF ASR0", false, false);
	ASR1 = std::make_shared<EEDmacChannelRegister_ASR_t>("EE DMAC CH_GIF ASR1", false, false);
	ASR[0] = ASR0;
	ASR[1] = ASR1;
}

EEDmacChannel_fromIPU_t::EEDmacChannel_fromIPU_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_B030(std::make_shared<ConstantByteMemory_t>("EE DMAC B030", false, false, 0x3D0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_FROM_CHCR_t>("EE DMAC CH_fromIPU CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_fromIPU MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_fromIPU QWC", false, false);
}

EEDmacChannel_toIPU_t::EEDmacChannel_toIPU_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_B440(std::make_shared<ConstantByteMemory_t>("EE DMAC B440", false, false, 0xBC0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_TO_CHCR_t>("EE DMAC CH_toIPU CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_toIPU MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_toIPU QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_toIPU TADR", false, false);
}

EEDmacChannel_SIF0_t::EEDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C030(std::make_shared<ConstantByteMemory_t>("EE DMAC C030", false, false, 0x3D0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_SIF0_CHCR_t>("EE DMAC CH_SIF0 CHCR", false, false, sbusF240);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_SIF0 MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_SIF0 QWC", false, false);
}

EEDmacChannel_SIF1_t::EEDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C440(std::make_shared<ConstantByteMemory_t>("EE DMAC C440", false, false, 0x3C0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_SIF1_CHCR_t>("EE DMAC CH_SIF1 CHCR", false, false, sbusF240);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_SIF1 MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_SIF1 QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_SIF1 TADR", false, false);
}

EEDmacChannel_SIF2_t::EEDmacChannel_SIF2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	EEDmacChannel_t(CHANNEL_ID, fifoQueue),
	MEMORY_C830(std::make_shared<ConstantByteMemory_t>("EE DMAC C830", false, false, 0x7D0))
{
	CHCR = std::make_shared<EEDmacChannelRegister_SIF2_CHCR_t>("EE DMAC CH_SIF2 CHCR", false, false, sbusF240);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_SIF2 MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_SIF2 QWC", false, false);
}

EEDmacChannel_fromSPR_t::EEDmacChannel_fromSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	MEMORY_D030(std::make_shared<ConstantByteMemory_t>("EE DMAC D030", false, false, 0x50)),
	MEMORY_D090(std::make_shared<ConstantByteMemory_t>("EE DMAC D090", false, false, 0x370))
{
	CHCR = std::make_shared<EEDmacChannelRegister_FROM_CHCR_t>("EE DMAC CH_fromSPR CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_fromSPR MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_fromSPR QWC", false, false);
	SADR = std::make_shared<EEDmacChannelRegister_SADR_t>("EE DMAC CH_fromSPR SADR", false, false);
}

EEDmacChannel_toSPR_t::EEDmacChannel_toSPR_t() :
	EEDmacChannel_t(CHANNEL_ID),
	MEMORY_D440(std::make_shared<ConstantByteMemory_t>("EE DMAC D440", false, false, 0x40)),
	MEMORY_D490(std::make_shared<ConstantByteMemory_t>("EE DMAC D490", false, false, 0xB70))
{
	CHCR = std::make_shared<EEDmacChannelRegister_TO_CHCR_t>("EE DMAC CH_toSPR CHCR", false, false);
	MADR = std::make_shared<EEDmacChannelRegister_MADR_t>("EE DMAC CH_toSPR MADR", false, false);
	QWC = std::make_shared<EEDmacChannelRegister_QWC_t>("EE DMAC CH_toSPR QWC", false, false);
	TADR = std::make_shared<EEDmacChannelRegister_TADR_t>("EE DMAC CH_toSPR TADR", false, false);
	SADR = std::make_shared<EEDmacChannelRegister_SADR_t>("EE DMAC CH_toSPR SADR", false, false);
}
