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

	sword val_source1 = static_cast<sword>(reg_source1->read_uword(0));
	sword val_source2 = static_cast<sword>(reg_source2->read_uword(0));
	sdword val_lo = static_cast<sdword>(static_cast<sword>(lo.read_uword(0)));
	sdword val_hi = static_cast<sdword>(static_cast<sword>(hi.read_uword(0)));
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

	uword val_source1 = static_cast<uword>(reg_source1->read_uword(0));
	uword val_source2 = static_cast<uword>(reg_source2->read_uword(0));
	udword val_lo = static_cast<udword>(static_cast<uword>(lo.read_uword(0)));
	udword val_hi = static_cast<udword>(static_cast<uword>(hi.read_uword(0)));
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

	sword value[NUMBER_WORDS_IN_QWORD];

	auto madd = [](const uhword a0, const uhword b0, const uhword a1, const uhword b1) -> sword
	{
		sword sa0 = static_cast<sword>(static_cast<shword>(a0));
		sword sb0 = static_cast<sword>(static_cast<shword>(b0));
		sword sa1 = static_cast<sword>(static_cast<shword>(a1));
		sword sb1 = static_cast<sword>(static_cast<shword>(b1));
		return ((sa1 * sb1) + (sa0 * sb0));
	};

	value[0] = madd(
		reg_source1->read_uhword(0), reg_source2->read_uhword(0),
		reg_source1->read_uhword(1), reg_source2->read_uhword(1)
	);
	value[1] = madd(
		reg_source1->read_uhword(2), reg_source2->read_uhword(2),
		reg_source1->read_uhword(3), reg_source2->read_uhword(3)
	);
	value[2] = madd(
		reg_source1->read_uhword(4), reg_source2->read_uhword(4),
		reg_source1->read_uhword(5), reg_source2->read_uhword(5)
	);
	value[3] = madd(
		reg_source1->read_uhword(6), reg_source2->read_uhword(6),
		reg_source1->read_uhword(7), reg_source2->read_uhword(7)
	);

	reg_dest->write_uword(0, value[0]);
	reg_dest->write_uword(1, value[1]);
	reg_dest->write_uword(2, value[2]);
	reg_dest->write_uword(3, value[3]);

	lo.write_uword(0, value[0]);
	lo.write_uword(2, value[2]);

	hi.write_uword(0, value[1]);
	hi.write_uword(2, value[3]);
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

	sword value[NUMBER_WORDS_IN_QWORD];

	auto madd = [](const uhword a0, const uhword b0, const uhword a1, const uhword b1) -> sword
	{
		sword sa0 = static_cast<sword>(static_cast<shword>(a0));
		sword sb0 = static_cast<sword>(static_cast<shword>(b0));
		sword sa1 = static_cast<sword>(static_cast<shword>(a1));
		sword sb1 = static_cast<sword>(static_cast<shword>(b1));
		return ((sa1 * sb1) - (sa0 * sb0));
	};

	value[0] = madd(
		reg_source1->read_uhword(0), reg_source2->read_uhword(0),
		reg_source1->read_uhword(1), reg_source2->read_uhword(1)
	);
	value[1] = madd(
		reg_source1->read_uhword(2), reg_source2->read_uhword(2),
		reg_source1->read_uhword(3), reg_source2->read_uhword(3)
	);
	value[2] = madd(
		reg_source1->read_uhword(4), reg_source2->read_uhword(4),
		reg_source1->read_uhword(5), reg_source2->read_uhword(5)
	);
	value[3] = madd(
		reg_source1->read_uhword(6), reg_source2->read_uhword(6),
		reg_source1->read_uhword(7), reg_source2->read_uhword(7)
	);

	reg_dest->write_uword(0, value[0]);
	reg_dest->write_uword(1, value[1]);
	reg_dest->write_uword(2, value[2]);
	reg_dest->write_uword(3, value[3]);

	lo.write_uword(0, value[0]);
	lo.write_uword(2, value[2]);

	hi.write_uword(0, value[1]);
	hi.write_uword(2, value[3]);
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

	uword value[NUMBER_WORDS_IN_QWORD * 2];

	auto madd = [](const uhword a, const uhword b, const uword c) -> sword
	{
		shword sa = static_cast<shword>(a);
		shword sb = static_cast<shword>(b);
		sword sc = static_cast<sword>(c);
		return ((sa * sb) + sc);
	};

	value[0] = madd(reg_source1->read_uhword(0), reg_source2->read_uhword(0), lo.read_uword(0));
	value[1] = madd(reg_source1->read_uhword(1), reg_source2->read_uhword(1), lo.read_uword(1));
	value[2] = madd(reg_source1->read_uhword(2), reg_source2->read_uhword(2), hi.read_uword(0));
	value[3] = madd(reg_source1->read_uhword(3), reg_source2->read_uhword(3), hi.read_uword(1));
	value[4] = madd(reg_source1->read_uhword(4), reg_source2->read_uhword(4), lo.read_uword(2));
	value[5] = madd(reg_source1->read_uhword(5), reg_source2->read_uhword(5), lo.read_uword(3));
	value[6] = madd(reg_source1->read_uhword(6), reg_source2->read_uhword(6), hi.read_uword(2));
	value[7] = madd(reg_source1->read_uhword(7), reg_source2->read_uhword(7), hi.read_uword(3));

	lo.write_uword(0, value[0]);
	lo.write_uword(1, value[1]);
	lo.write_uword(2, value[4]);
	lo.write_uword(3, value[5]);

	hi.write_uword(0, value[2]);
	hi.write_uword(1, value[3]);
	hi.write_uword(2, value[6]);
	hi.write_uword(3, value[7]);

	reg_dest->write_uword(0, value[0]);
	reg_dest->write_uword(1, value[2]);
	reg_dest->write_uword(2, value[4]);
	reg_dest->write_uword(3, value[5]);
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

	auto madd = [](const uword a, const uword b, const uword c0, const uword c1) -> std::tuple<udword, sdword, sdword>
	{
		udword da = static_cast<udword>(a);
		udword db = static_cast<udword>(b);
		udword dc0 = static_cast<udword>(c0);
		udword dc1 = static_cast<udword>(c1);
		udword result = ((dc1 << 32) | dc0) + (da * db);
		return {
			result,
			static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)),
			static_cast<sdword>(static_cast<sword>(result >> 32))
		};
	};

	auto[value0, lo0, hi0] = madd(reg_source1->read_uword(0), reg_source2->read_uword(0), lo.read_uword(0), hi.read_uword(0));
	auto[value1, lo1, hi1] = madd(reg_source1->read_uword(2), reg_source2->read_uword(2), lo.read_uword(2), hi.read_uword(2));

	reg_dest->write_udword(0, value0);
	reg_dest->write_udword(1, value1);

	lo.write_udword(0, lo0);
	lo.write_udword(1, lo1);

	hi.write_udword(0, hi0);
	hi.write_udword(1, hi1);
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

	auto madd = [](const uword a, const uword b, const uword c0, const uword c1) -> std::tuple<sdword, sdword, sdword>
	{
		sdword sda = static_cast<sdword>(static_cast<sword>(a));
		sdword sdb = static_cast<sdword>(static_cast<sword>(b));
		sdword sdc0 = static_cast<sdword>(static_cast<sword>(c0));
		sdword sdc1 = static_cast<sdword>(static_cast<sword>(c1));
		sdword result = ((sdc1 << 32) | sdc0) + (sda * sdb);
		return {
			result,
			static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)),
			static_cast<sdword>(static_cast<sword>(result >> 32))
		};
	};

	auto[value0, lo0, hi0] = madd(reg_source1->read_uword(0), reg_source2->read_uword(0), lo.read_uword(0), hi.read_uword(0));
	auto[value1, lo1, hi1] = madd(reg_source1->read_uword(2), reg_source2->read_uword(2), lo.read_uword(2), hi.read_uword(2));

	reg_dest->write_udword(0, value0);
	reg_dest->write_udword(1, value1);

	lo.write_udword(0, lo0);
	lo.write_udword(1, lo1);

	hi.write_udword(0, hi0);
	hi.write_udword(1, hi1);
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

	uword value[NUMBER_WORDS_IN_QWORD * 2];

	auto madd = [](const uhword a, const uhword b, const uword c) -> sword
	{
		shword sa = static_cast<shword>(a);
		shword sb = static_cast<shword>(b);
		sword sc = static_cast<sword>(c);
		return (sc - (sa * sb));
	};

	value[0] = madd(reg_source1->read_uhword(0), reg_source2->read_uhword(0), lo.read_uword(0));
	value[1] = madd(reg_source1->read_uhword(1), reg_source2->read_uhword(1), lo.read_uword(1));
	value[2] = madd(reg_source1->read_uhword(2), reg_source2->read_uhword(2), hi.read_uword(0));
	value[3] = madd(reg_source1->read_uhword(3), reg_source2->read_uhword(3), hi.read_uword(1));
	value[4] = madd(reg_source1->read_uhword(4), reg_source2->read_uhword(4), lo.read_uword(2));
	value[5] = madd(reg_source1->read_uhword(5), reg_source2->read_uhword(5), lo.read_uword(3));
	value[6] = madd(reg_source1->read_uhword(6), reg_source2->read_uhword(6), hi.read_uword(2));
	value[7] = madd(reg_source1->read_uhword(7), reg_source2->read_uhword(7), hi.read_uword(3));

	lo.write_uword(0, value[0]);
	lo.write_uword(1, value[1]);
	lo.write_uword(2, value[4]);
	lo.write_uword(3, value[5]);

	hi.write_uword(0, value[2]);
	hi.write_uword(1, value[3]);
	hi.write_uword(2, value[6]);
	hi.write_uword(3, value[7]);

	reg_dest->write_uword(0, value[0]);
	reg_dest->write_uword(1, value[2]);
	reg_dest->write_uword(2, value[4]);
	reg_dest->write_uword(3, value[5]);
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

	auto madd = [](const uword a, const uword b, const uword c0, const uword c1) -> std::tuple<sdword, sdword, sdword>
	{
		sdword sda = static_cast<sdword>(static_cast<sword>(a));
		sdword sdb = static_cast<sdword>(static_cast<sword>(b));
		sdword sdc0 = static_cast<sdword>(static_cast<sword>(c0));
		sdword sdc1 = static_cast<sdword>(static_cast<sword>(c1));
		sdword result = ((sdc1 << 32) | sdc0) - (sda * sdb);
		return {
			result,
			static_cast<sdword>(static_cast<sword>(result & 0xFFFFFFFF)),
			static_cast<sdword>(static_cast<sword>(result >> 32))
		};
	};

	auto[value0, lo0, hi0] = madd(reg_source1->read_uword(0), reg_source2->read_uword(0), lo.read_uword(0), hi.read_uword(0));
	auto[value1, lo1, hi1] = madd(reg_source1->read_uword(2), reg_source2->read_uword(2), lo.read_uword(2), hi.read_uword(2));

	reg_dest->write_udword(0, value0);
	reg_dest->write_udword(1, value1);

	lo.write_udword(0, lo0);
	lo.write_udword(1, lo1);

	hi.write_udword(0, hi0);
	hi.write_udword(1, hi1);
}
