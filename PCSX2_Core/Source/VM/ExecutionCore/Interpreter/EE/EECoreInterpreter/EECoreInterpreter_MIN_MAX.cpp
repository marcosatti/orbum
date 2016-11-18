#include "stdafx.h"

#include <algorithm>

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

/*
Min/Max instruction family.
*/

void EECoreInterpreter::PMAXH()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source1Val = source1Reg->readHwordS(i);
		s16 source2Val = source2Reg->readHwordS(i);
		s16 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 1 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeHwordS(i, result);
	}
}

void EECoreInterpreter::PMAXW()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source1Val = source1Reg->readWordS(i);
		s32 source2Val = source2Reg->readWordS(i);
		s32 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns left parameter if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeWordS(i, result);
	}
}

void EECoreInterpreter::PMINH()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source1Val = source1Reg->readHwordS(i);
		s16 source2Val = source2Reg->readHwordS(i);
		s16 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns left parameter if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeHwordS(i, result);
	}
}

void EECoreInterpreter::PMINW()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source1Val = source1Reg->readWordS(i);
		s32 source2Val = source2Reg->readWordS(i);
		s32 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns left parameter if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeWordS(i, result);
	}
}

void EECoreInterpreter::MAX_S()
{
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRShamt()]; // Fd
	auto& CSR = getVM()->getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val >= source2Val) ? source1Val : source2Val;
	destReg->writeFloat(result);

	CSR->setFieldValue(FPURegister_CSR_t::Fields::O, 0); 
	CSR->setFieldValue(FPURegister_CSR_t::Fields::U, 0);
}

void EECoreInterpreter::MIN_S()
{
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->FPU->isCoprocessorUsable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->FPU->FPR[mInstruction.getRShamt()]; // Fd
	auto& CSR = getVM()->getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val <= source2Val) ? source1Val : source2Val;
	destReg->writeFloat(result);

	CSR->setFieldValue(FPURegister_CSR_t::Fields::O, 0);
	CSR->setFieldValue(FPURegister_CSR_t::Fields::U, 0);
}

