#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"

void EECoreInterpreter_s::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MOVN()
{
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	if (source2Reg->readDword(getContext(), 0) != 0)
		destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MOVZ()
{
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	if (source2Reg->readDword(getContext(), 0) == 0)
		destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MFHI1()
{
	// Rd = HI1. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::MFLO1()
{
	// Rd = LO1. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::MTHI1()
{
	// HI1 = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::MTLO1()
{
	// LO1 = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 0));
}

void EECoreInterpreter_s::PMFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::PMFHL()
{
	switch (mEECoreInstruction.getRShamt())
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

void EECoreInterpreter_s::PMFHL_LH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;
	auto& source2Reg = mEECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, -1, 3, -1, 6, -1, 7, -1 };
	s32 LOIndex[] = { 0, -1, 1, -1, 4, -1, 5, -1 };
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeHword(getContext(), HIIndex[i], source1Reg->readHword(getContext(), i));
		if (LOIndex[i] != -1)
			destReg->writeHword(getContext(), LOIndex[i], source2Reg->readHword(getContext(), i));
	}
}

void EECoreInterpreter_s::PMFHL_LW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;
	auto& source2Reg = mEECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 1, -1, 3, -1 };
	s32 LOIndex[] = { 0, -1, 2, -1 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWord(getContext(), HIIndex[i], source1Reg->readWord(getContext(), i));
		if (LOIndex[i] != -1)
			destReg->writeWord(getContext(), LOIndex[i], source2Reg->readWord(getContext(), i));
	}
}

void EECoreInterpreter_s::PMFHL_SH()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;
	auto& source2Reg = mEECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { 2, 3, 6, 7 };
	s32 LOIndex[] = { 0, 1, 4, 5 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(getContext(), i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(getContext(), i));

		if (HIIndex[i] != -1)
			destReg->writeHword(getContext(), HIIndex[i], MathUtil::saturateWordToHword(source1Val));
		if (LOIndex[i] != -1)
			destReg->writeHword(getContext(), LOIndex[i], MathUtil::saturateWordToHword(source2Val));
	}
}

void EECoreInterpreter_s::PMFHL_SLW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;
	auto& source2Reg = mEECore->R5900->LO;

	// Indexes 0 and 2 get copied.
	s64 tempValue;
	s32 result;

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWord(getContext(), 0)) << 32) | static_cast<u64>(source2Reg->readWord(getContext(), 0)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDword(getContext(), 0, result);

	tempValue = static_cast<s64>((static_cast<u64>(source1Reg->readWord(getContext(), 2)) << 32) | static_cast<u64>(source2Reg->readWord(getContext(), 2)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->writeDword(getContext(), 1, result);
}

void EECoreInterpreter_s::PMFHL_UW()
{
	// Rd = (HI, LO). No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;
	auto& source2Reg = mEECore->R5900->LO;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	s32 HIIndex[] = { -1, 1, -1, 3 };
	s32 LOIndex[] = { -1, 0, -1, 2 };
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->writeWord(getContext(), HIIndex[i], source1Reg->readWord(getContext(), i));
		if (LOIndex[i] != -1)
			destReg->writeWord(getContext(), LOIndex[i], source2Reg->readWord(getContext(), i));
	}
}

void EECoreInterpreter_s::PMFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 0, source2Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source2Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::PMTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->HI;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::PMTHL_LW()
{
	// (HI, LO) = Rs. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& dest1Reg = mEECore->R5900->HI;
	auto& dest2Reg = mEECore->R5900->LO;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			dest2Reg->writeWord(getContext(), i, source1Reg->readWord(getContext(), i));
		else
			dest1Reg->writeWord(getContext(), i - 1, source1Reg->readWord(getContext(), i));
	}
}

void EECoreInterpreter_s::PMTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->LO;

	destReg->writeDword(getContext(), 0, source1Reg->readDword(getContext(), 0));
	destReg->writeDword(getContext(), 1, source1Reg->readDword(getContext(), 1));
}

void EECoreInterpreter_s::MFC1()
{
	// Rt = COP1_FPR[Fs]. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs

	destReg->writeWord(getContext(), 0, source1Reg->readWord(getContext()));

	// Sign extend
	if (FPUUtil::isNegative(source1Reg->readFloat(getContext())))
	{
		destReg->writeWord(getContext(), 1, Constants::VALUE_U32_MAX);
		destReg->writeWord(getContext(), 2, Constants::VALUE_U32_MAX);
		destReg->writeWord(getContext(), 3, Constants::VALUE_U32_MAX);
	}
	else
	{
		destReg->writeWord(getContext(), 1, 0);
		destReg->writeWord(getContext(), 2, 0);
		destReg->writeWord(getContext(), 3, 0);
	}
}

void EECoreInterpreter_s::MOV_S()
{
	// Fd = Fs. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd

	destReg->writeFloat(getContext(),source1Reg->readFloat(getContext()));
}

void EECoreInterpreter_s::MTC1()
{
	// COP1_FPR[Fs] = Rt. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs

	destReg->writeWord(getContext(), source1Reg->readWord(getContext(), 0));
}

