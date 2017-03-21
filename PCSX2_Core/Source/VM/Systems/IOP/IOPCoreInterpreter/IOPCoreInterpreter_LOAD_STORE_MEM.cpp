#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter_s::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s8>(mPhysicalMMU->readByte(IOP, physicalAddress));
	destReg->writeWord(IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readByte(IOP, physicalAddress);
	destReg->writeWord(IOP, static_cast<u32>(value));
}

void IOPCoreInterpreter_s::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s16>(mPhysicalMMU->readHword(IOP, physicalAddress));
	destReg->writeWord(IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readHword(IOP, physicalAddress);
	destReg->writeWord(IOP, static_cast<u32>(value));
}

void IOPCoreInterpreter_s::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto imm = static_cast<s32>(mInstruction.getIImmS());

	s32 result = imm << 16;

	destReg->writeWord(IOP, result);
}

void IOPCoreInterpreter_s::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(IOP, physicalAddress);
	destReg->writeWord(IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(IOP, physicalAddress);
	destReg->writeWord(IOP, (destReg->readWord(IOP) & (0x00FFFFFF >> shift)) | (value << (24 - shift)));
}

void IOPCoreInterpreter_s::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(IOP) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(IOP, physicalAddress);
	destReg->writeWord(IOP, (destReg->readWord(IOP) & (0xFFFFFF00 << (24 - shift))) | (value >> shift));
}

void IOPCoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeByte(IOP, physicalAddress, source2Reg->readByte(IOP, 0));
}

void IOPCoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeHword(IOP, physicalAddress, source2Reg->readHword(IOP, 0));
}

void IOPCoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(IOP) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mPhysicalMMU->writeWord(IOP, physicalAddress, source2Reg->readWord(IOP));
}

void IOPCoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(IOP) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(IOP, physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeWord(IOP, physicalAddress, ((source2Reg->readWord(IOP) >> (24 - shift))) | (value & (0xFFFFFF00 << shift))); 
}

void IOPCoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(IOP) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mPhysicalMMU->readWord(IOP, physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mPhysicalMMU->writeWord(IOP, physicalAddress, ((source2Reg->readWord(IOP) << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

