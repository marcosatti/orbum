#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"
#include <Common/PS2 Types/PS2Exception/PS2Exception_t.h>

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

/*
Add instruction family.
Note: the EE Core Instruction Manual says that the 32-bit results must be sign extended to 64-bit.
*/
void InterpreterR5900::ADD(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	s64 result = static_cast<s64>(source1Reg.SW[0] + source2Reg.SW[0]);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) {
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}
	
	destReg.SD[0] = result;
}

void InterpreterR5900::ADDI(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	s16 imm = instruction.getIImmS();

	s64 result = static_cast<s64>(sourceReg.SW[0] + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) {
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg.SD[0] = result;
}

void InterpreterR5900::ADDIU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rt = Rs + Imm (signed).
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& sourceReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	destReg.SD[0] = static_cast<s64>(sourceReg.SW[0] + instruction.getIImmS());
}

void InterpreterR5900::ADDU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Rd = Rs + Rt
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	destReg.SD[0] = static_cast<s64>(source1Reg.SW[0] + source2Reg.SW[0]);
}
