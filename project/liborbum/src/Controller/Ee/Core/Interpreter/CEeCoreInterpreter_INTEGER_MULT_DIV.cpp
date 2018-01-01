#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::DIV(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<sdword>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (val_source1 == VALUE_SWORD_MIN &&
		val_source2 == -1)
	{
		lo.write_udword(0, static_cast<sdword>(VALUE_SWORD_MIN));
		hi.write_udword(0, static_cast<sdword>(0));
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
		lo.write_udword(0, static_cast<sdword>(resultQ));

		// Remainder.
		hi.write_udword(0, static_cast<sdword>(resultR));
	}
}

void CEeCoreInterpreter::DIV1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIV(inst);
}

void CEeCoreInterpreter::DIVU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<udword>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<uword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<uword>(reg_source2->read_uword(0));

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
		lo.write_udword(0, static_cast<sdword>(static_cast<sword>(resultQ)));

		// Remainder.
		hi.write_udword(0, static_cast<sdword>(static_cast<sword>(resultR)));
	}
}

void CEeCoreInterpreter::DIVU1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIVU(inst);
}

void CEeCoreInterpreter::MULT(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (Rd, LO, HI) = SignExtend<sdword>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<sdword>(static_cast<sword>(reg_source1->read_uword(0)));
	auto val_source2 = static_cast<sdword>(static_cast<sword>(reg_source2->read_uword(0)));

	sdword result = val_source1 * val_source2;

	reg_dest->write_udword(0, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
	lo.write_udword(0, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
	hi.write_udword(0, static_cast<sdword>(static_cast<sword>(result >> 32)));
}

void CEeCoreInterpreter::MULT1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULT(inst);
}

void CEeCoreInterpreter::MULTU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (Rd, LO, HI) = SignExtend<sdword>(Rs[UW] * Rt[UW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<udword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<udword>(reg_source2->read_uword(0));

	udword result = val_source1 * val_source2;

	reg_dest->write_udword(0, static_cast<udword>(static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF))));
	lo.write_udword(0, static_cast<udword>(static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF))));
	hi.write_udword(0, static_cast<udword>(static_cast<sdword>(static_cast<sword>(result >> 32))));
}

void CEeCoreInterpreter::MULTU1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULTU(inst);
}

void CEeCoreInterpreter::PDIVBW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<sdword>(Rs[SW] / Rt[SH,0]) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source2 = static_cast<shword>(reg_source2->read_uhword(0)); // Constant.

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (val_source1 == VALUE_SWORD_MIN &&
			val_source2 == -1)
		{
			lo.write_uword(i, static_cast<sword>(VALUE_SWORD_MIN));
			hi.write_uword(i, static_cast<sword>(0));
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
			lo.write_uword(i, resultQ);

			// Remainder.
			hi.write_uword(i, resultR);
		}
	}
}

void CEeCoreInterpreter::PDIVUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI)(0,1) = SignExtend<udword>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto val_source1 = static_cast<uword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<uword>(reg_source2->read_uword(i));

		// Check for divide by 0, in which case result is undefined (do nothing).
		if (val_source2 == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
		}
		// Else perform normal operation.
		else
		{
			udword resultQ = val_source1 / val_source2;
			udword resultR = val_source1 % val_source2;

			// Quotient.
			lo.write_udword(i / 2, resultQ);

			// Remainder.
			hi.write_udword(i / 2, resultR);
		}
	}
}

void CEeCoreInterpreter::PDIVW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI)(0,1) = SignExtend<sdword>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto val_source1 = static_cast<uword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<uword>(reg_source2->read_uword(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (val_source1 == VALUE_SWORD_MIN &&
			val_source2 == -1)
		{
			lo.write_udword(i / 2, static_cast<sdword>(VALUE_SWORD_MIN));
			hi.write_udword(i / 2, static_cast<sdword>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (val_source2 == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			udword resultQ = val_source1 / val_source2;
			udword resultR = val_source1 % val_source2;

			// Quotient.
			lo.write_udword(i / 2, resultQ);

			// Remainder.
			hi.write_udword(i / 2, resultR);
		}
	}
}

void CEeCoreInterpreter::PMULTH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sword>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()]; // "A"
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()]; // "B"
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		sword result = val_source1 * val_source2;

		if (i % 2 == 0)
			reg_dest->write_uword(i / 2, result); // Write to Rd for even indexes. A0xB0, A2xB2, A4xB4, A6xB6.

		if ((i / 2) % 2 == 0)
			lo.write_uword(((i / 2 > 0) ? i - 2 : i), result); // A0xB0, A1xB1, A4xB4, A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
		else
			hi.write_uword(((i / 2 > 1) ? i - 4 : i - 2), result); // A2xB2, A3xB3, A6xB6, A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
	}
}

void CEeCoreInterpreter::PMULTUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<udword>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto val_source1 = static_cast<uword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<uword>(reg_source2->read_uword(i));
		udword result = val_source1 * val_source2;

		lo.write_udword(i / 2, static_cast<udword>(static_cast<uword>(result & 0xFFFFFFFF)));
		hi.write_udword(i / 2, static_cast<udword>(static_cast<uword>(result >> 32)));
		reg_dest->write_udword(i / 2, result);
	}
}

void CEeCoreInterpreter::PMULTW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sdword>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto val_source1 = static_cast<sword>(reg_source1->read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		sdword result = val_source1 * val_source2;

		lo.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
		hi.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result >> 32)));
		reg_dest->write_udword(i / 2, result);
	}
}