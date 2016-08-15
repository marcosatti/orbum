#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::LB()
{
	// Rd = MEM[SB]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordS(0, static_cast<s64>(getMMUHandler()->readByteS(PS2VirtualAddress)));
}

void InterpreterEECore::LBU()
{
	// Rd = MEM[UB]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, static_cast<u64>(getMMUHandler()->readByteU(PS2VirtualAddress)));
}

void InterpreterEECore::LD()
{
	// Rd = MEM[UD]. Exceptions generated through other components.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	u32 PS2VirtualAddress = sourceReg->readWordU(0) + imm;
	destReg->writeDwordU(0, static_cast<u64>(getMMUHandler()->readDwordU(PS2VirtualAddress)));
}

void InterpreterEECore::LDL()
{
}

void InterpreterEECore::LDR()
{
}

void InterpreterEECore::LH()
{
}

void InterpreterEECore::LHU()
{
}

void InterpreterEECore::LUI()
{
}

void InterpreterEECore::LW()
{
}

void InterpreterEECore::LWL()
{
}

void InterpreterEECore::LWR()
{
}

void InterpreterEECore::LWU()
{
}

void InterpreterEECore::LQ()
{
}

void InterpreterEECore::LWC1()
{
}
