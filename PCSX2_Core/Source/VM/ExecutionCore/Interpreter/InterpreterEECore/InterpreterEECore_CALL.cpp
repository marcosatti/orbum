#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
	{
		getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
}

void InterpreterEECore::BGEZALL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
	{
		getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
	{
		getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
}

void InterpreterEECore::BLTZALL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
	{
		getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::JAL()
{
	// JUMP_LINK(). No exceptions.
	getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
	const s32 offset = getInstruction().getJOffsetAddress();
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCJOffset(offset, 1);
}

void InterpreterEECore::JALR()
{
	// JUMP_LINK_REGISTER(). Exceptions generated by other components.
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, static_cast<u64>(getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() + 8));
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(sourceReg->readWordU(0), 1);
}
