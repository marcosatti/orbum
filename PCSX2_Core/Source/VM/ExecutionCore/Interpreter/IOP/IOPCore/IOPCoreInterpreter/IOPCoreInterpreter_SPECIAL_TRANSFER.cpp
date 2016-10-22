#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreCOP0/IOPCoreCOP0_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/Types/IOPCoreException_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

void IOPCoreInterpreter::MFC0()
{
	if (!getVM()->getResources()->IOP->IOPCore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(IOPCoreException_t(IOPCoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->COP0->Registers[getInstruction().getRRd()];

	destReg->writeWordU(static_cast<u32>(sourceReg->getRegisterValue()));
}

void IOPCoreInterpreter::MTC0()
{
	if (!getVM()->getResources()->IOP->IOPCore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(IOPCoreException_t(IOPCoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->COP0->Registers[getInstruction().getRRd()];

	destReg->setRegisterValue(sourceReg->readWordU());
}

void IOPCoreInterpreter::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->HI;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPCoreInterpreter::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->LO;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPCoreInterpreter::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->HI;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPCoreInterpreter::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->LO;

	destReg->writeWordU(source1Reg->readWordU());
}
