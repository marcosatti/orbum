#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/LinkRegister32_t.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter_s::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	if (source1Val == source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val >= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val >= 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress(getContext());
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
	}
}

void IOPCoreInterpreter_s::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val > 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val <= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val < 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));

	if (source1Val < 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress(getContext());
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
	}
}

void IOPCoreInterpreter_s::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->readWord(getContext()));
	auto source2Val = static_cast<s32>(source2Reg->readWord(getContext()));

	if (source1Val != source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void IOPCoreInterpreter_s::J()
{
	// JUMP(). No Exceptions.
	mIOPCore->R3000->PC->setBranchPCJRegion(getContext(), mIOPCoreInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JR()
{
	// JUMP_REGISTER().
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	mIOPCore->R3000->PC->setBranchPCAbsolute(source1Reg->readWord(getContext()), 2);
}

void IOPCoreInterpreter_s::JAL()
{
	// JUMP_LINK(). No exceptions.
	mIOPCore->R3000->LinkRegister->setLinkAddress(getContext());
	mIOPCore->R3000->PC->setBranchPCJRegion(getContext(), mIOPCoreInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JALR()
{
	// JUMP_LINK_REGISTER().
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->writeWord(getContext(), static_cast<u32>(mIOPCore->R3000->PC->readWord(getContext()) + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	mIOPCore->R3000->PC->setBranchPCAbsolute(sourceReg->readWord(getContext()), 2);
}

