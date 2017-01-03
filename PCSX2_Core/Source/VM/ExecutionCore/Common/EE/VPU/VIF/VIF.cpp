#include "stdafx.h"

#include "Common/Tables/VIFcodeInstructionTable/VIFcodeInstructionTable.h"

#include "VM/ExecutionCore/Common/EE/VPU/VIF/VIF.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VIFUnits_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VIFUnitRegisters_t.h"

VIF::VIF(VMMain* vmMain, u32 vifUnitIndex) :
	VMExecutionCoreComponent(vmMain),
	mVIFUnitIndex(vifUnitIndex),
	mDMAPacket()
{
}

VIF::~VIF()
{
}

s64 VIF::executionStep(const ClockSource_t& clockSource)
{
	auto& VIF = getResources()->EE->VPU->VIF->VIF_UNITS[mVIFUnitIndex];

	// Check if VIF is stalled, do not do anything (FBRST.STC needs to be written to before we continue).
	if (isVIFStalled())
		return 1;

	// Check the FIFO queue for incoming DMA packet. Return if there is nothing to process.
	if (!checkIncomingDMAPacket())
		return 1;

	// We have an incoming DMA unit of data, now we must split it into 4 x 32-bit and process each one. // TODO: check wih pcsx2's code.
	for (auto& data : mDMAPacket.UW)
	{
		// Check the NUM register, to determine if we are continuing a VIFcode instruction instead of reading a VIFcode.
		if (VIF->NUM->getFieldValue(VifUnitRegister_NUM_t::Fields::NUM))
		{
		
		}
		else
		{
			// Set the current data as the VIFcode.
			mVIFcode.setValue(data);

			// Get the instruction info.
			VIFcodeInstructionInfo_t instruction = VIFcodeInstructionTable::getInstructionInfo(mVIFcode);

			// Process the VIFcode by calling the instruction handler.
			(this->*INSTRUCTION_TABLE[instruction.mBaseInfo->mImplementationIndex])();

			// If the I bit is set, we need to raise an interrupt after the whole VIF packet has been processed - set a context variable.

		}
	}


	// VIF has completed 1 cycle.
	return 1;
}

bool VIF::isVIFStalled() const
{
	auto& VIF = getResources()->EE->VPU->VIF->VIF_UNITS[mVIFUnitIndex];
	auto& STAT = VIF->STAT;

	// If any of the STAT.VSS, VFS, VIS, INT, ER0 or ER1 fields are set to 1, 
	//  then the VIF has stalled and needs to be reset by writing to FBRST.STC.
	if (STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::VSS)
		|| STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::VFS)
		|| STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::VIS)
		|| STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::INT)
		|| STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::ER0)
		|| STAT->getFieldValue(VifUnitRegister_STAT_t::Fields::ER1))
	{
		return true;
	}

	return false;
}

bool VIF::checkIncomingDMAPacket()
{
	throw std::runtime_error("Not implemented.");
}

void VIF::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("VIFcode CMD field was invalid! Please fix.");
}

void VIF::NOP()
{
}

void VIF::STCYCL()
{
}

void VIF::OFFSET()
{
}

void VIF::BASE()
{
}

void VIF::ITOP()
{
}

void VIF::STMOD()
{
}

void VIF::MSKPATH3()
{
}

void VIF::MARK()
{
}

void VIF::FLUSHE()
{
}

void VIF::FLUSH()
{
}

void VIF::FLUSHA()
{
}

void VIF::MSCAL()
{
}

void VIF::MSCNT()
{
}

void VIF::MSCALF()
{
}

void VIF::STMASK()
{
}

void VIF::STROW()
{
}

void VIF::STCOL()
{
}

void VIF::MPG()
{
}

void VIF::DIRECT()
{
}

void VIF::DIRECTHL()
{
}

void VIF::UNPACK_S_32()
{
}

void VIF::UNPACK_S_16()
{
}

void VIF::UNPACK_S_8()
{
}

void VIF::UNPACK_V2_32()
{
}

void VIF::UNPACK_V2_16()
{
}

void VIF::UNPACK_V2_8()
{
}

void VIF::UNPACK_V3_32()
{
}

void VIF::UNPACK_V3_16()
{
}

void VIF::UNPACK_V3_8()
{
}

void VIF::UNPACK_V4_32()
{
}

void VIF::UNPACK_V4_16()
{
}

void VIF::UNPACK_V4_8()
{
}

void VIF::UNPACK_V4_5()
{
}
