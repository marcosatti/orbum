
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Bus/ByteBus.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Vpu/VuCores.hpp"

void EECoreInterpreter_s::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s8>(mByteMMU->read_ubyte(physicalAddress));
	destReg->write_udword(0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_ubyte(physicalAddress);
	destReg->write_udword(0, static_cast<udword>(value));
}

void EECoreInterpreter_s::LD()
{
	// Rd = MEM[UD]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s64>(mByteMMU->read_udword(physicalAddress));
	destReg->write_udword(0, value);
}

void EECoreInterpreter_s::LDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UD] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword shift = (virtualAddress & 7) << 3;
	uword dwordAddress = (virtualAddress & 0xFFFFFFF8);

	uword physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_udword(physicalAddress);
	destReg->write_udword(0, (destReg->read_udword(0) & (0x00FFFFFFFFFFFFFF >> shift)) | (value << (56 - shift)));
}

void EECoreInterpreter_s::LDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword shift = (virtualAddress & 7) << 3;
	uword dwordAddress = (virtualAddress & 0xFFFFFFF8);

	uword physicalAddress;
	if (getPhysicalAddress(dwordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_udword(physicalAddress);
	destReg->write_udword(0, (destReg->read_udword(0) & (0xFFFFFFFFFFFFFF00 << (56 - shift))) | (value >> shift));
}

void EECoreInterpreter_s::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s16>(mByteMMU->read_uhword(physicalAddress));
	destReg->write_udword(0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uhword(physicalAddress);
	destReg->write_udword(0, static_cast<udword>(value));
}

void EECoreInterpreter_s::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto imm = static_cast<s32>(mEECoreInstruction.getIImmS());

	s64 result = static_cast<s64>(imm << 16);

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = static_cast<s32>(mByteMMU->read_uword(physicalAddress));
	destReg->write_udword(0, static_cast<s64>(value));
}

void EECoreInterpreter_s::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_udword(0, static_cast<s64>(static_cast<s32>((destReg->read_uword(0) & (0x00FFFFFF >> shift)) | (value << (24 - shift)))));
}

void EECoreInterpreter_s::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword shift = (virtualAddress & 3) << 3;
	uword wordAddress = (virtualAddress & 0xFFFFFFFC);

	uword physicalAddress;
	if (getPhysicalAddress(wordAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_udword(0, static_cast<s64>(static_cast<s32>((destReg->read_uword(0) & (0xFFFFFF00 << (24 - shift))) | (value >> shift))));
}

void EECoreInterpreter_s::LWU()
{
	// Rd = MEM[UW]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = sourceReg->read_uword(0) + imm;
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_udword(0, static_cast<udword>(value));
}

void EECoreInterpreter_s::LQ()
{
	// Rd = MEM[UQ]. Address error or TLB error generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = (sourceReg->read_uword(0) + imm);
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uqword(physicalAddress);
	destReg->write_uqword(value);
}

void EECoreInterpreter_s::LWC1()
{
	// Ft = MEM[UQ]. Address error or TLB error generated.
	if (handleCOP1Usable())
		return;

	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = (sourceReg->read_uword(0) + imm);
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uword(physicalAddress);
	destReg->write_uword(value);
}

void EECoreInterpreter_s::LQC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (handleCOP2Usable())
		return;

	auto& destReg = mVU0->VF[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "Base"
	const s16 imm = mEECoreInstruction.getIImmS();

	uword virtualAddress = (sourceReg->read_uword(0) + imm);
	uword physicalAddress;
	if (getPhysicalAddress(virtualAddress, READ, physicalAddress))
		return;

	auto value = mByteMMU->read_uqword(physicalAddress);
	destReg->write_uqword(value);
}