#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

void InterpreterEECore::MFHI(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = HI. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MFLO(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = LO. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MOVN(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	if (source2Reg->readDwordU(0) != 0)
		destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MOVZ(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];

	if (source2Reg->readDwordU(0) == 0)
		destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTHI(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// HI = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& destReg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTLO(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// LO = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& destReg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MFHI1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = HI1. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(1));
}

void InterpreterEECore::MFLO1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = LO1. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(1));
}

void InterpreterEECore::MTHI1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// HI1 = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& destReg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(1, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTLO1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// LO1 = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& destReg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeDwordU(1, source1Reg->readDwordU(0));
}

void InterpreterEECore::PMFHI(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = HI. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::PMFHL_LH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, -1, 3, -1, 6, -1, 7, -1 };
	s32 LOIndex[] = { 0, -1, 1, -1, 4, -1, 5, -1 };
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeHwordU(HIIndex[i], source1Reg->readHwordU(i));
		if (LOIndex[i] != -1)
			destReg->writeHwordU(LOIndex[i], source2Reg->readHwordU(i));
	}
}

void InterpreterEECore::PMFHL_LW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 1, -1, 3, -1 };
	s32 LOIndex[] = { 0, -1, 2, -1 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWordU(HIIndex[i], source1Reg->readWordU(i));
		if (LOIndex[i] != -1)
			destReg->writeWordU(LOIndex[i], source2Reg->readWordU(i));
	}
}

void InterpreterEECore::PMFHL_SH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, 3, 6, 7 };
	s32 LOIndex[] = { 0, 1, 4, 5 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeHwordS(HIIndex[i], MathUtil::saturateWordToHword(source1Reg->readWordS(i)));
		if (LOIndex[i] != -1)
			destReg->writeHwordS(LOIndex[i], MathUtil::saturateWordToHword(source2Reg->readWordS(i)));
	}
}

void InterpreterEECore::PMFHL_SLW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	// Indexes 0 and 2 get copied.
	s64 tempValue;
	s32 result;

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWordU(0)) << 32) || static_cast<u64>(source2Reg->readWordU(0)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDwordS(0, result);

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWordU(2)) << 32) || static_cast<u64>(source2Reg->readWordU(2)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDwordS(1, result);
}

void InterpreterEECore::PMFHL_UW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { -1, 1, -1, 3 };
	s32 LOIndex[] = { -1, 0, -1, 2 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWordU(HIIndex[i], source1Reg->readWordU(i));
		if (LOIndex[i] != -1)
			destReg->writeWordU(LOIndex[i], source2Reg->readWordU(i));
	}
}

void InterpreterEECore::PMFLO(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = LO. No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeWordU(0, source2Reg->readDwordU(0));
	destReg->writeWordU(1, source2Reg->readDwordU(1));
}

void InterpreterEECore::PMTHI(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// HI = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& destReg = PS2Resources->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::PMTHL_LW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// (HI, LO) = Rs. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& dest1Reg = PS2Resources->EE->EECore->R5900->HI;
	auto& dest2Reg = PS2Resources->EE->EECore->R5900->LO;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			dest2Reg->writeWordU(i, source1Reg->readWordU(i));
		else
			dest1Reg->writeWordU(i - 1, source1Reg->readWordU(i));
	}
}

void InterpreterEECore::PMTLO(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// LO = Rd. No exceptions.
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& destReg = PS2Resources->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::MFC1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	destReg->writeWordU(0, source1Reg->readWordU());

	// Sign extend
	if (EECoreCOP1Util::getSign(source1Reg->readFloat()))
	{
		destReg->writeWordU(1, Constants::VALUE_U32_MAX);
		destReg->writeWordU(2, Constants::VALUE_U32_MAX);
		destReg->writeWordU(3, Constants::VALUE_U32_MAX);
	}
	else
	{
		destReg->writeWordU(1, 0);
		destReg->writeWordU(2, 0);
		destReg->writeWordU(3, 0);
	}
}

void InterpreterEECore::MOV_S(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	auto& source1Reg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRShamt()]; // Fd

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	destReg->writeFloat(source1Reg->readFloat());
}

void InterpreterEECore::MTC1(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];
	auto& destReg = PS2Resources->EE->EECore->COP1->FPR[instruction.getRRd()]; // Fs

	if (EECoreCOP1Util::isCOP1Unusable(PS2Resources))
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_COPROCESSOR_UNUSABLE);

	destReg->writeWordU(source1Reg->readWordU(0));
}
