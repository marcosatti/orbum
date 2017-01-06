#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readByte(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<s64>(value));
}

void EECoreInterpreter::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readByte(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<u64>(value));
}

void EECoreInterpreter::LD()
{
	// Rd = MEM[UD]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readDword(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, value);
}

void EECoreInterpreter::LDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UD] = Rd. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned read. LDL is to be used with LDR, to read in a full 64-bit value.
	// LDL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = mMMUHandler->readDword(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	// Check for MMU error and do not continue if true.
	if (!checkNoMMUError())
        return;

	u8 MSBShift = ((8 - (offset + 1)) * 8); // A shift value used thoughout.
	u64 MSBMask = Constants::VALUE_U64_MAX >> MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 MSBValue = (alignedValue & MSBMask) << MSBShift; // Calculate the MSB value part.

	u64 keepMask = ~(MSBMask << MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	
	destReg->writeDword(Context_t::EE, 0, (destReg->readDword(Context_t::EE, 0) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.
}

void EECoreInterpreter::LDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned read. LDR is to be used with LDL, to read in a full 64-bit value.
	// LDR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDL.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = mMMUHandler->readDword(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.
	
	// Check for MMU error and do not continue if true.
	if (!checkNoMMUError())
        return;

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u64 LSBMask = Constants::VALUE_U64_MAX << LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 LSBValue = (alignedValue & LSBMask) >> LSBShift; // Calculate the LSB value part.

	u64 keepMask = ~(LSBMask >> LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDword(Context_t::EE, 0, (destReg->readDword(Context_t::EE, 0) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.
}

void EECoreInterpreter::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readHword(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<s64>(value));
}

void EECoreInterpreter::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readHword(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<u64>(value));
}

void EECoreInterpreter::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto imm = static_cast<s32>(mInstruction.getIImmS());

	s64 result = static_cast<s64>(imm << 16);

	destReg->writeDword(Context_t::EE, 0, result);
}

void EECoreInterpreter::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readWord(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<s64>(value));
}

void EECoreInterpreter::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWL is to be used with LWR, to read in a full 32-bit value.
	// LWL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = mMMUHandler->readWord(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	// Check for MMU error and do not continue if true.
	if (!checkNoMMUError())
        return;

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX >> MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) << MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask << MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDword(Context_t::EE, 0, static_cast<s64>(static_cast<s32>((destReg->readWord(Context_t::EE, 0) & keepMask) | MSBValue))); // Calculate the new desination register value and write to it.
}

void EECoreInterpreter::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWR is to be used with LWL, to read in a full 32-bit value.
	// LWR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LWL.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = mMMUHandler->readWord(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	// Check for MMU error and do not continue if true.
	if (!checkNoMMUError())
        return;

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX << LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) >> LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask >> LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeDword(Context_t::EE, 0, static_cast<s64>(static_cast<s32>((destReg->readWord(Context_t::EE, 0) & keepMask) | LSBValue))); // Calculate the new desination register value and write to it.
}

void EECoreInterpreter::LWU()
{
	// Rd = MEM[UW]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::EE, 0) + imm;
	auto value = mMMUHandler->readWord(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeDword(Context_t::EE, 0, static_cast<u64>(value));
}

void EECoreInterpreter::LQ()
{
	// Rd = MEM[UQ]. Address error or TLB error generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWord(Context_t::EE, 0) + imm) & (~static_cast<u32>(0xF)); // Strip the last 4 bits, as the access must be aligned (the documentation says to do this).
	// TODO: Im not sure if this is correct for big-endian.
	
	u128 value = mMMUHandler->readQword(PS2VirtualAddress);
	// Check for MMU error.
	if (!checkNoMMUError())
		return;
	else
		destReg->writeQword(Context_t::EE, value);
}

void EECoreInterpreter::LWC1()
{
	// Ft = MEM[UQ]. Address error or TLB error generated.
	if (!checkCOP1Usable())
		return;

	auto& destReg = getResources()->EE->EECore->FPU->FPR[mInstruction.getIRt()]; // Ft
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = (sourceReg->readWord(Context_t::EE, 0) + imm);
	auto value = mMMUHandler->readWord(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::EE, value);
}
