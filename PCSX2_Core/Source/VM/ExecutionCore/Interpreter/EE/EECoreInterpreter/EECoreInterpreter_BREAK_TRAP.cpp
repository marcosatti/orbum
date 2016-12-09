#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"
#include "Common/Types/MIPSCoprocessor/COP0Registers_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

void EECoreInterpreter::BREAK()
{
	// EXCEPTION(BREAKPOINT)
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_BREAK));
}

void EECoreInterpreter::SYSCALL()
{
	// EXCEPTION(SYSCALL)
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_SYSTEMCALL));
}

void EECoreInterpreter::TEQ()
{
	// TRAP_EXCEPTION(Rs == Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TEQI()
{
	// TRAP_EXCEPTION(Rs == imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	s64 imm = static_cast<s64>(mInstruction.getIImmS());

	if (source1Reg->readDwordS(0) == imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGE()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordS(0) >= source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEI()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	s64 imm = static_cast<s64>(mInstruction.getIImmS());

	if (source1Reg->readDwordS(0) >= imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEIU()
{
	// TRAP_EXCEPTION(Rs >= imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(mInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) >= imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TGEU()
{
	// TRAP_EXCEPTION(Rs >= Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordU(0) >= source2Reg->readDwordU(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLT()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordS(0) < source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTI()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	s64 imm = static_cast<s64>(mInstruction.getIImmS());

	if (source1Reg->readDwordS(0) < imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTIU()
{
	// TRAP_EXCEPTION(Rs < imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	u64 imm = static_cast<u64>(static_cast<s64>(mInstruction.getIImmS())); // Sign-extend first, then treat as unsigned. This is according to the docs.

	if (source1Reg->readDwordU(0) < imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TLTU()
{
	// TRAP_EXCEPTION(Rs < Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordU(0) < source2Reg->readDwordU(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TNE()
{
	// TRAP_EXCEPTION(Rs != Rt).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::TNEI()
{
	// TRAP_EXCEPTION(Rs != imm).
	auto& Exceptions = getResources()->EE->EECore->Exceptions;
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	s64 imm = static_cast<s64>(mInstruction.getIImmS());

	if (source1Reg->readDwordS(0) != imm)
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_TRAP));
}

void EECoreInterpreter::ERET()
{
	// ERET is an outlier, where it does not cause a branch delay instruction to be executed. However, still use the R5900->setBranchDelay* functions with cycles = 0.
	// ERET(). No exceptions.
	if (getResources()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::ERL) == 1)
	{
		const u32 & pcValue = getResources()->EE->EECore->COP0->ErrorEPC->getFieldValue(EECoreCOP0Register_ErrorEPC_t::Fields::ErrorEPC);
		getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::ERL, 0);
	}
	else
	{
		const u32 & pcValue = getResources()->EE->EECore->COP0->EPC->getFieldValue(COP0RegisterEPC_t::Fields::EPC);
		getResources()->EE->EECore->R5900->setBranchDelayPCTarget(pcValue, 0);
		getResources()->EE->EECore->COP0->Status->setFieldValue(EECoreCOP0Register_Status_t::Fields::EXL, 0);
	}
}
