#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"
#include "Utilities/Utilities.hpp"

void CEeCoreInterpreter::ADD(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs + Rt (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sword>(reg_source1.read_uword(0));
    auto val_source2 = static_cast<sword>(reg_source2.read_uword(0));
    sdword result = val_source1 + val_source2;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_32_check(val_source1, val_source2))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::ADDI(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rt = Rs + Imm (signed) (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
    auto imm = inst.s_imm();

    auto val_source = static_cast<sword>(reg_source.read_uword(0));
    sdword result = val_source + imm;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_32_check(val_source, imm))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::ADDIU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rt = Rs + Imm (signed).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
    auto imm = inst.s_imm();

    auto val_source = static_cast<sword>(reg_source.read_uword(0));
    sdword result = val_source + imm;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::ADDU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs + Rt
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sword>(reg_source1.read_uword(0));
    auto val_source2 = static_cast<sword>(reg_source2.read_uword(0));
    sdword result = val_source1 + val_source2;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DADD(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs + Rt (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));
    sdword result = val_source1 + val_source2;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_64_check(val_source1, val_source2))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DADDI(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rt = Rs + Imm (signed) (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
    auto imm = inst.s_imm();

    auto val_source = static_cast<sdword>(reg_source.read_udword(0));
    sdword result = val_source + imm;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_64_check(val_source, imm))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DADDIU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rt = Rs + Imm (signed).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
    auto imm = inst.s_imm();

    auto val_source = static_cast<sdword>(reg_source.read_udword(0));
    sdword result = val_source + imm;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DADDU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs + Rt
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));
    sdword result = val_source1 + val_source2;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DSUB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs - Rt (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));
    sdword result = val_source1 - val_source2;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_64_check(val_source1, val_source2))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::DSUBU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs - Rt
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));
    sdword result = val_source1 - val_source2;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::SUB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs - Rt (Exception on Integer Overflow).
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sword>(reg_source1.read_uword(0));
    auto val_source2 = static_cast<sword>(reg_source2.read_uword(0));
    sdword result = val_source1 - val_source2;

    // Check for over/under flow.
    if (!handle_no_over_or_underflow_32_check(val_source1, val_source2))
        return;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::SUBU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = Rs - Rt
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    auto val_source1 = static_cast<sword>(reg_source1.read_uword(0));
    auto val_source2 = static_cast<sword>(reg_source2.read_uword(0));
    sdword result = val_source1 - val_source2;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::PADDB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SB] = Rs[SB] + Rt[SB]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    ubyte value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        value[i] = reg_source1.read_ubyte(i) + reg_source2.read_ubyte(i);

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, value[i]);
}

void CEeCoreInterpreter::PADDH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SH] = Rs[SH] + Rt[SH]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uhword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = reg_source1.read_uhword(i) + reg_source2.read_uhword(i);

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PADDSB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    shword value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        value[i] = static_cast<shword>(static_cast<sbyte>(reg_source1.read_ubyte(i)))
                   + static_cast<shword>(static_cast<sbyte>(reg_source2.read_ubyte(i)));

        if (value[i] > VALUE_SBYTE_MAX)
            value[i] = VALUE_SBYTE_MAX;
        else if (value[i] < VALUE_SBYTE_MIN)
            value[i] = VALUE_SBYTE_MIN;
    }

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, static_cast<sbyte>(value[i]));
}

void CEeCoreInterpreter::PADDSH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sword>(static_cast<shword>(reg_source1.read_uhword(i)))
                   + static_cast<sword>(static_cast<shword>(reg_source2.read_uhword(i)));

        if (value[i] > VALUE_SHWORD_MAX)
            value[i] = VALUE_SHWORD_MAX;
        else if (value[i] < VALUE_SHWORD_MIN)
            value[i] = VALUE_SHWORD_MIN;
    }

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, static_cast<shword>(value[i]));
}

void CEeCoreInterpreter::PADDSW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sdword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sdword>(static_cast<sword>(reg_source1.read_uword(i)))
                   + static_cast<sdword>(static_cast<sword>(reg_source2.read_uword(i)));

        if (value[i] > VALUE_SWORD_MAX)
            value[i] = VALUE_SWORD_MAX;
        else if (value[i] < VALUE_SWORD_MIN)
            value[i] = VALUE_SWORD_MIN;
    }

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, static_cast<sword>(value[i]));
}

void CEeCoreInterpreter::PADDUB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UB] = Rs[UB] + Rt[UB]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uhword value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        value[i] = static_cast<uhword>(reg_source1.read_ubyte(i))
                   + static_cast<uhword>(reg_source2.read_ubyte(i));

        if (value[i] > VALUE_UBYTE_MAX)
            value[i] = VALUE_UBYTE_MAX;
    }

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, static_cast<ubyte>(value[i]));
}

void CEeCoreInterpreter::PADDUH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UH] = Rs[UH] + Rt[UH]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<uword>(reg_source1.read_uhword(i))
                   + static_cast<uhword>(reg_source2.read_uhword(i));

        if (value[i] > VALUE_UHWORD_MAX)
            value[i] = VALUE_UHWORD_MAX;
    }

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, static_cast<uhword>(value[i]));
}

