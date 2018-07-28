#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"
#include "Utilities/Utilities.hpp"

void CEeCoreInterpreter::SLT(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<sdword>((Rs < Rt) ? 1 : 0)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

    sdword result = (val_source1 < val_source2) ? 1 : 0;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::SLTI(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<sdword>((Rs < Imm) ? 1 : 0)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto imm = static_cast<sdword>(inst.s_imm());

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    sdword result = (val_source1 < imm) ? 1 : 0;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::SLTIU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<udword>((Rs < Imm) ? 1 : 0)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
    auto imm = static_cast<udword>(static_cast<sdword>(inst.s_imm()));

    auto val_source1 = static_cast<udword>(reg_source1.read_udword(0));

    udword result = (val_source1 < imm) ? 1 : 0;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::SLTU(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<udword>((Rs < Rt) ? 1 : 0)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    auto val_source1 = static_cast<udword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<udword>(reg_source2.read_udword(0));

    udword result = (val_source1 < val_source2) ? 1 : 0;

    reg_dest.write_udword(0, result);
}

void CEeCoreInterpreter::PCEQB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<ubyte>((Rs == Rt) ? 0xFF : 0x00)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        ubyte val_source1 = reg_source1.read_ubyte(i);
        ubyte val_source2 = reg_source2.read_ubyte(i);
        ubyte result = (val_source1 == val_source2) ? 0xFF : 0x00;
        reg_dest.write_ubyte(i, result);
    }
}

void CEeCoreInterpreter::PCEQH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<uhword>((Rs == Rt) ? 0xFFFF : 0x0000)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        uhword val_source1 = reg_source1.read_uhword(i);
        uhword val_source2 = reg_source2.read_uhword(i);
        uhword result = (val_source1 == val_source2) ? 0xFFFF : 0x0000;
        reg_dest.write_uhword(i, result);
    }
}

void CEeCoreInterpreter::PCEQW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<uword>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        uword val_source1 = reg_source1.read_uword(i);
        uword val_source2 = reg_source2.read_uword(i);
        uword result = (val_source1 == val_source2) ? 0xFFFFFFFF : 0x00000000;
        reg_dest.write_uword(i, result);
    }
}

void CEeCoreInterpreter::PCGTB(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<ubyte>((Rs > Rt) ? 0xFF : 0x00)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
    {
        ubyte val_source1 = reg_source1.read_ubyte(i);
        ubyte val_source2 = reg_source2.read_ubyte(i);
        ubyte result = (val_source1 > val_source2) ? 0xFF : 0x00;
        reg_dest.write_ubyte(i, result);
    }
}

void CEeCoreInterpreter::PCGTH(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<uhword>((Rs > Rt) ? 0xFFFF : 0x0000)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
    {
        uhword val_source1 = reg_source1.read_uhword(i);
        uhword val_source2 = reg_source2.read_uhword(i);
        uhword result = (val_source1 > val_source2) ? 0xFFFF : 0x0000;
        reg_dest.write_uhword(i, result);
    }
}

void CEeCoreInterpreter::PCGTW(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // Rd = SignExtended<uword>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
    // No Exceptions generated.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

    for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
    {
        uword val_source1 = reg_source1.read_uword(i);
        uword val_source2 = reg_source2.read_uword(i);
        uword result = (val_source1 > val_source2) ? 0xFFFFFFFF : 0x00000000;
        reg_dest.write_uword(i, result);
    }
}

void CEeCoreInterpreter::C_EQ_S(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
    // No Exceptions generated, except for coprocessor unavailable.
    if (!handle_cop1_usable())
        return;

    auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
    auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
    auto& csr = r.ee.core.fpu.csr;                    // FCR[31] aka control status register.

    f32 val_source1 = reg_source1.read_float();
    f32 val_source2 = reg_source2.read_float();

    if (val_source1 == val_source2)
        csr.insert_field(EeCoreFpuRegister_Csr::C, 1);
    else
        csr.insert_field(EeCoreFpuRegister_Csr::C, 0);
}

void CEeCoreInterpreter::C_F_S(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
    // (FCR[31] or CSR, C field) = 0
    // No Exceptions generated, except for coprocessor unavailable.
    if (!handle_cop1_usable())
        return;

    auto& csr = r.ee.core.fpu.csr; // FCR[31] aka control status register.

    csr.insert_field(EeCoreFpuRegister_Csr::C, 0);
}

void CEeCoreInterpreter::C_LE_S(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
    // No Exceptions generated, except for coprocessor unavailable.
    if (!handle_cop1_usable())
        return;

    auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
    auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
    auto& csr = r.ee.core.fpu.csr;                    // FCR[31] aka control status register.

    f32 val_source1 = reg_source1.read_float();
    f32 val_source2 = reg_source2.read_float();

    if (val_source1 <= val_source2)
        csr.insert_field(EeCoreFpuRegister_Csr::C, 1);
    else
        csr.insert_field(EeCoreFpuRegister_Csr::C, 0);
}

void CEeCoreInterpreter::C_LT_S(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
    // No Exceptions generated, except for coprocessor unavailable.
    if (!handle_cop1_usable())
        return;

    auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
    auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
    auto& csr = r.ee.core.fpu.csr;                    // FCR[31] aka control status register.

    f32 val_source1 = reg_source1.read_float();
    f32 val_source2 = reg_source2.read_float();

    if (val_source1 < val_source2)
        csr.insert_field(EeCoreFpuRegister_Csr::C, 1);
    else
        csr.insert_field(EeCoreFpuRegister_Csr::C, 0);
}
