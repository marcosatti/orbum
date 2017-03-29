#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter_s::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) & source2Reg->readDword(EE, 0));
}

void EECoreInterpreter_s::ANDI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	u64 imm = static_cast<u64>(mEECoreInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) & imm);
}

void EECoreInterpreter_s::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->writeDword(EE, 0, ~(source1Reg->readDword(EE, 0) | source2Reg->readDword(EE, 0)));
}

void EECoreInterpreter_s::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) | source2Reg->readDword(EE, 0));
}

void EECoreInterpreter_s::ORI()
{
	// Rd = Rt AND Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	s64 imm = static_cast<s64>(mEECoreInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) | imm);
}

void EECoreInterpreter_s::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) ^ source2Reg->readDword(EE, 0));
}

void EECoreInterpreter_s::XORI()
{
	// Rd = Rt XOR Extended<u64>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	u64 imm = static_cast<u64>(mEECoreInstruction.getIImmU());

	destReg->writeDword(EE, 0, source1Reg->readDword(EE, 0) ^ imm);
}

void EECoreInterpreter_s::PAND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) & source2Reg->readDword(EE, i));
	}
}

void EECoreInterpreter_s::PNOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, ~(source1Reg->readDword(EE, i) | source2Reg->readDword(EE, i)));
	}
}

void EECoreInterpreter_s::POR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) | source2Reg->readDword(EE, i));
	}
}

void EECoreInterpreter_s::PXOR()
{
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->writeDword(EE, i, source1Reg->readDword(EE, i) ^ source2Reg->readDword(EE, i));
	}
}
