#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/Types/EECore_COP0_Registers_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP0_BitfieldRegisters_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"

void EECoreInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_BREAK));
}

void EECoreInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_SYSTEMCALL));
}

void EECoreInterpreter::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) == imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) >= source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) >= imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) >= imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) >= source2Reg->readDwordU(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) < source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) < imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(getInstruction().getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) < imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordU(0) < source2Reg->readDwordU(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	s64 imm = static_cast<s64>(getInstruction().getIImmS());

	if (source1Reg->readDwordS(0) != imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed. However, still use the R5900->setBranchDelay* functions with cycles = 0.
	// ERET(). No exceptions.
	if (getVM()->getResources()->EE->EECore->COP0->Status->getFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL) == 1)
	{
		const u32 & pcValue = getVM()->getResources()->EE->EECore->COP0->ErrorEPC->getFieldValue(EECore_COP0RegisterErrorEPC_t::Fields::ErrorEPC);
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(EECore_COP0RegisterStatus_t::Fields::ERL, 0);
	}
	else
	{
		const u32 & pcValue = getVM()->getResources()->EE->EECore->COP0->EPC->getFieldValue(COP0RegisterEPC_t::Fields::EPC);
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getVM()->getResources()->EE->EECore->COP0->Status->setFieldValue(EECore_COP0RegisterStatus_t::Fields::EXL, 0);
	}
}
