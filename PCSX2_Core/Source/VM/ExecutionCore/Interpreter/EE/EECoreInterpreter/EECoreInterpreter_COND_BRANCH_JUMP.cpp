#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/MIPS/PCRegister32_t.h"
#include "Common/Types/MIPSBranchDelay/MIPSBranchDelay_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(EE, 0));

	if (source1Val == source2Val)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BEQL()
{
	// BRANCH_LIKELY(Rs == Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(EE, 0));

	if (source1Val == source2Val)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val >= 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BGEZL()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val >= 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val > 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BGTZL()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val > 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val <= 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BLEZL()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val <= 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val < 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BLTZL()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));

	if (source1Val < 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(EE, 0));

	if (source1Val != source2Val)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BNEL()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getIRt()];
	auto& source2Reg = mEECore->R5900->GPR[mInstruction.getIRs()];
	auto offset = mInstruction.getIImmS();

	auto source1Val = static_cast<s64>(source1Reg->readDword(EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(EE, 0));

	if (source1Val != source2Val)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BC0F()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	// if (CPCOND0 == false)
		// branch; 
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC0F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0F: Not implemented.");
#endif
}

void EECoreInterpreter::BC0FL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	// if (CPCOND0 == false)
		// branch likely; 
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC0FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0FL: Not implemented.");
#endif
}

void EECoreInterpreter::BC0T()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	// if (CPCOND0 == true)
	// branch; 
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC0T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0T: Not implemented.");
#endif
}

void EECoreInterpreter::BC0TL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	if (handleCOP0Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	// if (CPCOND0 == true)
	// branch likely; 
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC0TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC0TL: Not implemented.");
#endif
}

void EECoreInterpreter::BC1F()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(EECoreFPURegister_CSR_t::Fields::C) == 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BC1FL()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(EECoreFPURegister_CSR_t::Fields::C) == 0)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BC1T()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(EECoreFPURegister_CSR_t::Fields::C) == 1)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
}

void EECoreInterpreter::BC1TL()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (handleCOP1Usable())
        return;

	const s16 offset = mInstruction.getIImmS();

	if (mEECore->FPU->CSR->getFieldValue(EECoreFPURegister_CSR_t::Fields::C) == 1)
		mEECore->R5900->BD->setBranchDelayPCIOffset(offset, 2);
	else
		mEECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::J()
{
	// JUMP(). No Exceptions.
	mEECore->R5900->BD->setBranchDelayPCJRegion(mInstruction.getJRegionAddress(), 2);
}

void EECoreInterpreter::JR()
{
	// JUMP(). Address error exception generated upon instruction load - but not in this instruction.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRs()];
	mEECore->R5900->BD->setBranchDelayPCAbsolute(source1Reg->readWord(EE, 0), 2);
}
