#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::AND(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest->write_udword(0, reg_source1->read_udword(0) & reg_source2->read_udword(0));
}

void CEeCoreInterpreter::ANDI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	udword imm = static_cast<udword>(inst.u_imm());

	reg_dest->write_udword(0, reg_source1->read_udword(0) & imm);
}

void CEeCoreInterpreter::NOR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest->write_udword(0, ~(reg_source1->read_udword(0) | reg_source2->read_udword(0)));
}

void CEeCoreInterpreter::OR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest->write_udword(0, reg_source1->read_udword(0) | reg_source2->read_udword(0));
}

void CEeCoreInterpreter::ORI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	sdword imm = static_cast<sdword>(inst.u_imm());

	reg_dest->write_udword(0, reg_source1->read_udword(0) | imm);
}

void CEeCoreInterpreter::XOR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest->write_udword(0, reg_source1->read_udword(0) ^ reg_source2->read_udword(0));
}

void CEeCoreInterpreter::XORI(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt XOR Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	udword imm = static_cast<udword>(inst.u_imm());

	reg_dest->write_udword(0, reg_source1->read_udword(0) ^ imm);
}

void CEeCoreInterpreter::PAND(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		reg_dest->write_udword(i, reg_source1->read_udword(i) & reg_source2->read_udword(i));
	}
}

void CEeCoreInterpreter::PNOR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		reg_dest->write_udword(i, ~(reg_source1->read_udword(i) | reg_source2->read_udword(i)));
	}
}

void CEeCoreInterpreter::POR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		reg_dest->write_udword(i, reg_source1->read_udword(i) | reg_source2->read_udword(i));
	}
}

void CEeCoreInterpreter::PXOR(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		reg_dest->write_udword(i, reg_source1->read_udword(i) ^ reg_source2->read_udword(i));
	}
}
