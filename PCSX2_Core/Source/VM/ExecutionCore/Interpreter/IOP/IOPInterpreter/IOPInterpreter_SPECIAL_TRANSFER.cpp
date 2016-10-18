#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPMMUHandler/IOPMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCOP0/IOPCOP0_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/IOPExceptions_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/Types/IOPException_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

void IOPInterpreter::MFC0()
{
	if (!getVM()->getResources()->IOP->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->IOP->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(IOPException_t(IOPException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRt()];
	auto& sourceReg = getVM()->getResources()->IOP->COP0->Registers[getInstruction().getRRd()];

	destReg->writeWordU(static_cast<u32>(sourceReg->getRegisterValue()));
}

void IOPInterpreter::MTC0()
{
	if (!getVM()->getResources()->IOP->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->IOP->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(IOPException_t(IOPException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& sourceReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->COP0->Registers[getInstruction().getRRd()];

	destReg->setRegisterValue(sourceReg->readWordU());
}

void IOPInterpreter::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->R3000->HI;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPInterpreter::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->R3000->LO;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPInterpreter::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->IOP->R3000->HI;

	destReg->writeWordU(source1Reg->readWordU());
}

void IOPInterpreter::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->IOP->R3000->LO;

	destReg->writeWordU(source1Reg->readWordU());
}
