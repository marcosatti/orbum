#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPInterpreter.h"
#include "VM/ExecutionCore/Interpreter/IOP/IOPInterpreter/IOPMMUHandler/IOPMMUHandler.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/R3000/Types/LinkRegister32_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"

void IOPInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() == source2Reg->readWordS())
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() >= 0)
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() >= 0)
	{
		getVM()->getResources()->IOP->R3000->LinkRegister->setLinkAddress();
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
	}
}

void IOPInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() > 0)
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() <= 0)
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() < 0)
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() < 0)
	{
		getVM()->getResources()->IOP->R3000->LinkRegister->setLinkAddress();
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
	}
}

void IOPInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readWordS() != source2Reg->readWordS())
		getVM()->getResources()->IOP->R3000->setBranchDelayPCIOffset(offset, 1);
}

void IOPInterpreter::J()
{
	// JUMP(). No Exceptions.
	const s32 offset = getInstruction().getJRegionAddress();
	getVM()->getResources()->IOP->R3000->setBranchDelayPCJRegion(offset, 1);
}

void IOPInterpreter::JR()
{
	// JUMP(). Address error exception generated upon instruction load - but not in this instruction.
	auto& source1Reg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRs()];
	getVM()->getResources()->IOP->R3000->setBranchDelayPCTarget(source1Reg->readWordU(), 1);
}

void IOPInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	getVM()->getResources()->IOP->R3000->LinkRegister->setLinkAddress();
	const s32 offset = getInstruction().getJRegionAddress();
	getVM()->getResources()->IOP->R3000->setBranchDelayPCJRegion(offset, 1);
}

void IOPInterpreter::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->IOP->R3000->GPR[getInstruction().getRRd()];

	destReg->writeWordU(static_cast<u32>(getVM()->getResources()->IOP->R3000->PC->getPCValue() + 8));
	getVM()->getResources()->IOP->R3000->setBranchDelayPCTarget(sourceReg->readWordU(), 1);
}

