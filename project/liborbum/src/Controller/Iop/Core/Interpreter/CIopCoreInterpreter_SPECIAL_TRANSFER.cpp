#include "Core.hpp"

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CIopCoreInterpreter::MFC0(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
		return;

	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.cop0.registers[inst.rd()];

	reg_dest->write_uword(static_cast<uword>(reg_source->read_uword()));
}

void CIopCoreInterpreter::MTC0(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
		return;

	auto& reg_source = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.cop0.registers[inst.rd()];

	reg_dest->write_uword(reg_source->read_uword());
}

void CIopCoreInterpreter::MFHI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = HI. No exceptions.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& hi = r.iop.core.r3000.hi;

	reg_dest->write_uword(hi.read_uword());
}

void CIopCoreInterpreter::MFLO(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = LO. No exceptions.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& lo = r.iop.core.r3000.lo;

	reg_dest->write_uword(lo.read_uword());
}

void CIopCoreInterpreter::MTHI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// HI = Rd. No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rd()];
	auto& hi = r.iop.core.r3000.hi;

	hi.write_uword(reg_source1->read_uword());
}

void CIopCoreInterpreter::MTLO(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// LO = Rd. No exceptions.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rd()];
	auto& lo = r.iop.core.r3000.lo;

	lo.write_uword(reg_source1->read_uword());
}
