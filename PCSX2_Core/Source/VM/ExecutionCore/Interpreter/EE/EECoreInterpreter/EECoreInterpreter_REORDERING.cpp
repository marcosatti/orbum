#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"

void EECoreInterpreter::PCPYH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 4)
	{
		// Loop for getting the value from Rt.
		u16 source1Val = source1Reg->readHword(Context_t::EE, i);
		for (auto j = 0; j < Constants::NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			// Inner loop for copying to Rd.
			u8 destIndex = i * 4 + j;
			destReg->writeHword(Context_t::EE, destIndex, source1Val);
		}
	}
}

void EECoreInterpreter::PCPYLD()
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0) 
			destReg->writeDword(Context_t::EE, i, source2Reg->readDword(Context_t::EE, 0));
		else
			destReg->writeDword(Context_t::EE, i, source1Reg->readDword(Context_t::EE, 0));
	}
}

void EECoreInterpreter::PCPYUD()
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			destReg->writeDword(Context_t::EE, i, source1Reg->readDword(Context_t::EE, 1));
		else
			destReg->writeDword(Context_t::EE, i, source2Reg->readDword(Context_t::EE, 1));
	}
}

void EECoreInterpreter::PEXCH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		for (auto j = 0; j < Constants::NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			u8 destIndex = i * 4; // Start with the base index of which Dword we are in.
			if (j == 1)
				destIndex += 2;
			else if (j == 2)
				destIndex += 1;
			else
				destIndex += j;

			destReg->writeHword(Context_t::EE, destIndex, source1Reg->readHword(Context_t::EE, i * 4 + j));
		}
	}
}

void EECoreInterpreter::PEXCW()
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		u8 destIndex; 
		if (i == 1)
			destIndex = 2;
		else if (i == 2)
			destIndex = 1;
		else
			destIndex = i;

		destReg->writeWord(Context_t::EE, destIndex, source1Reg->readWord(Context_t::EE, i));
	}
}

void EECoreInterpreter::PEXEH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		for (auto j = 0; j < Constants::NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			u8 destIndex = i * 4; // Start with the base index of which Dword we are in.
			if (j == 0)
				destIndex += 2;
			else if (j == 2)
				destIndex += 0;
			else
				destIndex += j;

			destReg->writeHword(Context_t::EE, destIndex, source1Reg->readHword(Context_t::EE, i * 4 + j));
		}
	}
}

void EECoreInterpreter::PEXEW()
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		u8 destIndex;
		if (i == 0)
			destIndex = 2;
		else if (i == 2)
			destIndex = 0;
		else
			destIndex = i;

		destReg->writeWord(Context_t::EE, destIndex, source1Reg->readWord(Context_t::EE, i));
	}
}

void EECoreInterpreter::PEXTLB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD / 2; i++)
	{
			destReg->writeByte(Context_t::EE, i * 2, source2Reg->readByte(Context_t::EE, i));
			destReg->writeByte(Context_t::EE, i * 2 + 1, source1Reg->readByte(Context_t::EE, i));
	}
}

void EECoreInterpreter::PEXTLH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHword(Context_t::EE, i * 2, source2Reg->readHword(Context_t::EE, i));
		destReg->writeHword(Context_t::EE, i * 2 + 1, source1Reg->readHword(Context_t::EE, i));
	}
}

void EECoreInterpreter::PEXTLW()
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		destReg->writeWord(Context_t::EE, i * 2, source2Reg->readWord(Context_t::EE, i));
		destReg->writeWord(Context_t::EE, i * 2 + 1, source1Reg->readWord(Context_t::EE, i));
	}
}

void EECoreInterpreter::PEXTUB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = Constants::NUMBER_BYTES_IN_QWORD / 2; i > 0 ; i--)
	{
		destReg->writeByte(Context_t::EE, (i - 1) * 2 + 1, source1Reg->readByte(Context_t::EE, (i - 1) + (Constants::NUMBER_BYTES_IN_QWORD / 2)));
		destReg->writeByte(Context_t::EE, (i - 1) * 2, source2Reg->readByte(Context_t::EE, (i - 1) + (Constants::NUMBER_BYTES_IN_QWORD / 2)));
	}
}

