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
	u8 readWrite, area, maxBlocks;
	if (!mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext(), readWrite)
		|| !mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext(), area)
		|| !mCDVD->S_RDY_DIN->DATA_IN->readByte(getContext(), maxBlocks))
		{
			throw std::runtime_error("CDVD_s: Instruction 0x40 failed, one of the paramters did not read ok. Please debug.");
		}

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
	if (!mCDVD->S_DATA_OUT->write(getContext(), reinterpret_cast<u8*>(buffer), 16))
		throw std::runtime_error("CDVD_s: Instruction 0x41 failed, not enough space in the FIFO queue to write. Please debug");
}

void CDVD_s::SCMD_INSTRUCTION_42()
{
	// Write config data block and return success.
	// A block is 16 bytes / 8 hwords long.
	// TODO: check for endianess problems.
	u16 buffer[8];
	if (!mCDVD->S_RDY_DIN->DATA_IN->read(getContext(), reinterpret_cast<u8*>(buffer), 16))
		throw std::runtime_error("CDVD_s: Instruction 0x42 failed, not enough data in the FIFO queue to read. Please debug.");
	mCDVD->NVRAM->writeConfigBlock(getContext(), buffer);
	mCDVD->S_DATA_OUT->writeByte(getContext(), 0);
}

void CDVD_s::SCMD_INSTRUCTION_43()
{
	// Reset config parameters and return success.
	mCDVD->NVRAM->setConfigAccessParams(0, 0, 0, 0);
	mCDVD->S_DATA_OUT->writeByte(getContext(), 0);
}
