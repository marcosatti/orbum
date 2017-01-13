#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Tables/EECoreSyscallTable/EECoreSyscallTable.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

void EECoreInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t::EX_BREAK);
}

void EECoreInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t::EX_SYSTEMCALL);

#if DEBUG_LOG_SYSCALLS
	// Debug print the syscall mnemonic.
	// The convention is to store the syscall number in register $v1 ($3), then use the syscall instruction (the 'code' field within the syscall instruction is apparently unused).
	// When the syscall number is loaded into $v1, it is done so through
	//   ADDIU $v1, $0, number.
	// If the 16-bit 'syscall number' above has the sign bit set (negative), the EE OS will first make it unsigned then call the handler with the (i) prefix... TODO: not sure what the differnece is.
	// The EE OS only defines handlers for syscall numbers 0 -> 127 (128 total). 
	u8 index = getResources()->EE->EECore->R5900->GPR[3]->readByte(Context_t::EE, 0);
	logDebug("EECore Syscall, number %d (%s).", index, EECoreSyscallTable::getSyscallMnemonic(index));
#endif
}

void EECoreInterpreter::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(Context_t::EE, 0));

	if (source1Val == source2Val)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<s64>(mInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Val == imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(Context_t::EE, 0));

	if (source1Val >= source2Val)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<s64>(mInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Val >= imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<u64>(static_cast<s64>(mInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto source1Val = static_cast<u64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Val >= imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<u64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<u64>(source2Reg->readDword(Context_t::EE, 0));

	if (source1Val >= source2Val)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(Context_t::EE, 0));

	if (source1Val < source2Val)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<s64>(mInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Val < imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<u64>(static_cast<s64>(mInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	auto source1Val = static_cast<u64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Reg->readDword(Context_t::EE, 0) < imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDword(Context_t::EE, 0) < source2Reg->readDword(Context_t::EE, 0))
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(Context_t::EE, 0));

	if (source1Val != source2Val)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = static_cast<s64>(mInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));

	if (source1Val != imm)
		Exceptions->setException(EECoreException_t::EX_TRAP);
}

void EECoreInterpreter::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed. However, still use the BD->setBranchDelay* functions to trigger immediately next cycle.
	// TODO: might need to just set PC directly... not sure how this plays out if an interrupt were to happen on the next cycle.
	// ERET(). No exceptions.
	if (getResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL) > 0)
	{
		const u32 & pcValue = getResources()->EE->EECore->COP0->ErrorEPC->readWord(Context_t::EE);
		getResources()->EE->EECore->R5900->BD->setBranchDelayPCAbsolute(pcValue, 1);
		getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 0);
	}
	else
	{
		const u32 & pcValue = getResources()->EE->EECore->COP0->EPC->readWord(Context_t::EE);
		getResources()->EE->EECore->R5900->BD->setBranchDelayPCAbsolute(pcValue, 1);
		getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::EXL, 0);
	}
}
