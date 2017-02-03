#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) & source2Reg->readDword(EE, 0));
}

void EECoreInterpreter::ANDI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getIRt()];
	u64 imm = static_cast<u64>(mInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) & imm);
}

void EECoreInterpreter::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, ~(source1Reg->readDword(EE, 0) | source2Reg->readDword(EE, 0)));
}

void EECoreInterpreter::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) | source2Reg->readDword(EE, 0));
}

void EECoreInterpreter::ORI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getIRt()];
	s64 imm = static_cast<s64>(mInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) | imm);
}

void EECoreInterpreter::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) ^ source2Reg->readDword(EE, 0));
}

void EECoreInterpreter::XORI()
{
	// Rd = Rt XOR Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getIRt()];
	u64 imm = static_cast<u64>(mInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) ^ imm);
}

void EECoreInterpreter::PAND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) & source2Reg->readDword(EE, i));
	}
}

void EECoreInterpreter::PNOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, ~(source1Reg->readDword(EE, i) | source2Reg->readDword(EE, i)));
	}
}

void EECoreInterpreter::POR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) | source2Reg->readDword(EE, i));
	}
}

void EECoreInterpreter::PXOR()
{
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) ^ source2Reg->readDword(EE, i));
	}
}
