#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"

#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(IOP));

	if (source1Val == source2Val)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val >= 0)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val >= 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val > 0)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val <= 0)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val < 0)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val < 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(IOP));

	if (source1Val != source2Val)
		mIOPCore->R3000->BD->setBranchDelayPCIOffset(offset, 2);
}

void IOPCoreInterpreter::J()
{
	// JUMP(). No Exceptions.
	mIOPCore->R3000->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter::JR()
{
	// JUMP_REGISTER().
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getRRs()];
	mIOPCore->R3000->BD->setBranchDelayPCAbsolute(source1Reg->readWord(IOP), 2);
}

void IOPCoreInterpreter::JAL()
{
	// JUMP_LINK(). No exceptions.
	mIOPCore->R3000->LinkRegister->setLinkAddress();
	mIOPCore->R3000->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter::JALR()
{
	// JUMP_LINK_REGISTER().
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(IOP, static_cast<u32>(mIOPCore->R3000->PC->readWord(IOP) + Constants::SIZE_MIPS_INSTRUCTION));
	mIOPCore->R3000->BD->setBranchDelayPCAbsolute(sourceReg->readWord(IOP), 2);
}

