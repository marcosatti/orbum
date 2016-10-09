#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VmMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/PCRegister32_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/Types/LinkRegister128_t.h"

void EECoreInterpreter::BGEZAL()
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

void EECoreInterpreter::BGEZALL()
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
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLTZAL()
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

void EECoreInterpreter::BLTZALL()
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
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	getVM()->getResources()->EE->EECore->R5900->LinkRegister->setLinkAddress();
	const s32 offset = getInstruction().getJRegionAddress();
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCJRegion(offset, 1);
}

void EECoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	destReg->writeDwordU(0, static_cast<u64>(getVM()->getResources()->EE->EECore->R5900->PC->getPCValue() + 8));
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(sourceReg->readWordU(0), 1);
}
