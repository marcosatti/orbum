#include "stdafx.h"

#include <cmath>

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

void InterpreterEECore::PABSH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source2Val = source2Reg->readHwordS(i);
		if (source2Val == Constants::VALUE_S16_MIN) // Need to account for when the value is at the minimum for s16, as the absolute value will not fit in an s16. In this case it is set to abs(S16_MIN) - 1 aka S16_MAX.
			destReg->writeHwordS(i, Constants::VALUE_S16_MAX);
		else
			destReg->writeHwordS(i, std::abs(source2Val));
	}
}

void InterpreterEECore::PABSW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source2Val = source2Reg->readWordS(i);
		if (source2Val == Constants::VALUE_S32_MIN) // Need to account for when the value is at the minimum for s32, as the absolute value will not fit in an s32. In this case it is set to abs(S32_MIN) - 1 aka S32_MAX.
			destReg->writeWordS(i, Constants::VALUE_S32_MAX);
		else
			destReg->writeWordS(i, std::abs(source2Val));
	}
}

void InterpreterEECore::PLZCW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = ABS(Rt), No exceptions. I do not understand the manuals operation working...
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_DWORD; i++)
	{
		u32 source1Val = source1Reg->readWordS(i);
		u32 leadingBitsCount = MathUtil::countLeadingBits(source1Val) - 1; // Minus 1 as the PS2 spec requires this (exclude the sign bit in the count).
		destReg->writeWordU(i, leadingBitsCount);
	}
}

void InterpreterEECore::ABS_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Fd = ABS(Fs) (Exception on COP1 unusable only).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	destReg->writeFloat(std::abs(source1Reg->readFloat())); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.

	PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 0);
	PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 0);
}

void InterpreterEECore::NEG_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Fd = NEG(Fs) (Exception on COP1 unusable only).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	destReg->writeFloat(-source1Reg->readFloat()); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.

	PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::O, 0);
	PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::U, 0);
}

void InterpreterEECore::RSQRT_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Fd = RSQRT(Fs, Ft) (Exception on COP1 unusable only).
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	if (source2Val == 0.0F)
	{
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::D, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SD, 1);
		result = static_cast<f32>(PS2Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source2Val < 0.0F)
	{
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::I, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SI, 1);
		result = source1Val / std::sqrtf(std::abs(source2Val));
	}
	else
	{
		result = source1Val / std::sqrtf(source2Val);
	}

	// Check for overflow or underflow (no flags set?).
	if (EECoreCOP1Util::isOverflowed(result) || EECoreCOP1Util::isUnderflowed(result))
		result = EECoreCOP1Util::formatIEEEToPS2Float(result);
		
	destReg->writeFloat(result);
}

void InterpreterEECore::SQRT_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Fd = SQRT(Ft) (Exception on COP1 unusable only).
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 source2Val = source2Reg->readFloat();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	if (source2Val == 0.0F && EECoreCOP1Util::getSign(source2Val))
	{
		result = -0.0F;
	}
	else if (source2Val < 0.0F)
	{
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::I, 1);
		PS2Resources->EE->EECore->COP1->CSR->setFieldValue(RegisterCSR_t::Fields::SI, 1);
		result = std::sqrtf(std::abs(source2Val));
	}
	else
	{
		result = std::sqrtf(source2Val);
	}

	destReg->writeFloat(result);
}

