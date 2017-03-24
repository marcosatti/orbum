#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"

void EECoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeByte(EE, physicalAddress, source2Reg->readByte(EE, 0));
}

void EECoreInterpreter_s::SD()
{
	// MEM[UD] = Rt. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeDword(EE, physicalAddress, source2Reg->readDword(EE, 0));
}

void EECoreInterpreter_s::SDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readDword(EE, physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeDword(EE, physicalAddress, ((source2Reg->readDword(EE, 0) >> (56 - shift))) | (value & (0xFFFFFFFFFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readDword(EE, physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeDword(EE, physicalAddress, ((source2Reg->readDword(EE, 0) << shift) | (value & (0x00FFFFFFFFFFFFFF >> (56 - shift)))));
}

void EECoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeHword(EE, physicalAddress, source2Reg->readHword(EE, 0));
}

void EECoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeWord(EE, physicalAddress, source2Reg->readWord(EE, 0));
}

void EECoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(EE, physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeWord(EE, physicalAddress, ((source2Reg->readWord(EE, 0) >> (24 - shift))) | (value & (0xFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(EE, physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeWord(EE, physicalAddress, ((source2Reg->readWord(EE, 0) << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

void EECoreInterpreter_s::SQ()
{
	// MEM[UQ] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeQword(EE, physicalAddress, source2Reg->readQword(EE));
}

void EECoreInterpreter_s::SWC1()
{
	// MEM[UW] = Ft. Address error or TLB error generated.
	if (handleCOP1Usable())
		return;

	auto& source2Reg = mEECore->FPU->FPR[mInstruction.getIRt()]; // Ft
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = (source1Reg->readWord(EE, 0) + imm);
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeWord(EE, physicalAddress, source2Reg->readWord(EE));
}

void EECoreInterpreter_s::SQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
		return;

	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mVU0->VF[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(EE, 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeQword(EE, physicalAddress, source2Reg->readQword(EE));
}