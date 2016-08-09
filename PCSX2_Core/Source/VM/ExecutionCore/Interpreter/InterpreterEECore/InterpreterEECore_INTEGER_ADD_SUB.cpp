#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

/*
Integer Addition/Subtraction instruction family.
*/

void InterpreterEECore::ADD(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg.SW[0] + source2Reg.SW[0]);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}
	
	destReg.SD[0] = result;
}

void InterpreterEECore::ADDI(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRs()];
	const s16 imm = instruction.getIImmS();

	const s64 result = static_cast<s64>(sourceReg.SW[0] + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterEECore::ADDIU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRs()];

	destReg.SD[0] = static_cast<s64>(sourceReg.SW[0] + instruction.getIImmS());
}

void InterpreterEECore::ADDU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	destReg.SD[0] = static_cast<s64>(source1Reg.SW[0] + source2Reg.SW[0]);
}

void InterpreterEECore::DADD(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg.SD[0] + source2Reg.SD[0]);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg.SD[0]^source2Reg.SD[0]))&(source1Reg.SD[0]^result)) < 0) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterEECore::DADDI(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRs()];
	const s16 imm = instruction.getIImmS();

	const s64 result = static_cast<s64>(sourceReg.SD[0] + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(sourceReg.SD[0] ^ imm))&(sourceReg.SD[0] ^ result)) < 0)
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterEECore::DADDIU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getIRs()];

	destReg.SD[0] = static_cast<s64>(sourceReg.SD[0] + instruction.getIImmS());
}

void InterpreterEECore::DADDU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	destReg.SD[0] = static_cast<s64>(source1Reg.SD[0] + source2Reg.SD[0]);
}

void InterpreterEECore::DSUB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg.SD[0] - source2Reg.SD[0]);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg.SD[0] ^ -source2Reg.SD[0]))&(source1Reg.SD[0] ^ result)) < 0) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterEECore::DSUBU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs - Rt
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	destReg.SD[0] = static_cast<s64>(source1Reg.SD[0] - source2Reg.SD[0]);
}

void InterpreterEECore::SUB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg.SW[0] - source2Reg.SW[0]);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterEECore::SUBU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs - Rt
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	destReg.SD[0] = static_cast<s64>(source1Reg.SW[0] - source2Reg.SW[0]);
}

void InterpreterEECore::PADDB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for(auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		destReg.SB[i] = source1Reg.SB[i] + source2Reg.SB[i];
	}
}

void InterpreterEECore::PADDH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg.SH[i] = source1Reg.SH[i] + source2Reg.SH[i];
	}
}

void InterpreterEECore::PADDSB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg.SB[i] + source2Reg.SB[i];
		if (result > Constants::VALUE_S8_MAX)
			destReg.SB[i] = Constants::VALUE_S8_MAX;
		else if (result < Constants::VALUE_S8_MIN)
			destReg.SB[i] = Constants::VALUE_S8_MIN;
		else
			destReg.SB[i] = static_cast<s8>(result);
	}
}

void InterpreterEECore::PADDSH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg.SH[i] + source2Reg.SH[i];
		if (result > Constants::VALUE_S16_MAX)
			destReg.SH[i] = Constants::VALUE_S16_MAX;
		else if (result < Constants::VALUE_S16_MIN)
			destReg.SH[i] = Constants::VALUE_S16_MIN;
		else
			destReg.SH[i] = static_cast<s16>(result);
	}
}

void InterpreterEECore::PADDSW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg.SW[i] + source2Reg.SW[i];
		if (result > Constants::VALUE_S32_MAX)
			destReg.SW[i] = Constants::VALUE_S32_MAX;
		else if (result < Constants::VALUE_S32_MIN)
			destReg.SW[i] = Constants::VALUE_S32_MIN;
		else
			destReg.SW[i] = static_cast<s32>(result);
	}
}

void InterpreterEECore::PADDUB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg.UB[i] + source2Reg.UB[i];
		if (result > Constants::VALUE_U8_MAX)
			destReg.UB[i] = Constants::VALUE_U8_MAX;
		else
			destReg.UB[i] = static_cast<s8>(result);
	}
}

void InterpreterEECore::PADDUH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg.UH[i] + source2Reg.UH[i];
		if (result > Constants::VALUE_U16_MAX)
			destReg.UH[i] = Constants::VALUE_U16_MAX;
		else
			destReg.UH[i] = static_cast<s16>(result);
	}
}

void InterpreterEECore::PADDUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg.UW[i] + source2Reg.UW[i];
		if (result > Constants::VALUE_U32_MAX)
			destReg.UW[i] = Constants::VALUE_U32_MAX;
		else
			destReg.UW[i] = static_cast<s32>(result);
	}
}

void InterpreterEECore::PADDW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg.SW[i] = source1Reg.SW[i] + source2Reg.SW[i];
	}
}

void InterpreterEECore::PADSBH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg.SH[i] = source1Reg.SH[i] - source2Reg.SH[i];
	}
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg.SH[i] = source1Reg.SH[i] + source2Reg.SH[i];
	}
}

void InterpreterEECore::PSUBB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		destReg.SB[i] = source1Reg.SB[i] - source2Reg.SB[i];
	}
}

void InterpreterEECore::PSUBH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg.SH[i] = source1Reg.SH[i] - source2Reg.SH[i];
	}
}

void InterpreterEECore::PSUBSB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg.SB[i] - source2Reg.SB[i];
		if (result > Constants::VALUE_S8_MAX)
			destReg.SB[i] = Constants::VALUE_S8_MAX;
		else if (result < Constants::VALUE_S8_MIN)
			destReg.SB[i] = Constants::VALUE_S8_MIN;
		else
			destReg.SB[i] = static_cast<s8>(result);
	}
}

void InterpreterEECore::PSUBSH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg.SH[i] - source2Reg.SH[i];
		if (result > Constants::VALUE_S16_MAX)
			destReg.SH[i] = Constants::VALUE_S16_MAX;
		else if (result < Constants::VALUE_S16_MIN)
			destReg.SH[i] = Constants::VALUE_S16_MIN;
		else
			destReg.SH[i] = static_cast<s16>(result);
	}
}

void InterpreterEECore::PSUBSW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg.SW[i] - source2Reg.SW[i];
		if (result > Constants::VALUE_S32_MAX)
			destReg.SW[i] = Constants::VALUE_S32_MAX;
		else if (result < Constants::VALUE_S32_MIN)
			destReg.SW[i] = Constants::VALUE_S32_MIN;
		else
			destReg.SW[i] = static_cast<s32>(result);
	}
}

void InterpreterEECore::PSUBUB(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg.UB[i] - source2Reg.UB[i];
		if (result > Constants::VALUE_U8_MAX)
			destReg.UB[i] = Constants::VALUE_U8_MAX;
		else
			destReg.UB[i] = static_cast<s8>(result);
	}
}

void InterpreterEECore::PSUBUH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg.UH[i] - source2Reg.UH[i];
		if (result > Constants::VALUE_U16_MAX)
			destReg.UH[i] = Constants::VALUE_U16_MAX;
		else
			destReg.UH[i] = static_cast<s16>(result);
	}
}

void InterpreterEECore::PSUBUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg.UW[i] - source2Reg.UW[i];
		if (result > Constants::VALUE_U32_MAX)
			destReg.UW[i] = Constants::VALUE_U32_MAX;
		else
			destReg.UW[i] = static_cast<s32>(result);
	}
}

void InterpreterEECore::PSUBW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg.SW[i] = source1Reg.SW[i] - source2Reg.SW[i];
	}
}

