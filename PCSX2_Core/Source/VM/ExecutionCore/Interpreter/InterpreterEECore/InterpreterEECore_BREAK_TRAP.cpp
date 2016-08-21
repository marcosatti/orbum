#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_BREAK);
}

void InterpreterEECore::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_SYSTEMCALL);
}

void InterpreterEECore::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) == imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) >= source2Reg->readDwordS(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) >= imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) >= imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) >= source2Reg->readDwordU(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) < source2Reg->readDwordS(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) < imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) < imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) < source2Reg->readDwordU(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) != imm)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_TRAP);
}

void InterpreterEECore::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed. However, still use the R5900->setBranchDelay* functions with cycles = 0.
	// ERET()
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
