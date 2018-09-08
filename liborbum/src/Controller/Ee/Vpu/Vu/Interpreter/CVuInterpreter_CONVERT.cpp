#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"

// All instructions here are related to the conversion between floating-points and 
// fixed-points.
//
// FTOIx are the instructions for converting a float to a fixed with (32-x) bits
// as the integer part, and (x) bits as the fractional part.
//
// ITOFx are the instructions for converting a fixed to a float.

void CVuInterpreter::FTOI0(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 f = fs.read_float(field);
            // No conversions needed
            const uword result = static_cast<uword>(f);
            ft.write_uword(field, result);
        }
    }
}

void CVuInterpreter::FTOI4(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            // Multiply the float by (1 << n), where n is the precision of the fixed-point
            // See ITOF4 for the (reversed) reason for doing so
            const f32 f = fs.read_float(field) * (1 << 4);

            // Cast the resultant float into an integer
            const uword result = static_cast<uword>(f);
            
            ft.write_uword(field, result);
        }
    }
}

void CVuInterpreter::FTOI12(VuUnit_Base* unit, const VuInstruction inst)
{
    // See FTOI4 for more details on how the code works.

    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 f = fs.read_float(field) * (1 << 12);
            const uword result = static_cast<uword>(f);
            ft.write_uword(field, result);
        }
    }
}

void CVuInterpreter::FTOI15(VuUnit_Base* unit, const VuInstruction inst)
{
    // See FTOI4 for more details on how the code works.

    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const f32 f = fs.read_float(field) * (1 << 15);
            const uword result = static_cast<uword>(f);
            ft.write_uword(field, result);
        }
    }
}

void CVuInterpreter::ITOF0(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            uword u = fs.read_uword(field);
            
            // No fractional parts to worry about, just cast it
            const f32 result = static_cast<f32>(u);

            ft.write_float(field, result);
        }
    }
}

void CVuInterpreter::ITOF4(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const uword u = fs.read_uword(field);

            // The FPU is faster multiplying than dividing, thus we let the compiler
            // calculate (1 / n) for us, and we multiply that value later
            // Since the values we use are representable in floats, there's no precision loss
            constexpr f32 multiplier = 1 / static_cast<f32>(1 << 4);

            // By dividing the input, we essentially "move" the decimal point of it
            // i.e. 10010101 to 1001.0101
            const f32 result = u * multiplier;

            ft.write_float(field, result);
        }
    }
}

void CVuInterpreter::ITOF12(VuUnit_Base* unit, const VuInstruction inst)
{
    // See ITOF4 for more details

    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const uword u = fs.read_uword(field);
            constexpr f32 multiplier = 1 / static_cast<f32>(1 << 12);
            const f32 result = u * multiplier;
            ft.write_float(field, result);
        }
    }
}

void CVuInterpreter::ITOF15(VuUnit_Base* unit, const VuInstruction inst)
{
    // See ITOF4 for more details

    SizedQwordRegister& ft = unit->vf[inst.ft()];
    SizedQwordRegister& fs = unit->vf[inst.fs()];
    ubyte dest = inst.dest();

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            const uword u = fs.read_uword(field);
            constexpr f32 multiplier = 1 / static_cast<f32>(1 << 15);
            const f32 result = u * multiplier;
            ft.write_float(field, result);
        }
    }
}