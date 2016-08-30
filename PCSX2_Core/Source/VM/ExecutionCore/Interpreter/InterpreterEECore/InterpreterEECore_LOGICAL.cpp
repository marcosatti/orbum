#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

/*
Logical instruction family.
*/

void InterpreterEECore::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0) & source2Reg->readDwordU(0));
}

void InterpreterEECore::ANDI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	u64 imm = static_cast<u64>(getInstruction().getIImmU());

	destReg->writeDwordU(0, source1Reg->readDwordU(0) & imm);
}

void InterpreterEECore::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, ~(source1Reg->readDwordU(0) | source2Reg->readDwordU(0)));
}

void InterpreterEECore::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0) | source2Reg->readDwordU(0));
}

void InterpreterEECore::ORI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	s64 imm = static_cast<s64>(getInstruction().getIImmU());

	destReg->writeDwordU(0, source1Reg->readDwordU(0) | imm);
}

void InterpreterEECore::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0) ^ source2Reg->readDwordU(0));
}

void InterpreterEECore::XORI()
{
	// Rd = Rt XOR Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	u64 imm = static_cast<u64>(getInstruction().getIImmU());

	destReg->writeDwordU(0, source1Reg->readDwordU(0) ^ imm);
}

void InterpreterEECore::PAND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDwordU(i, source1Reg->readDwordU(i) & source2Reg->readDwordU(i));
	}
}

void InterpreterEECore::PNOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDwordU(i, ~(source1Reg->readDwordU(i) | source2Reg->readDwordU(i)));
	}
}

void InterpreterEECore::POR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDwordU(i, source1Reg->readDwordU(i) | source2Reg->readDwordU(i));
	}
}

void InterpreterEECore::PXOR()
{
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDwordU(i, source1Reg->readDwordU(i) ^ source2Reg->readDwordU(i));
	}
}
