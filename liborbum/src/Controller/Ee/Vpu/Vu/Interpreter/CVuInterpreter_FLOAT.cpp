#include <cmath>

#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnitRegisters.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Utilities/Utilities.hpp"

void CVuInterpreter::ABS(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // std::abs uses compiler intrinsics internally, and hence it's
            // sometimes faster than bit ops ...
            // const float val = reg_source.read_float(field);
            // const float result = to_ps2_float(std::abs(val), flags);

            // ... but it might screw the PS2 floats out, so we do bit ops
            const uword raw = reg_source.read_uword(field) & 0x7FFFFFFF;
            const float result = *reinterpret_cast<const float*>(&raw);

            reg_dest.write_float(field, result);
        }
    }
}

void CVuInterpreter::ADD(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDbc(unit, inst, 0);
}

void CVuInterpreter::ADDbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDbc(unit, inst, 1);
}

void CVuInterpreter::ADDbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDbc(unit, inst, 2);
}

void CVuInterpreter::ADDbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDbc(unit, inst, 3);
}

void CVuInterpreter::ADDA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDAi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDAq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a + b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADDAbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDAbc(unit, inst, 0);
}

void CVuInterpreter::ADDAbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDAbc(unit, inst, 1);
}

void CVuInterpreter::ADDAbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDAbc(unit, inst, 2);
}

void CVuInterpreter::ADDAbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    ADDAbc(unit, inst, 3);
}

void CVuInterpreter::SUB(VuUnit_Base* unit, const VuInstruction inst)
{
    // Fd = Fs - Ft.
    auto& reg_dest = unit->vf[inst.fd()];
    auto& reg_source1 = unit->vf[inst.fs()];
    auto& reg_source2 = unit->vf[inst.ft()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            f32 result = to_ps2_float(reg_source1.read_float(field) - reg_source2.read_float(field), flags);
            reg_dest.write_float(field, result);
            unit->mac.update_vector_field(field, flags);
        }
        else
            unit->mac.clear_vector_field(field);
    }
}

void CVuInterpreter::SUBi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBbc(unit, inst, 0);
}

void CVuInterpreter::SUBbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBbc(unit, inst, 1);
}

void CVuInterpreter::SUBbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBbc(unit, inst, 2);
}

void CVuInterpreter::SUBbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBbc(unit, inst, 3);
}

void CVuInterpreter::SUBA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBAi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBAq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::SUBAbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBAbc(unit, inst, 0);
}

void CVuInterpreter::SUBAbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBAbc(unit, inst, 1);
}

void CVuInterpreter::SUBAbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBAbc(unit, inst, 2);
}

void CVuInterpreter::SUBAbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    SUBAbc(unit, inst, 3);
}

void CVuInterpreter::MUL(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULbc(unit, inst, 0);
}

void CVuInterpreter::MULbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULbc(unit, inst, 1);
}

void CVuInterpreter::MULbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULbc(unit, inst, 2);
}

void CVuInterpreter::MULbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULbc(unit, inst, 3);
}

void CVuInterpreter::MULA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULAi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULAq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float result = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MULAbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULAbc(unit, inst, 0);
}

void CVuInterpreter::MULAbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULAbc(unit, inst, 1);
}

void CVuInterpreter::MULAbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULAbc(unit, inst, 2);
}

void CVuInterpreter::MULAbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MULAbc(unit, inst, 3);
}

void CVuInterpreter::MADD(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDbc(unit, inst, 0);
}

void CVuInterpreter::MADDbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDbc(unit, inst, 1);
}

void CVuInterpreter::MADDbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDbc(unit, inst, 2);
}

void CVuInterpreter::MADDbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDbc(unit, inst, 3);
}

void CVuInterpreter::MADDA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDAi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDAq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c + a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MADDAbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDAbc(unit, inst, 0);
}

void CVuInterpreter::MADDAbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDAbc(unit, inst, 1);
}

void CVuInterpreter::MADDAbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDAbc(unit, inst, 2);
}

void CVuInterpreter::MADDAbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MADDAbc(unit, inst, 3);
}

void CVuInterpreter::MSUB(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBbc(unit, inst, 0);
}

void CVuInterpreter::MSUBbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBbc(unit, inst, 1);
}

void CVuInterpreter::MSUBbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBbc(unit, inst, 2);
}

void CVuInterpreter::MSUBbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBbc(unit, inst, 3);
}

void CVuInterpreter::MSUBA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBAi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBAq(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBAbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    unit->status.clear_flags();

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            const float c = reg_source_3.read_float(field);
            const float result = to_ps2_float(c - a * b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MSUBAbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBAbc(unit, inst, 0);
}

void CVuInterpreter::MSUBAbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBAbc(unit, inst, 1);
}

void CVuInterpreter::MSUBAbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBAbc(unit, inst, 2);
}

void CVuInterpreter::MSUBAbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MSUBAbc(unit, inst, 3);
}

void CVuInterpreter::MAX(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            reg_dest.write_float(field, std::max(a, b));
        }
    }
}

void CVuInterpreter::MAXi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            reg_dest.write_float(field, std::max(a, b));
        }
    }
}

