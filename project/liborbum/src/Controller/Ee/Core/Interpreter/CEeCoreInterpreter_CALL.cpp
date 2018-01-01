#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::BGEZAL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));

	if (val_source1 >= 0)
	{
		r.ee.core.r5900.gpr[31]->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
		r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
	}
}

void CEeCoreInterpreter::BGEZALL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs >= 0). No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));

	if (val_source1 >= 0)
	{
		r.ee.core.r5900.gpr[31]->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
		r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
	}
	else
		r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::BLTZAL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));

	if (val_source1 < 0)
	{
		r.ee.core.r5900.gpr[31]->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
		r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
	}
}

void CEeCoreInterpreter::BLTZALL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// BRANCH_LINK(Rs < 0). No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto offset = inst.s_imm();

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));

	if (val_source1 < 0)
	{
		r.ee.core.r5900.gpr[31]->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
		r.ee.core.r5900.bdelay.set_branch_itype(r.ee.core.r5900.pc, offset);
	}
	else
		r.ee.core.r5900.bdelay.advance_pc(r.ee.core.r5900.pc); // Immediate jump to the instruction at PC + 8 (nullify next instruction).
}

void CEeCoreInterpreter::JAL(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP_LINK(). No exceptions.
	r.ee.core.r5900.gpr[31]->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	r.ee.core.r5900.bdelay.set_branch_jtype(r.ee.core.r5900.pc, inst.addr());
}

void CEeCoreInterpreter::JALR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// JUMP_LINK_REGISTER(). Address error exception generated upon instruction load - but not in this instruction.
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest->write_udword(0, static_cast<udword>(r.ee.core.r5900.pc.read_uword() + Constants::MIPS::SIZE_MIPS_INSTRUCTION * 2));
	r.ee.core.r5900.bdelay.set_branch_direct(reg_source->read_uword(0));
}
