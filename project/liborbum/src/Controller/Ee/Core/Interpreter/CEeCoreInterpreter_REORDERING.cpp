#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PCPYH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 4)
	{
		// Loop for getting the value from Rt.
		uhword val_source1 = reg_source1->read_uhword(i);
		for (auto j = 0; j < NUMBER_HWORDS_IN_QWORD / 2; j++)
		{
			// Inner loop for copying to Rd.
			ubyte destIndex = i * 4 + j;
			reg_dest->write_uhword(destIndex, val_source1);
		}
	}
}

void CEeCoreInterpreter::PCPYLD(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0) 
			reg_dest->write_udword(i, reg_source2->read_udword(0));
		else
			reg_dest->write_udword(i, reg_source1->read_udword(0));
	}
}

void CEeCoreInterpreter::PCPYUD(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// I know a loop is not required for this instruction, but it makes it easier to copy and paste for other instructions, and makes it consistent.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			reg_dest->write_udword(i, reg_source1->read_udword(1));
		else
			reg_dest->write_udword(i, reg_source2->read_udword(1));
	}
}

void CEeCoreInterpreter::PEXCH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

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

			reg_dest->write_uhword(destIndex, reg_source1->read_uhword(i * 4 + j));
		}
	}
}

void CEeCoreInterpreter::PEXCW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		ubyte destIndex; 
		if (i == 1)
			destIndex = 2;
		else if (i == 2)
			destIndex = 1;
		else
			destIndex = i;

		reg_dest->write_uword(destIndex, reg_source1->read_uword(i));
	}
}

void CEeCoreInterpreter::PEXEH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

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

			reg_dest->write_uhword(destIndex, reg_source1->read_uhword(i * 4 + j));
		}
	}
}

void CEeCoreInterpreter::PEXEW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		ubyte destIndex;
		if (i == 0)
			destIndex = 2;
		else if (i == 2)
			destIndex = 0;
		else
			destIndex = i;

		reg_dest->write_uword(destIndex, reg_source1->read_uword(i));
	}
}

void CEeCoreInterpreter::PEXTLB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD / 2; i++)
	{
			reg_dest->write_ubyte(i * 2, reg_source2->read_ubyte(i));
			reg_dest->write_ubyte(i * 2 + 1, reg_source1->read_ubyte(i));
	}
}

void CEeCoreInterpreter::PEXTLH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		reg_dest->write_uhword(i * 2, reg_source2->read_uhword(i));
		reg_dest->write_uhword(i * 2 + 1, reg_source1->read_uhword(i));
	}
}

void CEeCoreInterpreter::PEXTLW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD / 2; i++)
	{
		reg_dest->write_uword(i * 2, reg_source2->read_uword(i));
		reg_dest->write_uword(i * 2 + 1, reg_source1->read_uword(i));
	}
}

void CEeCoreInterpreter::PEXTUB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = NUMBER_BYTES_IN_QWORD / 2; i > 0 ; i--)
	{
		reg_dest->write_ubyte((i - 1) * 2 + 1, reg_source1->read_ubyte((i - 1) + (NUMBER_BYTES_IN_QWORD / 2)));
		reg_dest->write_ubyte((i - 1) * 2, reg_source2->read_ubyte((i - 1) + (NUMBER_BYTES_IN_QWORD / 2)));
	}
}

void CEeCoreInterpreter::PEXTUH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i > 0; i--)
	{
		reg_dest->write_uhword((i - 1) * 2 + 1, reg_source1->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
		reg_dest->write_uhword((i - 1) * 2, reg_source2->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
	}
}

void CEeCoreInterpreter::PEXTUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = NUMBER_WORDS_IN_QWORD / 2; i > 0; i--)
	{
		reg_dest->write_uword((i - 1) * 2 + 1, reg_source1->read_uword((i - 1) + (NUMBER_WORDS_IN_QWORD / 2)));
		reg_dest->write_uword((i - 1) * 2, reg_source2->read_uword((i - 1) + (NUMBER_WORDS_IN_QWORD / 2)));
	}
}

void CEeCoreInterpreter::PINTEH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		reg_dest->write_uhword(i * 2, reg_source2->read_uhword(i));
		reg_dest->write_uhword(i * 2 + 1, reg_source1->read_uhword(i));
	}
}

void CEeCoreInterpreter::PINTH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.

	// Rt
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
		reg_dest->write_uhword(i * 2, reg_source2->read_uhword(i));

	// Rs
	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i > 0 ; i--)
		reg_dest->write_uhword((i - 1) * 2 + 1, reg_source1->read_uhword((i - 1) + (NUMBER_HWORDS_IN_QWORD / 2)));
}

void CEeCoreInterpreter::PPACB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use halfwords for this, just read the low-order bytes directly.

	// Rt
	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i += 2)
		reg_dest->write_ubyte(i / 2, reg_source2->read_ubyte(i));

	// Rs
	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i += 2)
		reg_dest->write_ubyte(i / 2 + (NUMBER_BYTES_IN_QWORD / 2), reg_source1->read_ubyte(i));
}

void CEeCoreInterpreter::PPACH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use words for this, just read the low-order hwords directly.

	// Rt
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
		reg_dest->write_uhword(i / 2, reg_source2->read_uhword(i));

	// Rs
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
		reg_dest->write_uhword(i / 2 + (NUMBER_HWORDS_IN_QWORD / 2), reg_source1->read_uhword(i));
}

void CEeCoreInterpreter::PPACW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	// Easier to write this instruction using two loops - one for Rs and one for Rt.
	// Also dont need to use dwords for this, just read the low-order words directly.

	// Rt
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
		reg_dest->write_uword(i / 2, reg_source2->read_uword(i));

	// Rs
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
		reg_dest->write_uword(i / 2 + (NUMBER_WORDS_IN_QWORD / 2), reg_source1->read_uword(i));
}

void CEeCoreInterpreter::PREVH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		reg_dest->write_uhword((NUMBER_HWORDS_IN_QWORD / 2) - 1 - i, reg_source2->read_uhword(i)); // Lower 4 hwords.
		reg_dest->write_uhword(NUMBER_HWORDS_IN_QWORD - 1 - i, reg_source2->read_uhword(i + (NUMBER_HWORDS_IN_QWORD / 2))); // Upper 4 hwords.

	}
}

void CEeCoreInterpreter::PROT3W(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions. Bit of a weird one...
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	reg_dest->write_uword(0, reg_source2->read_uword(1));
	reg_dest->write_uword(1, reg_source2->read_uword(2));
	reg_dest->write_uword(2, reg_source2->read_uword(0));
	reg_dest->write_uword(3, reg_source2->read_uword(3));
}

