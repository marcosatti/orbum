#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::AND(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest.write_udword(0, reg_source1.read_udword(0) & reg_source2.read_udword(0));
}

void CEeCoreInterpreter::ANDI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	udword imm = static_cast<udword>(inst.u_imm());

	reg_dest.write_udword(0, reg_source1.read_udword(0) & imm);
}

void CEeCoreInterpreter::NOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest.write_udword(0, ~(reg_source1.read_udword(0) | reg_source2.read_udword(0)));
}

void CEeCoreInterpreter::OR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest.write_udword(0, reg_source1.read_udword(0) | reg_source2.read_udword(0));
}

void CEeCoreInterpreter::ORI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	sdword imm = static_cast<sdword>(inst.u_imm());

	reg_dest.write_udword(0, reg_source1.read_udword(0) | imm);
}

void CEeCoreInterpreter::XOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	reg_dest.write_udword(0, reg_source1.read_udword(0) ^ reg_source2.read_udword(0));
}

void CEeCoreInterpreter::XORI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt XOR Extended<udword>(Imm).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	udword imm = static_cast<udword>(inst.u_imm());

	reg_dest.write_udword(0, reg_source1.read_udword(0) ^ imm);
}

void CEeCoreInterpreter::PAND(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	udword value0 = reg_source1.read_udword(0) & reg_source2.read_udword(0);
	udword value1 = reg_source1.read_udword(1) & reg_source2.read_udword(1);

	reg_dest.write_udword(0, value0);
	reg_dest.write_udword(1, value1);
}

void CEeCoreInterpreter::PNOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	udword value0 = ~(reg_source1.read_udword(0) | reg_source2.read_udword(0));
	udword value1 = ~(reg_source1.read_udword(1) | reg_source2.read_udword(1));

	reg_dest.write_udword(0, value0);
	reg_dest.write_udword(1, value1);
}

void CEeCoreInterpreter::POR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	udword value0 = reg_source1.read_udword(0) | reg_source2.read_udword(0);
	udword value1 = reg_source1.read_udword(1) | reg_source2.read_udword(1);

	reg_dest.write_udword(0, value0);
	reg_dest.write_udword(1, value1);
}

void CEeCoreInterpreter::PXOR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Rt XOR Rs.
	// No Exceptions generated.
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];

	udword value0 = reg_source1.read_udword(0) ^ reg_source2.read_udword(0);
	udword value1 = reg_source1.read_udword(1) ^ reg_source2.read_udword(1);

	reg_dest.write_udword(0, value0);
	reg_dest.write_udword(1, value1);
}
