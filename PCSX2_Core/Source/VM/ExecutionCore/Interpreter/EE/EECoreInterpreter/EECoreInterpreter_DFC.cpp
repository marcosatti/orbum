#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter::PEXT5()
{
	// Rd = EXTEND[1-5-5-5 -> 32](Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		u16 packedValue = source1Reg->readHword(EE, i);
		u32 temp0 = ((packedValue & 0x1F) << 3);
		u32 temp1 = ((packedValue & 0x3E0) >> 5) << 11;
		u32 temp2 = ((packedValue & 0x7C00) >> 10) << 19;
		u32 temp3 = ((packedValue & 0x8000) >> 16) << 31;
		u32 extendedValue = temp3 | temp2 | temp1 | temp0;
		destReg->writeWord(EE, i / 2, extendedValue);
	}
}

void EECoreInterpreter::PPAC5()
{
	// Rd = PACK[32 -> 1-5-5-5](Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = mEECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 extendedValue = source1Reg->readWord(EE, i);
		u8 temp0 = ((extendedValue & 0xF8) >> 3);
		u8 temp1 = ((extendedValue & 0xF800) >> 11) << 5;
		u8 temp2 = ((extendedValue & 0xF80000) >> 19) << 10;
		u8 temp3 = ((extendedValue & 0x80000000) >> 31) << 15;
		u32 packedValue = 0x0 | temp3 | temp2 | temp1 | temp0; // Slightly different to the above instruction - need to make sure the empty space is packed with 0's.
		destReg->writeWord(EE, i, packedValue);
	}
}

void EECoreInterpreter::CVT_S_W()
{
	// Fd = CONVERT_AND_ROUND<s32 -> f32>(Fs) (Exception on FPU unusable).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mInstruction.getRShamt()]; // Fd

	destReg->writeFloat(EE,static_cast<f32>(source1Reg->readWord(EE)));
}

void EECoreInterpreter::CVT_W_S()
{
	// Fd = CONVERT_AND_ROUND<f32 -> s32>(Fs) (Exception on FPU unusable). Clamping occurs if exponent is > 0x9D.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mInstruction.getRShamt()]; // Fd

	f32 source1Val = source1Reg->readFloat(EE);

	if (FPUUtil::getExponent(source1Val) <= 0x9D)
		destReg->writeWord(EE, static_cast<u32>(source1Val));
	else if (FPUUtil::isNegative(source1Val)) // Clamping has occured, write either S32_MIN or S32_MAX, depending on sign.
		destReg->writeWord(EE, Constants::VALUE_S32_MIN);
	else
		destReg->writeWord(EE, Constants::VALUE_S32_MAX);
}
