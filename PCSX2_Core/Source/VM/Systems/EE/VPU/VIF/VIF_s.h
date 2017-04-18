#pragma once

#include "Common/Global/Globals.h"

#include "VM/Types/VMSystem_s.h"

#include "Resources/EE/VPU/VIF/Types/VIFcodeInstruction_t.h"

/*
An implementation of the VIF channel system.
The VIF is responsible for processing and transfering data to the VU units, or optionally the GIF in the case of VIF1.

For each cycle @ BUSCLK, the VIF operates on 4 x 32-bits at a time, totaling the size of 1 DMA transfer unit of 128-bits.
*/
class VIF_s : public VMSystem_s
{
public:
	VIF_s(VM * vm, const int vifCoreIndex);
	virtual ~VIF_s() = default;

	/*
	Initalisation.
	*/
	void initalise() override;

	/*
	Check the FIFO queue and process data if available.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:

	/*
	Context of which VIF this system is processing.
	*/
	u32 mVIFUnitIndex;

	/*
	A temporary holder for a DMA packet currently being processed from the FIFO queue.
	*/
	u128 mDMAPacket;

	/*
	A holder for a VIFcode instruction.
	*/
	VIFcodeInstruction_t mVIFcodeInstruction;

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
	void(VIF_s::* INSTRUCTION_TABLE[Constants::EE::VPU::VIF::NUMBER_INSTRUCTIONS])() =
	{
		&VIF_s::INSTRUCTION_UNSUPPORTED,
		&VIF_s::NOP,
		&VIF_s::STCYCL,
		&VIF_s::OFFSET,
		&VIF_s::BASE,
		&VIF_s::ITOP,
		&VIF_s::STMOD,
		&VIF_s::MSKPATH3,
		&VIF_s::MARK,
		&VIF_s::FLUSHE,
		&VIF_s::FLUSH,
		&VIF_s::FLUSHA,
		&VIF_s::MSCAL,
		&VIF_s::MSCALF,
		&VIF_s::MSCNT,
		&VIF_s::STMASK,
		&VIF_s::STROW,
		&VIF_s::STCOL,
		&VIF_s::MPG,
		&VIF_s::DIRECT,
		&VIF_s::DIRECTHL,
		&VIF_s::UNPACK_S_32,
		&VIF_s::UNPACK_S_16,
		&VIF_s::UNPACK_S_8,
		&VIF_s::UNPACK_V2_32,
		&VIF_s::UNPACK_V2_16,
		&VIF_s::UNPACK_V2_8,
		&VIF_s::UNPACK_V3_32,
		&VIF_s::UNPACK_V3_16,
		&VIF_s::UNPACK_V3_8,
		&VIF_s::UNPACK_V4_32,
		&VIF_s::UNPACK_V4_16,
		&VIF_s::UNPACK_V4_8,
		&VIF_s::UNPACK_V4_5
	};

};