void EECoreInterpreter::PEXTUH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->writeHword(Context_t::EE, (i - 1) * 2 + 1, source1Reg->readHword(Context_t::EE, (i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
		destReg->writeHword(Context_t::EE, (i - 1) * 2, source2Reg->readHword(Context_t::EE, (i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
	}
}

void EECoreInterpreter::PEXTUW()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = Constants::NUMBER_WORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->writeWord(Context_t::EE, (i - 1) * 2 + 1, source1Reg->readWord(Context_t::EE, (i - 1) + (Constants::NUMBER_WORDS_IN_QWORD / 2)));
		destReg->writeWord(Context_t::EE, (i - 1) * 2, source2Reg->readWord(Context_t::EE, (i - 1) + (Constants::NUMBER_WORDS_IN_QWORD / 2)));
	}
}

void EECoreInterpreter::PINTEH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		destReg->writeHword(Context_t::EE, i * 2, source2Reg->readHword(Context_t::EE, i));
		destReg->writeHword(Context_t::EE, i * 2 + 1, source1Reg->readHword(Context_t::EE, i));
	}
}

void EECoreInterpreter::PINTH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
		destReg->writeHword(Context_t::EE, i * 2, source2Reg->readHword(Context_t::EE, i));

	// Rs
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i > 0 ; i--)
		destReg->writeHword(Context_t::EE, (i - 1) * 2 + 1, source1Reg->readHword(Context_t::EE, (i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
}

void EECoreInterpreter::PPACB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use halfwords for this, just read the low-order bytes directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->writeByte(Context_t::EE, i / 2, source2Reg->readByte(Context_t::EE, i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->writeByte(Context_t::EE, i / 2 + (Constants::NUMBER_BYTES_IN_QWORD / 2), source1Reg->readByte(Context_t::EE, i));
}

void EECoreInterpreter::PPACH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use words for this, just read the low-order hwords directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->writeHword(Context_t::EE, i / 2, source2Reg->readHword(Context_t::EE, i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->writeHword(Context_t::EE, i / 2 + (Constants::NUMBER_HWORDS_IN_QWORD / 2), source1Reg->readHword(Context_t::EE, i));
}

void EECoreInterpreter::PPACW()
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use dwords for this, just read the low-order words directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->writeWord(Context_t::EE, i / 2, source2Reg->readWord(Context_t::EE, i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->writeWord(Context_t::EE, i / 2 + (Constants::NUMBER_WORDS_IN_QWORD / 2), source1Reg->readWord(Context_t::EE, i));
}

void EECoreInterpreter::PREVH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHword(Context_t::EE, (Constants::NUMBER_HWORDS_IN_QWORD / 2) - 1 - i, source2Reg->readHword(Context_t::EE, i)); // Lower 4 hwords.
		destReg->writeHword(Context_t::EE, Constants::NUMBER_HWORDS_IN_QWORD - 1 - i, source2Reg->readHword(Context_t::EE, i + (Constants::NUMBER_HWORDS_IN_QWORD / 2))); // Upper 4 hwords.

	}
}

void EECoreInterpreter::PROT3W()
{
	// Rd = COPY_W(Rt), No exceptions. Bit of a weird one...
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];

	destReg->writeWord(Context_t::EE, 0, source2Reg->readWord(Context_t::EE, 1));
	destReg->writeWord(Context_t::EE, 1, source2Reg->readWord(Context_t::EE, 2));
	destReg->writeWord(Context_t::EE, 2, source2Reg->readWord(Context_t::EE, 0));
	destReg->writeWord(Context_t::EE, 3, source2Reg->readWord(Context_t::EE, 3));
}

