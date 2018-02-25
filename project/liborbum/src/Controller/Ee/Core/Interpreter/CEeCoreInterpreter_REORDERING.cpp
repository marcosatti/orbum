#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PCPYH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source1->read_uhword(0);
	uhword value4 = reg_source1->read_uhword(4);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value0);
	reg_dest->write_uhword(2, value0);
	reg_dest->write_uhword(3, value0);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value4);
	reg_dest->write_uhword(6, value4);
	reg_dest->write_uhword(7, value4);
}

void CEeCoreInterpreter::PCPYLD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	udword value0 = reg_source2->read_udword(0);
	udword value1 = reg_source1->read_udword(0);

	reg_dest->write_udword(0, value0);
	reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PCPYUD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_DW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	udword value0 = reg_source1->read_udword(1);
	udword value1 = reg_source2->read_udword(1);

	reg_dest->write_udword(0, value0);
	reg_dest->write_udword(1, value1);
}

void CEeCoreInterpreter::PEXCH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source1->read_uhword(0);
	uhword value1 = reg_source1->read_uhword(2);
	uhword value2 = reg_source1->read_uhword(1);
	uhword value3 = reg_source1->read_uhword(3);
	uhword value4 = reg_source1->read_uhword(4);
	uhword value5 = reg_source1->read_uhword(6);
	uhword value6 = reg_source1->read_uhword(5);
	uhword value7 = reg_source1->read_uhword(7);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PEXCW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source1->read_uword(0);
	uword value1 = reg_source1->read_uword(2);
	uword value2 = reg_source1->read_uword(1);
	uword value3 = reg_source1->read_uword(3);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PEXEH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source1->read_uhword(2);
	uhword value1 = reg_source1->read_uhword(1);
	uhword value2 = reg_source1->read_uhword(0);
	uhword value3 = reg_source1->read_uhword(3);
	uhword value4 = reg_source1->read_uhword(6);
	uhword value5 = reg_source1->read_uhword(5);
	uhword value6 = reg_source1->read_uhword(4);
	uhword value7 = reg_source1->read_uhword(7);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PEXEW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source1->read_uword(2);
	uword value1 = reg_source1->read_uword(1);
	uword value2 = reg_source1->read_uword(0);
	uword value3 = reg_source1->read_uword(3);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PEXTLB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	ubyte value0 = reg_source2->read_ubyte(0);
	ubyte value1 = reg_source1->read_ubyte(0);
	ubyte value2 = reg_source2->read_ubyte(1);
	ubyte value3 = reg_source1->read_ubyte(1);
	ubyte value4 = reg_source2->read_ubyte(2);
	ubyte value5 = reg_source1->read_ubyte(2);
	ubyte value6 = reg_source2->read_ubyte(3);
	ubyte value7 = reg_source1->read_ubyte(3);
	ubyte value8 = reg_source2->read_ubyte(4);
	ubyte value9 = reg_source1->read_ubyte(4);
	ubyte value10 = reg_source2->read_ubyte(5);
	ubyte value11 = reg_source1->read_ubyte(5);
	ubyte value12 = reg_source2->read_ubyte(6);
	ubyte value13 = reg_source1->read_ubyte(6);
	ubyte value14 = reg_source2->read_ubyte(7);
	ubyte value15 = reg_source1->read_ubyte(7);

	reg_dest->write_ubyte(0, value0);
	reg_dest->write_ubyte(1, value1);
	reg_dest->write_ubyte(2, value2);
	reg_dest->write_ubyte(3, value3);
	reg_dest->write_ubyte(4, value4);
	reg_dest->write_ubyte(5, value5);
	reg_dest->write_ubyte(6, value6);
	reg_dest->write_ubyte(7, value7);
	reg_dest->write_ubyte(8, value8);
	reg_dest->write_ubyte(9, value9);
	reg_dest->write_ubyte(10, value10);
	reg_dest->write_ubyte(11, value11);
	reg_dest->write_ubyte(12, value12);
	reg_dest->write_ubyte(13, value13);
	reg_dest->write_ubyte(14, value14);
	reg_dest->write_ubyte(15, value15);
}

