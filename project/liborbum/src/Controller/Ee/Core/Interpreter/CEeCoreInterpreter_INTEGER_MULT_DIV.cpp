#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::DIV(const EeCoreInstruction inst)
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

void CEeCoreInterpreter::DIV1(const EeCoreInstruction inst)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIV(inst);
}

void CEeCoreInterpreter::DIVU(const EeCoreInstruction inst)
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

void CEeCoreInterpreter::DIVU1(const EeCoreInstruction inst)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIVU(inst);
}

void CEeCoreInterpreter::MULT(const EeCoreInstruction inst)
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

void CEeCoreInterpreter::MULT1(const EeCoreInstruction inst)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULT(inst);
}

void CEeCoreInterpreter::MULTU(const EeCoreInstruction inst)
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

void CEeCoreInterpreter::MULTU1(const EeCoreInstruction inst)
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULTU(inst);
}

void CEeCoreInterpreter::PDIVBW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI) = SignExtend<sdword>(Rs[SW] / Rt[SH,0]) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    shword divisor = static_cast<shword>(reg_source2->read_uhword(0));

    auto div = [divisor](const uword a) -> std::tuple<uword, uword>
    {
        sword sa = static_cast<sword>(a);

        // Check for VALUE_S32_MIN / -1 (special condition).
        if (sa == VALUE_SWORD_MIN && divisor == -1)
        {
            return {
                static_cast<uword>(VALUE_SWORD_MIN),
                static_cast<uword>(0)
            };
        }
        // Check for divide by 0, in which case result is undefined (do nothing).
        else if (divisor == 0)
        {
            // TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
            return {
                static_cast<uword>(0),
                static_cast<uword>(0)
            };
        }
        // Else perform normal operation.
        else
        {
            return {
                static_cast<uword>(sa / divisor),
                static_cast<uword>(sa % divisor)
            };
        }
    };

    auto[q0, r0] = div(reg_source1->read_uword(0));
    auto[q1, r1] = div(reg_source1->read_uword(1));
    auto[q2, r2] = div(reg_source1->read_uword(2));
    auto[q3, r3] = div(reg_source1->read_uword(3));

    lo.write_uword(0, q0);
    lo.write_uword(1, q1);
    lo.write_uword(2, q2);
    lo.write_uword(3, q3);

    hi.write_uword(0, r0);
    hi.write_uword(1, r1);
    hi.write_uword(2, r2);
    hi.write_uword(3, r3);
}

void CEeCoreInterpreter::PDIVUW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI)(0,1) = SignExtend<udword>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    auto div = [](const uword a, const uword b) -> std::tuple<udword, udword>
    {
        // Check for divide by 0, in which case result is undefined (do nothing).
        if (b == 0)
        {
            // TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
            return {
                static_cast<udword>(0),
                static_cast<udword>(0)
            };
        }
        // Else perform normal operation.
        else
        {
            return {
                static_cast<udword>(static_cast<sdword>(static_cast<sword>(a / b))),
                static_cast<udword>(static_cast<sdword>(static_cast<sword>(a % b)))
            };
        }
    };

    auto[q0, r0] = div(reg_source1->read_uword(0), reg_source2->read_uword(0));
    auto[q1, r1] = div(reg_source1->read_uword(2), reg_source2->read_uword(2));

    lo.write_udword(0, q0);
    lo.write_udword(1, q1);

    hi.write_udword(0, r0);
    hi.write_udword(1, r1);
}

void CEeCoreInterpreter::PDIVW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI)(0,1) = SignExtend<sdword>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    auto div = [](const uword a, const uword b) -> std::tuple<udword, udword>
    {
        sword sa = static_cast<sword>(a);
        sword sb = static_cast<sword>(b);

        if (a == VALUE_SWORD_MIN && b == -1)
        {
            return {
                static_cast<udword>(static_cast<sdword>(VALUE_SWORD_MIN)),
                static_cast<udword>(static_cast<sdword>(0))
            };
        }
        // Check for divide by 0, in which case result is undefined (do nothing).
        if (b == 0)
        {
            // TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
            return {
                static_cast<udword>(0),
                static_cast<udword>(0)
            };
        }
        // Else perform normal operation.
        else
        {
            return {
                static_cast<udword>(static_cast<sdword>(sa / sb)),
                static_cast<udword>(static_cast<sdword>(sa % sb))
            };
        }
    };

    auto[q0, r0] = div(reg_source1->read_uword(0), reg_source2->read_uword(0));
    auto[q1, r1] = div(reg_source1->read_uword(2), reg_source2->read_uword(2));

    lo.write_udword(0, q0);
    lo.write_udword(1, q1);

    hi.write_udword(0, r0);
    hi.write_udword(1, r1);
}

