#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::ADD(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	sdword result = val_source1 + val_source2;

	// Check for over/under flow.
	if (handle_over_or_underflow_32(val_source1, val_source2))
        return;
	
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::ADDI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sword>(reg_source->read_uword(0));
	sdword result = val_source + imm;

	// Check for over/under flow.
	if (handle_over_or_underflow_32(val_source, imm))
        return;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::ADDIU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sword>(reg_source->read_uword(0));
	sdword result = val_source + imm;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::ADDU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	sdword result = val_source1 + val_source2;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DADD(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2->read_udword(0));
	sdword result = val_source1 + val_source2;

	// Check for over/under flow.
	if (handle_over_or_underflow_64(val_source1, val_source2))
        return;
		
	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DADDI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sdword>(reg_source->read_udword(0));
	sdword result = val_source + imm;

	// Check for over/under flow.
    if (handle_over_or_underflow_64(val_source, imm))
        return;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DADDIU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rt = Rs + Imm (signed).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto imm = inst.s_imm();

	auto val_source = static_cast<sdword>(reg_source->read_udword(0));
	sdword result = val_source + imm;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DADDU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs + Rt
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2->read_udword(0));
	sdword result = val_source1 + val_source2;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DSUB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2->read_udword(0));
	sdword result = val_source1 - val_source2;

	// Check for over/under flow.
	if (handle_over_or_underflow_64(val_source1, val_source2))
		return;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::DSUBU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sdword>(reg_source1->read_udword(0));
	auto val_source2 = static_cast<sdword>(reg_source2->read_udword(0));
	sdword result = val_source1 - val_source2;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SUB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	sdword result = val_source1 - val_source2;

	// Check for over/under flow.
	if (handle_over_or_underflow_32(val_source1, val_source2))
		return;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::SUBU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs - Rt
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	sdword result = val_source1 - val_source2;

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::PADDB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sbyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<sbyte>(reg_source2->read_ubyte(i));
		sbyte result = val_source1 + val_source2;
		reg_dest->write_ubyte(i, result);
	}
}

void CEeCoreInterpreter::PADDH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++) 
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = val_source1 + val_source2;
		reg_dest->write_uhword(i, result);
	}
}

void CEeCoreInterpreter::PADDSB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sbyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<sbyte>(reg_source2->read_ubyte(i));
		shword result = val_source1 + val_source2;

		if (result > VALUE_SBYTE_MAX)
			reg_dest->write_ubyte(i, VALUE_SBYTE_MAX);
		else if (result < VALUE_SBYTE_MIN)
			reg_dest->write_ubyte(i, VALUE_SBYTE_MIN);
		else
			reg_dest->write_ubyte(i, static_cast<sbyte>(result));
	}
}

void CEeCoreInterpreter::PADDSH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		sword result = val_source1 + val_source2;

		if (result > VALUE_SHWORD_MAX)
			reg_dest->write_uhword(i, VALUE_SHWORD_MAX);
		else if (result < VALUE_SHWORD_MIN)
			reg_dest->write_uhword(i, VALUE_SHWORD_MIN);
		else
			reg_dest->write_uhword(i, static_cast<shword>(result));
	}
}

void CEeCoreInterpreter::PADDSW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sdword result = val_source1 + val_source2;

		if (result > VALUE_SWORD_MAX)
			reg_dest->write_uword(i, VALUE_SWORD_MAX);
		else if (result < VALUE_SWORD_MIN)
			reg_dest->write_uword(i, VALUE_SWORD_MIN);
		else
			reg_dest->write_uword(i, static_cast<sword>(result));
	}
}

void CEeCoreInterpreter::PADDUB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<ubyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<ubyte>(reg_source2->read_ubyte(i));
		uhword result = val_source1 + val_source2;

		if (result > VALUE_UBYTE_MAX)
			reg_dest->write_ubyte(i, VALUE_UBYTE_MAX);
		else
			reg_dest->write_ubyte(i, static_cast<ubyte>(result));
	}
}

