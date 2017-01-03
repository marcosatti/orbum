#pragma once

#include "Common/Global/Globals.h"
#include "Common/Interfaces/VMExecutionCoreComponent.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/EE/VPU/VIF/Types/VIFcode_t.h"

/*
An implementation of the VIF channel system.

The VIF is responsible for processing and transfering data to the VU units, or optionally the GIF in the case of VIF1.

For each cycle @ BUSCLK, the VIF operates on 4 x 32-bits at a time, totaling the size of 1 DMA transfer unit of 128-bits.
*/
class VIF : public VMExecutionCoreComponent
{
public:
	explicit VIF(VMMain * vmMain, u32 vifUnitIndex);
	~VIF();

	/*
	Check the FIFO queue and process data if available.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

private:

	/*
	Context of which VIF this system is processing.
	*/
	const u32 mVIFUnitIndex;

	/*
	A temporary holder for a DMA packet currently being processed from the FIFO queue.
	*/
	u128 mDMAPacket;

	/*
	A holder for a VIFcode instruction.
	*/
	VIFcode_t mVIFcode;

	/*
	Checks if the VIF has stalled by looking at the STAT register fields.
	*/
	bool isVIFStalled() const;

	/*
	Check the FIFO queue for an incoming packet.
	Returns true if there is and sets mDMAPacket.
	*/
	bool checkIncomingDMAPacket();

	/*
	VIFcode handler functions.
	See EE Users Manual page 87 onwards.
	*/
	void INSTRUCTION_UNSUPPORTED();
	void NOP();
	void STCYCL();
	void OFFSET();
	void BASE();
	void ITOP();
	void STMOD();
	void MSKPATH3();
	void MARK();
	void FLUSHE();
	void FLUSH();
	void FLUSHA();
	void MSCAL();
	void MSCNT();
	void MSCALF();
	void STMASK();
	void STROW();
	void STCOL();
	void MPG();
	void DIRECT();
	void DIRECTHL();
	void UNPACK_S_32();
	void UNPACK_S_16();
	void UNPACK_S_8();
	void UNPACK_V2_32();
	void UNPACK_V2_16();
	void UNPACK_V2_8();
	void UNPACK_V3_32();
	void UNPACK_V3_16();
	void UNPACK_V3_8();
	void UNPACK_V4_32();
	void UNPACK_V4_16();
	void UNPACK_V4_8();
	void UNPACK_V4_5();

	/*
	Static arrays needed to call the appropriate VIFcode handler function.
	In total there are 34 unique instructions, based on the VIFcodeInstructionTable unique index.
	*/
	void(VIF::* INSTRUCTION_TABLE[PS2Constants::EE::VPU::VIF::NUMBER_INSTRUCTIONS])() =
	{
		&VIF::INSTRUCTION_UNSUPPORTED,
		&VIF::NOP,
		&VIF::STCYCL,
		&VIF::OFFSET,
		&VIF::BASE,
		&VIF::ITOP,
		&VIF::STMOD,
		&VIF::MSKPATH3,
		&VIF::MARK,
		&VIF::FLUSHE,
		&VIF::FLUSH,
		&VIF::FLUSHA,
		&VIF::MSCAL,
		&VIF::MSCALF,
		&VIF::MSCNT,
		&VIF::STMASK,
		&VIF::STROW,
		&VIF::STCOL,
		&VIF::MPG,
		&VIF::DIRECT,
		&VIF::DIRECTHL,
		&VIF::UNPACK_S_32,
		&VIF::UNPACK_S_16,
		&VIF::UNPACK_S_8,
		&VIF::UNPACK_V2_32,
		&VIF::UNPACK_V2_16,
		&VIF::UNPACK_V2_8,
		&VIF::UNPACK_V3_32,
		&VIF::UNPACK_V3_16,
		&VIF::UNPACK_V3_8,
		&VIF::UNPACK_V4_32,
		&VIF::UNPACK_V4_16,
		&VIF::UNPACK_V4_8,
		&VIF::UNPACK_V4_5
	};

};