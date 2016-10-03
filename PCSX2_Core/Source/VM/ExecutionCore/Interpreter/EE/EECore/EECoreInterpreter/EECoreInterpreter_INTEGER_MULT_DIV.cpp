#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

/*
Integer Multiply/Divide instruction family.
*/

void EECoreInterpreter::DIV()
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Reg->readWordS(0) == Constants::VALUE_S32_MIN &&
		source2Reg->readWordS(0) == -1)
	{
		getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(0, static_cast<s64>(Constants::VALUE_S32_MIN));
		getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(0, static_cast<s64>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Reg->readWordS(0) == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(0, static_cast<s64>(source1Reg->readWordS(0) / source2Reg->readWordS(0)));

		// Remainder.
		getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(0, static_cast<s64>(source1Reg->readWordS(0) % source2Reg->readWordS(0)));
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
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Reg->readWordU(0) == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		getVM()->getResources()->EE->EECore->R5900->LO->writeDwordU(0, static_cast<u64>(source1Reg->readWordU(0) / source2Reg->readWordU(0)));

		// Remainder.
		getVM()->getResources()->EE->EECore->R5900->HI->writeDwordU(0, static_cast<u64>(source1Reg->readWordU(0) % source2Reg->readWordU(0)));
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
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	s64 result = source1Reg->readWordS(0) * source2Reg->readWordS(0);
	destReg->writeDwordS(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(0, static_cast<s64>(static_cast<s32>(result >> 32)));
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
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	u64 result = source1Reg->readWordU(0) * source2Reg->readWordU(0);
	destReg->writeDwordU(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	getVM()->getResources()->EE->EECore->R5900->LO->writeDwordU(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	getVM()->getResources()->EE->EECore->R5900->HI->writeDwordU(0, static_cast<u64>(static_cast<u32>(result >> 32)));
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
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Reg->readWordS(i) == Constants::VALUE_S32_MIN &&
			source2Reg->readHwordS(0) == -1)
		{
			getVM()->getResources()->EE->EECore->R5900->LO->writeWordS(i, static_cast<s32>(Constants::VALUE_S32_MIN));
			getVM()->getResources()->EE->EECore->R5900->HI->writeWordS(i, static_cast<s32>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Reg->readHwordS(0) == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			getVM()->getResources()->EE->EECore->R5900->LO->writeWordS(i, static_cast<s64>(source1Reg->readWordS(i) / source2Reg->readHwordS(0)));

			// Remainder.
			getVM()->getResources()->EE->EECore->R5900->HI->writeWordS(i, static_cast<s64>(source1Reg->readWordS(i) % source2Reg->readHwordS(0)));
		}
	}
}

void EECoreInterpreter::PDIVUW()
{
	// (LO, HI)(0,1) = SignExtend<u64>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		// Check for divide by 0, in which case result is undefined (do nothing).
		if (source2Reg->readWordU(i) == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			getVM()->getResources()->EE->EECore->R5900->LO->writeDwordU(i / 2, static_cast<u64>(source1Reg->readWordU(i) / source2Reg->readWordU(i)));

			// Remainder.
			getVM()->getResources()->EE->EECore->R5900->HI->writeDwordU(i / 2, static_cast<u64>(source1Reg->readWordU(i) % source2Reg->readWordU(i)));
		}
	}
}

void EECoreInterpreter::PDIVW()
{
	// (LO, HI)(0,1) = SignExtend<u64>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Reg->readWordS(i) == Constants::VALUE_S32_MIN 
			&& source2Reg->readWordS(i) == -1)
		{
			getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(i / 2, static_cast<s64>(Constants::VALUE_S32_MIN));
			getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(i / 2, static_cast<s64>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Reg->readWordS(i) == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			// Quotient.
			getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(i / 2, static_cast<s64>(source1Reg->readWordS(i) / source2Reg->readWordS(i)));

			// Remainder.
			getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(i / 2, static_cast<s64>(source1Reg->readWordS(i) % source2Reg->readWordS(i)));
		}
	}
}

void EECoreInterpreter::PMULTH()
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()]; // "A"
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()]; // "B"
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordS(i) * source2Reg->readHwordS(i);

		if (i % 2 == 0)
			destReg->writeWordS(i / 2, result); // Write to Rd for even indexes. A0xB0, A2xB2, A4xB4, A6xB6.

		if ((i / 2) % 2 == 0)
			getVM()->getResources()->EE->EECore->R5900->LO->writeWordS(((i / 2 > 0) ? i - 2 : i), result); // A0xB0, A1xB1, A4xB4, A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
		else
			getVM()->getResources()->EE->EECore->R5900->HI->writeWordS(((i / 2 > 1) ? i - 4 : i - 2), result); // A2xB2, A3xB3, A6xB6, A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
	}
}

void EECoreInterpreter::PMULTUW()
{
	// (LO, HI, Rd) = SignExtend<u64>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u64 result = source1Reg->readWordU(i) * source2Reg->readWordU(i);

		getVM()->getResources()->EE->EECore->R5900->LO->writeDwordU(i / 2, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
		getVM()->getResources()->EE->EECore->R5900->HI->writeDwordU(i / 2, static_cast<u64>(static_cast<u32>(result >> 32)));
		destReg->writeDwordU(i / 2, result);
	}
}

void EECoreInterpreter::PMULTW()
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		s64 result = source1Reg->readWordS(i) * source2Reg->readWordS(i);

		getVM()->getResources()->EE->EECore->R5900->LO->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		getVM()->getResources()->EE->EECore->R5900->HI->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDwordS(i / 2, result);
	}
}