#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::MFHI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = HI. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;

	reg_dest->write_udword(0, reg_source1.read_udword(0));
}

void CEeCoreInterpreter::MFLO(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = LO. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.lo;

	reg_dest->write_udword(0, reg_source1.read_udword(0));
}

void CEeCoreInterpreter::MOVN(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs, if Rt =/= 0. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	if (reg_source2->read_udword(0) != 0)
		reg_dest->write_udword(0, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::MOVZ(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rs, if Rt == 0. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	if (reg_source2->read_udword(0) == 0)
		reg_dest->write_udword(0, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::MTHI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// HI = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_dest = r.ee.core.r5900.hi;

	reg_dest.write_udword(0, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::MTLO(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// LO = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_dest = r.ee.core.r5900.lo;

	reg_dest.write_udword(0, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::MFHI1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = HI1. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;

	reg_dest->write_udword(0, reg_source1.read_udword(1));
}

void CEeCoreInterpreter::MFLO1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = LO1. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.lo;

	reg_dest->write_udword(0, reg_source1.read_udword(1));
}

void CEeCoreInterpreter::MTHI1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// HI1 = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_dest = r.ee.core.r5900.hi;

	reg_dest.write_udword(1, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::MTLO1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// LO1 = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_dest = r.ee.core.r5900.lo;

	reg_dest.write_udword(1, reg_source1->read_udword(0));
}

void CEeCoreInterpreter::PMFHI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = HI. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;

	reg_dest->write_udword(0, reg_source1.read_udword(0));
	reg_dest->write_udword(1, reg_source1.read_udword(1));
}

void CEeCoreInterpreter::PMFHL(const EeCoreInstruction inst) const
{
	switch (inst.shamt())
	{
	case 0x0:
	{
		PMFHL_LW(inst);
		break;
	}
	case 0x1:
	{
		PMFHL_UW(inst);
		break;
	}
	case 0x2:
	{
		PMFHL_SLW(inst);
		break;
	}
	case 0x3:
	{
		PMFHL_LH(inst);
		break;
	}
	case 0x4:
	{
		PMFHL_SH(inst);
		break;
	}
	}
}

void CEeCoreInterpreter::PMFHL_LH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    uhword value[NUMBER_HWORDS_IN_QWORD];

    value[0] = lo.read_uhword(0);
    value[1] = lo.read_uhword(2);
    value[2] = hi.read_uhword(0);
    value[3] = hi.read_uhword(2);
    value[4] = lo.read_uhword(4);
    value[5] = lo.read_uhword(6);
    value[6] = hi.read_uhword(4);
    value[7] = hi.read_uhword(6);

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest->write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PMFHL_LW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    uword value[NUMBER_WORDS_IN_QWORD];

    value[0] = lo.read_uword(0);
    value[1] = hi.read_uword(0);
    value[2] = lo.read_uword(2);
    value[3] = hi.read_uword(2);

    for (int i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
        reg_dest->write_uword(i, value[i]);
}

void CEeCoreInterpreter::PMFHL_SH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    uhword value[NUMBER_HWORDS_IN_QWORD];

    auto saturate = [](const uword value) -> uhword
    {
        sword svalue = static_cast<sword>(value);
        shword shvalue = saturate_word_to_hword(svalue);
        return static_cast<uhword>(shvalue);
    };

    value[0] = saturate(lo.read_uword(0));
    value[1] = saturate(lo.read_uword(1));
    value[2] = saturate(hi.read_uword(0));
    value[3] = saturate(hi.read_uword(1));
    value[4] = saturate(lo.read_uword(2));
    value[5] = saturate(lo.read_uword(3));
    value[6] = saturate(hi.read_uword(2));
    value[7] = saturate(hi.read_uword(3));

    for (int i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
        reg_dest->write_uhword(i, value[i]);
}

void CEeCoreInterpreter::PMFHL_SLW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    auto clamp = [] (const uword lo, const uword hi) -> udword
    {
        udword dhi = static_cast<udword>(hi) << 32;
        udword dlo = static_cast<udword>(lo);
        sdword dvalue = static_cast<sdword>(saturate_dword_to_word(static_cast<sdword>(hi | lo)));
        return static_cast<udword>(dvalue);
    };

    udword value0 = clamp(lo.read_uword(0), hi.read_uword(0));
    udword value1 = clamp(lo.read_uword(2), hi.read_uword(2));

    reg_dest->write_udword(0, value0);
    reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PMFHL_UW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    uword value0 = lo.read_uword(1);
    uword value1 = hi.read_uword(1);
    uword value2 = lo.read_uword(3);
    uword value3 = hi.read_uword(3);

    reg_dest->write_uword(0, value0);
    reg_dest->write_uword(1, value1);
    reg_dest->write_uword(2, value2);
    reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PMFLO(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = LO. No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source2 = r.ee.core.r5900.lo;

	reg_dest->write_udword(0, reg_source2.read_udword(0));
	reg_dest->write_udword(1, reg_source2.read_udword(1));
}

void CEeCoreInterpreter::PMTHI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// HI = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.hi;

	reg_dest.write_udword(0, reg_source1->read_udword(0));
	reg_dest.write_udword(1, reg_source1->read_udword(1));
}

void CEeCoreInterpreter::PMTHL_LW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// (HI, LO) = Rs. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& hi = r.ee.core.r5900.hi;
	auto& lo = r.ee.core.r5900.lo;

    uword value0 = reg_source1->read_uword(0);
    uword value1 = reg_source1->read_uword(1);
    uword value2 = reg_source1->read_uword(2);
    uword value3 = reg_source1->read_uword(3);

    lo.write_uword(0, value0);
    lo.write_uword(2, value2);

    hi.write_uword(0, value1);
    hi.write_uword(2, value3);
}

void CEeCoreInterpreter::PMTLO(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// LO = Rd. No exceptions.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.lo;

	reg_dest.write_udword(0, reg_source1->read_udword(0));
	reg_dest.write_udword(1, reg_source1->read_udword(1));
}

void CEeCoreInterpreter::MFC1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rt = COP1_FPR[Fs]. Exception on FPU unusable.
	if (handle_cop1_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs

	reg_dest->write_uword(0, reg_source1.read_uword());

	// Sign extend
	if (reg_source1.read_float() < 0.0)
	{
		reg_dest->write_uword(1, VALUE_UWORD_MAX);
		reg_dest->write_uword(2, VALUE_UWORD_MAX);
		reg_dest->write_uword(3, VALUE_UWORD_MAX);
	}
	else
	{
		reg_dest->write_uword(1, 0);
		reg_dest->write_uword(2, 0);
		reg_dest->write_uword(3, 0);
	}
}

void CEeCoreInterpreter::MOV_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = Fs. Exception on FPU unusable.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd

	reg_dest.write_float(reg_source1.read_float());
}

void CEeCoreInterpreter::MTC1(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// COP1_FPR[Fs] = Rt. Exception on FPU unusable.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.fpu.fpr[inst.rd()]; // Fs

	reg_dest.write_uword(reg_source1->read_uword(0));
}

