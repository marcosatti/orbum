#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Types/EECoreException_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/Types/FPRegister32_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/Util/EECoreCOP1Util/EECoreCOP1Util.h"
#include "Common/Util/MathUtil/MathUtil.h"

void InterpreterEECore::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MOVN()
{
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	if (source2Reg->readDwordU(0) != 0)
		destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MOVZ()
{
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	if (source2Reg->readDwordU(0) == 0)
		destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
}

void InterpreterEECore::MFHI1()
{
	// Rd = HI1. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(1));
}

void InterpreterEECore::MFLO1()
{
	// Rd = LO1. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(1));
}

void InterpreterEECore::MTHI1()
{
	// HI1 = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(1, source1Reg->readDwordU(0));
}

void InterpreterEECore::MTLO1()
{
	// LO1 = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(1, source1Reg->readDwordU(0));
}

void InterpreterEECore::PMFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::PMFHL()
{
	switch (getInstruction().getRShamt())
	{
	case 0x0:
	{
		PMFHL_LW();
		break;
	}
	case 0x1:
	{
		PMFHL_UW();
		break;
	}
	case 0x2:
	{
		PMFHL_SLW();
		break;
	}
	case 0x3:
	{
		PMFHL_LH();
		break;
	}
	case 0x4:
	{
		PMFHL_SH();
		break;
	}
	}
}

void InterpreterEECore::PMFHL_LH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

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

void InterpreterEECore::PMFHL_LW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

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

void InterpreterEECore::PMFHL_SH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

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

void InterpreterEECore::PMFHL_SLW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

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

void InterpreterEECore::PMFHL_UW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

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

void InterpreterEECore::PMFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source2Reg->readDwordU(0));
	destReg->writeDwordU(1, source2Reg->readDwordU(1));
}

void InterpreterEECore::PMTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->HI;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::PMTHL_LW()
{
	// (HI, LO) = Rs. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& dest1Reg = getVM()->getResources()->EE->EECore->R5900->HI;
	auto& dest2Reg = getVM()->getResources()->EE->EECore->R5900->LO;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			dest2Reg->writeWordU(i, source1Reg->readWordU(i));
		else
			dest1Reg->writeWordU(i - 1, source1Reg->readWordU(i));
	}
}

void InterpreterEECore::PMTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->LO;

	destReg->writeDwordU(0, source1Reg->readDwordU(0));
	destReg->writeDwordU(1, source1Reg->readDwordU(1));
}

void InterpreterEECore::MFC1()
{
	// Rt = COP1_FPR[Fs]. Exception on COP1 unusable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs

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

void InterpreterEECore::MOV_S()
{
	// Fd = Fs. Exception on COP1 unusable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRShamt()]; // Fd

	destReg->writeFloat(source1Reg->readFloat());
}

void InterpreterEECore::MTC1()
{
	// COP1_FPR[Fs] = Rt. Exception on COP1 unusable.
	if (!getVM()->getResources()->EE->EECore->COP1->isCOP1Usable())
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		COPExceptionInfo_t copExInfo = { 1 };
		Exceptions->ExceptionQueue->push(EECoreException_t(EECoreException_t::ExType::EX_COPROCESSOR_UNUSABLE, nullptr, nullptr, &copExInfo));
		return;
	}

	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->COP1->FPR[getInstruction().getRRd()]; // Fs

	destReg->writeWordU(source1Reg->readWordU(0));
}

