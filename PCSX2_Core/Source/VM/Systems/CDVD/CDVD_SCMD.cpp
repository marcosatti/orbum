#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/CDVD/CDVD_s.h"

#include "Resources/Resources_t.h"
#include "Resources/CDVD/CDVD_t.h"
#include "Resources/CDVD/Types/CDVDRegisters_t.h"
#include "Resources/CDVD/Types/CDVDNvrams_t.h"
#include "Resources/CDVD/Types/CDVDFIFOQueues_t.h"

void CDVD_s::SCMD_INSTRUCTION_40()
{
	// Read config parameters.
	u8 readWrite = mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext());
	u8 area = mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext());
	u8 maxBlocks = mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext());

	// Set NVRAM config parameters.
	mCDVD->NVRAM->setConfigAccessParams(readWrite, area, maxBlocks, 0);

	// Return success.
	mCDVD->S_DATA_OUT->writeByte(getContext(), 0);
}

void CDVD_s::SCMD_INSTRUCTION_41()
{
	// Read and return config block data.
	// A block is 16 bytes / 8 hwords long.
	// TODO: check for endianess problems.
	u16 buffer[8];
	mCDVD->NVRAM->readConfigBlock(getContext(), buffer);
	mCDVD->S_DATA_OUT->write(getContext(), reinterpret_cast<u8*>(buffer), 16);
}

void CDVD_s::SCMD_INSTRUCTION_42()
{
	// Write config data block and return success.
	// A block is 16 bytes / 8 hwords long.
	// TODO: check for endianess problems.
	u16 buffer[8];
	mCDVD->S_RDY_DIN->DATA_IN->read(getContext(), reinterpret_cast<u8*>(buffer), 16);
	mCDVD->NVRAM->writeConfigBlock(getContext(), buffer);
	mCDVD->S_DATA_OUT->writeByte(getContext(), 0);
}

void CDVD_s::SCMD_INSTRUCTION_43()
{
	// Reset config parameters and return success.
	mCDVD->NVRAM->setConfigAccessParams(0, 0, 0, 0);
	mCDVD->S_DATA_OUT->writeByte(getContext(), 0);
}