void CEeCoreInterpreter::PEXTLH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source2->read_uhword(0);
	uhword value1 = reg_source1->read_uhword(0);
	uhword value2 = reg_source2->read_uhword(1);
	uhword value3 = reg_source1->read_uhword(1);
	uhword value4 = reg_source2->read_uhword(2);
	uhword value5 = reg_source1->read_uhword(2);
	uhword value6 = reg_source2->read_uhword(3);
	uhword value7 = reg_source1->read_uhword(3);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PEXTLW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source2->read_uword(0);
	uword value1 = reg_source1->read_uword(0);
	uword value2 = reg_source2->read_uword(1);
	uword value3 = reg_source1->read_uword(1);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PEXTUB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	ubyte value0 = reg_source2->read_ubyte(8);
	ubyte value1 = reg_source1->read_ubyte(8);
	ubyte value2 = reg_source2->read_ubyte(9);
	ubyte value3 = reg_source1->read_ubyte(9);
	ubyte value4 = reg_source2->read_ubyte(10);
	ubyte value5 = reg_source1->read_ubyte(10);
	ubyte value6 = reg_source2->read_ubyte(11);
	ubyte value7 = reg_source1->read_ubyte(11);
	ubyte value8 = reg_source2->read_ubyte(12);
	ubyte value9 = reg_source1->read_ubyte(12);
	ubyte value10 = reg_source2->read_ubyte(13);
	ubyte value11 = reg_source1->read_ubyte(13);
	ubyte value12 = reg_source2->read_ubyte(14);
	ubyte value13 = reg_source1->read_ubyte(14);
	ubyte value14 = reg_source2->read_ubyte(15);
	ubyte value15 = reg_source1->read_ubyte(15);

	reg_dest->write_ubyte(0, value0);
	reg_dest->write_ubyte(1, value1);
	reg_dest->write_ubyte(2, value2);
	reg_dest->write_ubyte(3, value3);
	reg_dest->write_ubyte(4, value4);
	reg_dest->write_ubyte(5, value5);
	reg_dest->write_ubyte(6, value6);
	reg_dest->write_ubyte(7, value7);
	reg_dest->write_ubyte(8, value8);
	reg_dest->write_ubyte(9, value9);
	reg_dest->write_ubyte(10, value10);
	reg_dest->write_ubyte(11, value11);
	reg_dest->write_ubyte(12, value12);
	reg_dest->write_ubyte(13, value13);
	reg_dest->write_ubyte(14, value14);
	reg_dest->write_ubyte(15, value15);
}

