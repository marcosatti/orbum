#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "Common/Types/Registers/LinkRegister128_t.h"

void EECoreInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
	{
		getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
}

void EECoreInterpreter::BGEZALL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
	{
		getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
	else
		getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readDwordS(0) < 0)
	{
		getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
}

void EECoreInterpreter::BLTZALL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readDwordS(0) < 0)
	{
		getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
		getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	}
	else
		getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
	const s32 offset = mInstruction.getJRegionAddress();
	getResources()->EE->EECore->R5900->setBranchDelayPCJRegion(offset, 1);
}

void EECoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	destReg->writeDwordU(0, static_cast<u64>(getResources()->EE->EECore->R5900->PC->getPCValue() + 8));
	getResources()->EE->EECore->R5900->setBranchDelayPCTarget(sourceReg->readWordU(0), 1);
}
