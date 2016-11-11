#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter::BEQ()
{
	// BRANCH(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BEQL()
{
	// BRANCH_LIKELY(Rs == Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) == source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BGEZ()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BGEZL()
{
	// BRANCH(Rs >= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) >= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BGTZ()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BGTZL()
{
	// BRANCH(Rs > 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) > 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLEZ()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BLEZL()
{
	// BRANCH(Rs <= 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) <= 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BLTZ()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BLTZL()
{
	// BRANCH(Rs < 0). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) < 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BNE()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BNEL()
{
	// BRANCH(Rs != Rt). No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 offset = getInstruction().getIImmS();

	if (source1Reg->readDwordS(0) != source2Reg->readDwordS(0))
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BC0F()
{
	// TODO: Implement.
	// BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

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
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

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
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

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
	if (!getVM()->getResources()->EE->EECore->COP0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 0 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

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
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->FPU->CSR->getFieldValue(FPURegister_CSR_t::Fields::C) == 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BC1FL()
{
	// BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->FPU->CSR->getFieldValue(FPURegister_CSR_t::Fields::C) == 0)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BC1T()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->FPU->CSR->getFieldValue(FPURegister_CSR_t::Fields::C) == 1)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
}

void EECoreInterpreter::BC1TL()
{
	// BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	const s16 offset = getInstruction().getIImmS();

	if (getVM()->getResources()->EE->EECore->FPU->CSR->getFieldValue(FPURegister_CSR_t::Fields::C) == 1)
		getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCIOffset(offset, 1);
	else
		getVM()->getResources()->EE->EECore->R5900->PC->setPCValueNext(); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void EECoreInterpreter::BC2F()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2F: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2F: Not implemented.");
#endif
}

void EECoreInterpreter::BC2FL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2FL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2FL: Not implemented.");
#endif
}

void EECoreInterpreter::BC2T()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2T: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2T: Not implemented.");
#endif
}

void EECoreInterpreter::BC2TL()
{
	// TODO: Implement.
#if defined(BUILD_DEBUG)
	logDebug("(%s, %d) BC2TL: Not implemented.", __FILENAME__, __LINE__);
#else
	throw std::runtime_error("BC2TL: Not implemented.");
#endif
}

void EECoreInterpreter::J()
{
	// JUMP(). No Exceptions.
	const s32 offset = getInstruction().getJRegionAddress();
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCJRegion(offset, 1);
}

void EECoreInterpreter::JR()
{
	// JUMP(). Address error exception generated upon instruction load - but not in this instruction.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	getVM()->getResources()->EE->EECore->R5900->setBranchDelayPCTarget(source1Reg->readWordU(0), 1);
}
