#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"
#include "Resources/Ee/Vpu/Vu/VuUnits.hpp"
#include "Utilities/Utilities.hpp"

// All instructions here are related to integer arithmetics.

void CVuInterpreter::IADD(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[id] = VI[is] + VI[it]

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];
    SizedHwordRegister& reg_dest = unit->vi[inst.id()];

    const shword a = reg_source_1.read_uhword();
    const shword b = reg_source_2.read_uhword();
    const shword result = a + b;

    // The behaviour is standard-defined and thus cross-platform. (Phew!)
    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::IADDI(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[it] = VI[is] + Imm

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    const ubyte reg_source_2 = inst.imm5();
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    // Imm5 is a five-bit signed integer, so convert it
    const shword a = static_cast<shword>(reg_source_1.read_uhword());
    const shword b = extend_integer<shword, ubyte, 5>(reg_source_2);
    shword result = a + b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::IADDIU(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[it] = VI[is] + Imm

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    const uhword reg_source_2 = inst.imm15();
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    const shword a = static_cast<shword>(reg_source_1.read_uhword());
    const uhword b = reg_source_2;
    shword result = a + b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::IAND(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[id] = VI[is] & VI[it]

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];
    SizedHwordRegister& reg_dest = unit->vi[inst.id()];

    const shword a = reg_source_1.read_uhword();
    const shword b = reg_source_2.read_uhword();
    const shword result = a & b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::IOR(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[id] = VI[is] | VI[it]

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];
    SizedHwordRegister& reg_dest = unit->vi[inst.id()];

    const shword a = reg_source_1.read_uhword();
    const shword b = reg_source_2.read_uhword();
    const shword result = a | b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::ISUB(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[id] = VI[is] - VI[it]

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    SizedHwordRegister& reg_source_2 = unit->vi[inst.it()];
    SizedHwordRegister& reg_dest = unit->vi[inst.id()];

    const shword a = reg_source_1.read_uhword();
    const shword b = reg_source_2.read_uhword();
    const shword result = a - b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}

void CVuInterpreter::ISUBIU(VuUnit_Base* unit, const VuInstruction inst)
{
    // VI[it] = VI[is] - Imm

    SizedHwordRegister& reg_source_1 = unit->vi[inst.is()];
    const uhword reg_source_2 = inst.imm15();
    SizedHwordRegister& reg_dest = unit->vi[inst.it()];

    const shword a = static_cast<shword>(reg_source_1.read_uhword());
    const uhword b = reg_source_2;
    shword result = a - b;

    reg_dest.write_uhword(static_cast<uhword>(result));
}
