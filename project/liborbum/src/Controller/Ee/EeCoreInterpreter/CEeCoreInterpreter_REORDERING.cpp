
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::PCPYH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 4)
	{
		// Loop for getting the value from Rt.
		uhword source1Val = source1Reg->read_uhword(i);
		for (auto j = 0; j < NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			// Inner loop for copying to Rd.
			ubyte destIndex = i * 4 + j;
			destReg->write_uhword(destIndex, source1Val);
		}
	}
}

void EECoreInterpreter_s::PCPYLD()
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0) 
			destReg->write_udword(i, source2Reg->read_udword(0));
		else
			destReg->write_udword(i, source1Reg->read_udword(0));
	}
}

void EECoreInterpreter_s::PCPYUD()
{
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			destReg->write_udword(i, source1Reg->read_udword(1));
		else
			destReg->write_udword(i, source2Reg->read_udword(1));
	}
}

void EECoreInterpreter_s::PEXCH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		for (auto j = 0; j < NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			ubyte destIndex = i * 4; // Start with the base index of which Dword we are in.
			if (j == 1)
				destIndex += 2;
			else if (j == 2)
				destIndex += 1;
			else
				destIndex += j;

			destReg->write_uhword(destIndex, source1Reg->read_uhword(i * 4 + j));
		}
	}
}

void EECoreInterpreter_s::PEXCW()
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		ubyte destIndex; 
		if (i == 1)
			destIndex = 2;
		else if (i == 2)
			destIndex = 1;
		else
			destIndex = i;

		destReg->write_uword(destIndex, source1Reg->read_uword(i));
	}
}

void EECoreInterpreter_s::PEXEH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		for (auto j = 0; j < NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			ubyte destIndex = i * 4; // Start with the base index of which Dword we are in.
			if (j == 0)
				destIndex += 2;
			else if (j == 2)
				destIndex += 0;
			else
				destIndex += j;

			destReg->write_uhword(destIndex, source1Reg->read_uhword(i * 4 + j));
		}
	}
}

void EECoreInterpreter_s::PEXEW()
{
	// Rd = COPY_W(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		ubyte destIndex;
		if (i == 0)
			destIndex = 2;
		else if (i == 2)
			destIndex = 0;
		else
			destIndex = i;

		destReg->write_uword(destIndex, source1Reg->read_uword(i));
	}
}

void EECoreInterpreter_s::PEXTLB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD / 2; i++)
	{
			destReg->write_ubyte(i * 2, source2Reg->read_ubyte(i));
			destReg->write_ubyte(i * 2 + 1, source1Reg->read_ubyte(i));
	}
}

void EECoreInterpreter_s::PEXTLH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->write_uhword(i * 2, source2Reg->read_uhword(i));
		destReg->write_uhword(i * 2 + 1, source1Reg->read_uhword(i));
	}
}

void EECoreInterpreter_s::PEXTLW()
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		destReg->write_uword(i * 2, source2Reg->read_uword(i));
		destReg->write_uword(i * 2 + 1, source1Reg->read_uword(i));
	}
}

void EECoreInterpreter_s::PEXTUB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = NUMBER_BYTES_IN_QWORD / 2; i > 0 ; i--)
	{
		destReg->write_ubyte((i - 1) * 2 + 1, source1Reg->read_ubyte((i - 1) + (NUMBER_BYTES_IN_QWORD / 2)));
		destReg->write_ubyte((i - 1) * 2, source2Reg->read_ubyte((i - 1) + (NUMBER_BYTES_IN_QWORD / 2)));
	}
}

void EECoreInterpreter_s::PEXTUH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->write_uhword((i - 1) * 2 + 1, source1Reg->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
		destReg->write_uhword((i - 1) * 2, source2Reg->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
	}
}

void EECoreInterpreter_s::PEXTUW()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = NUMBER_WORDS_IN_QWORD / 2; i > 0; i--)
	{
		destReg->write_uword((i - 1) * 2 + 1, source1Reg->read_uword((i - 1) + (NUMBER_WORDS_IN_QWORD / 2)));
		destReg->write_uword((i - 1) * 2, source2Reg->read_uword((i - 1) + (NUMBER_WORDS_IN_QWORD / 2)));
	}
}

void EECoreInterpreter_s::PINTEH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		destReg->write_uhword(i * 2, source2Reg->read_uhword(i));
		destReg->write_uhword(i * 2 + 1, source1Reg->read_uhword(i));
	}
}

void EECoreInterpreter_s::PINTH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.

	// Rt
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
		destReg->write_uhword(i * 2, source2Reg->read_uhword(i));

	// Rs
	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i > 0 ; i--)
		destReg->write_uhword((i - 1) * 2 + 1, source1Reg->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
}

void EECoreInterpreter_s::PPACB()
{
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use halfwords for this, just read the low-order bytes directly.

	// Rt
	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->write_ubyte(i / 2, source2Reg->read_ubyte(i));

	// Rs
	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i += 2)
		destReg->write_ubyte(i / 2 + (NUMBER_BYTES_IN_QWORD / 2), source1Reg->read_ubyte(i));
}

void EECoreInterpreter_s::PPACH()
{
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use words for this, just read the low-order hwords directly.

	// Rt
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->write_uhword(i / 2, source2Reg->read_uhword(i));

	// Rs
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
		destReg->write_uhword(i / 2 + (NUMBER_HWORDS_IN_QWORD / 2), source1Reg->read_uhword(i));
}

void EECoreInterpreter_s::PPACW()
{
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use dwords for this, just read the low-order words directly.

	// Rt
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->write_uword(i / 2, source2Reg->read_uword(i));

	// Rs
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
		destReg->write_uword(i / 2 + (NUMBER_WORDS_IN_QWORD / 2), source1Reg->read_uword(i));
}

void EECoreInterpreter_s::PREVH()
{
	// Rd = COPY_HW(Rt), No exceptions.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->write_uhword((NUMBER_HWORDS_IN_QWORD / 2) - 1 - i, source2Reg->read_uhword(i)); // Lower 4 hwords.
		destReg->write_uhword(NUMBER_HWORDS_IN_QWORD - 1 - i, source2Reg->read_uhword(i + (NUMBER_HWORDS_IN_QWORD / 2))); // Upper 4 hwords.

	}
}

void EECoreInterpreter_s::PROT3W()
{
	// Rd = COPY_W(Rt), No exceptions. Bit of a weird one...
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];

	destReg->write_uword(0, source2Reg->read_uword(1));
	destReg->write_uword(1, source2Reg->read_uword(2));
	destReg->write_uword(2, source2Reg->read_uword(0));
	destReg->write_uword(3, source2Reg->read_uword(3));
}

