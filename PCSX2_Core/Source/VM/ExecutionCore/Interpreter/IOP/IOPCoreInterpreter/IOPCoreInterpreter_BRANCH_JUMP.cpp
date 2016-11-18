#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreMMUHandler/IOPCoreMMUHandler.h"
#include "VM/VMMain.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"
#include "Common/Types/Registers/LinkRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"

void IOPCoreInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() == source2Reg->readWordS())
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() >= 0)
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() >= 0)
	{
		getVM()->getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
	}
}

void IOPCoreInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() > 0)
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() <= 0)
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() < 0)
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() < 0)
	{
		getVM()->getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
	}
}

void IOPCoreInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	const s16 offset = mInstruction.getIImmS();

	if (source1Reg->readWordS() != source2Reg->readWordS())
		getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPCoreInterpreter::J()
{
	// JUMP(). No Exceptions.
	const s32 offset = mInstruction.getJRegionAddress();
	getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCJRegion(offset, 1);
}

void IOPCoreInterpreter::JR()
{
	// JUMP(). Address error exception generated upon instruction load - but not in this instruction.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCTarget(source1Reg->readWordU(), 1);
}

void IOPCoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	getVM()->getResources()->IOP->IOPCore->R3000->LinkRegister->setLinkAddress();
	const s32 offset = mInstruction.getJRegionAddress();
	getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCJRegion(offset, 1);
}

void IOPCoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWordU(static_cast<u32>(getVM()->getResources()->IOP->IOPCore->R3000->PC->getPCValue() + 8));
	getVM()->getResources()->IOP->IOPCore->R3000->setBranchDelayPCTarget(sourceReg->readWordU(), 1);
}

