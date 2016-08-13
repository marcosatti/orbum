#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"

/*
Floating-Point instruction family.
TODO: Check if a convert IEEE to PS2 float function call is needed on the values involved before doing anything - old PCSX2 seems to do this, but there should never be IEEE floats in the registers in the first place (ie: redundant).
*/

void InterpreterEECore::ADD_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Fd = Fs + Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() + source2Reg->readFloat();
	
	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::ADDA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// ACC = Fs + Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->ACC; // ACC

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() + source2Reg->readFloat();

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MADD_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Fd = ACC + (Fs * Ft) (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& source3Reg = PS2Resources->EE->EECore->COP1->ACC; // ACC
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source3Reg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat());

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MADDA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// ACC = ACC + (Fs * Ft) (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->ACC; // ACC

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = destReg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat());

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MUL_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Fd = Fs * Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() * source2Reg->readFloat();

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MULA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// ACC = Fs * Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->ACC; // ACC

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() * source2Reg->readFloat();

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MSUB_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Fd = ACC - (Fs * Ft) (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& source3Reg = PS2Resources->EE->EECore->COP1->ACC; // ACC
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source3Reg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat());

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::MSUBA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// ACC = ACC - (Fs * Ft) (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->ACC; // ACC

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = destReg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat());

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::SUB_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Fd = Fs - Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() - source2Reg->readFloat();

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

void InterpreterEECore::SUBA_S(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// ACC = Fs - Ft (Exception on COP1 unusable).
	// COP1 status bits set on exponent overflow/underflow (no exception generated).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->ACC; // ACC

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 result = source1Reg->readFloat() - source2Reg->readFloat();

	if (EECoreCOP1Util::isOverflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SO, 1);
	}
	else if (EECoreCOP1Util::isUnderflowed(result))
	{
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SU, 1);
	}

	destReg->writeFloat(result);
}

