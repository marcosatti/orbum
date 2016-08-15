#include "stdafx.h"

#include <algorithm>

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"

/*
Min/Max instruction family.
*/

void InterpreterEECore::PMAXH()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source1Val = source1Reg->readHwordS(i);
		s16 source2Val = source2Reg->readHwordS(i);
		s16 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns parameter 1 if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeHwordS(i, result);
	}
}

void InterpreterEECore::PMAXW()
{
	// Rd = MAX(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source1Val = source1Reg->readWordS(i);
		s32 source2Val = source2Reg->readWordS(i);
		s32 result = std::max(source2Val, source1Val); // Format parameters this way as std::max returns left parameter if they are equal, and value in Rt is returned according to docs if they are equal.
		destReg->writeWordS(i, result);
	}
}

void InterpreterEECore::PMINH()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s16 source1Val = source1Reg->readHwordS(i);
		s16 source2Val = source2Reg->readHwordS(i);
		s16 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns left parameter if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeHwordS(i, result);
	}
}

void InterpreterEECore::PMINW()
{
	// Rd = MIN(Rs, Rt)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s32 source1Val = source1Reg->readWordS(i);
		s32 source2Val = source2Reg->readWordS(i);
		s32 result = std::min(source1Val, source2Val); // Format parameters this way as std::min returns left parameter if they are equal, and value in Rs is returned according to docs if they are equal.
		destReg->writeWordS(i, result);
	}
}

void InterpreterEECore::MAX_S()
{
	// Fd = MAX(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRShamt()]; // Fd
	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val >= source2Val) ? source1Val : source2Val;
	destReg->writeFloat(result);

	CSR->setFieldValue(RegisterCSR_t::Fields::O, 0); 
	CSR->setFieldValue(RegisterCSR_t::Fields::U, 0);
}

void InterpreterEECore::MIN_S()
{
	// Fd = MIN(Fs, Ft), flags set.
	// No Exceptions generated, except for coprocessor unavailable.
	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRt()]; // Ft
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRShamt()]; // Fd
	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();
	f32 result = (source1Val <= source2Val) ? source1Val : source2Val;
	destReg->writeFloat(result);

	CSR->setFieldValue(RegisterCSR_t::Fields::O, 0);
	CSR->setFieldValue(RegisterCSR_t::Fields::U, 0);
}

