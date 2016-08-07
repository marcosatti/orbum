#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"
#include <Common/PS2 Types/PS2Exception/PS2Exception_t.h>

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

/*
Integer Multiply/Divide instruction family.
*/

void InterpreterR5900::DIV(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
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

void InterpreterR5900::DIVU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
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

void InterpreterR5900::MULT(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	s64 result = source1Reg.SW[0] * source2Reg.SW[0];
	PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<s64>(static_cast<s32>(result >> 32));
}

void InterpreterR5900::MULTU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];

	u64 result = source1Reg.UW[0] * source2Reg.UW[0];
	PS2Resources.EE.EECore.R5900.LO.UD[0] = static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.UD[0] = static_cast<u64>(static_cast<u32>(result >> 32));
}

void InterpreterR5900::PDIVBW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
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

void InterpreterR5900::PDIVUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{

}	
