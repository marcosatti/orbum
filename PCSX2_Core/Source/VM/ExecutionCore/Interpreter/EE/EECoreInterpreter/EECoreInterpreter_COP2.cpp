#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreMMUHandler/EECoreMMUHandler.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/VuUnits_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register128_t.h"

void EECoreInterpreter::QMFC2()
{
	// GPR = VU0.VF. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// Check for the interlock bit.
	if (getInstruction().getRFunct() & 0x1)
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source1Reg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getRRd()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void EECoreInterpreter::QMTC2()
{
	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// Check for the interlock bit.
	if (getInstruction().getRFunct() & 0x1)
	{
		throw std::runtime_error("COP2 (VU0) interlock bit set, but not implemented");
	}

	auto& destReg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void EECoreInterpreter::LQC2()
{
	// VF = MEM[UQ]. Address error or TLB error generated.
	auto& destReg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	const s16 imm = getInstruction().getIImmS();

	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	u32 PS2VirtualAddress = (sourceReg->readWordU(0) + imm) & (~static_cast<u32>(0xF)); // Strip the last 4 bits, as the access must be aligned (the documentation says to do this).
	u64 value;
	// TODO: Im not sure if this is correct for big-endian.

	value = getMMUHandler()->readDwordU(PS2VirtualAddress);
	// Check for MMU error (1).
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return; // Return early, dont bother trying to load the second dword.
	}
	else
		destReg->writeDwordU(0, value); // Get first 8 bytes (bytes 0 -> 7).

	value = getMMUHandler()->readDwordU(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD);
	// Check for MMU error (2).
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
	else
		destReg->writeDwordU(1, value); // Get second 8 bytes (bytes 8 -> 15).
}

void EECoreInterpreter::SQC2()
{
	// MEM[UQ] = VF. Address error or TLB error generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()]; // "Base"
	auto& source2Reg = getVM()->getResources()->EE->VPU->VU0->VF[getInstruction().getIRt()];
	const s16 imm = getInstruction().getIImmS();

	// VU0.VF = GPR. Coprocessor unusable exception.
	if (!getVM()->getResources()->EE->VPU->VU0->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 2 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	u32 PS2VirtualAddress = source1Reg->readWordU(0) + imm;

	getMMUHandler()->writeDwordU(PS2VirtualAddress, source2Reg->readDwordU(0));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return; // Return early, dont bother trying to write the second dword.
	}

	getMMUHandler()->writeDwordU(PS2VirtualAddress + Constants::NUMBER_BYTES_IN_DWORD, source2Reg->readDwordU(1));
	// Check for MMU error.
	if (getMMUHandler()->hasExceptionOccurred())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(getMMUHandler()->getExceptionInfo());
		return;
	}
}

void EECoreInterpreter::CFC2()
{
}

void EECoreInterpreter::CTC2()
{
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