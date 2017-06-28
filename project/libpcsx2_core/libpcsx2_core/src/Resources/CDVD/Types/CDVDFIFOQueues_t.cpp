#include "Resources/CDVD/Types/CDVDFIFOQueues_t.h"

CDVDFIFOQueue_NS_DATA_OUT_t::CDVDFIFOQueue_NS_DATA_OUT_t(const char* mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize, const std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> & NS_RDY_DIN) :
	FIFOQueue_t(mnemonic, debugReads, debugWrites, maxByteSize),
	mNS_RDY_DIN(NS_RDY_DIN)
{
}

bool CDVDFIFOQueue_NS_DATA_OUT_t::readByte(const Context_t context, u8 & data)
{
	auto success = FIFOQueue_t::readByte(context, data);

	// Check if FIFO is empty.
	if (getReadAvailable() == 0)
		mNS_RDY_DIN->READY->writeByte(context, mNS_RDY_DIN->READY->readByte(context) | 0x40);

	return success;
}

bool CDVDFIFOQueue_NS_DATA_OUT_t::writeByte(const Context_t context, const u8 data)
{
	bool success = FIFOQueue_t::writeByte(context, data);

	// Check if FIFO is empty (write could fail).
	if (getReadAvailable() > 0)
		mNS_RDY_DIN->READY->writeByte(context, mNS_RDY_DIN->READY->readByte(context) & (~0x40));

	return success;
}
