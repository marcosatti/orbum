#include <cmath>

#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"

// All instructions here are related to the EFU (Elementary Functio Unit).
// All results produced by those instructions are stored in the P register.

void CVuInterpreter::ESADD(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = VF[fs](x)^2 + VF[fs](y)^2 + VF[fs](z)^2

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 c = reg_source.read_float(VuVectorField::Z);
    const f32 result = (a * a) + (b * b) + (c * c);

    reg_dest.write_float(result);
}

void CVuInterpreter::ERSADD(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = 1 / (VF[fs](x)^2 + VF[fs](y)^2 + VF[fs](z)^2)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 c = reg_source.read_float(VuVectorField::Z);
    const f32 result = 1.0f / ((a * a) + (b * b) + (c * c));

    reg_dest.write_float(result);
}

void CVuInterpreter::ELENG(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = sqrt(VF[fs](x)^2 + VF[fs](y)^2 + VF[fs](z)^2)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 c = reg_source.read_float(VuVectorField::Z);
    const f32 result = std::sqrt((a * a) + (b * b) + (c * c));

    reg_dest.write_float(result);
}

void CVuInterpreter::ERLENG(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = 1 / sqrt(VF[fs](x)^2 + VF[fs](y)^2 + VF[fs](z)^2)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 c = reg_source.read_float(VuVectorField::Z);
    const f32 result = 1.0f / std::sqrt((a * a) + (b * b) + (c * c));

    reg_dest.write_float(result);
}

void CVuInterpreter::EATANxy(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = arctan(VF[fs](y) / VF[fs](x))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 result = std::atan(b / a);

    reg_dest.write_float(result);
}

void CVuInterpreter::EATANxz(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = arctan(VF[fs](y) / VF[fs](x))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Z);
    const f32 result = std::atan(b / a);

    reg_dest.write_float(result);
}

void CVuInterpreter::ESUM(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = VF[fs](w) + VF[fs](x) + VF[fs](y) + VF[fs](z)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(VuVectorField::X);
    const f32 b = reg_source.read_float(VuVectorField::Y);
    const f32 c = reg_source.read_float(VuVectorField::Z);
    const f32 d = reg_source.read_float(VuVectorField::W);
    const f32 result = a + b + c + d;

    reg_dest.write_float(result);
}

void CVuInterpreter::ERCPR(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = 1 / VF[fs](fsf)

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = 1.0f / a;

    reg_dest.write_float(result);
}

void CVuInterpreter::ESQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = sqrt(VF[fs](fsf))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = std::sqrt(a);

    reg_dest.write_float(result);
}

void CVuInterpreter::ERSQRT(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = 1 / sqrt(VF[fs](fsf))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = 1.0f / std::sqrt(a);

    reg_dest.write_float(result);
}

void CVuInterpreter::ESIN(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = sin(VF[fs](fsf))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = std::sin(a);

    reg_dest.write_float(result);
}

void CVuInterpreter::EATAN(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = arctan(VF[fs](fsf))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = std::atan(a);

    reg_dest.write_float(result);
}

void CVuInterpreter::EEXP(VuUnit_Base* unit, const VuInstruction inst)
{
    // P = exp(-VF[fs](fsf))

    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->p;

    const f32 a = reg_source.read_float(inst.fsf());
    const f32 result = std::exp(-a);

    reg_dest.write_float(result);
}
