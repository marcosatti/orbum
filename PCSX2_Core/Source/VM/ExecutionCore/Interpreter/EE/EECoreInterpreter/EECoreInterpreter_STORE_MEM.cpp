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

void EECoreInterpreter::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;
	mMMUHandler->writeByte(PS2VirtualAddress, source2Reg->readByte(Context_t::EE, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SD()
{
	// MEM[UD] = Rt. Address error or TLB error generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;
	mMMUHandler->writeDword(PS2VirtualAddress, source2Reg->readDword(Context_t::EE, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned write. SDL is to be used with SDR, to write a full 64-bit value.
	// SDL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in memory are not changed. They are changed through SDR.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::EE, 0) + imm;
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = source2Reg->readDword(Context_t::EE, 0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((8 - (offset + 1)) * 8); // A shift value used thoughout.
	u64 MSBMask = Constants::VALUE_U64_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u64 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeDword(baseAddress, (mMMUHandler->readDword(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned write. SDR is to be used with SDL, to write a full 64-bit value.
	// SDR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in memory are not changed. They are changed through SDL.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = source2Reg->readDword(Context_t::EE, 0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u64 LSBMask = Constants::VALUE_U64_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u64 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeDword(baseAddress, (mMMUHandler->readDword(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;
	mMMUHandler->writeHword(PS2VirtualAddress, source2Reg->readHword(Context_t::EE, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;
	mMMUHandler->writeWord(PS2VirtualAddress, source2Reg->readWord(Context_t::EE, 0));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWL is to be used with SWR, to write a full 32-bit value.
	// SWL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWR.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWord(Context_t::EE, 0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeWord(baseAddress, (mMMUHandler->readWord(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWR is to be used with SWL, to write a full 32-bit value.
	// SWR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWL.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 unalignedAddress = source1Reg->readWord(Context_t::EE, 0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWord(Context_t::EE, 0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	mMMUHandler->writeWord(baseAddress, (mMMUHandler->readWord(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.
	
	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SQ()
{
	// MEM[UQ] = Rd. Address error or TLB error generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWord(Context_t::EE, 0) + imm;

	mMMUHandler->writeQword(PS2VirtualAddress, source2Reg->readQword(Context_t::EE));
	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

void EECoreInterpreter::SWC1()
{
	// MEM[UW] = Ft. Address error or TLB error generated.
	if (!checkCOP1Usable())
		return;

	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getIRt()]; // Ft
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()]; // "Base"
	const s16 imm = mInstruction.getIImmS();

	u32 PS2VirtualAddress = (source1Reg->readWord(Context_t::EE, 0) + imm);
	mMMUHandler->writeWord(PS2VirtualAddress, source2Reg->readWord(Context_t::EE));

	// Check for MMU error.
	if (!checkNoMMUError())
        return;
}

