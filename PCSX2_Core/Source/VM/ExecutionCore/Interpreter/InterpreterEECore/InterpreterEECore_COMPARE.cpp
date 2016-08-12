#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"
#include "Common/Util/EECoreFPUUtil/EECoreFPUUtil.h"

/*
Compare instruction family.
*/

void InterpreterEECore::SLT(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<s64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	s64 source1Val = source1Reg->readDwordS(0);
	s64 source2Val = source2Reg->readDwordS(0);
	s64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::SLTI(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<s64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];

	s64 source1Val = source1Reg->readDwordS(0);
	s64 imm = static_cast<s64>(instruction.getIImmS());
	s64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::SLTIU(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];

	u64 source1Val = source1Reg->readDwordU(0);
	u64 imm = static_cast<u64>(instruction.getIImmU());
	u64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDwordU(0, result);
}

void InterpreterEECore::SLTU(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	u64 source1Val = source1Reg->readDwordU(0);
	u64 source2Val = source2Reg->readDwordU(0);
	u64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDwordU(0, result);
}

void InterpreterEECore::PCEQB(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u8>((Rs == Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByteU(i);
		u8 source2Val = source2Reg->readByteU(i);
		u8 result = (source1Val == source2Val) ? 0xFF : 0x00;
		destReg->writeByteU(i, result);
	}
}

void InterpreterEECore::PCEQH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u16>((Rs == Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHwordU(i);
		u16 source2Val = source2Reg->readHwordU(i);
		u16 result = (source1Val == source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHwordU(i, result);
	}
}

void InterpreterEECore::PCEQW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u32>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWordU(i);
		u32 source2Val = source2Reg->readWordU(i);
		u32 result = (source1Val == source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWordU(i, result);
	}
}

void InterpreterEECore::PCETB(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u8>((Rs > Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByteU(i);
		u8 source2Val = source2Reg->readByteU(i);
		u8 result = (source1Val > source2Val) ? 0xFF : 0x00;
		destReg->writeByteU(i, result);
	}
}

void InterpreterEECore::PCETH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u16>((Rs > Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHwordU(i);
		u16 source2Val = source2Reg->readHwordU(i);
		u16 result = (source1Val > source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHwordU(i, result);
	}
}

void InterpreterEECore::PCETW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = SignExtended<u32>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWordU(i);
		u32 source2Val = source2Reg->readWordU(i);
		u32 result = (source1Val > source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWordU(i, result);
	}
}

void InterpreterEECore::C_EQ_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& CSR = PS2Resources->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	if (EECoreFPUUtil::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val == source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_F_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
	// (FCR[31] or CSR, C field) = 0
	auto& CSR = PS2Resources->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	if (EECoreFPUUtil::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_LE_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& CSR = PS2Resources->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	if (EECoreFPUUtil::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val <= source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}

void InterpreterEECore::C_LT_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& source2Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRt()]; // Ft
	auto& CSR = PS2Resources->EE->EECore->COP1->CSR; // FCR[31] aka control status register.

	if (EECoreFPUUtil::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	f32 source1Val = source1Reg->readFloat();
	f32 source2Val = source2Reg->readFloat();

	if (source1Val < source2Val)
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(RegisterCSR_t::Fields::C, 0);
}


