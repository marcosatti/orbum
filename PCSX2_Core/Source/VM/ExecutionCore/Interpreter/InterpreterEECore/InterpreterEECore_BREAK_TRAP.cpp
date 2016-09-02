#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_BREAK));
}

void InterpreterEECore::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_SYSTEMCALL));
}

void InterpreterEECore::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) == imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) >= source2Reg->readDwordS(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) >= imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) >= imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) >= source2Reg->readDwordU(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) < source2Reg->readDwordS(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) < imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) < imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) < source2Reg->readDwordU(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& ExceptionQueue = getVM()->getResources()->EE->EECore->Exceptions->ExceptionQueue;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) != imm)
		ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void InterpreterEECore::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed. However, still use the R5900->setBranchDelay* functions with cycles = 0.
	// ERET(). No exceptions.
	if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(RegisterStatus_t::Fields::ERL) == 1)
	{
		const u32 & pcValue = getVM()->getResources()->EE->EECore->COP0->ErrorEPC->getFieldValue(RegisterErrorEPC_t::Fields::ErrorEPC);
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::ERL, 0);
	}
	else
	{
		const u32 & pcValue = getVM()->getResources()->EE->EECore->COP0->EPC->getFieldValue(RegisterEPC_t::Fields::EPC);
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(RegisterStatus_t::Fields::EXL, 0);
	}
}
