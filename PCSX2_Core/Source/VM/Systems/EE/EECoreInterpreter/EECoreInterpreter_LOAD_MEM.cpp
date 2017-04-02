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
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"

void EECoreInterpreter_s::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s8>(mPhysicalMMU->readByte(getContext(), physicalAddress));
	destReg->writeDword(getContext(), 0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readByte(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, static_cast<u64>(value));
}

void EECoreInterpreter_s::LD()
{
	// Rd = MEM[UD]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s64>(mPhysicalMMU->readDword(getContext(), physicalAddress));
	destReg->writeDword(getContext(), 0, value);
}

void EECoreInterpreter_s::LDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UD] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readDword(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, (destReg->readDword(getContext(), 0) & (0x00FFFFFFFFFFFFFF >> shift)) | (value << (56 - shift)));
}

void EECoreInterpreter_s::LDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 7) << 3;
	u32 dwordAddress = (virtualAddress & 0xFFFFFFF8);

	u32 physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readDword(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, (destReg->readDword(getContext(), 0) & (0xFFFFFFFFFFFFFF00 << (56 - shift))) | (value >> shift));
}

void EECoreInterpreter_s::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s16>(mPhysicalMMU->readHword(getContext(), physicalAddress));
	destReg->writeDword(getContext(), 0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readHword(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, static_cast<u64>(value));
}

void EECoreInterpreter_s::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto imm = static_cast<s32>(mEECoreInstruction.getIImmS());

	s64 result = static_cast<s64>(imm << 16);

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s32>(mPhysicalMMU->readWord(getContext(), physicalAddress));
	destReg->writeDword(getContext(), 0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, static_cast<s64>(static_cast<s32>((destReg->readWord(getContext(), 0) & (0x00FFFFFF >> shift)) | (value << (24 - shift)))));
}

void EECoreInterpreter_s::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, static_cast<s64>(static_cast<s32>((destReg->readWord(getContext(), 0) & (0xFFFFFF00 << (24 - shift))) | (value >> shift))));
}

void EECoreInterpreter_s::LWU()
{
	// Rd = MEM[UW]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext(), 0) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(getContext(), physicalAddress);
	destReg->writeDword(getContext(), 0, static_cast<u64>(value));
}

void EECoreInterpreter_s::LQ()
{
	// Rd = MEM[UQ]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = (sourceReg->readWord(getContext(), 0) + imm);
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readQword(getContext(), physicalAddress);
	destReg->writeQword(getContext(), value);
}

void EECoreInterpreter_s::LWC1()
{
	// Ft = MEM[UQ]. Address error or TLB error generated.
	if (handleCOP1Usable())
		return;

	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = (sourceReg->readWord(getContext(), 0) + imm);
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(getContext(), physicalAddress);
	destReg->writeWord(getContext(), value);
}

void EECoreInterpreter_s::LQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
		return;

	auto& destReg = mVU0->VF[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	u32 virtualAddress = (sourceReg->readWord(getContext(), 0) + imm);
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readQword(getContext(), physicalAddress);
	destReg->writeQword(getContext(), value);
}