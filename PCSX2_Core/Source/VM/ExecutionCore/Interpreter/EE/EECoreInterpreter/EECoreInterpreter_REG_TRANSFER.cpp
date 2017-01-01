#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Util/MathUtil/MathUtil.h"

void EECoreInterpreter::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MOVN()
{
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	if (source2Reg->readDword(0) != 0)
		destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MOVZ()
{
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	if (source2Reg->readDword(0) == 0)
		destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(0, source1Reg->readDword(0));
}

void EECoreInterpreter::MFHI1()
{
	// Rd = HI1. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(0, source1Reg->readDword(1));
}

void EECoreInterpreter::MFLO1()
{
	// Rd = LO1. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(0, source1Reg->readDword(1));
}

void EECoreInterpreter::MTHI1()
{
	// HI1 = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(1, source1Reg->readDword(0));
}

void EECoreInterpreter::MTLO1()
{
	// LO1 = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& destReg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(1, source1Reg->readDword(0));
}

void EECoreInterpreter::PMFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(0, source1Reg->readDword(0));
	destReg->writeDword(1, source1Reg->readDword(1));
}

void EECoreInterpreter::PMFHL()
{
	switch (mInstruction.getRShamt())
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

void EECoreInterpreter::PMFHL_LH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, -1, 3, -1, 6, -1, 7, -1 };
	s32 LOIndex[] = { 0, -1, 1, -1, 4, -1, 5, -1 };
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeHword(HIIndex[i], source1Reg->readHword(i));
		if (LOIndex[i] != -1)
			destReg->writeHword(LOIndex[i], source2Reg->readHword(i));
	}
}

void EECoreInterpreter::PMFHL_LW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 1, -1, 3, -1 };
	s32 LOIndex[] = { 0, -1, 2, -1 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWord(HIIndex[i], source1Reg->readWord(i));
		if (LOIndex[i] != -1)
			destReg->writeWord(LOIndex[i], source2Reg->readWord(i));
	}
}

void EECoreInterpreter::PMFHL_SH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, 3, 6, 7 };
	s32 LOIndex[] = { 0, 1, 4, 5 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));

		if (HIIndex[i] != -1)
			destReg->writeHword(HIIndex[i], MathUtil::saturateWordToHword(source1Val));
		if (LOIndex[i] != -1)
			destReg->writeHword(LOIndex[i], MathUtil::saturateWordToHword(source2Val));
	}
}

void EECoreInterpreter::PMFHL_SLW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	// Indexes 0 and 2 get copied.
	s64 tempValue;
	s32 result;

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWord(0)) << 32) | static_cast<u64>(source2Reg->readWord(0)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDword(0, result);

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWord(2)) << 32) | static_cast<u64>(source2Reg->readWord(2)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDword(1, result);
}

void EECoreInterpreter::PMFHL_UW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->HI;
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { -1, 1, -1, 3 };
	s32 LOIndex[] = { -1, 0, -1, 2 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWord(HIIndex[i], source1Reg->readWord(i));
		if (LOIndex[i] != -1)
			destReg->writeWord(LOIndex[i], source2Reg->readWord(i));
	}
}

void EECoreInterpreter::PMFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source2Reg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(0, source2Reg->readDword(0));
	destReg->writeDword(1, source2Reg->readDword(1));
}

void EECoreInterpreter::PMTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->EE->EECore->R5900->HI;

	destReg->writeDword(0, source1Reg->readDword(0));
	destReg->writeDword(1, source1Reg->readDword(1));
}

void EECoreInterpreter::PMTHL_LW()
{
	// (HI, LO) = Rs. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& dest1Reg = getResources()->EE->EECore->R5900->HI;
	auto& dest2Reg = getResources()->EE->EECore->R5900->LO;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			dest2Reg->writeWord(i, source1Reg->readWord(i));
		else
			dest1Reg->writeWord(i - 1, source1Reg->readWord(i));
	}
}

void EECoreInterpreter::PMTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->EE->EECore->R5900->LO;

	destReg->writeDword(0, source1Reg->readDword(0));
	destReg->writeDword(1, source1Reg->readDword(1));
}

void EECoreInterpreter::MFC1()
{
	// Rt = COP1_FPR[Fs]. Exception on FPU unusable.
	if (!checkCOP1Usable())
        return;

	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs

	destReg->writeWord(0, source1Reg->readWord());

	// Sign extend
	if (FPUUtil::isNegative(source1Reg->readFloat()))
	{
		destReg->writeWord(1, Constants::VALUE_U32_MAX);
		destReg->writeWord(2, Constants::VALUE_U32_MAX);
		destReg->writeWord(3, Constants::VALUE_U32_MAX);
	}
	else
	{
		destReg->writeWord(1, 0);
		destReg->writeWord(2, 0);
		destReg->writeWord(3, 0);
	}
}

void EECoreInterpreter::MOV_S()
{
	// Fd = Fs. Exception on FPU unusable.
	if (!checkCOP1Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& destReg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRShamt()]; // Fd

	destReg->writeFloat(source1Reg->readFloat());
}

void EECoreInterpreter::MTC1()
{
	// COP1_FPR[Fs] = Rt. Exception on FPU unusable.
	if (!checkCOP1Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs

	destReg->writeWord(source1Reg->readWord(0));
}

