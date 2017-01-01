#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"

/*
Integer Multiply/Divide instruction family.
*/

void EECoreInterpreter::DIV()
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Val == Constants::VALUE_S32_MIN &&
		source2Val == -1)
	{
		LO->writeDword(0, static_cast<s64>(Constants::VALUE_S32_MIN));
		HI->writeDword(0, static_cast<s64>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		s64 resultQ = source1Val / source2Val;
		s64 resultR = source1Val % source2Val;

		// Quotient.
		LO->writeDword(0, resultQ);

		// Remainder.
		HI->writeDword(0, resultR);
	}
}

void EECoreInterpreter::DIV1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIV();
}

void EECoreInterpreter::DIVU()
{
	// (LO, HI) = SignExtend<u64>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	auto source1Val = static_cast<u32>(source1Reg->readWord(0));
	auto source2Val = static_cast<u32>(source2Reg->readWord(0));

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		u64 resultQ = source1Val / source2Val;
		u64 resultR = source1Val % source2Val;

		// Quotient.
		getResources()->EE->EECore->R5900->LO->writeDword(0, resultQ);

		// Remainder.
		getResources()->EE->EECore->R5900->HI->writeDword(0, resultR);
	}
}

void EECoreInterpreter::DIVU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIVU();
}

void EECoreInterpreter::MULT()
{
	// (Rd, LO, HI) = SignExtend<s64>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	auto source1Val = static_cast<s32>(source1Reg->readWord(0));
	auto source2Val = static_cast<s32>(source2Reg->readWord(0));

	s64 result = source1Val * source2Val;

	destReg->writeDword(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	LO->writeDword(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	HI->writeDword(0, static_cast<s64>(static_cast<s32>(result >> 32)));
}

void EECoreInterpreter::MULT1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULT();
}

void EECoreInterpreter::MULTU()
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	auto source1Val = static_cast<u32>(source1Reg->readWord(0));
	auto source2Val = static_cast<u32>(source2Reg->readWord(0));

	u64 result = source1Val * source2Val;

	destReg->writeDword(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	LO->writeDword(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	HI->writeDword(0, static_cast<u64>(static_cast<u32>(result >> 32)));
}

void EECoreInterpreter::MULTU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULTU();
}

void EECoreInterpreter::PDIVBW()
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SH,0]) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	auto source2Val = static_cast<s16>(source2Reg->readHword(0)); // Constant.

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Val == Constants::VALUE_S32_MIN &&
			source2Val == -1)
		{
			LO->writeWord(i, static_cast<s32>(Constants::VALUE_S32_MIN));
			HI->writeWord(i, static_cast<s32>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Val == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			s32 resultQ = source1Val / source2Val;
			s32 resultR = source1Val % source2Val;

			// Quotient.
			LO->writeWord(i, resultQ);

			// Remainder.
			HI->writeWord(i, resultR);
		}
	}
}

void EECoreInterpreter::PDIVUW()
{
	// (LO, HI)(0,1) = SignExtend<u64>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(i));

		// Check for divide by 0, in which case result is undefined (do nothing).
		if (source2Val == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
		}
		// Else perform normal operation.
		else
		{
			u64 resultQ = source1Val / source2Val;
			u64 resultR = source1Val % source2Val;

			// Quotient.
			LO->writeDword(i / 2, resultQ);

			// Remainder.
			HI->writeDword(i / 2, resultR);
		}
	}
}

void EECoreInterpreter::PDIVW()
{
	// (LO, HI)(0,1) = SignExtend<s64>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Val == Constants::VALUE_S32_MIN &&
			source2Val == -1)
		{
			LO->writeDword(i / 2, static_cast<s64>(Constants::VALUE_S32_MIN));
			HI->writeDword(i / 2, static_cast<s64>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Val == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			u64 resultQ = source1Val / source2Val;
			u64 resultR = source1Val % source2Val;

			// Quotient.
			LO->writeDword(i / 2, resultQ);

			// Remainder.
			HI->writeDword(i / 2, resultR);
		}
	}
}

void EECoreInterpreter::PMULTH()
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()]; // "A"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()]; // "B"
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->readHword(i));
		auto source2Val = static_cast<s16>(source2Reg->readHword(i));
		s32 result = source1Val * source2Val;

		if (i % 2 == 0)
			destReg->writeWord(i / 2, result); // Write to Rd for even indexes. A0xB0, A2xB2, A4xB4, A6xB6.

		if ((i / 2) % 2 == 0)
			LO->writeWord(((i / 2 > 0) ? i - 2 : i), result); // A0xB0, A1xB1, A4xB4, A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
		else
			HI->writeWord(((i / 2 > 1) ? i - 4 : i - 2), result); // A2xB2, A3xB3, A6xB6, A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
	}
}

void EECoreInterpreter::PMULTUW()
{
	// (LO, HI, Rd) = SignExtend<u64>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<u32>(source1Reg->readWord(i));
		auto source2Val = static_cast<u32>(source2Reg->readWord(i));
		u64 result = source1Val * source2Val;

		LO->writeDword(i / 2, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
		HI->writeDword(i / 2, static_cast<u64>(static_cast<u32>(result >> 32)));
		destReg->writeDword(i / 2, result);
	}
}

void EECoreInterpreter::PMULTW()
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& LO = getResources()->EE->EECore->R5900->LO;
	auto& HI = getResources()->EE->EECore->R5900->HI;

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<s32>(source1Reg->readWord(i));
		auto source2Val = static_cast<s32>(source2Reg->readWord(i));
		s64 result = source1Val * source2Val;

		LO->writeDword(i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		HI->writeDword(i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDword(i / 2, result);
	}
}