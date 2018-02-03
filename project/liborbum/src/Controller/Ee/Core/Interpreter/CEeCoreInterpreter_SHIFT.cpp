#include <bitset>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::DSRA(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest->write_udword(0, static_cast<sdword>(reg_source1->read_udword(0)) >> shamt);
}

void CEeCoreInterpreter::DSLL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt << shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest->write_udword(0, reg_source1->read_udword(0) << shamt);
}

void CEeCoreInterpreter::DSLL32(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt << shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt() + 32;

	reg_dest->write_udword(0, reg_source1->read_udword(0) << shamt);
}

void CEeCoreInterpreter::DSLLV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt << Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x3F;

	reg_dest->write_udword(0, reg_source1->read_udword(0) << shamt);
}

void CEeCoreInterpreter::DSRA32(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(32->61). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt() + 32;

	reg_dest->write_udword(0, static_cast<sdword>(reg_source1->read_udword(0)) >> shamt);
}

void CEeCoreInterpreter::DSRAV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 6 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x3F;

	reg_dest->write_udword(0, static_cast<sdword>(reg_source1->read_udword(0)) >> shamt);
}

void CEeCoreInterpreter::DSRL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest->write_udword(0, reg_source1->read_udword(0) >> shamt);
}

void CEeCoreInterpreter::DSRL32(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt() + 32;

	reg_dest->write_udword(0, reg_source1->read_udword(0) >> shamt);
}

void CEeCoreInterpreter::DSRLV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x3F;

	reg_dest->write_udword(0, reg_source1->read_udword(0) >> shamt);
}

void CEeCoreInterpreter::SLL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sdword>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0) << shamt));
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SLLV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sdword>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x1F;

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0) << shamt));
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SRA(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0)) >> shamt);
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SRAV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x1F;

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0)) >> shamt);
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SRL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0) >> shamt));
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SRLV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	ubyte shamt = reg_source2->read_ubyte(0) & 0x1F;

	sdword result = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0) >> shamt));
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::PSLLH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt << shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	int shamt = inst.shamt() & 0xF;

    uhword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = reg_source1->read_uhword(i) << shamt;

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest->write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PSLLVW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sdword>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    auto shift = [](const uword value, const int shamt) -> udword
    {
        sdword result = static_cast<sdword>(static_cast<sword>(value << shamt));
        return static_cast<udword>(result);
    };

    udword value0 = shift(
        reg_source1->read_uword(0),
        reg_source2->read_uword(0) & 0x1F
    );
	
    udword value1 = shift(
        reg_source1->read_uword(2),
        reg_source2->read_uword(2) & 0x1F
    );

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PSLLW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt << shamt. Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	int shamt = inst.shamt();

    uword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = reg_source1->read_uword(i) << shamt;

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest->write_uword(i, value[i]);
}

void CEeCoreInterpreter::PSRAH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(lowest 4 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	int shamt = inst.shamt() & 0xF;

    uhword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = static_cast<uhword>(static_cast<shword>(reg_source1->read_uhword(i)) >> shamt);

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest->write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PSRAVW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sdword>(Rt >> Rs (lowest 5 bits)). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    auto shift = [](const uword value, const int shamt) -> udword
    {
        sdword result = static_cast<sdword>(static_cast<sword>(value) >> shamt);
        return static_cast<udword>(result);
    };

    udword value0 = shift(
        reg_source1->read_uword(0),
        reg_source2->read_uword(0) & 0x1F
    );

    udword value1 = shift(
        reg_source1->read_uword(2),
        reg_source2->read_uword(2) & 0x1F
    );

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PSRAW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt. Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    int shamt = inst.shamt();

    uword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = static_cast<uword>(static_cast<sword>(reg_source1->read_uword(i)) >> shamt);

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest->write_uword(i, value[i]);
}

void CEeCoreInterpreter::PSRLH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    int shamt = inst.shamt() & 0xF;

    uhword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = reg_source1->read_uhword(i) >> shamt;

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest->write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PSRLVW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sdword>(Rt >> Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    auto shift = [](const uword value, const int shamt) -> udword
    {
        sdword result = static_cast<sdword>(static_cast<sword>(value >> shamt));
        return static_cast<udword>(result);
    };

    udword value0 = shift(
        reg_source1->read_uword(0),
        reg_source2->read_uword(0) & 0x1F
    );

    udword value1 = shift(
        reg_source1->read_uword(2),
        reg_source2->read_uword(2) & 0x1F
    );

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PSRLW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt. Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    int shamt = inst.shamt();

    uword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = reg_source1->read_uword(i) >> shamt;

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest->write_uword(i, value[i]);
}

void CEeCoreInterpreter::QFSRV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd (lower 128-bits) = (Rs || Rt)(256-bit concatenation) >> SA. Logical shift? Not specified, but assumed to be.
	// No Exceptions generated.
	// TODO: check this instruction... not sure how to make this efficient???
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_sa = r.ee.core.r5900.sa;

	uword shamt = reg_sa.read_uword(); // From the docs it must be a multiple of bytes or halfwords, as you use the MTSAB or MTSAH instructions to write to the SA register.

	// Can use the STL class "bitset" to perform what we need... MUCH more cleaner than the old PCSX2 code.
	// This forms our 256-bit 'type' from 4 x 64-bits.
	std::bitset<256> result;
	(result |= reg_source1->read_udword(0)) <<= 64;
	(result |= reg_source1->read_udword(1)) <<= 64;
	(result |= reg_source2->read_udword(0)) <<= 64;
	(result |= reg_source2->read_udword(1));

	// Perform the right shift.
	result >>= shamt;

	// Extract the low-order 128-bit result value, 64-bits at a time (unsigned long long, guaranteed to be at least 64-bits), as that is the largest integral size available to the compiler. 
	// Store the extracted value into the destination register. Also need to create a temp bitset to store 64-bits into at one time. N must be the same size as the other bitset otherwise 
	// an error is thrown, but the extra bits are never used.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		std::bitset<256> temp64; 
		temp64 = result >> (64 * i);
		temp64 &= VALUE_UDWORD_MAX;
		udword result_int = temp64.to_ullong();
		reg_dest->write_udword(i, result_int);
	}
}