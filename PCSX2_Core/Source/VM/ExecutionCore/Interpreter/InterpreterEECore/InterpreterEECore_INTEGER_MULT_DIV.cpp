#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

/*
Integer Multiply/Divide instruction family.
*/

void InterpreterEECore::DIV(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Reg.SW[0] == Constants::VALUE_S32_MIN &&
		source2Reg.SW[0] == -1)
	{
		PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<s64>(Constants::VALUE_S32_MIN);
		PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<s64>(0);
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Reg.SW[0] == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<s64>(source1Reg.SW[0] / source2Reg.SW[0]);

		// Remainder.
		PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<s64>(source1Reg.SW[0] % source2Reg.SW[0]);
	}
}

void InterpreterEECore::DIV1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIV(instruction, PS2Resources);
}

void InterpreterEECore::DIVU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = SignExtend<u64>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Reg.UW[0] == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		PS2Resources.EE.EECore.R5900.LO.UD[0] = static_cast<u64>(source1Reg.UW[0] / source2Reg.UW[0]);

		// Remainder.
		PS2Resources.EE.EECore.R5900.HI.UD[0] = static_cast<u64>(source1Reg.UW[0] % source2Reg.UW[0]);
	}
}

void InterpreterEECore::DIVU1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIVU(instruction, PS2Resources);
}

void InterpreterEECore::MULT(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	s64 result = source1Reg.SW[0] * source2Reg.SW[0];
	PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<s64>(static_cast<s32>(result >> 32));
}

void InterpreterEECore::MULT1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULT(instruction, PS2Resources);
}

void InterpreterEECore::MULTU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	u64 result = source1Reg.UW[0] * source2Reg.UW[0];
	PS2Resources.EE.EECore.R5900.LO.UD[0] = static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.UD[0] = static_cast<u64>(static_cast<u32>(result >> 32));
}

void InterpreterEECore::MULTU1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULTU(instruction, PS2Resources);
}

void InterpreterEECore::PDIVBW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SH,0]) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Reg.SW[i] == Constants::VALUE_S32_MIN &&
			source2Reg.SH[0] == -1)
		{
			PS2Resources.EE.EECore.R5900.LO.SW[i] = static_cast<s64>(Constants::VALUE_S32_MIN);
			PS2Resources.EE.EECore.R5900.HI.SW[i] = static_cast<s64>(0);
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Reg.SH[0] == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			PS2Resources.EE.EECore.R5900.LO.SW[i] = static_cast<s64>(source1Reg.SW[i] / source2Reg.SH[0]);

			// Remainder.
			PS2Resources.EE.EECore.R5900.HI.SW[i] = static_cast<s64>(source1Reg.SW[i] % source2Reg.SH[0]);
		}
	}
}

void InterpreterEECore::PDIVUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI)(0,1) = SignExtend<u64>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		// Check for divide by 0, in which case result is undefined (do nothing).
		if (source2Reg.UW[i] == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			PS2Resources.EE.EECore.R5900.LO.UD[i / 2] = static_cast<u64>(source1Reg.UW[i] / source2Reg.UW[i]);

			// Remainder.
			PS2Resources.EE.EECore.R5900.HI.UD[i / 2] = static_cast<u64>(source1Reg.UW[i] % source2Reg.UW[i]);
		}
	}
}

void InterpreterEECore::PDIVW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI)(0,1) = SignExtend<u64>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Reg.SW[i] == Constants::VALUE_S32_MIN 
			&& source2Reg.SW[i] == -1)
		{
			PS2Resources.EE.EECore.R5900.LO.SD[i / 2] = static_cast<s64>(Constants::VALUE_S32_MIN);
			PS2Resources.EE.EECore.R5900.HI.SD[i / 2] = static_cast<s64>(0);
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Reg.SW[i] == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			PS2Resources.EE.EECore.R5900.LO.SD[i / 2] = static_cast<s64>(source1Reg.SW[i] / source2Reg.SW[i]);

			// Remainder.
			PS2Resources.EE.EECore.R5900.HI.SD[i / 2] = static_cast<s64>(source1Reg.SW[i] % source2Reg.SW[i]);
		}
	}
}

void InterpreterEECore::PMULTH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()]; // "A"
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()]; // "B"
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg.SH[i] * source2Reg.SH[i];

		if (i % 2 == 0)
			destReg.SW[i / 2] = result; // Write to Rd for even indexes. A0xB0, A2xB2, A4xB4, A6xB6.

		if ((i / 2) % 2 == 0)
			PS2Resources.EE.EECore.R5900.LO.SW[((i / 2 > 0) ? i - 2 : i)] = result; // A0xB0, A1xB1, A4xB4, A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
		else
			PS2Resources.EE.EECore.R5900.HI.SW[((i / 2 > 1) ? i - 4 : i - 2)] = result; // A2xB2, A3xB3, A6xB6, A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
	}
}

void InterpreterEECore::PMULTUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI, Rd) = SignExtend<u64>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u64 result = source1Reg.UW[i] * source2Reg.UW[i];

		PS2Resources.EE.EECore.R5900.LO.UD[i / 2] = static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF));
		PS2Resources.EE.EECore.R5900.HI.UD[i / 2] = static_cast<u64>(static_cast<u32>(result >> 32));
		destReg.UD[i / 2] = result;
	}
}

void InterpreterEECore::PMULTW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		s64 result = source1Reg.SW[i] * source2Reg.SW[i];

		PS2Resources.EE.EECore.R5900.LO.SD[i / 2] = static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF));
		PS2Resources.EE.EECore.R5900.HI.SD[i / 2] = static_cast<s64>(static_cast<s32>(result >> 32));
		destReg.SD[i / 2] = result;
	}
}