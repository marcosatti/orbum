#include "stdafx.h"

#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmacChannel_t::IOPDmacChannel_t(const int channelID, const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	MADR(nullptr),
	BCR(nullptr),
	CHCR(nullptr),
	TADR(nullptr),
	mFIFOQueue(fifoQueue),
	mChannelID(channelID)
{
	// Perform lookup for constant channel info.
	mInfo = IOPDmacChannelTable::getInfo(this);
}

int IOPDmacChannel_t::getChannelID() const
{
	return mChannelID;
}

const IOPDmacChannelTable::IOPDmacChannelInfo_t * IOPDmacChannel_t::getInfo()
{
	return mInfo;
}

IOPDmacChannel_fromMDEC_t::IOPDmacChannel_fromMDEC_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_fromMDEC MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_fromMDEC BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_fromMDEC CHCR");
}

IOPDmacChannel_toMDEC_t::IOPDmacChannel_toMDEC_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_toMDEC MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_toMDEC BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_toMDEC CHCR");
}

IOPDmacChannel_SIF2_t::IOPDmacChannel_SIF2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_SIF2 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_SIF2 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF2_CHCR_t>("IOP CH_SIF2 CHCR", sbusF240);
}

IOPDmacChannel_CDROM_t::IOPDmacChannel_CDROM_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_CDROM MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_CDROM BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_CDROM CHCR");
}

IOPDmacChannel_SPU2c1_t::IOPDmacChannel_SPU2c1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_SPU2c1 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_SPU2c1 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_SPU2c1 CHCR");
	TADR = std::make_shared<IOPDmacChannelRegister_TADR_t>("IOP CH_SPU2c1 TADR");
}

IOPDmacChannel_PIO_t::IOPDmacChannel_PIO_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_PIO MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_PIO BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_PIO CHCR");
}

IOPDmacChannel_OTClear_t::IOPDmacChannel_OTClear_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_OTClear MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_OTClear BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_OTClear CHCR");
}

IOPDmacChannel_SPU2c2_t::IOPDmacChannel_SPU2c2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_SPU2c2 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_SPU2c2 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_SPU2c2 CHCR");
}

IOPDmacChannel_DEV9_t::IOPDmacChannel_DEV9_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_DEV9 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_DEV9 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_DEV9 CHCR");
}

IOPDmacChannel_SIF0_t::IOPDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_SIF0 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_SIF0 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF0_CHCR_t>("IOP CH_SIF0 CHCR", sbusF240);
	TADR = std::make_shared<IOPDmacChannelRegister_TADR_t>("IOP CH_SIF0 TADR");
}

IOPDmacChannel_SIF1_t::IOPDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_SIF1 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_SIF1 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF1_CHCR_t>("IOP CH_SIF1 CHCR", sbusF240);
}

IOPDmacChannel_fromSIO2_t::IOPDmacChannel_fromSIO2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_fromSIO2 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_fromSIO2 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_fromSIO2 CHCR");
}

IOPDmacChannel_toSIO2_t::IOPDmacChannel_toSIO2_t(const std::shared_ptr<FIFOQueue32_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP CH_toSIO2 MADR");
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP CH_toSIO2 BCR");
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP CH_toSIO2 CHCR");
}
