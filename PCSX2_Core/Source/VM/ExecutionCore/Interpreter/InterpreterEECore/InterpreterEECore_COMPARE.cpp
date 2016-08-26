#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VMMain.h"
#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"

/*
Compare instruction family.
*/

void InterpreterEECore::SLT()
{
	// Rd = SignExtended<s64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	s64 source1Val = source1Reg->readDwordS(0);
	s64 source2Val = source2Reg->readDwordS(0);
	s64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::SLTI()
{
	// Rd = SignExtended<s64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];

	s64 source1Val = source1Reg->readDwordS(0);
	s64 imm = static_cast<s64>(getInstruction().getIImmS());
	s64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::SLTIU()
{
	// Rd = SignExtended<u64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];

	u64 source1Val = source1Reg->readDwordU(0);
	u64 imm = static_cast<u64>(getInstruction().getIImmU());
	u64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDwordU(0, result);
}

void InterpreterEECore::SLTU()
{
	// Rd = SignExtended<u64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	u64 source1Val = source1Reg->readDwordU(0);
	u64 source2Val = source2Reg->readDwordU(0);
	u64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDwordU(0, result);
}

void InterpreterEECore::PCEQB()
{
	// Rd = SignExtended<u8>((Rs == Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByteU(i);
		u8 source2Val = source2Reg->readByteU(i);
		u8 result = (source1Val == source2Val) ? 0xFF : 0x00;
		destReg->writeByteU(i, result);
	}
}

void InterpreterEECore::PCEQH()
{
	// Rd = SignExtended<u16>((Rs == Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHwordU(i);
		u16 source2Val = source2Reg->readHwordU(i);
		u16 result = (source1Val == source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHwordU(i, result);
	}
}

void InterpreterEECore::PCEQW()
{
	// Rd = SignExtended<u32>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWordU(i);
		u32 source2Val = source2Reg->readWordU(i);
		u32 result = (source1Val == source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWordU(i, result);
	}
}

void InterpreterEECore::PCGTB()
{
	// Rd = SignExtended<u8>((Rs > Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByteU(i);
		u8 source2Val = source2Reg->readByteU(i);
		u8 result = (source1Val > source2Val) ? 0xFF : 0x00;
		destReg->writeByteU(i, result);
	}
}

void InterpreterEECore::PCGTH()
{
	// Rd = SignExtended<u16>((Rs > Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHwordU(i);
		u16 source2Val = source2Reg->readHwordU(i);
		u16 result = (source1Val > source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHwordU(i, result);
	}
}

void InterpreterEECore::PCGTW()
{
	// Rd = SignExtended<u32>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWordU(i);
		u32 source2Val = source2Reg->readWordU(i);
		u32 result = (source1Val > source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWordU(i, result);
	}
}

void InterpreterEECore::C_EQ_S()
{
	// (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRt()]; // Ft
	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val == source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_F_S()
{
	// TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
	// (FCR[31] or CSR, C field) = 0
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_LE_S()
{
	// (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRt()]; // Ft
	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val <= source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_LT_S()
{
	// (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& source2Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRt()]; // Ft
	auto& CSR = getVM()->getResources()->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val < source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}


