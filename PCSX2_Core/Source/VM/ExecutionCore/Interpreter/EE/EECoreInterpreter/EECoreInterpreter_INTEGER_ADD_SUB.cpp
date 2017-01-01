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
Integer Addition/Subtraction instruction family.
*/

void EECoreInterpreter::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (!checkNoOverOrUnderflow32(source1Val, source2Val))
        return;
	
	destReg->writeDword(0, result);
}

void EECoreInterpreter::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
	if (!checkNoOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(0));
	s64 result = sourceVal + imm;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));
	s64 result = source1Val + source2Val;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::DADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (!checkNoOverOrUnderflow64(source1Val, source2Val))
        return;
		
	destReg->writeDword(0, result);
}

void EECoreInterpreter::DADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->readDword(0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
    if (!checkNoOverOrUnderflow64(sourceVal, imm))
        return;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::DADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->readDword(0));
	s64 result = sourceVal + imm;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::DADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(0));
	s64 result = source1Val + source2Val;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::DSUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (!checkNoOverOrUnderflow64(source1Val, source2Val))
		return;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::DSUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(0));
	s64 result = source1Val - source2Val;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (!checkNoOverOrUnderflow32(source1Val, source2Val))
		return;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));
	s64 result = source1Val - source2Val;

	destReg->writeDword(0, result);
}

void EECoreInterpreter::PADDB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(i));
		s8 result = source1Val + source2Val;
		destReg->writeByte(i, result);
	}
}

void EECoreInterpreter::PADDH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++) 
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s16 result = source1Val + source2Val;
		destReg->writeHword(i, result);
	}
}

void EECoreInterpreter::PADDSB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(i));
		s16 result = source1Val + source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByte(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByte(i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByte(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter::PADDSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s32 result = source1Val + source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHword(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHword(i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHword(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter::PADDSW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));
		s64 result = source1Val + source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWord(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWord(i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWord(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter::PADDUB()
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u8>(source1Reg->readByte(i));
		auto source2Val = static_cast<u8>(source2Reg->readByte(i));
		u16 result = source1Val + source2Val;

		if (result > Constants::VALUE_U8_MAX)
			destReg->writeByte(i, Constants::VALUE_U8_MAX);
		else
			destReg->writeByte(i, static_cast<u8>(result));
	}
}

void EECoreInterpreter::PADDUH()
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u16>(source1Reg->readHword(i));
		auto source2Val = static_cast<u16>(source2Reg->readHword(i));
		u32 result = source1Val + source2Val;

		if (result > Constants::VALUE_U16_MAX)
			destReg->writeHword(i, Constants::VALUE_U16_MAX);
		else
			destReg->writeHword(i, static_cast<u16>(result));
	}
}

void EECoreInterpreter::PADDUW()
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(i));
		u64 result = source1Val + source2Val;

		if (result > Constants::VALUE_U32_MAX)
			destReg->writeWord(i, Constants::VALUE_U32_MAX);
		else
			destReg->writeWord(i, static_cast<u32>(result));
	}
}

void EECoreInterpreter::PADDW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));
		s32 result = source1Val + source2Val;
		destReg->writeWord(i, result);
	}
}

void EECoreInterpreter::PADSBH()
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s16 result = source1Val - source2Val;
		destReg->writeHword(i, result);
	}
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s16 result = source1Val + source2Val;
		destReg->writeHword(i, result);
	}
}

void EECoreInterpreter::PSUBB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(i));
		s8 result = source1Val - source2Val;
		destReg->writeByte(i, result);
	}
}

void EECoreInterpreter::PSUBH()
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s16 result = source1Val - source2Val;
		destReg->writeHword(i, result);
	}
}

void EECoreInterpreter::PSUBSB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(i));
		s16 result = source1Val - source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByte(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByte(i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByte(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter::PSUBSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s32 result = source1Val - source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHword(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHword(i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHword(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter::PSUBSW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));
		s64 result = source1Val - source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWord(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWord(i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWord(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter::PSUBUB()
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(i));
		s16 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeByte(i, 0);
		else
			destReg->writeByte(i, static_cast<u8>(result));
	}
}

void EECoreInterpreter::PSUBUH()
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s32 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeHword(i, 0);
		else
			destReg->writeHword(i, static_cast<u16>(result));
	}
}

void EECoreInterpreter::PSUBUW()
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readHword(i));
		auto source2Val = static_cast<s32>(source2Reg->readHword(i));
		s64 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeWord(i, 0);
		else
			destReg->writeWord(i, static_cast<u32>(result));
	}
}

void EECoreInterpreter::PSUBW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));
		s32 result = source1Val - source2Val;
		destReg->writeWord(i, result);
	}
}

