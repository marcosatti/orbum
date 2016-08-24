#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

void InterpreterEECore::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BEQL()
{
	// BRANCH_LIKELY(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BGEZL()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BGTZL()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BLEZL()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BLTZL()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BNE()
{
	// BRANCH(Rs != 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BNEL()
{
	// BRANCH(Rs != 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BC0F()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == false)
		// branch; 
#if defined(BUILD_DEBUG)
	logDebug("BC0F: Not implemented.");
#else
	throw std::runtime_error("BC0F: Not implemented.");
#endif
}

void InterpreterEECore::BC0FL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == false)
		// branch likely; 
#if defined(BUILD_DEBUG)
	logDebug("BC0FL: Not implemented.");
#else
	throw std::runtime_error("BC0FL: Not implemented.");
#endif
}

void InterpreterEECore::BC0T()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == true)
	// branch; 
#if defined(BUILD_DEBUG)
	logDebug("BC0T: Not implemented.");
#else
	throw std::runtime_error("BC0T: Not implemented.");
#endif
}

void InterpreterEECore::BC0TL()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	// if (CPCOND0 == true)
	// branch likely; 
#if defined(BUILD_DEBUG)
	logDebug("BC0TL: Not implemented.");
#else
	throw std::runtime_error("BC0TL: Not implemented.");
#endif
}

void InterpreterEECore::BC1F()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BC1FL()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BC1T()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 1)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void InterpreterEECore::BC1TL()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->COP1->CSR->getFieldValue(RegisterCSR_t::Fields::C) == 1)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(8, 0); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void InterpreterEECore::BC2F()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("BC2F: Not implemented.");
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void InterpreterEECore::BC2FL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("BC2FL: Not implemented.");
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void InterpreterEECore::BC2T()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("BC2T: Not implemented.");
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void InterpreterEECore::BC2TL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("BC2TL: Not implemented.");
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void InterpreterEECore::J()
{
	// JUMP(). No Exceptions.
	const s32 offset = getInstruction().getJOffsetAddress();
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCJOffset(offset, 1);
}

void InterpreterEECore::JR()
{
	// JUMP(). Exceptions generated by other components.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(source1Reg->readWordU(0), 1);
}
