#include <cmath>
#include <cstdlib>

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter_s::PABSH()
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source2Val = static_cast<s16>(source2Reg->readHword(getContext(), i));
		if (source2Val == Constants::VALUE_S16_MIN) // Need to account for when the value is at the minimum for s16, as the absolute value will not fit in an s16. In this case it is set to abs(S16_MIN) - 1 aka S16_MAX.
			destReg->writeHword(getContext(), i, Constants::VALUE_S16_MAX);
		else
			destReg->writeHword(getContext(), i, std::abs(source2Val));
	}
}

void EECoreInterpreter_s::PABSW()
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));
		if (source2Val == Constants::VALUE_S32_MIN) // Need to account for when the value is at the minimum for s32, as the absolute value will not fit in an s32. In this case it is set to abs(S32_MIN) - 1 aka S32_MAX.
			destReg->writeWord(getContext(), i, Constants::VALUE_S32_MAX);
		else
			destReg->writeWord(getContext(), i, std::abs(source2Val));
	}
}

void EECoreInterpreter_s::PLZCW()
{
	// Rd = ABS(Rt), No exceptions. I do not understand the manuals operation working...
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_DWORD; i++)
	{
		u32 source1Val = source1Reg->readWord(getContext(), i);
		u32 leadingBitsCount = MathUtil::countLeadingBits(source1Val) - 1; // Minus 1 as the PS2 spec requires this (exclude the sign bit in the count).
		destReg->writeWord(getContext(), i, leadingBitsCount);
	}
}

void EECoreInterpreter_s::ABS_S()
{
	// Fd = ABS(Fs) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	CSR->clearFlags(getContext());
	destReg->writeFloat(getContext(), std::abs(source1Reg->readFloat(getContext()))); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void EECoreInterpreter_s::NEG_S()
{
	// Fd = NEG(Fs) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	CSR->clearFlags(getContext());
	destReg->writeFloat(getContext(), -source1Reg->readFloat(getContext())); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void EECoreInterpreter_s::RSQRT_S()
{
	// Fd = RSQRT(Fs, Ft) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	CSR->clearFlags(getContext());
	if (source2Val == 0.0F)
	{
		CSR->setFieldValueSticky(getContext(), EECoreFPURegister_CSR_t::Fields::D, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source2Val < 0.0F)
	{
		CSR->setFieldValueSticky(getContext(), EECoreFPURegister_CSR_t::Fields::I, 1);
		result = source1Val / std::sqrt(std::abs(source2Val));
	}
	else
	{
		result = source1Val / std::sqrt(source2Val);
	}

	// Update flags.
	FPUFlags_t flags;
	result = FPUUtil::formatIEEEToPS2Float(result, flags);
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(), result);
}

void EECoreInterpreter_s::SQRT_S()
{
	// Fd = SQRT(Ft) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	f32 source2Val = source2Reg->readFloat(getContext());
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	CSR->clearFlags(getContext());
	if (source2Val == 0.0F && FPUUtil::isNegative(source2Val))
	{
		result = -0.0F;
	}
	else if (source2Val < 0.0F)
	{
		CSR->setFieldValueSticky(getContext(), EECoreFPURegister_CSR_t::Fields::I, 1);
		result = std::sqrt(std::abs(source2Val));
	}
	else
	{
		result = std::sqrt(source2Reg->readFloat(getContext()));
	}

	// Update flags.
	FPUFlags_t flags;
	result = FPUUtil::formatIEEEToPS2Float(result, flags);
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(), result);
}

