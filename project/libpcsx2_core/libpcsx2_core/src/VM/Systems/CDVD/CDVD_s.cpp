#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/CDVD/CDVD_s.h"

#include "Resources/Resources_t.h"
#include "Resources/CDVD/CDVD_t.h"
#include "Resources/CDVD/Types/CDVDRegisters_t.h"
#include "Resources/CDVD/Types/CDVDNvrams_t.h"

CDVD_s::CDVD_s(VM * vm) :
	VMSystem_t(vm, Context_t::CDVD)
{
	mCDVD = getVM()->getResources()->CDVD;
}

void CDVD_s::initialise()
{
	// Reset CDVD registers.
	
	// Set N_READY / S_READY.
	mCDVD->N_RDY_DIN->READY->writeByte(getContext(), 0x4E);
	mCDVD->S_RDY_DIN->READY->writeByte(getContext(), 0x40);

	// Set iLink Data magic values.
	mCDVD->NVRAM->writeILinkID(getContext(), reinterpret_cast<const u16*>(CDVDNvram_t::ILINK_DATA_MAGIC));
}

int CDVD_s::step(const Event_t & event)
{
	// 2 types of commands to process: N-type, and S-type.
	// Process N-type.

	// Process S-type.
	// Check for a pending command, only process if set.
	if (mCDVD->S_COMMAND->mPendingCommand)
	{
		// Command has been acknowledged, reset the variable.
		mCDVD->S_COMMAND->mPendingCommand = false;

		// Run the S function based upon the S_COMMAND index.
		(this->*SCMD_INSTRUCTION_TABLE[mCDVD->S_COMMAND->readByte(getContext())])();
	}

	return event.mQuantity;
}

void CDVD_s::NCMD_INSTRUCTION_UNKNOWN()
{
	log(Debug, "CDVD N_CMD Unknown Instruction called (0x%02X).", mCDVD->N_COMMAND->readByte(getContext()));
}

void CDVD_s::SCMD_INSTRUCTION_UNKNOWN()
{
	log(Debug, "CDVD S_CMD Unknown Instruction called (0x%02X).", mCDVD->S_COMMAND->readByte(getContext()));
}