
#include "Common/Types/Register/PCRegister32_t.h"
#include "Common/Types/Register/LinkRegister128_t.h"
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::BGEZAL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val >= 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->PC->setBranchPCIOffset(, offset, 2);
	}
}

void EECoreInterpreter_s::BGEZALL()
{
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val >= 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->PC->setBranchPCIOffset(, offset, 2);
	}
	else
		mEECore->R5900->PC->next(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BLTZAL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val < 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->PC->setBranchPCIOffset(, offset, 2);
	}
}

void EECoreInterpreter_s::BLTZALL()
{
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->read_udword(0));

	if (source1Val < 0)
	{
		mEECore->R5900->LinkRegister->setLinkAddress();
		mEECore->R5900->PC->setBranchPCIOffset(, offset, 2);
	}
	else
		mEECore->R5900->PC->next(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::JAL()
{
	// JUMP_LINK(). No exceptions.
	mEECore->R5900->LinkRegister->setLinkAddress();
	mEECore->R5900->PC->setBranchPCJRegion(, mEECoreInstruction.getJRegionAddress(), 2);
}

void EECoreInterpreter_s::JALR()
{
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& sourceReg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	destReg->write_udword(0, static_cast<udword>(mEECore->R5900->PC->read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	mEECore->R5900->PC->setBranchPCAbsolute(sourceReg->read_uword(0), 2);
}
