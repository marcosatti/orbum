#include "stdafx.h"

#include "VM/VM.h"
#include "VM/Systems/EE/VPU/VIF/VIF_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VIF/VIF_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCores_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCoreRegisters_t.h"

VIF_s::VIF_s(VM * vm, u32 vifUnitIndex) :
	VMSystem_s(vm, vifUnitIndex == 0 ? System_t::VIF0 : System_t::VIF1),
	mVIFUnitIndex(vifUnitIndex),
	mDMAPacket(),
	mVIFcodeInstruction(0)
{
}

int VIF_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	return ticksAvailable; // not yet completed.

	auto& VIF = getVM()->getResources()->EE->VPU->VIF->VIF_CORES[mVIFUnitIndex];

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
		if (VIF->NUM->getFieldValue(VIFCoreRegister_NUM_t::Fields::NUM))
		{
		
		}
		else
		{
			// Set the current data as the VIFcode.
			mVIFcodeInstruction = data;

			// Process the VIFcode by calling the instruction handler.
			(this->*INSTRUCTION_TABLE[mVIFcodeInstruction.getInstructionInfo()->mImplementationIndex])();

			// If the I bit is set, we need to raise an interrupt after the whole VIF packet has been processed - set a context variable.

		}
	}


	// VIF has completed 1 cycle.
	return 1;
}

bool VIF_s::isVIFStalled() const
{
	auto& VIF = getVM()->getResources()->EE->VPU->VIF->VIF_CORES[mVIFUnitIndex];
	auto& STAT = VIF->STAT;

	// If any of the STAT.VSS, VFS, VIS, INT, ER0 or ER1 fields are set to 1, 
	//  then the VIF has stalled and needs to be reset by writing to FBRST.STC.
	if (STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::VSS)
		|| STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::VFS)
		|| STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::VIS)
		|| STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::INT)
		|| STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::ER0)
		|| STAT->getFieldValue(VIFCoreRegister_STAT_t::Fields::ER1))
	{
		return true;
	}

	return false;
}

bool VIF_s::checkIncomingDMAPacket()
{
	throw std::runtime_error("Not implemented.");
}

void VIF_s::INSTRUCTION_UNSUPPORTED()
{
	throw std::runtime_error("VIFcode CMD field was invalid! Please fix.");
}

void VIF_s::NOP()
{
}

void VIF_s::STCYCL()
{
}

void VIF_s::OFFSET()
{
}

void VIF_s::BASE()
{
}

void VIF_s::ITOP()
{
}

void VIF_s::STMOD()
{
}

void VIF_s::MSKPATH3()
{
}

void VIF_s::MARK()
{
}

void VIF_s::FLUSHE()
{
}

void VIF_s::FLUSH()
{
}

void VIF_s::FLUSHA()
{
}

void VIF_s::MSCAL()
{
}

void VIF_s::MSCNT()
{
}

void VIF_s::MSCALF()
{
}

void VIF_s::STMASK()
{
}

void VIF_s::STROW()
{
}

void VIF_s::STCOL()
{
}

void VIF_s::MPG()
{
}

void VIF_s::DIRECT()
{
}

void VIF_s::DIRECTHL()
{
}

void VIF_s::UNPACK_S_32()
{
}

void VIF_s::UNPACK_S_16()
{
}

void VIF_s::UNPACK_S_8()
{
}

void VIF_s::UNPACK_V2_32()
{
}

void VIF_s::UNPACK_V2_16()
{
}

void VIF_s::UNPACK_V2_8()
{
}

void VIF_s::UNPACK_V3_32()
{
}

void VIF_s::UNPACK_V3_16()
{
}

void VIF_s::UNPACK_V3_8()
{
}

void VIF_s::UNPACK_V4_32()
{
}

void VIF_s::UNPACK_V4_16()
{
}

void VIF_s::UNPACK_V4_8()
{
}

void VIF_s::UNPACK_V4_5()
{
}
