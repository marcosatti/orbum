#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Utilities/Utilities.hpp"

// All instructions here are related to registers.
// Particularly load/store

void CVuInterpreter::MOVE(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            reg_dest.write_uword(reg_source.read_uword(field), field);
        }
    }
}

void CVuInterpreter::MFIR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            reg_dest.write_uword(reg_source.read_uhword(), field);
        }
    }
}

void CVuInterpreter::MTIR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    reg_dest.write_uhword(reg_source.read_uword(inst.fsf()) & 0xFFFF);
}

void CVuInterpreter::MR32(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    reg_dest.write_uword(reg_source.read_uword(VuVectorField::W), VuVectorField::X);
    reg_dest.write_uword(reg_source.read_uword(VuVectorField::X), VuVectorField::Y);
    reg_dest.write_uword(reg_source.read_uword(VuVectorField::Y), VuVectorField::Z);
    reg_dest.write_uword(reg_source.read_uword(VuVectorField::Z), VuVectorField::W);
}

void CVuInterpreter::LQ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    const shword offset = extend_integer<uhword, shword, 11>(inst.imm11());
    const uword address = (offset + reg_source.read_uhword()) * NUMBER_BYTES_IN_QWORD;
    const uqword source = unit->bus.read_uqword(BusContext::Vu, address);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // Investigate?: Endianness scares me
            reg_dest.write_uword(field, source.uw[field]);
        }
    }
}

void CVuInterpreter::LQD(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    // Pre-decrement VI first
    reg_source.write_uhword(reg_source.read_uhword() - 1);

    const uword address = reg_source.read_uhword() * NUMBER_BYTES_IN_QWORD;
    const uqword source = unit->bus.read_uqword(BusContext::Vu, address);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // Investigate?: Endianness scares me
            reg_dest.write_uword(field, source.uw[field]);
        }
    }
}

void CVuInterpreter::LQI(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    const uword address = reg_source.read_uhword() * NUMBER_BYTES_IN_QWORD;
    const uqword source = unit->bus.read_uqword(BusContext::Vu, address);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // Investigate?: Endianness scares me
            reg_dest.write_uword(field, source.uw[field]);
        }
    }

    // Post-increment the VI
    reg_source.write_uhword(reg_source.read_uhword() + 1);
}

void CVuInterpreter::SQ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];

    const shword offset = extend_integer<uhword, shword, 11>(inst.imm11());
    const uword address = (offset + reg_source_2.read_uhword()) * NUMBER_BYTES_IN_QWORD;

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            unit->bus.write_uword(BusContext::Vu, address + NUMBER_BYTES_IN_WORD * field, reg_source_1.read_uword(field));
        }
    }
}

void CVuInterpreter::SQD(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];

    reg_source_2.write_uhword(reg_source_2.read_uhword() - 1);

    const uword address = reg_source_2.read_uhword() * NUMBER_BYTES_IN_QWORD;

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            unit->bus.write_uword(BusContext::Vu, address + NUMBER_BYTES_IN_WORD * field, reg_source_1.read_uword(field));
        }
    }
}

void CVuInterpreter::SQI(VuUnit_Base* unit, const VuInstruction inst)
{
    // MEM(Ft) = Fs
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.ft()]; // Mem Addr.

    // Real address obtained by VI * 16 (qword addressing).
    const uword address = reg_source_2.read_uhword() * NUMBER_BYTES_IN_QWORD;

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            unit->bus.write_uword(BusContext::Vu, address + NUMBER_BYTES_IN_WORD * field, reg_source_1.read_uword(field));
        }
    }

    // Post increment.
    reg_source_2.write_uhword(reg_source_2.read_uhword() + 1);
}

void CVuInterpreter::ILW(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    const shword offset = extend_integer<uhword, shword, 11>(inst.imm11());
    const uword address = (offset + reg_source.read_uhword()) * NUMBER_BYTES_IN_QWORD;

    // Note: the operation is undefined when multiple fields are specified
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const uword source = unit->bus.read_uqword(BusContext::Vu, address).uw[field];
            reg_dest.write_uhword(static_cast<uhword>(source));
        }
    }
}

void CVuInterpreter::ISW(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.it()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.is()];

    const shword offset = extend_integer<uhword, shword, 11>(inst.imm11());
    const uword address = (offset + reg_source_2.read_uhword()) * NUMBER_BYTES_IN_QWORD;

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            unit->bus.write_uword(BusContext::Vu, address + NUMBER_BYTES_IN_WORD * field, reg_source_1.read_uhword());
        }
    }
}

void CVuInterpreter::ILWR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source = unit->vi[inst.is()];
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    // Note: the operation is undefined when multiple fields are specified
    const uword address = reg_source.read_uhword() * NUMBER_BYTES_IN_QWORD;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const uword source = unit->bus.read_uqword(BusContext::Vu, address).uw[field];
            reg_dest.write_uhword(static_cast<uhword>(source));
        }
    }
}

void CVuInterpreter::ISWR(VuUnit_Base* unit, const VuInstruction inst)
{
    // MEM(Fs) = Ft.
    SizedHwordRegister& reg_source_1 = unit->vi[inst.it()]; // Data.
    SizedHwordRegister& reg_source_2 = unit->vi[inst.is()]; // Mem Addr.

    // Real address obtained by VI * 16.
    const uword address = reg_source_2.read_uhword() * NUMBER_BYTES_IN_QWORD;

    // 32-bit write for each dest subfield. Upper 16-bits of VI[Ft] value is set to 0.
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            unit->bus.write_uword(BusContext::Vu, address + NUMBER_BYTES_IN_WORD * field, reg_source_1.read_uhword());
        }
    }
}

void CVuInterpreter::LOI(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call this instruction when the I bit of the upper instruction is set
    // And pass the lower instruction in

    unit->i.write_uword(inst.value);

    // (In case you are wondering... LOI is a pseudo-instruction, it's
    //  not supposed to be referenced)
}

void CVuInterpreter::MFP(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& reg_source = unit->p;
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            reg_dest.write_uword(reg_source.read_uword(), field);
        }
    }
}
