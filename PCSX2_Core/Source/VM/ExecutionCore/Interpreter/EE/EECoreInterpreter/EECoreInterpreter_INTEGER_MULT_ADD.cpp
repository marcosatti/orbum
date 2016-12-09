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
Integer Multiply-Add instruction family.
*/

void EECoreInterpreter::MADD()
{
	// (LO, HI, Rd) = (LO || HI) + SignExtend<s64>(Rs[SW] * Rt[SW])
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	s64 result = ((static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordS(0)) << 32) || static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordS(0))) + (source1Reg->readWordS(0) * source2Reg->readWordS(0));
	getResources()->EE->EECore->R5900->LO->writeDwordS(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	getResources()->EE->EECore->R5900->HI->writeDwordS(0, static_cast<s64>(static_cast<s32>(result >> 32)));
	destReg->writeDwordS(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
}

void EECoreInterpreter::MADD1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADD();
}

void EECoreInterpreter::MADDU()
{
	// (LO, HI, Rd) = (LO || HI) + SignExtend<u64>(Rs[UW] * Rt[UW])
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	u64 result = ((static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordU(0)) << 32) || static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordU(0))) + (source1Reg->readWordU(0) * source2Reg->readWordU(0));
	getResources()->EE->EECore->R5900->LO->writeDwordS(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
	getResources()->EE->EECore->R5900->HI->writeDwordS(0, static_cast<u64>(static_cast<u32>(result >> 32)));
	destReg->writeDwordS(0, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
}

void EECoreInterpreter::MADDU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADDU();
}

void EECoreInterpreter::PHMADH()
{
	// (LO, HI, Rd)[i] = SignExtend<s32>(Rs[SH] * Rt[SH])[i] + SignExtend<s32>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		s32 result = (source1Reg->readHwordS(i + 1) * source2Reg->readHwordS(i + 1)) + (source1Reg->readHwordS(i) * source2Reg->readHwordS(i));

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			getResources()->EE->EECore->R5900->LO->writeWordS((i / 4) * 2, result);
		else
			getResources()->EE->EECore->R5900->HI->writeWordS(((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		destReg->writeWordS(i / 2, result);
	}
}

void EECoreInterpreter::PHMSBH()
{
	// (LO, HI, Rd)[i] = SignExtend<s32>(Rs[SH] * Rt[SH])[i] - SignExtend<s32>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		s32 result = (source1Reg->readHwordS(i + 1) * source2Reg->readHwordS(i + 1)) - (source1Reg->readHwordS(i) * source2Reg->readHwordS(i));

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			getResources()->EE->EECore->R5900->LO->writeWordS((i / 4) * 2, result);
		else
			getResources()->EE->EECore->R5900->HI->writeWordS(((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		destReg->writeWordS(i / 2, result);
	}
}

void EECoreInterpreter::PMADDH()
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH] + (HI,LO)[i]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()]; // "A"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()]; // "B"
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordS(i) * source2Reg->readHwordS(i);

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // A0xB0 + C0, A1xB1 + C1, A4xB4 + C4, A5xB5 + C5. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + getResources()->EE->EECore->R5900->LO->readWordS(index); 
			getResources()->EE->EECore->R5900->LO->writeWordS(index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // A2xB2 + C2, A3xB3 + C3, A6xB6 + C6, A7xB7 + C7. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + getResources()->EE->EECore->R5900->HI->readWordS(index); 
			getResources()->EE->EECore->R5900->HI->writeWordS(index, result);
		}
			
		if (i % 2 == 0)
			destReg->writeWordS(i / 2, result); // Write to Rd for even indexes. A0xB0 + C0, A2xB2 + C2, A4xB4 + C4, A6xB6 + C6.
	}
}

void EECoreInterpreter::PMADDUW()
{
	// (LO, HI, Rd) = SignExtend<u64>(Rs[UW] * Rt[UW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 218).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		u64 result = source1Reg->readWordU(i) * source2Reg->readWordU(i) + ((static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordU(i)) << 32) || static_cast<u64>(getResources()->EE->EECore->R5900->LO->readWordU(i)));

		getResources()->EE->EECore->R5900->LO->writeDwordU(i / 2, static_cast<u64>(static_cast<u32>(result & 0xFFFFFFFF)));
		getResources()->EE->EECore->R5900->HI->writeDwordU(i / 2, static_cast<u64>(static_cast<u32>(result >> 32)));
		destReg->writeDwordU(i / 2, result);
	}
}

void EECoreInterpreter::PMADDW()
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 220).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		s64 result = source1Reg->readWordS(i) * source2Reg->readWordS(i) + ((static_cast<s64>(getResources()->EE->EECore->R5900->LO->readWordS(i)) << 32) || static_cast<s64>(getResources()->EE->EECore->R5900->LO->readWordS(i)));

		getResources()->EE->EECore->R5900->LO->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		getResources()->EE->EECore->R5900->HI->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDwordS(i / 2, result);
	}
}

void EECoreInterpreter::PMSUBH()
{
	// (LO, HI, Rd) = SignExtend<s32>((HI,LO)[i] - Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()]; // "A"
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()]; // "B"
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordS(i) * source2Reg->readHwordS(i);

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // C0 - A0xB0, C1 - A1xB1, C4 - A4xB4, C5 - A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
			result = getResources()->EE->EECore->R5900->LO->readWordS(index) - result;
			getResources()->EE->EECore->R5900->LO->writeWordS(index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // C2 - A2xB2, C3 - A3xB3, C6 - A6xB6, C7 - A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
			result = getResources()->EE->EECore->R5900->HI->readWordS(index) - result;
			getResources()->EE->EECore->R5900->HI->writeWordS(index, result);
		}

		if (i % 2 == 0)
			destReg->writeWordS(i / 2, result); // Write to Rd for even indexes. C0 - A0xB0, C2 - A2xB2, C4 - A4xB4, C6 - A6xB6.
	}
}

void EECoreInterpreter::PMSUBW()
{
	// (LO, HI, Rd) = SignExtend<s64>((HI || LO)[i] - Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 220).
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
	{
		s64 result = ((static_cast<s64>(getResources()->EE->EECore->R5900->LO->readWordS(i)) << 32) || static_cast<s64>(getResources()->EE->EECore->R5900->LO->readWordS(i))) - source1Reg->readWordS(i) * source2Reg->readWordS(i);

		getResources()->EE->EECore->R5900->LO->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		getResources()->EE->EECore->R5900->HI->writeDwordS(i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->writeDwordS(i / 2, result);
	}
}
