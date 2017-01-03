#include "stdafx.h"

#include <algorithm>

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter::PMAXH()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(Context_t::EE, i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(Context_t::EE, i));
		s16 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeHword(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PMAXW()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::EE, i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::EE, i));
		s32 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 0 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeWord(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PMINH()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(Context_t::EE, i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(Context_t::EE, i));
		s16 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeHword(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PMINW()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::EE, i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::EE, i));
		s32 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns parameter 0 if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeWord(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::MAX_S()
{
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& destReg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRShamt()]; // Fd
	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clearFlags();
	f32 source1Val = source1Reg->readFloat(Context_t::EE);
	f32 source2Val = source2Reg->readFloat(Context_t::EE);
	f32 result = (source1Val >= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(Context_t::EE,result);
}

void EECoreInterpreter::MIN_S()
{
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& destReg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRShamt()]; // Fd
	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->clearFlags();
	f32 source1Val = source1Reg->readFloat(Context_t::EE);
	f32 source2Val = source2Reg->readFloat(Context_t::EE);
	f32 result = (source1Val <= source2Val) ? source1Val : source2Val; // Dont have to check for valid float as should already be valid from before.
	destReg->writeFloat(Context_t::EE,result);
}