void CEeCoreInterpreter::PADDUH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<uhword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<uhword>(reg_source2->read_uhword(i));
		uword result = val_source1 + val_source2;

		if (result > VALUE_UHWORD_MAX)
			reg_dest->write_uhword(i, VALUE_UHWORD_MAX);
		else
			reg_dest->write_uhword(i, static_cast<uhword>(result));
	}
}

void CEeCoreInterpreter::PADDUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<uword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<uword>(reg_source2->read_uword(i));
		udword result = val_source1 + val_source2;

		if (result > VALUE_UWORD_MAX)
			reg_dest->write_uword(i, VALUE_UWORD_MAX);
		else
			reg_dest->write_uword(i, static_cast<uword>(result));
	}
}

void CEeCoreInterpreter::PADDW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sword result = val_source1 + val_source2;
		reg_dest->write_uword(i, result);
	}
}

void CEeCoreInterpreter::PADSBH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = val_source1 - val_source2;
		reg_dest->write_uhword(i, result);
	}
	for (auto i = NUMBER_HWORDS_IN_QWORD / 2; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = val_source1 + val_source2;
		reg_dest->write_uhword(i, result);
	}
}

void CEeCoreInterpreter::PSUBB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sbyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<sbyte>(reg_source2->read_ubyte(i));
		sbyte result = val_source1 - val_source2;
		reg_dest->write_ubyte(i, result);
	}
}

void CEeCoreInterpreter::PSUBH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		shword result = val_source1 - val_source2;
		reg_dest->write_uhword(i, result);
	}
}

void CEeCoreInterpreter::PSUBSB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sbyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<sbyte>(reg_source2->read_ubyte(i));
		shword result = val_source1 - val_source2;

		if (result > VALUE_SBYTE_MAX)
			reg_dest->write_ubyte(i, VALUE_SBYTE_MAX);
		else if (result < VALUE_SBYTE_MIN)
			reg_dest->write_ubyte(i, VALUE_SBYTE_MIN);
		else
			reg_dest->write_ubyte(i, static_cast<sbyte>(result));
	}
}

void CEeCoreInterpreter::PSUBSH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		sword result = val_source1 - val_source2;

		if (result > VALUE_SHWORD_MAX)
			reg_dest->write_uhword(i, VALUE_SHWORD_MAX);
		else if (result < VALUE_SHWORD_MIN)
			reg_dest->write_uhword(i, VALUE_SHWORD_MIN);
		else
			reg_dest->write_uhword(i, static_cast<shword>(result));
	}
}

void CEeCoreInterpreter::PSUBSW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sdword result = val_source1 - val_source2;

		if (result > VALUE_SWORD_MAX)
			reg_dest->write_uword(i, VALUE_SWORD_MAX);
		else if (result < VALUE_SWORD_MIN)
			reg_dest->write_uword(i, VALUE_SWORD_MIN);
		else
			reg_dest->write_uword(i, static_cast<sword>(result));
	}
}

void CEeCoreInterpreter::PSUBUB(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_BYTES_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sbyte>(reg_source1->read_ubyte(i));
		auto val_source2 = static_cast<sbyte>(reg_source2->read_ubyte(i));
		shword result = val_source1 - val_source2;

		if (result < 0)
			reg_dest->write_ubyte(i, 0);
		else
			reg_dest->write_ubyte(i, static_cast<ubyte>(result));
	}
}

void CEeCoreInterpreter::PSUBUH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		sword result = val_source1 - val_source2;

		if (result < 0)
			reg_dest->write_uhword(i, 0);
		else
			reg_dest->write_uhword(i, static_cast<uhword>(result));
	}
}

void CEeCoreInterpreter::PSUBUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uhword(i));
		sdword result = val_source1 - val_source2;

		if (result < 0)
			reg_dest->write_uword(i, 0);
		else
			reg_dest->write_uword(i, static_cast<uword>(result));
	}
}

void CEeCoreInterpreter::PSUBW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sword result = val_source1 - val_source2;
		reg_dest->write_uword(i, result);
	}
}

