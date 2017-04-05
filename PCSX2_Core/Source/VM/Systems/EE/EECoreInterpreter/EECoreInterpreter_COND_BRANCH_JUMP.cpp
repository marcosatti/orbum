#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/PCRegister32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter_s::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));

	if (source1Val == source2Val)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BEQL()
{
	// BRANCH_LIKELY(Rs == Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));

	if (source1Val == source2Val)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val >= 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BGEZL()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val >= 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val > 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BGTZL()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val > 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val <= 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BLEZL()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val <= 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val < 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BLTZL()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	if (source1Val < 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));

	if (source1Val != source2Val)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BNEL()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto offset = mEECoreInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));

	if (source1Val != source2Val)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BC0F()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	// if (CPCOND0 == false)
		// branch; 
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC0F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0F: Not implemented.");
#endif
}

void EECoreInterpreter_s::BC0FL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	// if (CPCOND0 == false)
		// branch likely; 
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC0FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0FL: Not implemented.");
#endif
}

void EECoreInterpreter_s::BC0T()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	// if (CPCOND0 == true)
	// branch; 
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC0T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0T: Not implemented.");
#endif
}

void EECoreInterpreter_s::BC0TL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	// if (CPCOND0 == true)
	// branch likely; 
#if defined(BUILD_DEBUG)
	log(Debug, "(%s, %d) BC0TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0TL: Not implemented.");
#endif
}

void EECoreInterpreter_s::BC1F()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C) == 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BC1FL()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C) == 0)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::BC1T()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C) == 1)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
}

void EECoreInterpreter_s::BC1TL()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mEECoreInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C) == 1)
		mEECore->R5900->PC->setBranchPCIOffset(getContext(), offset, 2);
	else
		mEECore->R5900->PC->next(getContext()); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter_s::J()
{
	// JUMP(). No Exceptions.
	mEECore->R5900->PC->setBranchPCJRegion(getContext(), mEECoreInstruction.getJRegionAddress(), 2);
}

void EECoreInterpreter_s::JR()
{
	// JUMP(). Address error exception generated upon instruction load - but not in this instruction.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	mEECore->R5900->PC->setBranchPCAbsolute(source1Reg->readWord(getContext(), 0), 2);
}