void CEeCoreInterpreter::PMULTH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sword>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()]; // "A"
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()]; // "B"
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    uword value[NUMBER_HWORDS_IN_QWORD];

    auto mult = [](const uhword a, const uhword b) -> uword
    {
        sword sa = static_cast<sword>(static_cast<shword>(a));
        sword sb = static_cast<sword>(static_cast<shword>(b));
        return static_cast<uword>(sa * sb);
    };

    value[0] = mult(reg_source1->read_uhword(0), reg_source2->read_uhword(0));
    value[1] = mult(reg_source1->read_uhword(1), reg_source2->read_uhword(1));
    value[2] = mult(reg_source1->read_uhword(2), reg_source2->read_uhword(2));
    value[3] = mult(reg_source1->read_uhword(3), reg_source2->read_uhword(3));
    value[4] = mult(reg_source1->read_uhword(4), reg_source2->read_uhword(4));
    value[5] = mult(reg_source1->read_uhword(5), reg_source2->read_uhword(5));
    value[6] = mult(reg_source1->read_uhword(6), reg_source2->read_uhword(6));
    value[7] = mult(reg_source1->read_uhword(7), reg_source2->read_uhword(7));

    reg_dest->write_uword(0, value[0]);
    reg_dest->write_uword(1, value[2]);
    reg_dest->write_uword(2, value[4]);
    reg_dest->write_uword(3, value[6]);

    lo.write_uword(0, value[0]);
    lo.write_uword(1, value[1]);
    lo.write_uword(2, value[4]);
    lo.write_uword(3, value[5]);

    hi.write_uword(0, value[2]);
    hi.write_uword(1, value[3]);
    hi.write_uword(2, value[6]);
    hi.write_uword(3, value[7]);
}

void CEeCoreInterpreter::PMULTUW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<udword>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    auto mult = [](const uword a, const uword b) -> std::tuple<udword, udword, udword>
    {
        udword da = static_cast<udword>(a);
        udword db = static_cast<udword>(b);
        udword result = da * db;
        return {
            result,
            static_cast<udword>(static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF))),
            static_cast<udword>(static_cast<sdword>(static_cast<sword>(result >> 32)))
        };
    };

    auto[value0, lo0, hi0] = mult(reg_source1->read_uword(0), reg_source1->read_uword(0));
    auto[value1, lo1, hi1] = mult(reg_source1->read_uword(2), reg_source1->read_uword(2));

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);
    
    lo.write_udword(0, lo0);
    lo.write_udword(1, lo1);

    hi.write_udword(0, hi0);
    hi.write_udword(1, hi1);
}

void CEeCoreInterpreter::PMULTW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sdword>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

    auto mult = [](const uword a, const uword b) -> std::tuple<udword, udword, udword>
    {
        sdword sda = static_cast<sdword>(static_cast<sword>(a));
        sdword sdb = static_cast<sdword>(static_cast<sword>(b));
        sdword result = sda * sdb;
        return {
            static_cast<udword>(result),
            static_cast<udword>(static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF))),
            static_cast<udword>(static_cast<sdword>(static_cast<sword>(result >> 32)))
        };
    };

    auto[value0, lo0, hi0] = mult(reg_source1->read_uword(0), reg_source1->read_uword(0));
    auto[value1, lo1, hi1] = mult(reg_source1->read_uword(2), reg_source1->read_uword(2));

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);

    lo.write_udword(0, lo0);
    lo.write_udword(1, lo1);

    hi.write_udword(0, hi0);
    hi.write_udword(1, hi1);
}