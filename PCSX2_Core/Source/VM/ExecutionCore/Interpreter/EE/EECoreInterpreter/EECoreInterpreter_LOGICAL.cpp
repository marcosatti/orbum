#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"

/*
Logical instruction family.
*/

void EECoreInterpreter::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(0, source1Reg->readDword(0) & source2Reg->readDword(0));
}

void EECoreInterpreter::ANDI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	u64 imm = static_cast<u64>(mInstruction.getIImmU());

	destReg->writeDword(0, source1Reg->readDword(0) & imm);
}

void EECoreInterpreter::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(0, ~(source1Reg->readDword(0) | source2Reg->readDword(0)));
}

void EECoreInterpreter::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(0, source1Reg->readDword(0) | source2Reg->readDword(0));
}

void EECoreInterpreter::ORI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	s64 imm = static_cast<s64>(mInstruction.getIImmU());

	destReg->writeDword(0, source1Reg->readDword(0) | imm);
}

void EECoreInterpreter::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(0, source1Reg->readDword(0) ^ source2Reg->readDword(0));
}

void EECoreInterpreter::XORI()
{
	// Rd = Rt XOR Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	u64 imm = static_cast<u64>(mInstruction.getIImmU());

	destReg->writeDword(0, source1Reg->readDword(0) ^ imm);
}

void EECoreInterpreter::PAND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(i, source1Reg->readDword(i) & source2Reg->readDword(i));
	}
}

void EECoreInterpreter::PNOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(i, ~(source1Reg->readDword(i) | source2Reg->readDword(i)));
	}
}

void EECoreInterpreter::POR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(i, source1Reg->readDword(i) | source2Reg->readDword(i));
	}
}

void EECoreInterpreter::PXOR()
{
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(i, source1Reg->readDword(i) ^ source2Reg->readDword(i));
	}
}
