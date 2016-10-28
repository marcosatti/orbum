#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"


void IOPCoreInterpreter::LB()
{
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU() + imm;
	auto value = getMMUHandler()->readByteS(PS2VirtualAddress);

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeWordS(static_cast<s32>(value));
}

void IOPCoreInterpreter::LBU()
{
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU() + imm;
	auto value = getMMUHandler()->readByteU(PS2VirtualAddress);

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeWordU(static_cast<u32>(value));
}

void IOPCoreInterpreter::LH()
{
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU() + imm;
	auto value = getMMUHandler()->readHwordS(PS2VirtualAddress);

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeWordS(static_cast<s32>(value));
}

void IOPCoreInterpreter::LHU()
{
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU() + imm;
	auto value = getMMUHandler()->readHwordU(PS2VirtualAddress);

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeWordU(static_cast<u32>(value));
}

void IOPCoreInterpreter::LUI()
{
	// Rd = Imm << 16. No exceptions generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	destReg->writeWordS(static_cast<s32>(imm << 16));
}

void IOPCoreInterpreter::LW()
{
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU() + imm;
	auto value = getMMUHandler()->readWordS(PS2VirtualAddress);

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeWordS(static_cast<s32>(value));
}

void IOPCoreInterpreter::LWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWL is to be used with LWR, to read in a full 32-bit value.
	// LWL reads in the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LDR.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU() + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = getMMUHandler()->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

																// Check for MMU error and do not continue if true.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX >> MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) << MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask << MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeWordS(static_cast<s32>(static_cast<s32>((destReg->readWordU() & keepMask) | MSBValue))); // Calculate the new desination register value and write to it.
}

void IOPCoreInterpreter::LWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Unaligned memory read. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned read. LWR is to be used with LWL, to read in a full 32-bit value.
	// LWR reads in the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination register.
	// Note that the other bytes already in the register are not changed. They are changed through LWL.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = sourceReg->readWordU() + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = getMMUHandler()->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	// Check for MMU error and do not continue if true.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX << LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) >> LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask >> LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	destReg->writeWordS(static_cast<s32>(static_cast<s32>((destReg->readWordU() & keepMask) | LSBValue))); // Calculate the new desination register value and write to it.
}

void IOPCoreInterpreter::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU() + imm;
	getMMUHandler()->writeByteU(PS2VirtualAddress, source2Reg->readByteU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void IOPCoreInterpreter::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU() + imm;
	getMMUHandler()->writeHwordU(PS2VirtualAddress, source2Reg->readHwordU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void IOPCoreInterpreter::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU() + imm;
	getMMUHandler()->writeWordU(PS2VirtualAddress, source2Reg->readWordU());

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void IOPCoreInterpreter::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWL is to be used with SWR, to write a full 32-bit value.
	// SWL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWR.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU() + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWordU(); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeWordU(baseAddress, (getMMUHandler()->readWordU(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void IOPCoreInterpreter::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWR is to be used with SWL, to write a full 32-bit value.
	// SWR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWL.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU() + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWordU(); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeWordU(baseAddress, (getMMUHandler()->readWordU(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.

	 // Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

