#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter_s::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s8>(mByteMMU->readByte(getContext(), physicalAddress));
	destReg->writeWord(getContext(), static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readByte(getContext(), physicalAddress);
	destReg->writeWord(getContext(), static_cast<u32>(value));
}

void IOPCoreInterpreter_s::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s16>(mByteMMU->readHword(getContext(), physicalAddress));
	destReg->writeWord(getContext(), static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readHword(getContext(), physicalAddress);
	destReg->writeWord(getContext(), static_cast<u32>(value));
}

void IOPCoreInterpreter_s::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto imm = static_cast<s32>(mIOPCoreInstruction.getIImmS());

	s32 result = imm << 16;

	destReg->writeWord(getContext(), result);
}

void IOPCoreInterpreter_s::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);
	destReg->writeWord(getContext(), static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);
	destReg->writeWord(getContext(), (destReg->readWord(getContext()) & (0x00FFFFFF >> shift)) | (value << (24 - shift)));
}

void IOPCoreInterpreter_s::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = sourceReg->readWord(getContext()) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);
	destReg->writeWord(getContext(), (destReg->readWord(getContext()) & (0xFFFFFF00 << (24 - shift))) | (value >> shift));
}

void IOPCoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeByte(getContext(), physicalAddress, source2Reg->readByte(getContext(), 0));
}

void IOPCoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeHword(getContext(), physicalAddress, source2Reg->readHword(getContext(), 0));
}

void IOPCoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext()) + imm;
	u32 physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, source2Reg->readWord(getContext()));
}

void IOPCoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext()) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, ((source2Reg->readWord(getContext()) >> (24 - shift))) | (value & (0xFFFFFF00 << shift))); 
}

void IOPCoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	u32 virtualAddress = source1Reg->readWord(getContext()) + imm;
	u32 shift = (virtualAddress & 3) << 3;
	u32 wordAddress = (virtualAddress & 0xFFFFFFFC);

	u32 physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->readWord(getContext(), physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->writeWord(getContext(), physicalAddress, ((source2Reg->readWord(getContext()) << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

