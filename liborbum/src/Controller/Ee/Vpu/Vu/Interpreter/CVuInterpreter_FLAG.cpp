#include <boost/format.hpp>

#include "Controller/Ee/Vpu/Vu/Interpreter/CVuInterpreter.hpp"
#include "Core.hpp"

// All instructions here are related to the flags.
// Mostly straightforward.

void CVuInterpreter::FSAND(VuUnit_Base* unit, const VuInstruction inst)
{
    const uword status = unit->status.read_uword();
    SizedHwordRegister& vi = unit->vi[inst.it()];
    vi.write_uhword(status & inst.imm12());
}

void CVuInterpreter::FSEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    const uword status = unit->status.read_uword();
    SizedHwordRegister& vi = unit->vi[inst.it()];
    vi.write_uhword((uhword)(status == inst.imm12()));
}

void CVuInterpreter::FSOR(VuUnit_Base* unit, const VuInstruction inst)
{
    const uword status = unit->status.read_uword();
    SizedHwordRegister& vi = unit->vi[inst.it()];
    vi.write_uhword(status | inst.imm12());
}

void CVuInterpreter::FSSET(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& status = unit->status;
    // Set the sticky flags
    // 0xFC0 == 0b111111000000
    status.write_uhword(0, status.read_uhword(0) | (inst.imm12() & 0xFC0));
}

void CVuInterpreter::FMAND(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& it = unit->vi[inst.it()];
    const uword mac = unit->mac.read_uword();
    const uhword is = unit->vi[inst.is()].read_uhword();
    it.write_uhword(mac & is);
}

void CVuInterpreter::FMEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& it = unit->vi[inst.it()];
    const uword mac = unit->mac.read_uword();
    const uhword is = unit->vi[inst.is()].read_uhword();
    it.write_uhword(mac == is);
}

void CVuInterpreter::FMOR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& it = unit->vi[inst.it()];
    const uword mac = unit->mac.read_uword();
    const uhword is = unit->vi[inst.is()].read_uhword();
    it.write_uhword(mac | is);
}

void CVuInterpreter::FCAND(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& vi01 = unit->vi[1];
    const uword clipping = unit->clipping.read_uword();
    vi01.write_uhword((clipping & inst.imm24()) > 0);
}

void CVuInterpreter::FCEQ(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& vi01 = unit->vi[1];
    const uword clipping = unit->clipping.read_uword();
    vi01.write_uhword(clipping == inst.imm24());
}

void CVuInterpreter::FCOR(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& vi01 = unit->vi[1];
    const uword clipping = unit->clipping.read_uword();
    vi01.write_uhword((clipping | inst.imm24()) == 0xFFFFFF);
}

void CVuInterpreter::FCSET(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedWordRegister& clipping = unit->clipping;
    clipping.write_uword(inst.imm24());
}

void CVuInterpreter::FCGET(VuUnit_Base* unit, const VuInstruction inst)
{
    SizedHwordRegister& it = unit->vi[inst.it()];
    const uhword clipping = unit->clipping.read_uword();
    it.write_uhword(clipping & 0xFFF);
}
