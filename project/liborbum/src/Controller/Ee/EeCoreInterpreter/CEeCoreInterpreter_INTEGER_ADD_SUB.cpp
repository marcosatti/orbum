
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword(0));
	auto source2Val = static_cast<s32>(source2Reg->read_uword(0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;
	
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->read_uword(0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->read_uword(0));
	s64 result = sourceVal + imm;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword(0));
	auto source2Val = static_cast<s32>(source2Reg->read_uword(0));
	s64 result = source1Val + source2Val;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));
	s64 result = source1Val + source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow64(source1Val, source2Val))
        return;
		
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->read_udword(0));
	s64 result = sourceVal + imm;

	// Check for over/under flow.
    if (handleOverOrUnderflow64(sourceVal, imm))
        return;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto imm = mEECoreInstruction.getIImmS();

	auto sourceVal = static_cast<s64>(sourceReg->read_udword(0));
	s64 result = sourceVal + imm;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));
	s64 result = source1Val + source2Val;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DSUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow64(source1Val, source2Val))
		return;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::DSUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));
	auto source2Val = static_cast<s64>(source2Reg->read_udword(0));
	s64 result = source1Val - source2Val;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword(0));
	auto source2Val = static_cast<s32>(source2Reg->read_uword(0));
	s64 result = source1Val - source2Val;

	// Check for over/under flow.
	if (handleOverOrUnderflow32(source1Val, source2Val))
		return;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword(0));
	auto source2Val = static_cast<s32>(source2Reg->read_uword(0));
	s64 result = source1Val - source2Val;

	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::PADDB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<s8>(source2Reg->read_ubyte(i));
		s8 result = source1Val + source2Val;
		destReg->write_ubyte(i, result);
	}
}

void EECoreInterpreter_s::PADDH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++) 
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = source1Val + source2Val;
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PADDSB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<s8>(source2Reg->read_ubyte(i));
		s16 result = source1Val + source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->write_ubyte(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->write_ubyte(i, Constants::VALUE_S8_MIN);
		else
			destReg->write_ubyte(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter_s::PADDSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s32 result = source1Val + source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->write_uhword(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->write_uhword(i, Constants::VALUE_S16_MIN);
		else
			destReg->write_uhword(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter_s::PADDSW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s64 result = source1Val + source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->write_uword(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->write_uword(i, Constants::VALUE_S32_MIN);
		else
			destReg->write_uword(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter_s::PADDUB()
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<ubyte>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<ubyte>(source2Reg->read_ubyte(i));
		uhword result = source1Val + source2Val;

		if (result > Constants::VALUE_ubyte_MAX)
			destReg->write_ubyte(i, Constants::VALUE_ubyte_MAX);
		else
			destReg->write_ubyte(i, static_cast<ubyte>(result));
	}
}

void EECoreInterpreter_s::PADDUH()
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<uhword>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<uhword>(source2Reg->read_uhword(i));
		uword result = source1Val + source2Val;

		if (result > Constants::VALUE_uhword_MAX)
			destReg->write_uhword(i, Constants::VALUE_uhword_MAX);
		else
			destReg->write_uhword(i, static_cast<uhword>(result));
	}
}

void EECoreInterpreter_s::PADDUW()
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<uword>(source1Reg->read_uword(i));
		auto source2Val = static_cast<uword>(source2Reg->read_uword(i));
		udword result = source1Val + source2Val;

		if (result > Constants::VALUE_uword_MAX)
			destReg->write_uword(i, Constants::VALUE_uword_MAX);
		else
			destReg->write_uword(i, static_cast<uword>(result));
	}
}

void EECoreInterpreter_s::PADDW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s32 result = source1Val + source2Val;
		destReg->write_uword(i, result);
	}
}

void EECoreInterpreter_s::PADSBH()
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = source1Val - source2Val;
		destReg->write_uhword(i, result);
	}
	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = source1Val + source2Val;
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PSUBB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<s8>(source2Reg->read_ubyte(i));
		s8 result = source1Val - source2Val;
		destReg->write_ubyte(i, result);
	}
}

void EECoreInterpreter_s::PSUBH()
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s16 result = source1Val - source2Val;
		destReg->write_uhword(i, result);
	}
}

void EECoreInterpreter_s::PSUBSB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<s8>(source2Reg->read_ubyte(i));
		s16 result = source1Val - source2Val;

		if (result > Constants::VALUE_S8_MAX)
			destReg->write_ubyte(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->write_ubyte(i, Constants::VALUE_S8_MIN);
		else
			destReg->write_ubyte(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter_s::PSUBSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s32 result = source1Val - source2Val;

		if (result > Constants::VALUE_S16_MAX)
			destReg->write_uhword(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->write_uhword(i, Constants::VALUE_S16_MIN);
		else
			destReg->write_uhword(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter_s::PSUBSW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s64 result = source1Val - source2Val;

		if (result > Constants::VALUE_S32_MAX)
			destReg->write_uword(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->write_uword(i, Constants::VALUE_S32_MIN);
		else
			destReg->write_uword(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter_s::PSUBUB()
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s8>(source1Reg->read_ubyte(i));
		auto source2Val = static_cast<s8>(source2Reg->read_ubyte(i));
		s16 result = source1Val - source2Val;

		if (result < 0)
			destReg->write_ubyte(i, 0);
		else
			destReg->write_ubyte(i, static_cast<ubyte>(result));
	}
}

void EECoreInterpreter_s::PSUBUH()
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s32 result = source1Val - source2Val;

		if (result < 0)
			destReg->write_uhword(i, 0);
		else
			destReg->write_uhword(i, static_cast<uhword>(result));
	}
}

void EECoreInterpreter_s::PSUBUW()
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uhword(i));
		s64 result = source1Val - source2Val;

		if (result < 0)
			destReg->write_uword(i, 0);
		else
			destReg->write_uword(i, static_cast<uword>(result));
	}
}

void EECoreInterpreter_s::PSUBW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s32 result = source1Val - source2Val;
		destReg->write_uword(i, result);
	}
}

