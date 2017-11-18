
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Util/FPUUtil/FPUUtil.h"
#include "Common/Util/MathUtil/MathUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"

void EECoreInterpreter_s::MFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->LO;

	destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MOVN()
{
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	if (source2Reg->read_udword(0) != 0)
		destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MOVZ()
{
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	if (source2Reg->read_udword(0) == 0)
		destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->HI;

	destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->LO;

	destReg->write_udword(0, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MFHI1()
{
	// Rd = HI1. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->write_udword(0, source1Reg->read_udword(1));
}

void EECoreInterpreter_s::MFLO1()
{
	// Rd = LO1. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->LO;

	destReg->write_udword(0, source1Reg->read_udword(1));
}

void EECoreInterpreter_s::MTHI1()
{
	// HI1 = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->HI;

	destReg->write_udword(1, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::MTLO1()
{
	// LO1 = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& destReg = mEECore->R5900->LO;

	destReg->write_udword(1, source1Reg->read_udword(0));
}

void EECoreInterpreter_s::PMFHI()
{
	// Rd = HI. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->HI;

	destReg->write_udword(0, source1Reg->read_udword(0));
	destReg->write_udword(1, source1Reg->read_udword(1));
}

void EECoreInterpreter_s::PMFHL()
{
	switch (mEECoreInstruction.shamt())
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
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->write_uhword(HIIndex[i], source1Reg->read_uhword(i));
		if (LOIndex[i] != -1)
			destReg->write_uhword(LOIndex[i], source2Reg->read_uhword(i));
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
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->write_uword(HIIndex[i], source1Reg->read_uword(i));
		if (LOIndex[i] != -1)
			destReg->write_uword(LOIndex[i], source2Reg->read_uword(i));
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
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));

		if (HIIndex[i] != -1)
			destReg->write_uhword(HIIndex[i], MathUtil::saturateWordToHword(source1Val));
		if (LOIndex[i] != -1)
			destReg->write_uhword(LOIndex[i], MathUtil::saturateWordToHword(source2Val));
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

	tempValue = static_cast<s64>((static_cast<udword>(source1Reg->read_uword(0)) << 32) | static_cast<udword>(source2Reg->read_uword(0)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->write_udword(0, result);

	tempValue = static_cast<s64>((static_cast<udword>(source1Reg->read_uword(2)) << 32) | static_cast<udword>(source2Reg->read_uword(2)));
	result = MathUtil::saturateDwordToWord(tempValue);
	destReg->write_udword(1, result);
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
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			destReg->write_uword(HIIndex[i], source1Reg->read_uword(i));
		if (LOIndex[i] != -1)
			destReg->write_uword(LOIndex[i], source2Reg->read_uword(i));
	}
}

void EECoreInterpreter_s::PMFLO()
{
	// Rd = LO. No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->LO;

	destReg->write_udword(0, source2Reg->read_udword(0));
	destReg->write_udword(1, source2Reg->read_udword(1));
}

void EECoreInterpreter_s::PMTHI()
{
	// HI = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->HI;

	destReg->write_udword(0, source1Reg->read_udword(0));
	destReg->write_udword(1, source1Reg->read_udword(1));
}

void EECoreInterpreter_s::PMTHL_LW()
{
	// (HI, LO) = Rs. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& dest1Reg = mEECore->R5900->HI;
	auto& dest2Reg = mEECore->R5900->LO;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			dest2Reg->write_uword(i, source1Reg->read_uword(i));
		else
			dest1Reg->write_uword(i - 1, source1Reg->read_uword(i));
	}
}

void EECoreInterpreter_s::PMTLO()
{
	// LO = Rd. No exceptions.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->LO;

	destReg->write_udword(0, source1Reg->read_udword(0));
	destReg->write_udword(1, source1Reg->read_udword(1));
}

void EECoreInterpreter_s::MFC1()
{
	// Rt = COP1_FPR[Fs]. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs

	destReg->write_uword(0, source1Reg->read_uword());

	// Sign extend
	if (FPUUtil::isNegative(source1Reg->readFloat()))
	{
		destReg->write_uword(1, Constants::VALUE_uword_MAX);
		destReg->write_uword(2, Constants::VALUE_uword_MAX);
		destReg->write_uword(3, Constants::VALUE_uword_MAX);
	}
	else
	{
		destReg->write_uword(1, 0);
		destReg->write_uword(2, 0);
		destReg->write_uword(3, 0);
	}
}

void EECoreInterpreter_s::MOV_S()
{
	// Fd = Fs. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd

	destReg->writeFloat(,source1Reg->readFloat());
}

void EECoreInterpreter_s::MTC1()
{
	// COP1_FPR[Fs] = Rt. Exception on FPU unusable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs

	destReg->write_uword(source1Reg->read_uword(0));
}