void CEeCoreInterpreter::PEXTUH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source2->read_uhword(4);
	uhword value1 = reg_source1->read_uhword(4);
	uhword value2 = reg_source2->read_uhword(5);
	uhword value3 = reg_source1->read_uhword(5);
	uhword value4 = reg_source2->read_uhword(6);
	uhword value5 = reg_source1->read_uhword(6);
	uhword value6 = reg_source2->read_uhword(7);
	uhword value7 = reg_source1->read_uhword(7);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PEXTUW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source2->read_uword(2);
	uword value1 = reg_source1->read_uword(2);
	uword value2 = reg_source2->read_uword(3);
	uword value3 = reg_source1->read_uword(3);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PINTEH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source2->read_uhword(0);
	uhword value1 = reg_source1->read_uhword(0);
	uhword value2 = reg_source2->read_uhword(2);
	uhword value3 = reg_source1->read_uhword(2);
	uhword value4 = reg_source2->read_uhword(4);
	uhword value5 = reg_source1->read_uhword(4);
	uhword value6 = reg_source2->read_uhword(6);
	uhword value7 = reg_source1->read_uhword(6);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PINTH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source2->read_uhword(0);
	uhword value1 = reg_source1->read_uhword(4);
	uhword value2 = reg_source2->read_uhword(1);
	uhword value3 = reg_source1->read_uhword(5);
	uhword value4 = reg_source2->read_uhword(2);
	uhword value5 = reg_source1->read_uhword(6);
	uhword value6 = reg_source2->read_uhword(3);
	uhword value7 = reg_source1->read_uhword(7);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PPACB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_B(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	ubyte value0 = reg_source2->read_ubyte(0);
	ubyte value1 = reg_source2->read_ubyte(2);
	ubyte value2 = reg_source2->read_ubyte(4);
	ubyte value3 = reg_source2->read_ubyte(6);
	ubyte value4 = reg_source2->read_ubyte(8);
	ubyte value5 = reg_source2->read_ubyte(10);
	ubyte value6 = reg_source2->read_ubyte(12);
	ubyte value7 = reg_source2->read_ubyte(14);
	ubyte value8 = reg_source1->read_ubyte(0);
	ubyte value9 = reg_source1->read_ubyte(2);
	ubyte value10 = reg_source1->read_ubyte(4);
	ubyte value11 = reg_source1->read_ubyte(6);
	ubyte value12 = reg_source1->read_ubyte(8);
	ubyte value13 = reg_source1->read_ubyte(10);
	ubyte value14 = reg_source1->read_ubyte(12);
	ubyte value15 = reg_source1->read_ubyte(14);

	reg_dest->write_ubyte(0, value0);
	reg_dest->write_ubyte(1, value1);
	reg_dest->write_ubyte(2, value2);
	reg_dest->write_ubyte(3, value3);
	reg_dest->write_ubyte(4, value4);
	reg_dest->write_ubyte(5, value5);
	reg_dest->write_ubyte(6, value6);
	reg_dest->write_ubyte(7, value7);
	reg_dest->write_ubyte(8, value8);
	reg_dest->write_ubyte(9, value9);
	reg_dest->write_ubyte(10, value10);
	reg_dest->write_ubyte(11, value11);
	reg_dest->write_ubyte(12, value12);
	reg_dest->write_ubyte(13, value13);
	reg_dest->write_ubyte(14, value14);
	reg_dest->write_ubyte(15, value15);
}

void CEeCoreInterpreter::PPACH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source2->read_uhword(0);
	uhword value1 = reg_source2->read_uhword(2);
	uhword value2 = reg_source2->read_uhword(4);
	uhword value3 = reg_source2->read_uhword(6);
	uhword value4 = reg_source1->read_uhword(0);
	uhword value5 = reg_source1->read_uhword(2);
	uhword value6 = reg_source1->read_uhword(4);
	uhword value7 = reg_source1->read_uhword(6);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PPACW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rs, Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source2->read_uword(0);
	uword value1 = reg_source2->read_uword(2);
	uword value2 = reg_source1->read_uword(0);
	uword value3 = reg_source1->read_uword(2);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

void CEeCoreInterpreter::PREVH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_HW(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uhword value0 = reg_source1->read_uhword(3);
	uhword value1 = reg_source1->read_uhword(2);
	uhword value2 = reg_source1->read_uhword(1);
	uhword value3 = reg_source1->read_uhword(0);
	uhword value4 = reg_source1->read_uhword(7);
	uhword value5 = reg_source1->read_uhword(6);
	uhword value6 = reg_source1->read_uhword(5);
	uhword value7 = reg_source1->read_uhword(4);

	reg_dest->write_uhword(0, value0);
	reg_dest->write_uhword(1, value1);
	reg_dest->write_uhword(2, value2);
	reg_dest->write_uhword(3, value3);
	reg_dest->write_uhword(4, value4);
	reg_dest->write_uhword(5, value5);
	reg_dest->write_uhword(6, value6);
	reg_dest->write_uhword(7, value7);
}

void CEeCoreInterpreter::PROT3W(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = COPY_W(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	uword value0 = reg_source1->read_uword(1);
	uword value1 = reg_source1->read_uword(2);
	uword value2 = reg_source1->read_uword(0);
	uword value3 = reg_source1->read_uword(3);

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
	reg_dest->write_uword(2, value2);
	reg_dest->write_uword(3, value3);
}

