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
	auto& reg_source1 = r.ee.core.r5900.hi;
	auto& reg_source2 = r.ee.core.r5900.lo;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	sword HIIndex[] = { 2, -1, 3, -1, 6, -1, 7, -1 };
	sword LOIndex[] = { 0, -1, 1, -1, 4, -1, 5, -1 };
	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			reg_dest->write_uhword(HIIndex[i], reg_source1.read_uhword(i));
		if (LOIndex[i] != -1)
			reg_dest->write_uhword(LOIndex[i], reg_source2.read_uhword(i));
	}
}

void CEeCoreInterpreter::PMFHL_LW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;
	auto& reg_source2 = r.ee.core.r5900.lo;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	sword HIIndex[] = { 1, -1, 3, -1 };
	sword LOIndex[] = { 0, -1, 2, -1 };
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			reg_dest->write_uword(HIIndex[i], reg_source1.read_uword(i));
		if (LOIndex[i] != -1)
			reg_dest->write_uword(LOIndex[i], reg_source2.read_uword(i));
	}
}

void CEeCoreInterpreter::PMFHL_SH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;
	auto& reg_source2 = r.ee.core.r5900.lo;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	sword HIIndex[] = { 2, 3, 6, 7 };
	sword LOIndex[] = { 0, 1, 4, 5 };
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto val_source1 = static_cast<sword>(reg_source1.read_uword(i));
		auto val_source2 = static_cast<sword>(reg_source2.read_uword(i));

		if (HIIndex[i] != -1)
			reg_dest->write_uhword(HIIndex[i], saturating_word_to_hword(val_source1));
		if (LOIndex[i] != -1)
			reg_dest->write_uhword(LOIndex[i], saturating_word_to_hword(val_source2));
	}
}

void CEeCoreInterpreter::PMFHL_SLW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;
	auto& reg_source2 = r.ee.core.r5900.lo;

	// Indexes 0 and 2 get copied.
	sdword tempValue;
	sword result;

	tempValue = static_cast<sdword>((static_cast<udword>(reg_source1.read_uword(0)) << 32) | static_cast<udword>(reg_source2.read_uword(0)));
	result = saturating_dword_to_word(tempValue);
	reg_dest->write_udword(0, result);

	tempValue = static_cast<sdword>((static_cast<udword>(reg_source1.read_uword(2)) << 32) | static_cast<udword>(reg_source2.read_uword(2)));
	result = saturating_dword_to_word(tempValue);
	reg_dest->write_udword(1, result);
}

void CEeCoreInterpreter::PMFHL_UW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = (HI, LO). No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.hi;
	auto& reg_source2 = r.ee.core.r5900.lo;

	// Use mappings to implement this instruction, -1 means not used, and >0 number means the index within Rd.
	sword HIIndex[] = { -1, 1, -1, 3 };
	sword LOIndex[] = { -1, 0, -1, 2 };
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (HIIndex[i] != -1)
			reg_dest->write_uword(HIIndex[i], reg_source1.read_uword(i));
		if (LOIndex[i] != -1)
			reg_dest->write_uword(LOIndex[i], reg_source2.read_uword(i));
	}
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
	auto& reg_dest1 = r.ee.core.r5900.hi;
	auto& reg_dest2 = r.ee.core.r5900.lo;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		if (i % 2 == 0)
			reg_dest2.write_uword(i, reg_source1->read_uword(i));
		else
			reg_dest1.write_uword(i - 1, reg_source1->read_uword(i));
	}
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

