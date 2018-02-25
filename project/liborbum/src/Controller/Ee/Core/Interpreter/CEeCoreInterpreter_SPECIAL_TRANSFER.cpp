#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::MFSA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source = r.ee.core.r5900.sa;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MTSA(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.sa;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTSAB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.sa;
	shword imm = inst.s_imm();

	reg_dest.write_uword(((reg_source->read_uword(0) & 0xF) ^ (imm & 0xF)) * 8);
}

void CEeCoreInterpreter::MTSAH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()];
	auto& reg_dest = r.ee.core.r5900.sa;
	shword imm = inst.s_imm();

	reg_dest.write_uword(((reg_source->read_uword(0) & 0x7) ^ (imm & 0x7)) * 16);
}

void CEeCoreInterpreter::MFBPC(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.bpc;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFC0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.registers[inst.rd()];

	reg_dest->write_udword(0, static_cast<udword>(reg_source->read_uword()));
}

void CEeCoreInterpreter::MFDAB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.dab;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFDABM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.dabm;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFDVB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.dvb;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFDVBM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.dvbm;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFIAB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.iab;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFIABM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
		return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.iabm;

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MFPC(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	ubyte index = inst.funct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& reg_source = r.ee.core.cop0.pcr_registers[index];

	reg_dest->write_udword(0, static_cast<udword>(reg_source->read_uword()));
}

void CEeCoreInterpreter::MFPS(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.cop0.pccr; // The reg field in the documentation must be 0, meaning the PCCR register.

	reg_dest->write_udword(0, static_cast<udword>(reg_source.read_uword()));
}

void CEeCoreInterpreter::MTBPC(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.bpc;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTC0(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.registers[inst.rd()];

	reg_dest->write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTDAB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.dab;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTDABM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.dabm;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTDVB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.dvb;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTDVBM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.dvbm;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTIAB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.iab;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTIABM(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.iabm;

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTPC(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	ubyte index = inst.funct() & 0x3E; // Last 5 bits of the funct field contain the performace counter register number to use. Must be 0 or 1 (but not checked).
	auto& reg_dest = r.ee.core.cop0.pcr_registers[index];

	reg_dest->write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::MTPS(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop0_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.cop0.pccr; // The reg field in the documentation must be 0, meaning the PCCR register.

	reg_dest.write_uword(reg_source->read_uword(0));
}

void CEeCoreInterpreter::CFC1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop1_usable())
        return;

	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.fpu.fcr[inst.rd()]; // Fs, can only be 0 or 31.

	reg_dest->write_udword(0, static_cast<udword>(reg_source->read_uword()));
}

void CEeCoreInterpreter::CTC1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	if (!handle_cop1_usable())
        return;

	auto& reg_source = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_dest = r.ee.core.fpu.fcr[inst.rd()];

	reg_dest->write_uword(reg_source->read_uword(0));
}