#include <cmath>

#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnitRegisters.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Utilities/Utilities.hpp"

// All instructions here are related to float arithmetic.
// 
// Explaination for the comments:
// VF[x]    - the x-th register of VF
// VF[x](f) - the f field of the x-th register of VF, if not specified
//            then the operation is applied to all fields (xyzw)

void CVuInterpreter::ABS(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[ft] = abs(VF[fs]) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // std::abs uses compiler intrinsics internally, and hence it's
            // sometimes faster than bit ops ...
            // const f32 val = reg_source.read_float(field);
            // const f32 result = to_ps2_float(std::abs(val), flags);

            // ... but it might screw the PS2 floats out, so we do bit ops by
            // ANDing the value with 0x7FFFFFFF, setting the first bit to 0 (positive).
            const uword raw = reg_source.read_uword(field) & 0x7FFFFFFF;
            const f32 result = *reinterpret_cast<const f32*>(&raw);

            reg_dest.write_float(field, result);
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::ADD(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[fd] = VF[fs] + VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a + b, flags);
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
    // VF[fd] = VF[fs] + I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a + b, flags);
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
    // VF[fd] = VF[fs] + Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a + b, flags);
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
    // VF[fd] = VF[fs] + VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a + b, flags);
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
    // ACC = VF[fs] + VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a + b, flags);
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
    // ACC = VF[fs] + I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a + b, flags);
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
    // ACC = VF[fs] + Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a + b, flags);
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
    // ACC = VF[fs] + VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a + b, flags);
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
    // VF[fd] = VF[fs] - VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a - b, flags);
            unit->mac.update_vector_field(field, flags);
            reg_dest.write_float(field, result);
        }
        else
            unit->mac.clear_vector_field(field);
    }
}

