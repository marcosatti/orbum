#include "Core.hpp"

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CIopCoreInterpreter::BEQ(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();

	// BRANCH(Rs == Rt). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());
	auto val_source2 = static_cast<sword>(reg_source2->read_uword());

	if (val_source1 == val_source2)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::BGEZ(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH(Rs >= 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 >= 0)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::BGEZAL(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 >= 0)
	{
		r.iop.core.r3000.gpr[31]->write_uword(r.iop.core.r3000.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
	}
}

void CIopCoreInterpreter::BGTZ(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH(Rs > 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 > 0)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::BLEZ(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH(Rs <= 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 <= 0)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::BLTZ(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH(Rs < 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 < 0)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::BLTZAL(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());

	if (val_source1 < 0)
	{
		r.iop.core.r3000.gpr[31]->write_uword(r.iop.core.r3000.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
	}
}

void CIopCoreInterpreter::BNE(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH(Rs != Rt). No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sword>(reg_source1->read_uword());
	auto val_source2 = static_cast<sword>(reg_source2->read_uword());

	if (val_source1 != val_source2)
		r.iop.core.r3000.bdelay.set_branch_itype(r.iop.core.r3000.pc, offset);
}

void CIopCoreInterpreter::J(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP(). No Exceptions.
	r.iop.core.r3000.bdelay.set_branch_jtype(r.iop.core.r3000.pc, inst.addr());
}

void CIopCoreInterpreter::JR(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP_REGISTER().
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	r.iop.core.r3000.bdelay.set_branch_direct(reg_source1->read_uword());
}

void CIopCoreInterpreter::JAL(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP_LINK(). No exceptions.
	// Note: "link register" is GPR[31].
	r.iop.core.r3000.gpr[31]->write_uword(r.iop.core.r3000.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2);
	r.iop.core.r3000.bdelay.set_branch_jtype(r.iop.core.r3000.pc, inst.addr());
}

void CIopCoreInterpreter::JALR(const IopCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP_LINK_REGISTER().
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	reg_dest->write_uword(static_cast<uword>(r.iop.core.r3000.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	r.iop.core.r3000.bdelay.set_branch_direct(reg_source->read_uword());
}

