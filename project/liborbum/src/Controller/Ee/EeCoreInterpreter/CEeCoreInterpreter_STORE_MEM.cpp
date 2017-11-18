
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Bus/ByteBus.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Vpu/VuCores.hpp"

void EECoreInterpreter_s::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_ubyte(physicalAddress, source2Reg->read_ubyte(0));
}

void EECoreInterpreter_s::SD()
{
	// MEM[UD] = Rt. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_udword(physicalAddress, source2Reg->read_udword(0));
}

void EECoreInterpreter_s::SDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword shift = (virtualAddress & 7) << 3;
	uword dwordAddress = (virtualAddress & 0xFFFFFFF8);

	uword physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_udword(physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_udword(physicalAddress, ((source2Reg->read_udword(0) >> (56 - shift))) | (value & (0xFFFFFFFFFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword shift = (virtualAddress & 7) << 3;
	uword dwordAddress = (virtualAddress & 0xFFFFFFF8);

	uword physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_udword(physicalAddress);

	if (getPhysicalAddress(dwordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_udword(physicalAddress, ((source2Reg->read_udword(0) << shift) | (value & (0x00FFFFFFFFFFFFFF >> (56 - shift)))));
}

void EECoreInterpreter_s::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uhword(physicalAddress, source2Reg->read_uhword(0));
}

void EECoreInterpreter_s::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uword(physicalAddress, source2Reg->read_uword(0));
}

void EECoreInterpreter_s::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_uword(physicalAddress, ((source2Reg->read_uword(0) >> (24 - shift))) | (value & (0xFFFFFF00 << shift)));
}

void EECoreInterpreter_s::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);

	if (getPhysicalAddress(wordAddress, WRITE, physicalAddress)) // Need to get phy address again, check for write conditions.
		return;

	mByteMMU->write_uword(physicalAddress, ((source2Reg->read_uword(0) << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

void EECoreInterpreter_s::SQ()
{
	// MEM[UQ] = Rd. Address error or TLB error generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uqword(physicalAddress, source2Reg->read_uqword());
}

void EECoreInterpreter_s::SWC1()
{
	// MEM[UW] = Ft. Address error or TLB error generated.
	if (handleCOP1Usable())
		return;

	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = (source1Reg->read_uword(0) + imm);
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uword(physicalAddress, source2Reg->read_uword());
}

void EECoreInterpreter_s::SQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
		return;

	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	auto& source2Reg = mVU0->VF[mEECoreInstruction.rt()];
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = source1Reg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, WRITE, physicalAddress))
		return;

	mByteMMU->write_uqword(physicalAddress, source2Reg->read_uqword());
}