void CVuInterpreter::SUBi(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[fd] = VF[fs] - I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a - b, flags);
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
    // VF[fd] = VF[fs] - Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a - b, flags);
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
    // VF[fd] = VF[fs] - VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a - b, flags);
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
    // ACC = VF[fs] - VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a - b, flags);
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
    // ACC = VF[fs] - I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a - b, flags);
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
    // ACC = VF[fs] - Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a - b, flags);
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
    // ACC = VF[fs] - VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a - b, flags);
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
    // VF[fd] = VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a * b, flags);
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
    // VF[fd] = VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a * b, flags);
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
    // VF[fd] = VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];    

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a * b, flags);
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
    // VF[fd] = VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a * b, flags);
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
    // ACC = VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 result = to_ps2_float(a * b, flags);
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
    // ACC = VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a * b, flags);
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
    // ACC = VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 result = to_ps2_float(a * b, flags);
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
    // ACC = VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 result = to_ps2_float(a * b, flags);
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
    // VF[fd] = ACC + VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 c = reg_source_3.read_float(field);

            // According to the VU manual,
            // MAC flag and status flag are set according to the final result
            // and the sticky flags indicate the exceptions raised during multiplication
            const f32 multiplied = to_ps2_float(a * b, flags);
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // VF[fd] = ACC + VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // VF[fd] = ACC + VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // VF[fd] = ACC + VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // ACC = ACC + VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // ACC = ACC + VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // ACC = ACC + VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // ACC = ACC + VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c + multiplied, flags);
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
    // VF[fd] = VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // VF[fd] = VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // VF[fd] = VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // VF[fd] = VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // ACC = VF[fs] * VF[ft] for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // ACC = VF[fs] * I for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // ACC = VF[fs] * Q for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->q;
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // ACC = VF[fs] * VF[ft](bc) for each field if (dest[field] == 1)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_source_3 = unit->acc;
    SizedQwordRegister& reg_dest = unit->acc;
    // const ubyte bc = inst.bc();
    const ubyte bc = static_cast<ubyte>(idx);

    FpuFlags flags;
    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            const f32 c = reg_source_3.read_float(field);
            
            const f32 multiplied = to_ps2_float(a * b, flags); // See MADD for details
            unit->mac.update_vector_field(field, flags);

            const f32 result = to_ps2_float(c - multiplied, flags);
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
    // VF[fd] = max(VF[fs], VF[ft])

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            reg_dest.write_float(field, std::max(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MAXi(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[fd] = max(VF[fs], i)

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            reg_dest.write_float(field, std::max(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MAXbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    // VF[fd] = max(VF[fs], VF[ft])

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    const ubyte bc = static_cast<ubyte>(idx);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            reg_dest.write_float(field, std::max(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
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
    // VF[fd] = min(VF[fs], VF[ft])

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(field);
            reg_dest.write_float(field, std::min(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MINIi(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[fd] = min(VF[fs], VF[ft])

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedWordRegister& reg_source_2 = unit->i;
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float();
            reg_dest.write_float(field, std::min(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
        }
    }
}

void CVuInterpreter::MINIbc(VuUnit_Base* unit, const VuInstruction inst, const int idx)
{
    // VF[fd] = min(VF[fs], VF[ft])

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedQwordRegister& reg_dest = unit->vf[inst.fd()];

    const ubyte bc = static_cast<ubyte>(idx);

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 a = reg_source_1.read_float(field);
            const f32 b = reg_source_2.read_float(bc);
            reg_dest.write_float(field, std::min(a, b));
        }
        else
        {
            unit->mac.clear_vector_field(field);
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
    // ACCx = VF[fs](y) * VF[ft](z)
    // ACCy = VF[fs](z) * VF[ft](x)
    // ACCz = VF[fs](x) * VF[ft](y)

    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& acc = unit->acc;

    FpuFlags flags;

    acc.write_float(VuVectorField::X, to_ps2_float(fs.read_float(VuVectorField::Y) * ft.read_float(VuVectorField::Z), flags));
    unit->mac.update_vector_field(VuVectorField::X, flags);

    acc.write_float(VuVectorField::Y, to_ps2_float(fs.read_float(VuVectorField::Z) * ft.read_float(VuVectorField::X), flags));
    unit->mac.update_vector_field(VuVectorField::Y, flags);

    acc.write_float(VuVectorField::Z, to_ps2_float(fs.read_float(VuVectorField::X) * ft.read_float(VuVectorField::Y), flags));
    unit->mac.update_vector_field(VuVectorField::Z, flags);

    unit->mac.clear_vector_field(VuVectorField::W);
}

void CVuInterpreter::OPMSUB(VuUnit_Base* unit, const VuInstruction inst)
{
    // VF[fd](x) = ACC(x) - VF[fs](y) * VF[ft](z)
    // VF[fd](y) = ACC(y) - VF[fs](z) * VF[ft](x)
    // VF[fd](z) = ACC(z) - VF[fs](x) * VF[ft](y)

    SizedQwordRegister& fd = unit->vf[inst.fd()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& acc = unit->acc;

    FpuFlags flags;
    fd.write_float(VuVectorField::X, to_ps2_float(acc.read_float(VuVectorField::X) - fs.read_float(VuVectorField::Y) * ft.read_float(VuVectorField::Z), flags));
    unit->mac.update_vector_field(VuVectorField::X, flags);

    fd.write_float(VuVectorField::Y, to_ps2_float(acc.read_float(VuVectorField::Y) - fs.read_float(VuVectorField::Z) * ft.read_float(VuVectorField::X), flags));
    unit->mac.update_vector_field(VuVectorField::Y, flags);

    fd.write_float(VuVectorField::Z, to_ps2_float(acc.read_float(VuVectorField::Z) - fs.read_float(VuVectorField::X) * ft.read_float(VuVectorField::Y), flags));
    unit->mac.update_vector_field(VuVectorField::Z, flags);

    unit->mac.clear_vector_field(VuVectorField::W);
}

void CVuInterpreter::DIV(VuUnit_Base* unit, const VuInstruction inst)
{
    // Q = vf[fs] / vs[ft]
    
    SizedWordRegister& q = unit->q;
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    SizedQwordRegister& ft = unit->vf[inst.ft()];

    FpuFlags flags;
    const f32 result = to_ps2_float(fs.read_float(inst.fsf()) / ft.read_float(inst.ftf()), flags);
    
    // If ft[ftf] is 0, division by zero occurs...
    if (ft.read_float(inst.ftf()) == 0.0f) 
    {
        // ...and if the dividend is 0, set the I flag, otherwise the D flag
        // See VU Users Manual pg 40
        if (fs.read_float(inst.fsf()) == 0.0f) 
        {
            unit->status.set_i_flag_sticky(1);
        } 
        else 
        {
            unit->status.set_d_flag_sticky(1);
        }
    }

    q.write_float(result);
}

void CVuInterpreter::SQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    // Q = sqrt(abs(VF[ft]))

    SizedWordRegister& q = unit->q;
    SizedQwordRegister& ft = unit->vf[inst.ft()];

    const f32 result = std::sqrt(std::abs(ft.read_float(inst.ftf())));

    // If the float is negative, set the I flag
    if ((ft.read_uword(inst.ftf()) >> 31 & 1) == 1) 
    {
        unit->status.set_i_flag_sticky(1);
    }

    // The D flag will always be zero after a sqrt
    unit->status.set_d_flag_sticky(0);

    q.write_float(result);
}

void CVuInterpreter::RSQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    // Q = VF[fs] / sqrt(abs(VF[ft]))
    SizedWordRegister& q = unit->q;
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];

    const f32 result = std::sqrt(std::abs(ft.read_float(inst.ftf())));

    // Set the I flag if the number to be sqrt-ed is negative.
    if ((ft.read_uword(inst.ftf()) >> 31 & 1) == 1) 
    {
        unit->status.set_i_flag_sticky(1);
    }

    // Set the D flag if the final result is 1 / 0
    if (ft.read_float(inst.ftf()) == 0.0f) 
    {
        unit->status.set_d_flag_sticky(1);
    }

    FpuFlags flag;
    q.write_float(to_ps2_float(fs.read_float(inst.fsf()) / result, flag));
}
