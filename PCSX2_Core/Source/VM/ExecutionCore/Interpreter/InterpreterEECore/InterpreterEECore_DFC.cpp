#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"

/*
Data Format Conversion (DFC) instruction family.
*/

void InterpreterEECore::PEXT5()
{
	// Rd = EXTEND[1-5-5-5 -> 32](Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		u16 packedValue = source1Reg->readHwordU(i);
		u32 temp0 = ((packedValue & 0x1F) << 3);
		u32 temp1 = ((packedValue & 0x3E0) >> 5) << 11;
		u32 temp2 = ((packedValue & 0x7C00) >> 10) << 19;
		u32 temp3 = ((packedValue & 0x8000) >> 16) << 31;
		u32 extendedValue = temp3 | temp2 | temp1 | temp0;
		destReg->writeWordU(i / 2, extendedValue);
	}
}

void InterpreterEECore::PPAC5()
{
	// Rd = PACK[32 -> 1-5-5-5](Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 extendedValue = source1Reg->readWordU(i);
		u8 temp0 = ((extendedValue & 0xF8) >> 3);
		u8 temp1 = ((extendedValue & 0xF800) >> 11) << 5;
		u8 temp2 = ((extendedValue & 0xF80000) >> 19) << 10;
		u8 temp3 = ((extendedValue & 0x80000000) >> 31) << 15;
		u32 packedValue = 0x0 | temp3 | temp2 | temp1 | temp0; // Slightly different to the above instruction - need to make sure the empty space is packed with 0's.
		destReg->writeWordU(i, packedValue);
	}
}

void InterpreterEECore::CVT_S_W()
{
	// Fd = CONVERT_AND_ROUND<s32 -> f32>(Fs) (Exception on COP1 unusable).
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRShamt()]; // Fd

	destReg->writeFloat(static_cast<f32>(source1Reg->readWordS()));
}

void InterpreterEECore::CVT_W_S()
{
	// Fd = CONVERT_AND_ROUND<f32 -> s32>(Fs) (Exception on COP1 unusable). Clamping occurs if exponent is > 0x9D.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRShamt()]; // Fd

	f32 source1Val = source1Reg->readFloat();

	if (EECoreCOP1Util::getExponent(source1Val) <= 0x9D)
		destReg->writeWordS(static_cast<s32>(source1Val));
	else if (EECoreCOP1Util::getSign(source1Val)) // Clamping has occured, write either S32_MIN or S32_MAX, depending on sign.
		destReg->writeWordS(Constants::VALUE_S32_MIN);
	else
		destReg->writeWordS(Constants::VALUE_S32_MAX);
}
