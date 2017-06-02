#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

void EECoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeByte(getContext(), physicalAddress, source2Reg->readByte(getContext(), 0));
}

void EECoreInterpreter_s::SD()
{
	// MEM[UD] = Rt. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeDword(getContext(), physicalAddress, source2Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::SDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readDword(getContext(), physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeDword(getContext(), physicalAddress, ((source2Reg->readDword(getContext(), 0) >> (56 - shift))) | (value & (0xFFFFFFFFFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readDword(getContext(), physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeDword(getContext(), physicalAddress, ((source2Reg->readDword(getContext(), 0) << shift) | (value & (0x00FFFFFFFFFFFFFF >> (56 - shift)))));
}

void EECoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeHword(getContext(), physicalAddress, source2Reg->readHword(getContext(), 0));
}

void EECoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, source2Reg->readWord(getContext(), 0));
}

void EECoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, ((source2Reg->readWord(getContext(), 0) >> (24 - shift))) | (value & (0xFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, ((source2Reg->readWord(getContext(), 0) << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

void EECoreInterpreter_s::SQ()
{
	// MEM[UQ] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeQword(getContext(), physicalAddress, source2Reg->readQword(getContext()));
}

void EECoreInterpreter_s::SWC1()
{
	// MEM[UW] = Ft. Address error or TLB error generated.
	if (handleCOP1Usable())
		return;

	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = (source1Reg->readWord(getContext(), 0) + imm);
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, source2Reg->readWord(getContext()));
}

void EECoreInterpreter_s::SQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
		return;

	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mVU0->VF[mEECoreInstruction.getRt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeQword(getContext(), physicalAddress, source2Reg->readQword(getContext()));
}