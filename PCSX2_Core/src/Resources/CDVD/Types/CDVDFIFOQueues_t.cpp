#include "Resources/CDVD/Types/CDVDFIFOQueues_t.h"

CDVDFIFOQueue_NS_DATA_OUT_t::CDVDFIFOQueue_NS_DATA_OUT_t(const char* mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize, const std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> & NS_RDY_DIN) :
	FIFOQueue_t(mnemonic, debugReads, debugWrites, maxByteSize),
	mNS_RDY_DIN(NS_RDY_DIN)
{
}

u8 CDVDFIFOQueue_NS_DATA_OUT_t::readByte(const System_t context)
{
	auto temp = FIFOQueue_t::readByte(context);

	if (getCurrentSize() == 0)
		mNS_RDY_DIN->READY->writeByte(context, mNS_RDY_DIN->READY->readByte(context) | 0x40);

	return temp;
}

void CDVDFIFOQueue_NS_DATA_OUT_t::writeByte(const System_t context, const u8 data)
{
	FIFOQueue_t::writeByte(context, data);
	mNS_RDY_DIN->READY->writeByte(context, mNS_RDY_DIN->READY->readByte(context) & (~0x40));
}
