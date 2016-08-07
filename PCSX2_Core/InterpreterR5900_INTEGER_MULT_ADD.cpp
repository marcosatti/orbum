#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterR5900/InterpreterR5900.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Types/R5900InstructionUtil/R5900InstructionUtil.h"
#include <Common/PS2 Types/PS2Exception/PS2Exception_t.h>

using R5900InstructionInfo_t = R5900InstructionUtil::R5900InstructionInfo_t;

/*
Integer Multiply-Add instruction family.
*/

void InterpreterR5900::MADD(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI, Rd) = (LO || HI) + SignExtend<s64>(Rs[SW] * Rt[SW])
	// No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	s64 result = ((PS2Resources.EE.EECore.R5900.HI.SW[0] << 32) || PS2Resources.EE.EECore.R5900.LO.SW[0]) + (source1Reg.SW[0] * source2Reg.SW[0]);
	PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<s64>(static_cast<s32>(result >> 32));
	destReg.SD[0] = static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF));
}

void InterpreterR5900::MADD1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADD(instruction, PS2Resources);
}

void InterpreterR5900::MADDU(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// (LO, HI, Rd) = (LO || HI) + SignExtend<u64>(Rs[UW] * Rt[UW])
	// No Exceptions generated.
	auto& source1Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRt()];
	auto& destReg = PS2Resources.EE.EECore.R5900.GPR[instruction.getRRd()];

	u64 result = ((PS2Resources.EE.EECore.R5900.HI.UW[0] << 32) || PS2Resources.EE.EECore.R5900.LO.UW[0]) + (source1Reg.UW[0] * source2Reg.UW[0]);
	PS2Resources.EE.EECore.R5900.LO.SD[0] = static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF));
	PS2Resources.EE.EECore.R5900.HI.SD[0] = static_cast<u64>(static_cast<u32>(result >> 32));
	destReg.SD[0] = static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF));
}

void InterpreterR5900::MADDU1(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADDU(instruction, PS2Resources);
}

void InterpreterR5900::PHMADH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PHMSBH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PMADDH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PMADDUW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PMADDW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PMSUBH(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}

void InterpreterR5900::PMSUBW(const MIPSInstruction_t& instruction, PS2Resources_t& PS2Resources)
{
}
