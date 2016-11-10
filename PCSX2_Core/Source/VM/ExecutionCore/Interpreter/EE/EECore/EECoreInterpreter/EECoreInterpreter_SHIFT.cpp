#include "stdafx.h"

#include <bitset>

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"


/*
Shift instruction family.
*/

void EECoreInterpreter::DSRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeDwordS(0, source1Reg->readDwordS(0) >> shamt);
}

void EECoreInterpreter::DSLL()
{
	// Rd = Rt << shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeDwordU(0, source1Reg->readDwordU(0) << shamt);
}

void EECoreInterpreter::DSLL32()
{
	// Rd = Rt << shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() + 32;

	destReg->writeDwordU(0, source1Reg->readDwordU(0) << shamt);
}

void EECoreInterpreter::DSLLV()
{
	// Rd = Rt << Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x3F;

	destReg->writeDwordU(0, source1Reg->readDwordU(0) << shamt);
}

void EECoreInterpreter::DSRA32()
{
	// Rd = Rt >> shamt(32->61). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() + 32;

	destReg->writeDwordS(0, source1Reg->readDwordS(0) >> shamt);
}

void EECoreInterpreter::DSRAV()
{
	// Rd = Rt >> Rs (lowest 6 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x3F;

	destReg->writeDwordS(0, source1Reg->readDwordS(0) >> shamt);
}

void EECoreInterpreter::DSRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeDwordU(0, source1Reg->readDwordU(0) >> shamt);
}

void EECoreInterpreter::DSRL32()
{
	// Rd = Rt >> shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() + 32;

	destReg->writeDwordU(0, source1Reg->readDwordU(0) >> shamt);
}

void EECoreInterpreter::DSRLV()
{
	// Rd = Rt >> Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x3F;

	destReg->writeDwordU(0, source1Reg->readDwordU(0) >> shamt);
}

void EECoreInterpreter::SLL()
{
	// Rd = SignExtend<s64>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	s64 result = static_cast<s64>(source1Reg->readWordU(0) << shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SLLV()
{
	// Rd = SignExtend<s64>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	s64 result = static_cast<s64>(source1Reg->readWordU(0) << shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	s64 result = static_cast<s64>(source1Reg->readWordS(0) >> shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	s64 result = static_cast<s64>(source1Reg->readWordS(0) >> shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	s64 result = static_cast<s64>(source1Reg->readWordU(0) >> shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	s64 result = static_cast<s64>(source1Reg->readWordU(0) >> shamt);
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::PSLLH()
{
	// Rd = Rt << shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() & 0xF;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordU(i, source1Reg->readHwordU(i) << shamt);
	}
}

void EECoreInterpreter::PSLLVW()
{
	// Rd = SignExtend<s64>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u8 shamt = source2Reg->readWordU(i) & 0x1F;
		s64 result = static_cast<s64>(source1Reg->readWordU(i) << shamt);
		destReg->writeDwordS(i / 2, result);
	}
}

void EECoreInterpreter::PSLLW()
{
	// Rd = Rt << shamt. Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordU(i, source1Reg->readWordU(i) << shamt);
	}
}

void EECoreInterpreter::PSRAH()
{
	// Rd = Rt >> shamt(lowest 4 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() & 0xF;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) >> shamt);
	}
}

void EECoreInterpreter::PSRAVW()
{
	// Rd = SignExtend<s64>(Rt >> Rs (lowest 5 bits)). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u8 shamt = source2Reg->readWordU(i) & 0x1F;
		s64 result = static_cast<s64>(source1Reg->readWordS(i) >> shamt);
		destReg->writeDwordS(i / 2, result);
	}
}

void EECoreInterpreter::PSRAW()
{
	// Rd = Rt >> shamt. Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordS(i, source1Reg->readWordS(i) >> shamt);
	}
}

void EECoreInterpreter::PSRLH()
{
	// Rd = Rt >> shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt() & 0xF;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordU(i, source1Reg->readHwordU(i) >> shamt);
	}
}

void EECoreInterpreter::PSRLVW()
{
	// Rd = SignExtend<s64>(Rt >> Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u8 shamt = source2Reg->readWordU(i) & 0x1F;
		s64 result = static_cast<s64>(source1Reg->readWordU(i) >> shamt);
		destReg->writeDwordS(i / 2, result);
	}
}

void EECoreInterpreter::PSRLW()
{
	// Rd = Rt >> shamt. Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordU(i, source1Reg->readWordU(i) >> shamt);
	}
}

void EECoreInterpreter::QFSRV()
{
	// Rd (lower 128-bits) = (Rs || Rt)(256-bit concatenation) >> SA. Logical shift? Not specified, but assumed to be.
	// No Exceptions generated.
	// TODO: check this instruction... were they high when they created this???
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& SAReg = getVM()->getResources()->EE->EECore->R5900->SA;

	u32 shamt = SAReg->readWordU(); // From the docs it must be a multiple of bytes or halfwords, as you use the MTSAB or MTSAH instructions to write to the SA register.

	// Can use the STL class "bitset" to perform what we need... MUCH more cleaner than the old PCSX2 code.
	// This forms our 256-bit 'type' from 4 x 64-bits.
	std::bitset<256> result;
	(result |= source1Reg->readDwordU(0)) <<= 64;
	(result |= source1Reg->readDwordU(1)) <<= 64;
	(result |= source2Reg->readDwordU(0)) <<= 64;
	(result |= source2Reg->readDwordU(1));

	// Perform the right shift.
	result >>= shamt;

	// Extract the low-order 128-bit result value, 64-bits at a time (unsigned long long, guaranteed to be at least 64-bits), as that is the largest integral size available to the compiler. 
	// Store the extracted value into the destination register. Also need to create a temp bitset to store 64-bits into at one time. N must be the same size as the other bitset otherwise 
	// an error is thrown, but the extra bits are never used.
	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		std::bitset<256> temp64; 
		temp64 = result >> (64 * i);
		temp64 &= Constants::VALUE_U64_MAX;
		u64 resultInt = temp64.to_ullong();
		destReg->writeDwordU(i, resultInt);
	}
}