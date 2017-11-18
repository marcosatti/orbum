#include <cmath>
#include <cstdlib>


#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreFpuRegisters.hpp"

void EECoreInterpreter_s::PABSH()
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		if (source2Val == Constants::VALUE_S16_MIN) // Need to account for when the value is at the minimum for s16, as the absolute value will not fit in an s16. In this case it is set to abs(S16_MIN) - 1 aka S16_MAX.
			destReg->write_uhword(i, Constants::VALUE_S16_MAX);
		else
			destReg->write_uhword(i, std::abs(source2Val));
	}
}

void EECoreInterpreter_s::PABSW()
{
	// Rd = ABS(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source2Val = static_cast<s32>(source2Reg->read_uword(i));
		if (source2Val == Constants::VALUE_S32_MIN) // Need to account for when the value is at the minimum for s32, as the absolute value will not fit in an s32. In this case it is set to abs(S32_MIN) - 1 aka S32_MAX.
			destReg->write_uword(i, Constants::VALUE_S32_MAX);
		else
			destReg->write_uword(i, std::abs(source2Val));
	}
}

void EECoreInterpreter_s::PLZCW()
{
	// Rd = ABS(Rt), No exceptions. I do not understand the manuals operation working...
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];

	for (auto i = 0; i < NUMBER_WORDS_IN_DWORD; i++)
	{
		uword source1Val = source1Reg->read_uword(i);
		uword leadingBitsCount = MathUtil::countLeadingBits(source1Val) - 1; // Minus 1 as the PS2 spec requires this (exclude the sign bit in the count).
		destReg->write_uword(i, leadingBitsCount);
	}
}

void EECoreInterpreter_s::ABS_S()
{
	// Fd = ABS(Fs) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	CSR->clear_flags();
	destReg->writeFloat(, std::abs(source1Reg->readFloat())); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void EECoreInterpreter_s::NEG_S()
{
	// Fd = NEG(Fs) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	CSR->clear_flags();
	destReg->writeFloat(, -source1Reg->readFloat()); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void EECoreInterpreter_s::RSQRT_S()
{
	// Fd = RSQRT(Fs, Ft) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	CSR->clear_flags();
	if (source2Val == 0.0F)
	{
		CSR->setFieldValueSticky(, EeCoreFpuRegister_Csr::D, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source2Val < 0.0F)
	{
		CSR->setFieldValueSticky(, EeCoreFpuRegister_Csr::I, 1);
		result = source1Val / std::sqrt(std::abs(source2Val));
	}
	else
	{
		result = source1Val / std::sqrt(source2Val);
	}

	// Update flags.
	FpuFlags flags;
	result = FPUUtil::formatIEEEToPS2Float(result, flags);
	CSR->update_result_flags(flags);

	destReg->writeFloat(, result);
}

void EECoreInterpreter_s::SQRT_S()
{
	// Fd = SQRT(Ft) (Exception on FPU unusable only).
	if (handleCOP1Usable())
        return;

	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	f32 source2Val = source2Reg->readFloat();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	CSR->clear_flags();
	if (source2Val == 0.0F && FPUUtil::isNegative(source2Val))
	{
		result = -0.0F;
	}
	else if (source2Val < 0.0F)
	{
		CSR->setFieldValueSticky(, EeCoreFpuRegister_Csr::I, 1);
		result = std::sqrt(std::abs(source2Val));
	}
	else
	{
		result = std::sqrt(source2Reg->readFloat());
	}

	// Update flags.
	FpuFlags flags;
	result = FPUUtil::formatIEEEToPS2Float(result, flags);
	CSR->update_result_flags(flags);

	destReg->writeFloat(, result);
}

