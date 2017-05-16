#pragma once

#include <memory>

#include "Common/Types/FIFOQueue/FIFOQueue_t.h"

#include "Resources/CDVD/Types/CDVDRegisters_t.h"

/*
CDVD extended FIFOQueue_t, used as the N/S command result FIFO's (N/S_DATA_OUT).
Upon reading or writing, it will check for the FIFO being empty, and set the NS_RDY_DIN->Ready register accordingly (magic values).
*/
class CDVDFIFOQueue_NS_DATA_OUT_t : public FIFOQueue_t
{
public:
	CDVDFIFOQueue_NS_DATA_OUT_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const size_t maxByteSize, const std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> & NS_RDY_DIN);

	/*
	Updates the Ready register upon reads/writes with magic values, based on if FIFO is empty.
	*/
	u8 readByte(const System_t context) override;
	void writeByte(const System_t context, const u8 data) override;
	
private:
	/*
	Reference to the NS_RDY_DIN register.
	*/
	std::shared_ptr<CDVDRegister_NS_RDY_DIN_t> mNS_RDY_DIN;
};