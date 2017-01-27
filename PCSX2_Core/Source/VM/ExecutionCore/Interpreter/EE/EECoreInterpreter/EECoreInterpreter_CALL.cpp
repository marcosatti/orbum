#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val >= 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void EECoreInterpreter::BGEZALL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val >= 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	}
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val < 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void EECoreInterpreter::BLTZALL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val < 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	}
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	mEECore->R5900->LinkRegister->setLinkAddress();
	mEECore->R5900->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void EECoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = mEECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDword(EE, 0, static_cast<u64>(mEECore->R5900->PC->readWord(EE) + Constants::SIZE_MIPS_INSTRUCTION));
	mEECore->R5900->BD->setBranchDelayPCAbsolute(sourceReg->readWord(EE, 0), 2);
}
