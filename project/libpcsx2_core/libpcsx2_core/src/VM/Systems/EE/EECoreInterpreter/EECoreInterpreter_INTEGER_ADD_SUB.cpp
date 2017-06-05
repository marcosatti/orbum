#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter_s::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), 0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), 0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;
	
	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(getContext(), 0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(getContext(), 0));
	s64 result = sourceVal + imm;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), 0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), 0));
	s64 result = source1Val + source2Val;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow64(source1Val, source2Val))
        return;
		
	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->readDword(getContext(), 0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
    if (handleOverOrUnderflow64(sourceVal, imm))
        return;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->readDword(getContext(), 0));
	s64 result = sourceVal + imm;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));
	s64 result = source1Val + source2Val;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DSUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow64(source1Val, source2Val))
		return;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::DSUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));
	s64 result = source1Val - source2Val;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), 0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), 0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(source1Val, source2Val))
		return;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), 0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), 0));
	s64 result = source1Val - source2Val;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::PADDB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(getContext(), i));
		s8 result = source1Val + source2Val;
		destReg->writeByte(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PADDH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++) 
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = source1Val + source2Val;
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PADDSB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(getContext(), i));
		s16 result = source1Val + source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByte(getContext(), i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByte(getContext(), i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByte(getContext(), i, static_cast<s8>(result));
	}
}

void EECoreInterpreter_s::PADDSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s32 result = source1Val + source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHword(getContext(), i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHword(getContext(), i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHword(getContext(), i, static_cast<s16>(result));
	}
}

void EECoreInterpreter_s::PADDSW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s64 result = source1Val + source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWord(getContext(), i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWord(getContext(), i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWord(getContext(), i, static_cast<s32>(result));
	}
}

void EECoreInterpreter_s::PADDUB()
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<u8>(source2Reg->readByte(getContext(), i));
		u16 result = source1Val + source2Val;

		if (result > Constants::VALUE_U8_MAX)
			destReg->writeByte(getContext(), i, Constants::VALUE_U8_MAX);
		else
			destReg->writeByte(getContext(), i, static_cast<u8>(result));
	}
}

void EECoreInterpreter_s::PADDUH()
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<u16>(source2Reg->readHword(getContext(), i));
		u32 result = source1Val + source2Val;

		if (result > Constants::VALUE_U16_MAX)
			destReg->writeHword(getContext(), i, Constants::VALUE_U16_MAX);
		else
			destReg->writeHword(getContext(), i, static_cast<u16>(result));
	}
}

void EECoreInterpreter_s::PADDUW()
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(getContext(), i));
		u64 result = source1Val + source2Val;

		if (result > Constants::VALUE_U32_MAX)
			destReg->writeWord(getContext(), i, Constants::VALUE_U32_MAX);
		else
			destReg->writeWord(getContext(), i, static_cast<u32>(result));
	}
}

void EECoreInterpreter_s::PADDW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s32 result = source1Val + source2Val;
		destReg->writeWord(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PADSBH()
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = source1Val - source2Val;
		destReg->writeHword(getContext(), i, result);
	}
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = source1Val + source2Val;
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PSUBB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(getContext(), i));
		s8 result = source1Val - source2Val;
		destReg->writeByte(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PSUBH()
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s16 result = source1Val - source2Val;
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PSUBSB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(getContext(), i));
		s16 result = source1Val - source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByte(getContext(), i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByte(getContext(), i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByte(getContext(), i, static_cast<s8>(result));
	}
}

void EECoreInterpreter_s::PSUBSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s32 result = source1Val - source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHword(getContext(), i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHword(getContext(), i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHword(getContext(), i, static_cast<s16>(result));
	}
}

void EECoreInterpreter_s::PSUBSW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s64 result = source1Val - source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWord(getContext(), i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWord(getContext(), i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWord(getContext(), i, static_cast<s32>(result));
	}
}

void EECoreInterpreter_s::PSUBUB()
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->readByte(getContext(), i));
		auto source2Val = static_cast<s8>(source2Reg->readByte(getContext(), i));
		s16 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeByte(getContext(), i, 0);
		else
			destReg->writeByte(getContext(), i, static_cast<u8>(result));
	}
}

void EECoreInterpreter_s::PSUBUH()
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		s32 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeHword(getContext(), i, 0);
		else
			destReg->writeHword(getContext(), i, static_cast<u16>(result));
	}
}

void EECoreInterpreter_s::PSUBUW()
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readHword(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readHword(getContext(), i));
		s64 result = source1Val - source2Val;

		if (result < 0)
			destReg->writeWord(getContext(), i, 0);
		else
			destReg->writeWord(getContext(), i, static_cast<u32>(result));
	}
}

void EECoreInterpreter_s::PSUBW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		s32 result = source1Val - source2Val;
		destReg->writeWord(getContext(), i, result);
	}
}

