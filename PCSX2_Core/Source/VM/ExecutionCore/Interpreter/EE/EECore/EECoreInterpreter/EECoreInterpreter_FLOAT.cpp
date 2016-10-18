#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreFPU/EECoreFPU_t.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/COP1_BitfieldRegisters_t.h"
#include "Common/PS2Resources/Types/Registers/FPRegister32_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"

/*
Floating-Point instruction family.
TODO: Check if a convert IEEE to PS2 float function call is needed on the values involved before doing anything - old PCSX2 seems to do this, but there should never be IEEE floats in the registers in the first place (ie: redundant).
*/

void EECoreInterpreter::ADD_S()
{
	// Fd = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	f32 result = source1Reg->readFloat() + source2Reg->readFloat();
	
	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::ADDA_S()
{
	// ACC = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC

	f32 result = source1Reg->readFloat() + source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::MADD_S()
{
	// Fd = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& source3Reg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	f32 result = source3Reg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat());

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::MADDA_S()
{
	// ACC = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC

	f32 result = destReg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat());

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::MUL_S()
{
	// Fd = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	f32 result = source1Reg->readFloat() * source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::MULA_S()
{
	// ACC = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC

	f32 result = source1Reg->readFloat() * source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::DIV_S()
{
	// Fd = Fs / Ft (Exception on FPU unusable).
	// TODO: Check if status bits need to be set.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	// Set flags when special conditions occur.
	f32 result;
	if (source1Reg->readFloat() != 0 && source2Reg->readFloat() == 0)
	{
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::D, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SD, 1);
		result = static_cast<f32>(PS2Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source1Reg->readFloat() == 0 && source2Reg->readFloat() == 0)
	{
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::I, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SI, 1);
		result = static_cast<f32>(PS2Constants::EE::EECore::FPU::FMAX_POS);
	}

	result = source1Reg->readFloat() / source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
		result = FPUUtil::formatIEEEToPS2Float(result);
	else if (FPUUtil::isUnderflowed(result))
		result = FPUUtil::formatIEEEToPS2Float(result);

	destReg->writeFloat(result);
}

void EECoreInterpreter::MSUB_S()
{
	// Fd = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& source3Reg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	f32 result = source3Reg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat());

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::MSUBA_S()
{
	// ACC = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC

	f32 result = destReg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat());

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::SUB_S()
{
	// Fd = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRShamt()]; // Fd

	f32 result = source1Reg->readFloat() - source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void EECoreInterpreter::SUBA_S()
{
	// ACC = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->ACC; // ACC

	f32 result = source1Reg->readFloat() - source2Reg->readFloat();

	if (FPUUtil::isOverflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::O, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SO, 1);
	}
	else if (FPUUtil::isUnderflowed(result))
	{
		result = FPUUtil::formatIEEEToPS2Float(result);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::U, 1);
		getVM()->getResources()->EE->EECore->FPU->CSR->setFieldValue(COP1RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

