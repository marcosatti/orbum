#include "Core.hpp"

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CIopCoreInterpreter::ADD(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());
	auto val_source2 = static_cast<sword>(reg_source2.read_uword());
	
	sword result = val_source1 + val_source2;

	if (!handle_no_over_or_underflow_32_check(val_source1, val_source2))
        return;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::ADDI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sword>(reg_source.read_uword());

	sword result = val_source + imm;

	if (!handle_no_over_or_underflow_32_check(val_source, imm))
        return;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::ADDIU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed).
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sword>(reg_source.read_uword());

	sword result = val_source + imm;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::ADDU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());
	auto val_source2 = static_cast<sword>(reg_source2.read_uword());

	sword result = val_source1 + val_source2;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::SUB(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());
	auto val_source2 = static_cast<sword>(reg_source2.read_uword());

	sword result = val_source1 - val_source2;

	if (!handle_no_over_or_underflow_32_check(val_source1, val_source2))
        return;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::SUBU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];

	auto val_source1 = static_cast<uword>(reg_source1.read_uword());
	auto val_source2 = static_cast<uword>(reg_source2.read_uword());

	uword result = val_source1 - val_source2;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::DIV(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<sword>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_SWORD_MIN / -1.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& lo = r.iop.core.r3000.lo;
	auto& hi = r.iop.core.r3000.hi;

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());
	auto val_source2 = static_cast<sword>(reg_source2.read_uword());

	// Check for VALUE_SWORD_MIN / -1 (special condition).
	if (val_source1 == VALUE_SWORD_MIN &&
		val_source2 == -1)
	{
		lo.write_uword(VALUE_SWORD_MIN);
		hi.write_uword(static_cast<sword>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (val_source2 == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		sword resultQ = val_source1 / val_source2;
		sword resultR = val_source1 % val_source2;

		// Quotient.
		lo.write_uword(resultQ);

		// Remainder.
		hi.write_uword(resultR);
	}
}

void CIopCoreInterpreter::DIVU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<uword>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& lo = r.iop.core.r3000.lo;
	auto& hi = r.iop.core.r3000.hi;

	auto val_source1 = static_cast<uword>(reg_source1.read_uword());
	auto val_source2 = static_cast<uword>(reg_source2.read_uword());

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (val_source2 == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		uword resultQ = val_source1 / val_source2;
		uword resultR = val_source1 % val_source2;

		// Quotient.
		lo.write_uword(resultQ);

		// Remainder.
		hi.write_uword(resultR);
	}
}

void CIopCoreInterpreter::MULT(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<sword>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& lo = r.iop.core.r3000.lo;
	auto& hi = r.iop.core.r3000.hi;

	auto val_source1 = static_cast<sdword>(static_cast<sword>(reg_source1.read_uword()));
	auto val_source2 = static_cast<sdword>(static_cast<sword>(reg_source2.read_uword()));

	sdword result = val_source1 * val_source2;

	lo.write_uword(static_cast<sword>(result & 0xFFFFFFFF));
	hi.write_uword(static_cast<sword>((result >> 32) & 0xFFFFFFFF));
}

void CIopCoreInterpreter::MULTU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& lo = r.iop.core.r3000.lo;
	auto& hi = r.iop.core.r3000.hi;

	auto val_source1 = static_cast<udword>(reg_source1.read_uword());
	auto val_source2 = static_cast<udword>(reg_source2.read_uword());

	udword result = val_source1 * val_source2;

	lo.write_uword(static_cast<uword>(result & 0xFFFFFFFF));
	hi.write_uword(static_cast<uword>((result >> 32) & 0xFFFFFFFF));
}

void CIopCoreInterpreter::SLL(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sword>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest.write_uword(reg_source1.read_uword() << shamt);
}

void CIopCoreInterpreter::SLLV(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtend<sword>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = reg_source2.read_ubyte(0) & 0x1F;

	reg_dest.write_uword(reg_source1.read_uword() << shamt);
}

void CIopCoreInterpreter::SRA(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest.write_uword(static_cast<sword>(reg_source1.read_uword()) >> shamt);
}

void CIopCoreInterpreter::SRAV(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = reg_source2.read_ubyte(0) & 0x1F;

	reg_dest.write_uword(static_cast<sword>(reg_source1.read_uword()) >> shamt);
}

void CIopCoreInterpreter::SRL(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = inst.shamt();

	reg_dest.write_uword(reg_source1.read_uword() >> shamt);
}

void CIopCoreInterpreter::SRLV(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];
	ubyte shamt = reg_source2.read_ubyte(0) & 0x1F;

	reg_dest.write_uword(reg_source1.read_uword() >> shamt);
}

void CIopCoreInterpreter::AND(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	reg_dest.write_uword(reg_source1.read_uword() & reg_source2.read_uword());
}

void CIopCoreInterpreter::ANDI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<uword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	uword imm = static_cast<uword>(inst.u_imm());

	reg_dest.write_uword(reg_source1.read_uword() & imm);
}

void CIopCoreInterpreter::NOR(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	reg_dest.write_uword(~(reg_source1.read_uword() | reg_source2.read_uword()));
}

void CIopCoreInterpreter::OR(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	reg_dest.write_uword(reg_source1.read_uword() | reg_source2.read_uword());
}

void CIopCoreInterpreter::ORI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<uword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	uword imm = static_cast<uword>(inst.u_imm());

	reg_dest.write_uword(reg_source1.read_uword() | imm);
}

void CIopCoreInterpreter::XOR(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	reg_dest.write_uword(reg_source1.read_uword() ^ reg_source2.read_uword());
}

void CIopCoreInterpreter::XORI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt XOR Extended<uword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	uword imm = static_cast<uword>(inst.u_imm());

	reg_dest.write_uword(reg_source1.read_uword() ^ imm);
}

void CIopCoreInterpreter::SLT(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtended<sword>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());
	auto val_source2 = static_cast<sword>(reg_source2.read_uword());

	sword result = (val_source1 < val_source2) ? 1 : 0;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::SLTI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtended<sword>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto imm = static_cast<sword>(inst.s_imm());

	auto val_source1 = static_cast<sword>(reg_source1.read_uword());

	sword result = (val_source1 < imm) ? 1 : 0;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::SLTIU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtended<uword>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];

	uword val_source1 = reg_source1.read_uword();
	uword imm = static_cast<uword>(static_cast<sword>(inst.s_imm()));

	uword result = (val_source1 < imm) ? 1 : 0;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::SLTU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = SignExtended<uword>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()];
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rd()];

	uword val_source1 = reg_source1.read_uword();
	uword val_source2 = reg_source2.read_uword();

	uword result = (val_source1 < val_source2) ? 1 : 0;

	reg_dest.write_uword(result);
}

