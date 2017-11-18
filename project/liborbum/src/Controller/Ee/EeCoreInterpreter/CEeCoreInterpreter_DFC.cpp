
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"

void EECoreInterpreter_s::PEXT5()
{
	// Rd = EXTEND[1-5-5-5 -> 32](Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		uhword packedValue = source1Reg->read_uhword(i);
		uword temp0 = ((packedValue & 0x1F) << 3);
		uword temp1 = ((packedValue & 0x3E0) >> 5) << 11;
		uword temp2 = ((packedValue & 0x7C00) >> 10) << 19;
		uword temp3 = ((packedValue & 0x8000) >> 16) << 31;
		uword extendedValue = temp3 | temp2 | temp1 | temp0;
		destReg->write_uword(i / 2, extendedValue);
	}
}

void EECoreInterpreter_s::PPAC5()
{
	// Rd = PACK[32 -> 1-5-5-5](Rt)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		uword extendedValue = source1Reg->read_uword(i);
		ubyte temp0 = ((extendedValue & 0xF8) >> 3);
		ubyte temp1 = ((extendedValue & 0xF800) >> 11) << 5;
		ubyte temp2 = ((extendedValue & 0xF80000) >> 19) << 10;
		ubyte temp3 = ((extendedValue & 0x80000000) >> 31) << 15;
		uword packedValue = 0x0 | temp3 | temp2 | temp1 | temp0; // Slightly different to the above instruction - need to make sure the empty space is packed with 0's.
		destReg->write_uword(i, packedValue);
	}
}

void EECoreInterpreter_s::CVT_S_W()
{
	// Fd = CONVERT_AND_ROUND<s32 -> f32>(Fs) (Exception on FPU unusable).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd

	destReg->writeFloat(,static_cast<f32>(source1Reg->read_uword()));
}

void EECoreInterpreter_s::CVT_W_S()
{
	// Fd = CONVERT_AND_ROUND<f32 -> s32>(Fs) (Exception on FPU unusable). Clamping occurs if exponent is > 0x9D.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd

	f32 source1Val = source1Reg->readFloat();

	if (FPUUtil::getExponent(source1Val) <= 0x9D)
		destReg->write_uword(static_cast<uword>(source1Val));
	else if (FPUUtil::isNegative(source1Val)) // Clamping has occured, write either S32_MIN or S32_MAX, depending on sign.
		destReg->write_uword(Constants::VALUE_S32_MIN);
	else
		destReg->write_uword(Constants::VALUE_S32_MAX);
}