void CVuInterpreter::MAXbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    const ubyte bc = static_cast<ubyte>(idx);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            reg_dest.write_float(field, std::max(a, b));
        }
    }
}

void CVuInterpreter::MAXbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MAXbc(unit, inst, 0);
}

void CVuInterpreter::MAXbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MAXbc(unit, inst, 1);
}

void CVuInterpreter::MAXbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MAXbc(unit, inst, 2);
}

void CVuInterpreter::MAXbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MAXbc(unit, inst, 3);
}

void CVuInterpreter::MINI(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(field);
            reg_dest.write_float(field, std::min(a, b));
        }
    }
}

void CVuInterpreter::MINIi(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float();
            reg_dest.write_float(field, std::min(a, b));
        }
    }
}

void CVuInterpreter::MINIbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    const ubyte bc = static_cast<ubyte>(idx);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const float a = reg_source_1.read_float(field);
            const float b = reg_source_2.read_float(bc);
            reg_dest.write_float(field, std::min(a, b));
        }
    }
}

void CVuInterpreter::MINIbc_0(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MINIbc(unit, inst, 0);
}

void CVuInterpreter::MINIbc_1(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MINIbc(unit, inst, 1);
}

void CVuInterpreter::MINIbc_2(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MINIbc(unit, inst, 2);
}

void CVuInterpreter::MINIbc_3(VuUnit_Base* unit, const VuInstruction inst)
{
    // Call base function.
    MINIbc(unit, inst, 3);
}

void CVuInterpreter::OPMULA(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& acc = unit->acc;

    FpuFlags flags;

    acc.write_float(VuVectorField::X, to_ps2_float(
                                          fs.read_float(VuVectorField::Y) * ft.read_float(VuVectorField::Z), flags));
    unit->mac.update_vector_field(VuVectorField::X, flags);

    acc.write_float(VuVectorField::Y, to_ps2_float(
                                          fs.read_float(VuVectorField::Z) * ft.read_float(VuVectorField::X), flags));
    unit->mac.update_vector_field(VuVectorField::Y, flags);

    acc.write_float(VuVectorField::Z, to_ps2_float(
                                          fs.read_float(VuVectorField::X) * ft.read_float(VuVectorField::Y), flags));
    unit->mac.update_vector_field(VuVectorField::Z, flags);
}

void CVuInterpreter::OPMSUB(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& fd = unit->vf[inst.fd()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& acc = unit->acc;

    FpuFlags flags;
    fd.write_float(VuVectorField::X, to_ps2_float(
                                         acc.read_float(VuVectorField::X) - fs.read_float(VuVectorField::Y) * ft.read_float(VuVectorField::Z), flags));
    unit->mac.update_vector_field(VuVectorField::X, flags);

    fd.write_float(VuVectorField::Y, to_ps2_float(
                                         acc.read_float(VuVectorField::Y) - fs.read_float(VuVectorField::Z) * ft.read_float(VuVectorField::X), flags));
    unit->mac.update_vector_field(VuVectorField::Y, flags);

    fd.write_float(VuVectorField::Z, to_ps2_float(
                                         acc.read_float(VuVectorField::Z) - fs.read_float(VuVectorField::X) * ft.read_float(VuVectorField::Y), flags));
    unit->mac.update_vector_field(VuVectorField::Z, flags);
}

void CVuInterpreter::DIV(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& q = unit->q;
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];

    FpuFlags flags;
    const float result = to_ps2_float(fs.read_float(inst.fsf()) / ft.read_float(inst.ftf()), flags);

    unit->status.clear_flags();
    
    if (ft.read_float(inst.ftf()) == 0.0f) 
    {
        if (fs.read_float(inst.ftf()) == 0.0f) {
            unit->status.insert_field(VuUnitRegister_Status::I, 1);
        } 
        else 
        {
            unit->status.insert_field(VuUnitRegister_Status::D, 1);
        }
    }

    q.write_float(result);
}

void CVuInterpreter::SQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& q = unit->q;
    SizedQwordRegister& ft = unit->vf[inst.ft()];

    const float result = std::sqrt(std::abs(ft.read_float(inst.ftf())));
    
    unit->status.clear_flags();

    if ((ft.read_uword(inst.ftf()) >> 31 & 1) == 1) {
        unit->status.insert_field(VuUnitRegister_Status::I, 1);
    }

    unit->status.insert_field(VuUnitRegister_Status::D, 0);

    q.write_float(result);
}

void CVuInterpreter::RSQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& q = unit->q;
    SizedQwordRegister& ft = unit->vf[inst.ft()];

    const float result = std::sqrt(std::abs(ft.read_float(inst.ftf())));
    
    unit->status.clear_flags();

    if ((ft.read_uword(inst.ftf()) >> 31 & 1) == 1) {
        unit->status.insert_field(VuUnitRegister_Status::I, 1);
    }

    if (ft.read_float(inst.ftf()) == 0.0f) {
        unit->status.insert_field(VuUnitRegister_Status::D, 1);
    }

    FpuFlags flag;
    q.write_float(to_ps2_float(1 / result, flag));
}
