#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"

/*
Reordering instruction family.
*/


void InterpreterEECore::PCPYH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 4)
	{
		// Loop for getting the value from Rt.
		u16 source1Val = source1Reg->readHwordU(i);
		for (auto j = 0; j < Constants::NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			// Inner loop for copying to Rd.
			u8 destIndex = i * 4 + j;
			destReg->writeHwordU(destIndex, source1Val);
		}
	}
}

void InterpreterEECore::PCPYLD(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0) 
			destReg->writeDwordU(i, source2Reg->readDwordU(0));
		else
			destReg->writeDwordU(i, source1Reg->readDwordU(0));
	}
}

void InterpreterEECore::PCPYUD(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < Constants::NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			destReg->writeDwordU(i, source1Reg->readDwordU(1));
		else
			destReg->writeDwordU(i, source2Reg->readDwordU(1));
	}
}

void InterpreterEECore::PEXCH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

			destReg->writeHwordU(destIndex, source1Reg->readHwordU(i * 4 + j));
		}
	}
}

void InterpreterEECore::PEXCW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		u8 destIndex; 
		if (i == 1)
			destIndex = 2;
		else if (i == 2)
			destIndex = 1;
		else
			destIndex = i;

		destReg->writeWordU(destIndex, source1Reg->readWordU(i));
	}
}

void InterpreterEECore::PEXEH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

			destReg->writeHwordU(destIndex, source1Reg->readHwordU(i * 4 + j));
		}
	}
}

void InterpreterEECore::PEXEW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		u8 destIndex;
		if (i == 0)
			destIndex = 2;
		else if (i == 2)
			destIndex = 0;
		else
			destIndex = i;

		destReg->writeWordU(destIndex, source1Reg->readWordU(i));
	}
}

void InterpreterEECore::PEXTLB(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD / 2; i++)
	{
			destReg->writeByteU(i * 2, source2Reg->readByteU(i));
			destReg->writeByteU(i * 2 + 1, source1Reg->readByteU(i));
	}
}

void InterpreterEECore::PEXTLH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHwordU(i * 2, source2Reg->readHwordU(i));
		destReg->writeHwordU(i * 2 + 1, source1Reg->readHwordU(i));
	}
}

void InterpreterEECore::PEXTLW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		destReg->writeWordU(i * 2, source2Reg->readWordU(i));
		destReg->writeWordU(i * 2 + 1, source1Reg->readWordU(i));
	}
}

void InterpreterEECore::PEXTUB(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = Constants::NUMBER_BYTES_IN_QWORD / 2; i > 0 ; i--)
	{
		destReg->writeByteU((i - 1) * 2 + 1, source1Reg->readByteU((i - 1) + (Constants::NUMBER_BYTES_IN_QWORD / 2)));
		destReg->writeByteU((i - 1) * 2, source2Reg->readByteU((i - 1) + (Constants::NUMBER_BYTES_IN_QWORD / 2)));
	}
}

void InterpreterEECore::PEXTUH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->writeHwordU((i - 1) * 2 + 1, source1Reg->readHwordU((i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
		destReg->writeHwordU((i - 1) * 2, source2Reg->readHwordU((i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
	}
}

void InterpreterEECore::PEXTUW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = Constants::NUMBER_WORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->writeWordU((i - 1) * 2 + 1, source1Reg->readWordU((i - 1) + (Constants::NUMBER_WORDS_IN_QWORD / 2)));
		destReg->writeWordU((i - 1) * 2, source2Reg->readWordU((i - 1) + (Constants::NUMBER_WORDS_IN_QWORD / 2)));
	}
}

void InterpreterEECore::PINTEH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		destReg->writeHwordU(i * 2, source2Reg->readHwordU(i));
		destReg->writeHwordU(i * 2 + 1, source1Reg->readHwordU(i));
	}
}

void InterpreterEECore::PINTH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
		destReg->writeHwordU(i * 2, source2Reg->readHwordU(i));

	// Rs
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i > 0 ; i--)
		destReg->writeHwordU((i - 1) * 2 + 1, source1Reg->readHwordU((i - 1) + (Constants::NUMBER_HWORDS_IN_QWORD / 2)));
}

void InterpreterEECore::PPACB(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use halfwords for this, just read the low-order bytes directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->writeByteU(i / 2, source2Reg->readByteU(i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->writeByteU(i / 2 + (Constants::NUMBER_BYTES_IN_QWORD / 2), source1Reg->readByteU(i));
}

void InterpreterEECore::PPACH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use words for this, just read the low-order hwords directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->writeHwordU(i / 2, source2Reg->readHwordU(i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->writeHwordU(i / 2 + (Constants::NUMBER_HWORDS_IN_QWORD / 2), source1Reg->readHwordU(i));
}

void InterpreterEECore::PPACW(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use dwords for this, just read the low-order words directly.

	// Rt
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->writeWordU(i / 2, source2Reg->readWordU(i));

	// Rs
	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->writeWordU(i / 2 + (Constants::NUMBER_WORDS_IN_QWORD / 2), source1Reg->readWordU(i));
}

void InterpreterEECore::PREVH(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHwordU((Constants::NUMBER_HWORDS_IN_QWORD / 2) - 1 - i, source2Reg->readHwordU(i)); // Lower 4 hwords.
		destReg->writeHwordU(Constants::NUMBER_HWORDS_IN_QWORD - 1 - i, source2Reg->readHwordU(i + (Constants::NUMBER_HWORDS_IN_QWORD / 2))); // Upper 4 hwords.

	}
}

void InterpreterEECore::PROT3W(const MIPSInstruction_t& instruction, std::shared_ptr<PS2Resources_t>& PS2Resources)
{
	// Rd = COPY_W(Rt), No exceptions. Bit of a weird one...
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	destReg->writeWordU(0, source2Reg->readWordU(1));
	destReg->writeWordU(1, source2Reg->readWordU(2));
	destReg->writeWordU(2, source2Reg->readWordU(0));
	destReg->writeWordU(3, source2Reg->readWordU(3));
}

