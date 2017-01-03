#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"


void IOPCoreInterpreter::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::IOP) + imm;
	auto value = static_cast<s8>(mMMUHandler->readByte(PS2VirtualAddress));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::IOP) + imm;
	auto value = mMMUHandler->readByte(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::IOP, static_cast<u32>(value));
}

void IOPCoreInterpreter::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::IOP) + imm;
	auto value = static_cast<s16>(mMMUHandler->readHword(PS2VirtualAddress));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::IOP) + imm;
	auto value = mMMUHandler->readHword(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::IOP, static_cast<u32>(value));
}

void IOPCoreInterpreter::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto imm = static_cast<s32>(mInstruction.getIImmS());

	s32 result = imm << 16;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWord(Context_t::IOP) + imm;
	auto value = mMMUHandler->readWord(PS2VirtualAddress);

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
	else
		destReg->writeWord(Context_t::IOP, static_cast<s32>(value));
}

void IOPCoreInterpreter::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWL is to be used with LWR, to read in a full 32-bit value.
	// LWL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::IOP) + imm; // Get the unaligned virtual address.
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
	destReg->writeWord(Context_t::IOP, static_cast<s32>(static_cast<s32>((destReg->readWord(Context_t::IOP) & keepMask) | MSBValue))); // Calculate the new desination register value and write to it.
}

void IOPCoreInterpreter::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWR is to be used with LWL, to read in a full 32-bit value.
	// LWR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LWL.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = sourceReg->readWord(Context_t::IOP) + imm; // Get the unaligned virtual address.
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
	destReg->writeWord(Context_t::IOP, static_cast<s32>(static_cast<s32>((destReg->readWord(Context_t::IOP) & keepMask) | LSBValue))); // Calculate the new desination register value and write to it.
}

void IOPCoreInterpreter::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::IOP) + imm;
	mMMUHandler->writeByte(PS2VirtualAddress, source2Reg->readByte(Context_t::IOP, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void IOPCoreInterpreter::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::IOP) + imm;
	mMMUHandler->writeHword(PS2VirtualAddress, source2Reg->readHword(Context_t::IOP, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void IOPCoreInterpreter::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::IOP) + imm;
	mMMUHandler->writeWord(PS2VirtualAddress, source2Reg->readWord(Context_t::IOP));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void IOPCoreInterpreter::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWL is to be used with SWR, to write a full 32-bit value.
	// SWL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWR.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::IOP) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWord(Context_t::IOP); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeWord(baseAddress, (mMMUHandler->readWord(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void IOPCoreInterpreter::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWR is to be used with SWL, to write a full 32-bit value.
	// SWR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWL.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::IOP) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWord(Context_t::IOP); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeWord(baseAddress, (mMMUHandler->readWord(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.

	 // Check for MMU error.
	if (!checkNoMMUError())
        return;
}