void CEeCoreInterpreter::PADDUW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UW] = Rs[UW] + Rt[UW]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    udword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<udword>(reg_source1.read_uword(i))
                   + static_cast<udword>(reg_source2.read_uword(i));

        if (value[i] > VALUE_UWORD_MAX)
            value[i] = VALUE_UWORD_MAX;
    }

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, static_cast<uword>(value[i]));
}

void CEeCoreInterpreter::PADDW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SW] = Rs[SW] + Rt[SW].
    // Not explicitly mentioned, but looks like it doesnt treat overflowing.
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = reg_source1.read_uword(i) + reg_source2.read_uword(i);

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, value[i]);
}

void CEeCoreInterpreter::PADSBH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uhword value[NUMBER_HWORDS_IN_QWORD];

    // Sub
    for (int i = 0; i < (NUMBER_HWORDS_IN_QWORD / 2); i++)
        value[i] = reg_source1.read_uhword(i) - reg_source2.read_uhword(i);

    // Add
    for (int i = (NUMBER_HWORDS_IN_QWORD / 2); i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = reg_source1.read_uhword(i) + reg_source2.read_uhword(i);

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PSUBB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SB] = Rs[SB] - Rt[SB]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    ubyte value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        value[i] = reg_source1.read_ubyte(i) - reg_source2.read_ubyte(i);

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, value[i]);
}

void CEeCoreInterpreter::PSUBH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SH] = Rs[SH] - Rt[SH]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uhword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        value[i] = reg_source1.read_uhword(i) - reg_source2.read_uhword(i);

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PSUBSB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    shword value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        value[i] = static_cast<shword>(static_cast<sbyte>(reg_source1.read_ubyte(i)))
                   - static_cast<shword>(static_cast<sbyte>(reg_source2.read_ubyte(i)));

        if (value[i] > VALUE_SBYTE_MAX)
            value[i] = VALUE_SBYTE_MAX;
        else if (value[i] < VALUE_SBYTE_MIN)
            value[i] = VALUE_SBYTE_MIN;
    }

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, static_cast<sbyte>(value[i]));
}

void CEeCoreInterpreter::PSUBSH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sword>(static_cast<shword>(reg_source1.read_uhword(i)))
                   - static_cast<sword>(static_cast<shword>(reg_source2.read_uhword(i)));

        if (value[i] > VALUE_SHWORD_MAX)
            value[i] = VALUE_SHWORD_MAX;
        else if (value[i] < VALUE_SHWORD_MIN)
            value[i] = VALUE_SHWORD_MIN;
    }

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, static_cast<shword>(value[i]));
}

void CEeCoreInterpreter::PSUBSW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sdword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sdword>(static_cast<sword>(reg_source1.read_uword(i)))
                   - static_cast<sdword>(static_cast<sword>(reg_source2.read_uword(i)));

        if (value[i] > VALUE_SWORD_MAX)
            value[i] = VALUE_SWORD_MAX;
        else if (value[i] < VALUE_SWORD_MIN)
            value[i] = VALUE_SWORD_MIN;
    }

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, static_cast<sword>(value[i]));
}

void CEeCoreInterpreter::PSUBUB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UB] = Rs[UB] - Rt[UB]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    shword value[NUMBER_BYTES_IN_QWORD];

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        value[i] = static_cast<shword>(static_cast<uhword>(reg_source1.read_ubyte(i)))
                   - static_cast<shword>(static_cast<uhword>(reg_source2.read_ubyte(i)));

        if (value[i] < 0)
            value[i] = 0;
    }

    for (int i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
        reg_dest.write_ubyte(i, static_cast<ubyte>(value[i]));
}

void CEeCoreInterpreter::PSUBUH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UH] = Rs[UH] - Rt[UH]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sword value[NUMBER_HWORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sword>(static_cast<uword>(reg_source1.read_uhword(i)))
                   - static_cast<sword>(static_cast<uhword>(reg_source2.read_uhword(i)));

        if (value[i] < 0)
            value[i] = 0;
    }

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest.write_uhword(i, static_cast<uhword>(value[i]));
}

void CEeCoreInterpreter::PSUBUW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[UW] = Rs[UW] - Rt[UW]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    sdword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        value[i] = static_cast<sdword>(static_cast<udword>(reg_source1.read_uword(i)))
                   - static_cast<sdword>(static_cast<udword>(reg_source2.read_uword(i)));

        if (value[i] < 0)
            value[i] = 0;
    }

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, static_cast<uword>(value[i]));
}

void CEeCoreInterpreter::PSUBW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Parallel Rd[SW] = Rs[SW] - Rt[SW]
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

    uword value[NUMBER_WORDS_IN_QWORD];

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        value[i] = reg_source1.read_uword(i) - reg_source2.read_uword(i);

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest.write_uword(i, value[i]);
}
