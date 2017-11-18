
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, source1Reg->read_udword(0) & source2Reg->read_udword(0));
}

void EECoreInterpreter_s::ANDI()
{
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	udword imm = static_cast<udword>(mEECoreInstruction.getIImmU());

	destReg->write_udword(0, source1Reg->read_udword(0) & imm);
}

void EECoreInterpreter_s::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, ~(source1Reg->read_udword(0) | source2Reg->read_udword(0)));
}

void EECoreInterpreter_s::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, source1Reg->read_udword(0) | source2Reg->read_udword(0));
}

void EECoreInterpreter_s::ORI()
{
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	s64 imm = static_cast<s64>(mEECoreInstruction.getIImmU());

	destReg->write_udword(0, source1Reg->read_udword(0) | imm);
}

void EECoreInterpreter_s::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, source1Reg->read_udword(0) ^ source2Reg->read_udword(0));
}

void EECoreInterpreter_s::XORI()
{
	// Rd = Rt XOR Extended<udword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	udword imm = static_cast<udword>(mEECoreInstruction.getIImmU());

	destReg->write_udword(0, source1Reg->read_udword(0) ^ imm);
}

void EECoreInterpreter_s::PAND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->write_udword(i, source1Reg->read_udword(i) & source2Reg->read_udword(i));
	}
}

void EECoreInterpreter_s::PNOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->write_udword(i, ~(source1Reg->read_udword(i) | source2Reg->read_udword(i)));
	}
}

void EECoreInterpreter_s::POR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->write_udword(i, source1Reg->read_udword(i) | source2Reg->read_udword(i));
	}
}

void EECoreInterpreter_s::PXOR()
{
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		destReg->write_udword(i, source1Reg->read_udword(i) ^ source2Reg->read_udword(i));
	}
}
