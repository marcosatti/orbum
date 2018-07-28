#include <boost/format.hpp>

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"
#include "Core.hpp"
#include "Resources/RResources.hpp"
#include "Utilities/Utilities.hpp"

void CEeCoreInterpreter::BEQ(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs == Rt). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

    if (val_source1 == val_source2)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BEQL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH_LIKELY(Rs == Rt). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

    if (val_source1 == val_source2)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BGEZ(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs >= 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 >= 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BGEZL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs >= 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 >= 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BGTZ(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs > 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 > 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BGTZL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs > 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 > 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BLEZ(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs <= 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 <= 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BLEZL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs <= 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 <= 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BLTZ(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs < 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 < 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BLTZL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs < 0). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));

    if (val_source1 < 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BNE(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs != Rt). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

    if (val_source1 != val_source2)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BNEL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(Rs != Rt). No exceptions.
    auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
    auto& reg_source2 = r.ee.core.r5900.gpr[inst.rs()];
    auto offset = inst.s_imm();

    auto val_source1 = static_cast<sdword>(reg_source1.read_udword(0));
    auto val_source2 = static_cast<sdword>(reg_source2.read_udword(0));

    if (val_source1 != val_source2)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BC0F(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // TODO: Implement.
    // BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
    if (!handle_cop0_usable())
        return;

    const shword offset = inst.s_imm();

    // if (CPCOND0 == false)
    // branch;
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC0F: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("BC0F: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC0FL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // TODO: Implement.
    // BRANCH(CPCOND0 == false). Coprocessor Unusable exception.
    if (!handle_cop0_usable())
        return;

    const shword offset = inst.s_imm();

    // if (CPCOND0 == false)
    // branch likely;
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC0FL: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("BC0FL: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC0T(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // TODO: Implement.
    // BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
    if (!handle_cop0_usable())
        return;

    const shword offset = inst.s_imm();

    // if (CPCOND0 == true)
    // branch;
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC0T: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("BC0T: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC0TL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // TODO: Implement.
    // BRANCH(CPCOND0 == true). Coprocessor Unusable exception.
    if (!handle_cop0_usable())
        return;

    const shword offset = inst.s_imm();

    // if (CPCOND0 == true)
    // branch likely;
#if defined(BUILD_DEBUG)
    BOOST_LOG(Core::get_logger()) << boost::format("(%s, %d) BC0TL: Not implemented.") % __FILENAME__ % __LINE__;
#else
    throw std::runtime_error("BC0TL: Not implemented.");
#endif
}

void CEeCoreInterpreter::BC1F(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
    if (!handle_cop1_usable())
        return;

    const shword offset = inst.s_imm();

    if (r.ee.core.fpu.csr.extract_field(EeCoreFpuRegister_Csr::C) == 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BC1FL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(FCR31[C flag] == 0). Coprocessor Unusable exception.
    if (!handle_cop1_usable())
        return;

    const shword offset = inst.s_imm();

    if (r.ee.core.fpu.csr.extract_field(EeCoreFpuRegister_Csr::C) == 0)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BC1T(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
    if (!handle_cop1_usable())
        return;

    const shword offset = inst.s_imm();

    if (r.ee.core.fpu.csr.extract_field(EeCoreFpuRegister_Csr::C) == 1)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
}

void CEeCoreInterpreter::BC1TL(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // BRANCH(FCR31[C flag] == 1). Coprocessor Unusable exception.
    if (!handle_cop1_usable())
        return;

    const shword offset = inst.s_imm();

    if (r.ee.core.fpu.csr.extract_field(EeCoreFpuRegister_Csr::C) == 1)
        r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
    else
        r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::J(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // JUMP(). No Exceptions.
    r.ee.core.r5900.bdelay.set_branch_jtype(r.ee.core.r5900.pc, inst.addr());
}

void CEeCoreInterpreter::JR(const EeCoreInstruction inst)
{
    auto& r = core->get_resources();

    // JUMP(). Address error exception generated upon instruction load - but not in this instruction.
    auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
    r.ee.core.r5900.bdelay.set_branch_direct(reg_source.read_uword(0));
}
