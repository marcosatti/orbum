#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"

IOPDmacChannel_t::IOPDmacChannel_t(const int channelID, const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	MADR(nullptr),
	BCR(nullptr),
	CHCR(nullptr),
	TADR(nullptr),
	FIFOQueue(fifoQueue),
	mChannelID(channelID)
{
	// Perform lookup for constant channel info.
	mInfo = IOPDmacChannelTable::getInfo(this);
}

int IOPDmacChannel_t::getChannelID() const
{
	return mChannelID;
}

const IOPDmacChannelTable::IOPDmacChannelInfo_t * IOPDmacChannel_t::getInfo() const
{
	return mInfo;
}

IOPDmacChannel_fromMDEC_t::IOPDmacChannel_fromMDEC_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_fromMDEC MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_fromMDEC BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_fromMDEC CHCR", false, false);
}

IOPDmacChannel_toMDEC_t::IOPDmacChannel_toMDEC_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_toMDEC MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_toMDEC BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_toMDEC CHCR", false, false);
}

IOPDmacChannel_SIF2_t::IOPDmacChannel_SIF2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_SIF2 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_SIF2 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF2_CHCR_t>("IOP DMAC CH_SIF2 CHCR", false, false, sbusF240);
}

IOPDmacChannel_CDROM_t::IOPDmacChannel_CDROM_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_CDROM MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_CDROM BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_CDROM CHCR", false, false);
}

IOPDmacChannel_SPU2C0_t::IOPDmacChannel_SPU2C0_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_SPU2C0 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_SPU2C0 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_SPU2C0 CHCR", false, false);
	TADR = std::make_shared<IOPDmacChannelRegister_TADR_t>("IOP DMAC CH_SPU2C0 TADR", false, false);
}

IOPDmacChannel_PIO_t::IOPDmacChannel_PIO_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_PIO MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_PIO BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_PIO CHCR", false, false);
}

IOPDmacChannel_OTClear_t::IOPDmacChannel_OTClear_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_OTClear MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_OTClear BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_OTClear CHCR", false, false);
}

IOPDmacChannel_SPU2C1_t::IOPDmacChannel_SPU2C1_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_SPU2C1 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_SPU2C1 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_SPU2C1 CHCR", false, false);
}

IOPDmacChannel_DEV9_t::IOPDmacChannel_DEV9_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_DEV9 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_DEV9 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_DEV9 CHCR", false, false);
}

IOPDmacChannel_SIF0_t::IOPDmacChannel_SIF0_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_SIF0 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_SIF0 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF0_CHCR_t>("IOP DMAC CH_SIF0 CHCR", false, false, sbusF240);
	TADR = std::make_shared<IOPDmacChannelRegister_TADR_t>("IOP DMAC CH_SIF0 TADR", false, false);
}

IOPDmacChannel_SIF1_t::IOPDmacChannel_SIF1_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue, const std::shared_ptr<Register32_t> & sbusF240) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_SIF1 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_SIF1 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_SIF1_CHCR_t>("IOP DMAC CH_SIF1 CHCR", false, false, sbusF240);
}

IOPDmacChannel_fromSIO2_t::IOPDmacChannel_fromSIO2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_fromSIO2 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_fromSIO2 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_fromSIO2 CHCR", false, true);
}

IOPDmacChannel_toSIO2_t::IOPDmacChannel_toSIO2_t(const std::shared_ptr<FIFOQueue_t> & fifoQueue) :
	IOPDmacChannel_t(CHANNEL_ID, fifoQueue)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_toSIO2 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_toSIO2 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_toSIO2 CHCR", false, true);
}

IOPDmacChannel_CH13_t::IOPDmacChannel_CH13_t() :
	IOPDmacChannel_t(CHANNEL_ID, nullptr)
{
	MADR = std::make_shared<IOPDmacChannelRegister_MADR_t>("IOP DMAC CH_13 MADR", false, false);
	BCR = std::make_shared<IOPDmacChannelRegister_BCR_t>("IOP DMAC CH_13 BCR", false, false);
	CHCR = std::make_shared<IOPDmacChannelRegister_CHCR_t>("IOP DMAC CH_13 CHCR", false, false);
}
