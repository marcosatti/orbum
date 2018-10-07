#include <cmath>

#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"
#include "Utilities/Utilities.hpp"

// Miscellaneous VU instructions.
// Includes:-
// - random (R* instructions)
// - branching & jumps
// - GIF/VIF interaction
// - WAIT* instruciotns (synchronization between different VU execution units)

void CVuInterpreter::NOP(VuUnit_Base* unit, const VuInstruction inst)
{
    return;
}

void CVuInterpreter::CLIP(VuUnit_Base* unit, const VuInstruction inst)
{
    // Left-shifts CLIP by 6 bits, compares the fields of FS with w field of FT,
    // and sets the corresponding flags

    SizedQwordRegister& reg_source_1 = unit->vf[inst.fs()];
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    VuUnitRegister_Clipping& clip = unit->clipping;

    const f32 ft = std::abs(reg_source_2.read_float(VuVectorField::W));

    clip.shift_judgement();
    clip.insert_field(VuUnitRegister_Clipping::POSX_0, reg_source_1.read_float(VuVectorField::X) > ft);
    clip.insert_field(VuUnitRegister_Clipping::NEGX_0, reg_source_1.read_float(VuVectorField::X) < -ft);
    clip.insert_field(VuUnitRegister_Clipping::POSY_0, reg_source_1.read_float(VuVectorField::Y) > ft);
    clip.insert_field(VuUnitRegister_Clipping::NEGY_0, reg_source_1.read_float(VuVectorField::Y) < -ft);
    clip.insert_field(VuUnitRegister_Clipping::POSZ_0, reg_source_1.read_float(VuVectorField::Z) > ft);
    clip.insert_field(VuUnitRegister_Clipping::NEGZ_0, reg_source_1.read_float(VuVectorField::Z) < -ft);
}

void CVuInterpreter::RINIT(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedQwordRegister& reg_source = unit->vf[inst.fs()];
    SizedWordRegister& reg_dest = unit->r;

    // Writes a float consisting 23 bits of R as mantissa and 001111111 as exp+sign.
    constexpr uword append = 0b001111111 << 23;
    const uword fsf = (reg_source.read_uword(inst.fsf()) & 0x7FFFFF) | append;
    reg_dest.write_uword(fsf);
}

void CVuInterpreter::RGET(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& reg_source = unit->r;
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    for (auto field : VuVectorField::VECTOR_FIELDS)
    {
        if (inst.test_dest_field(field))
        {
            reg_dest.write_uword(field, reg_source.read_uword());
        }
    }
}

void CVuInterpreter::RNEXT(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& reg_R = unit->r;
    SizedQwordRegister& reg_dest = unit->vf[inst.ft()];

    // A Galois form M-series LFSR adapted from PCSX2 (advance_r() in pcsx2/vu.cpp)
    const int x = (reg_R.read_uword() >> 4) & 1;
    const int y = (reg_R.read_uword() >> 22) & 1;
    reg_R.write_uword(((reg_R.read_uword() << 1) ^ (x ^ y)) & 0x7FFFFF);

    // Append the exp+sign to R
    reg_R.write_uword(reg_R.read_uword() | 0b001111111 << 23);
}

void CVuInterpreter::RXOR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& reg_source_1 = unit->r;
    SizedQwordRegister& reg_source_2 = unit->vf[inst.ft()];
    SizedWordRegister& reg_dest = unit->r;

    const uword a = reg_source_1.read_uword();
    const uword b = reg_source_2.read_uword(inst.fsf()) & 0x7FFFFF;
    const uword result = a ^ b;

    reg_dest.write_uword(result);
}

void CVuInterpreter::WAITQ(VuUnit_Base* unit, const VuInstruction inst)
{
    // WAITQ is handled as a special case in the interpreter

#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) WAITQ is called!") % __FILENAME__ % __LINE__;
#endif

    return;
}

void CVuInterpreter::IBEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];

    if (reg_source_1.read_uhword() == reg_source_2.read_uhword())
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::IBGEZ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];

    if (reg_source_1.read_uhword() >= 0)
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::IBGTZ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];

    if (reg_source_1.read_uhword() > 0)
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::IBLEZ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];

    if (reg_source_1.read_uhword() <= 0)
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::IBLTZ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];

    if (reg_source_1.read_uhword() < 0)
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::IBNE(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];

    if (reg_source_1.read_uhword() != reg_source_2.read_uhword())
    {
        shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
        unit->bdelay.set_branch_itype(unit->pc, offset_by);
    }
}

void CVuInterpreter::B(VuUnit_Base* unit, const VuInstruction inst)
{
    shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
    unit->bdelay.set_branch_itype(unit->pc, offset_by);
}

void CVuInterpreter::BAL(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    if (unit->bdelay.is_branch_pending())
    {
        // If there is a pending branch, the linked register becomes the
        // second instruction of said branch
        reg_dest.write_uhword((unit->bdelay.get_branch_pc() + 8) / 8);
    }
    else
    {
        // Otherwise, the linked register is the instruction next to the
        // branch delay slot
        reg_dest.write_uhword((unit->pc.read_uword() + 2 * 8) / 8);
    }

    shword offset_by = extend_integer<shword, uhword, 11>(inst.imm11());
    unit->bdelay.set_branch_itype(unit->pc, offset_by);
}

void CVuInterpreter::JR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];

    unit->bdelay.set_branch_jtype(unit->pc, reg_source_1.read_uhword());
}

void CVuInterpreter::JALR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    if (unit->bdelay.is_branch_pending())
    {
        // If there is a pending branch, the linked register becomes the
        // second instruction of said branch
        reg_dest.write_uhword((unit->bdelay.get_branch_pc() + 8) / 8);
    }
    else
    {
        // Otherwise, the linked register is the instruction next to the
        // branch delay slot
        reg_dest.write_uhword((unit->pc.read_uword() + 2 * 8) / 8);
    }

    unit->bdelay.set_branch_jtype(unit->pc, reg_source_1.read_uhword());
}

void CVuInterpreter::WAITP(VuUnit_Base* unit, const VuInstruction inst)
{
    // WAITP is handled as a special case in the interpreter

#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) WAITP is called!") % __FILENAME__ % __LINE__;
#endif

    return;
}

void CVuInterpreter::XGKICK(VuUnit_Base* unit, const VuInstruction inst)
{
    // TODO: Wait for GIF to be implemented

#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) XGKICK: Not implemented. (GIF not implemented)") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("XGKICK: Not implemented. (GIF not implemented)");
#endif
}

void CVuInterpreter::XTOP(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];
    const RResources& r = core->get_resources();

    VifUnit_Base* vif = r.ee.vpu.vif.units[unit->core_id];

    reg_dest.write_uhword(vif->top.read_uword());
}

void CVuInterpreter::XITOP(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];
    const RResources& r = core->get_resources();

    VifUnit_Base* vif = r.ee.vpu.vif.units[unit->core_id];

    reg_dest.write_uhword(vif->itop.read_uword());
}
