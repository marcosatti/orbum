#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/Registers/MIPS/LinkRegister32_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter_s::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(IOP));

	if (source1Val == source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val >= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val >= 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter_s::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val > 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val <= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val < 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));

	if (source1Val < 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
	}
}

void IOPCoreInterpreter_s::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(IOP));

	if (source1Val != source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(offset, 2);
}

void IOPCoreInterpreter_s::J()
{
	// JUMP(). No Exceptions.
	mIOPCore->R3000->PC->setBranchPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JR()
{
	// JUMP_REGISTER().
	auto& source1Reg = mIOPCore->R3000->GPR[mInstruction.getRRs()];
	mIOPCore->R3000->PC->setBranchPCAbsolute(source1Reg->readWord(IOP), 2);
}

void IOPCoreInterpreter_s::JAL()
{
	// JUMP_LINK(). No exceptions.
	mIOPCore->R3000->LinkRegister->setLinkAddress();
	mIOPCore->R3000->PC->setBranchPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JALR()
{
	// JUMP_LINK_REGISTER().
	auto& sourceReg = mIOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = mIOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(IOP, static_cast<u32>(mIOPCore->R3000->PC->readWord(IOP) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	mIOPCore->R3000->PC->setBranchPCAbsolute(sourceReg->readWord(IOP), 2);
}

