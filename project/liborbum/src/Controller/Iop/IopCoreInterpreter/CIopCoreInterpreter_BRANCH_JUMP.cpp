
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/LinkRegister32_t.h"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/Iop/Core/RIopCore.h"
#include "Resources/Iop/Core/IopCoreR3000.h"

void IOPCoreInterpreter_s::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	if (source1Val == source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val >= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val >= 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
	}
}

void IOPCoreInterpreter_s::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val > 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val <= 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val < 0)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	if (source1Val < 0)
	{
		mIOPCore->R3000->LinkRegister->setLinkAddress();
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
	}
}

void IOPCoreInterpreter_s::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto offset = mIOPCoreInstruction.getIImmS();

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	if (source1Val != source2Val)
		mIOPCore->R3000->PC->setBranchPCIOffset(, offset, 2);
}

void IOPCoreInterpreter_s::J()
{
	// JUMP(). No Exceptions.
	mIOPCore->R3000->PC->setBranchPCJRegion(, mIOPCoreInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JR()
{
	// JUMP_REGISTER().
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	mIOPCore->R3000->PC->setBranchPCAbsolute(source1Reg->read_uword(), 2);
}

void IOPCoreInterpreter_s::JAL()
{
	// JUMP_LINK(). No exceptions.
	mIOPCore->R3000->LinkRegister->setLinkAddress();
	mIOPCore->R3000->PC->setBranchPCJRegion(, mIOPCoreInstruction.getJRegionAddress(), 2);
}

void IOPCoreInterpreter_s::JALR()
{
	// JUMP_LINK_REGISTER().
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(static_cast<uword>(mIOPCore->R3000->PC->read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	mIOPCore->R3000->PC->setBranchPCAbsolute(sourceReg->read_uword(), 2);
}

