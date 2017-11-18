
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Bus/ByteBus.hpp"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/Iop/Core/RIopCore.h"
#include "Resources/Iop/Core/IopCoreR3000.h"

void IOPCoreInterpreter_s::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s8>(mByteMMU->read_ubyte(physicalAddress));
	destReg->write_uword(static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_ubyte(physicalAddress);
	destReg->write_uword(static_cast<uword>(value));
}

void IOPCoreInterpreter_s::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s16>(mByteMMU->read_uhword(physicalAddress));
	destReg->write_uword(static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uhword(physicalAddress);
	destReg->write_uword(static_cast<uword>(value));
}

void IOPCoreInterpreter_s::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto imm = static_cast<s32>(mIOPCoreInstruction.getIImmS());

	s32 result = imm << 16;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_uword(static_cast<s32>(value));
}

void IOPCoreInterpreter_s::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_uword((destReg->read_uword() & (0x00FFFFFF >> shift)) | (value << (24 - shift)));
}

void IOPCoreInterpreter_s::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword() + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_uword((destReg->read_uword() & (0xFFFFFF00 << (24 - shift))) | (value >> shift));
}

void IOPCoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_ubyte(physicalAddress, source2Reg->read_ubyte(0));
}

void IOPCoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uhword(physicalAddress, source2Reg->read_uhword(0));
}

void IOPCoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword() + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uword(physicalAddress, source2Reg->read_uword());
}

void IOPCoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword() + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_uword(physicalAddress, ((source2Reg->read_uword() >> (24 - shift))) | (value & (0xFFFFFF00 << shift))); 
}

void IOPCoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()]; // "Base"
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	const s16 imm = mIOPCoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword() + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_uword(physicalAddress, ((source2Reg->read_uword() << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

