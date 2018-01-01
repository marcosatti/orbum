#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::MADD(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = (HI || LO) + SignExtend<sdword>(Rs[SW] * Rt[SW])
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	auto val_lo = static_cast<sdword>(static_cast<sword>(lo.read_uword(0)));
	auto val_hi = static_cast<sdword>(static_cast<sword>(hi.read_uword(0)));
	sdword result = (val_hi << 32 | val_lo) + (val_source1 * val_source2);

	lo.write_udword(0, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
	hi.write_udword(0, static_cast<sdword>(static_cast<sword>(result >> 32)));
	reg_dest->write_udword(0, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
}

void CEeCoreInterpreter::MADD1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADD(inst);
}

void CEeCoreInterpreter::MADDU(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = (HI || LO) + SignExtend<udword>(Rs[UW] * Rt[UW])
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	auto val_source1 = static_cast<uword>(reg_source1->read_uword(0));
	auto val_source2 = static_cast<uword>(reg_source2->read_uword(0));
	auto val_lo = static_cast<udword>(static_cast<uword>(lo.read_uword(0)));
	auto val_hi = static_cast<udword>(static_cast<uword>(hi.read_uword(0)));
	udword result = (val_hi << 32 | val_lo) + (val_source1 * val_source2);

	lo.write_udword(0, static_cast<udword>(static_cast<uword>(result & 0xFFFFFFFF)));
	hi.write_udword(0, static_cast<udword>(static_cast<uword>(result >> 32)));
	reg_dest->write_udword(0, static_cast<udword>(static_cast<uword>(result & 0xFFFFFFFF)));
}

void CEeCoreInterpreter::MADDU1(const EeCoreInstruction inst) const
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MADDU(inst);
}

void CEeCoreInterpreter::PHMADH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd)[i] = SignExtend<sword>(Rs[SH] * Rt[SH])[i] + SignExtend<sword>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		auto source1Val1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto source2Val1 = static_cast<shword>(reg_source2->read_uhword(i));
		auto source1Val2 = static_cast<shword>(reg_source1->read_uhword(i + 1));
		auto source2Val2 = static_cast<shword>(reg_source2->read_uhword(i + 1));
		sword result = (source1Val2 * source2Val2) + (source1Val1 * source2Val1);

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			lo.write_uword((i / 4) * 2, result);
		else
			hi.write_uword(((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		reg_dest->write_uword(i / 2, result);
	}
}

void CEeCoreInterpreter::PHMSBH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd)[i] = SignExtend<sword>(Rs[SH] * Rt[SH])[i] - SignExtend<sword>(Rs[SH] * Rt[SH])[i + 1]
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& lo = r.ee.core.r5900.lo;
	auto& hi = r.ee.core.r5900.hi;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i += 2)
	{
		auto source1Val1 = static_cast<shword>(reg_source1->read_uhword(i));
		auto source2Val1 = static_cast<shword>(reg_source2->read_uhword(i));
		auto source1Val2 = static_cast<shword>(reg_source1->read_uhword(i + 1));
		auto source2Val2 = static_cast<shword>(reg_source2->read_uhword(i + 1));
		sword result = (source1Val2 * source2Val2) - (source1Val1 * source2Val1);

		// Store in LO on i % 4 == 0 (every second loop), else store in HI, at word indexes 0 and 2.
		if (i % 4 == 0)
			lo.write_uword((i / 4) * 2, result);
		else
			hi.write_uword(((i - 2) / 4) * 2, result);

		// Set Rd (always done on each loop).
		reg_dest->write_uword(i / 2, result);
	}
}

void CEeCoreInterpreter::PMADDH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sword>(Rs[SH] * Rt[SH] + (HI,LO)[i]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
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

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // A0xB0 + C0, A1xB1 + C1, A4xB4 + C4, A5xB5 + C5. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + static_cast<sword>(lo.read_uword(index)); 
			lo.write_uword(index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // A2xB2 + C2, A3xB3 + C3, A6xB6 + C6, A7xB7 + C7. Array ternary operator is to select the correct index from 0 -> 3.
			result = result + static_cast<sword>(hi.read_uword(index));
			hi.write_uword(index, result);
		}
			
		if (i % 2 == 0)
			reg_dest->write_uword(i / 2, result); // Write to Rd for even indexes. A0xB0 + C0, A2xB2 + C2, A4xB4 + C4, A6xB6 + C6.
	}
}

void CEeCoreInterpreter::PMADDUW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<udword>(Rs[UW] * Rt[UW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 218).
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
		auto val_lo = static_cast<udword>(static_cast<uword>(lo.read_uword(i)));
		auto val_hi = static_cast<udword>(static_cast<uword>(hi.read_uword(i)));
		udword result = (val_hi << 32 | val_lo) + (val_source1 * val_source2);

		lo.write_udword(i / 2, static_cast<udword>(static_cast<uword>(result & 0xFFFFFFFF)));
		hi.write_udword(i / 2, static_cast<udword>(static_cast<uword>(result >> 32)));
		reg_dest->write_udword(i / 2, result);
	}
}

void CEeCoreInterpreter::PMADDW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sdword>(Rs[SW] * Rt[SW] + (HI || LO)[i]) (varying indexes - see EE Core Instruction Manual page 220).
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
		auto val_lo = static_cast<sdword>(static_cast<sword>(lo.read_uword(i)));
		auto val_hi = static_cast<sdword>(static_cast<sword>(hi.read_uword(i)));
		sdword result = (val_hi << 32 | val_lo) + (val_source1 * val_source2);

		lo.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
		hi.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result >> 32)));
		reg_dest->write_udword(i / 2, result);
	}
}

void CEeCoreInterpreter::PMSUBH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sword>((HI,LO)[i] - Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 216).
	// (HI,LO)[i] = "C" in comments written below.
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

		if ((i / 2) % 2 == 0)
		{
			auto index = ((i / 2 > 0) ? i - 2 : i); // C0 - A0xB0, C1 - A1xB1, C4 - A4xB4, C5 - A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
			result = static_cast<sword>(lo.read_uword(index)) - result;
			lo.write_uword(index, result);
		}
		else
		{
			auto index = ((i / 2 > 1) ? i - 4 : i - 2); // C2 - A2xB2, C3 - A3xB3, C6 - A6xB6, C7 - A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
			result = static_cast<sword>(hi.read_uword(index)) - result;
			hi.write_uword(index, result);
		}

		if (i % 2 == 0)
			reg_dest->write_uword(i / 2, result); // Write to Rd for even indexes. C0 - A0xB0, C2 - A2xB2, C4 - A4xB4, C6 - A6xB6.
	}
}

void CEeCoreInterpreter::PMSUBW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (LO, HI, Rd) = SignExtend<sdword>((HI || LO)[i] - Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 220).
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
		auto val_lo = static_cast<sdword>(static_cast<sword>(lo.read_uword(i)));
		auto val_hi = static_cast<sdword>(static_cast<sword>(hi.read_uword(i)));
		sdword result = (val_hi << 32 | val_lo) - (val_source1 * val_source2);

		lo.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)));
		hi.write_udword(i / 2, static_cast<sdword>(static_cast<sword>(result >> 32)));
		reg_dest->write_udword(i / 2, result);
	}
}
