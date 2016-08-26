#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"


void InterpreterEECore::SB()
{
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;
	getMMUHandler()->writeByteU(PS2VirtualAddress, source2Reg->readByteU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SD()
{
	// MEM[UD] = Rt. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;
	getMMUHandler()->writeDwordU(PS2VirtualAddress, source2Reg->readDwordU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SDL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned write. SDL is to be used with SDR, to write a full 64-bit value.
	// SDL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in memory are not changed. They are changed through SDR.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU(0) + imm;
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = source2Reg->readDwordU(0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((8 - (offset + 1)) * 8); // A shift value used thoughout.
	u64 MSBMask = Constants::VALUE_U64_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u64 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeDwordU(baseAddress, (getMMUHandler()->readDwordU(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SDR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 8 byte boundary, but this instruction allows an unaligned write. SDR is to be used with SDL, to write a full 64-bit value.
	// SDR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in memory are not changed. They are changed through SDL.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x7); // Strip off the last 3 bits, making sure we are now aligned on a 8-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x7); // Get the value of the last 3 bits, which will be from 0 -> 7 indicating the byte offset within the 8-byte alignment.

	u64 alignedValue = source2Reg->readDwordU(0); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u64 LSBMask = Constants::VALUE_U64_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u64 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u64 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeDwordU(baseAddress, (getMMUHandler()->readDwordU(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SH()
{
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;
	getMMUHandler()->writeHwordU(PS2VirtualAddress, source2Reg->readHwordU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SW()
{
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;
	getMMUHandler()->writeWordU(PS2VirtualAddress, source2Reg->readWordU(0));

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
		
	}
}

void InterpreterEECore::SWL()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWL is to be used with SWR, to write a full 32-bit value.
	// SWL writes the most significant bytes (MSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWR.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 MSBShift = ((4 - (offset + 1)) * 8); // A shift value used thoughout.
	u32 MSBMask = Constants::VALUE_U32_MAX << MSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 MSBValue = (alignedValue & MSBMask) >> MSBShift; // Calculate the MSB value part.

	u32 keepMask = ~(MSBMask >> MSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeWordU(baseAddress, (getMMUHandler()->readWordU(baseAddress) & keepMask) | MSBValue); // Calculate the new desination register value and write to it.

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SWR()
{
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Unaligned memory write. Alignment occurs on an 4 byte boundary, but this instruction allows an unaligned write. SWR is to be used with SWL, to write a full 32-bit value.
	// SWR writes the least significant bytes (LSB's) depending on the virtual address offset, and stores them in the most significant part of the destination memory.
	// Note that the other bytes already in the register are not changed. They are changed through SWL.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 unalignedAddress = source1Reg->readWordU(0) + imm; // Get the unaligned virtual address.
	u32 baseAddress = unalignedAddress & ~static_cast<u32>(0x3); // Strip off the last 2 bits, making sure we are now aligned on a 4-byte boundary.
	u32 offset = unalignedAddress & static_cast<u32>(0x3); // Get the value of the last 2 bits, which will be from 0 -> 3 indicating the byte offset within the 4-byte alignment.

	u32 alignedValue = source2Reg->readWordU(baseAddress); // Get the full aligned value, but we only want the full value minus the offset number of bytes.

	u8 LSBShift = (offset * 8); // A shift value used thoughout.
	u32 LSBMask = Constants::VALUE_U32_MAX >> LSBShift; // Mask for getting rid of the unwanted bytes from the aligned value.
	u32 LSBValue = (alignedValue & LSBMask) << LSBShift; // Calculate the LSB value part.

	u32 keepMask = ~(LSBMask << LSBShift); // The keep mask is used to select the bytes in the register which we do not want to change - this mask will be AND with those bytes, while stripping away the other bytes about to be overriden.
	getMMUHandler()->writeWordU(baseAddress, (getMMUHandler()->readWordU(baseAddress) & keepMask) | LSBValue); // Calculate the new desination register value and write to it.
	
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SQ()
{
	// MEM[UQ] = Rd. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;

	getMMUHandler()->writeDwordU(PS2VirtualAddress, source2Reg->readDwordU(0));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
		return; // Return early, dont bother trying to write the second dword.
	}

	getMMUHandler()->writeDwordU(PS2VirtualAddress + 8, source2Reg->readDwordU(1));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

void InterpreterEECore::SWC1()
{
	// MEM[UW] = Ft. Address error or TLB error generated.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getIRt()]; // Ft
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = (source1Reg->readWordU(0) + imm);
	getMMUHandler()->writeWordU(PS2VirtualAddress, source2Reg->readWordU());

	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->ExceptionQueue->push(getMMUHandler()->getExceptionInfo());
	}
}

