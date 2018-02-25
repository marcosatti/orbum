#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::LB(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = static_cast<sbyte>(r.ee.bus.read_ubyte(BusContext::Ee, *physical_address));
	reg_dest->write_udword(0, static_cast<sdword>(value));
}

void CEeCoreInterpreter::LBU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_ubyte(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, static_cast<udword>(value));
}

void CEeCoreInterpreter::LD(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UD]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = static_cast<sdword>(r.ee.bus.read_udword(BusContext::Ee, *physical_address));
	reg_dest->write_udword(0, value);
}

void CEeCoreInterpreter::LDL(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UD] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	uword shift = (virtual_address & 7) << 3;
	uptr dword_address = (virtual_address & 0xFFFFFFF8);

	std::optional<uptr> physical_address = translate_address(dword_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_udword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, (reg_dest->read_udword(0) & (0x00FFFFFFFFFFFFFF >> shift)) | (value << (56 - shift)));
}

void CEeCoreInterpreter::LDR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[UD]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	uword shift = (virtual_address & 7) << 3;
	uptr dword_address = (virtual_address & 0xFFFFFFF8);

	std::optional<uptr> physical_address = translate_address(dword_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_udword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, (reg_dest->read_udword(0) & (0xFFFFFFFFFFFFFF00 << (56 - shift))) | (value >> shift));
}

void CEeCoreInterpreter::LH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = static_cast<shword>(r.ee.bus.read_uhword(BusContext::Ee, *physical_address));
	reg_dest->write_udword(0, static_cast<sdword>(value));
}

void CEeCoreInterpreter::LHU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uhword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, static_cast<udword>(value));
}

void CEeCoreInterpreter::LUI(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Imm << 16. No exceptions generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto imm = static_cast<sword>(inst.s_imm());

	sdword result = static_cast<sdword>(imm << 16);

	reg_dest->write_udword(0, result);
}

void CEeCoreInterpreter::LW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = static_cast<sword>(r.ee.bus.read_uword(BusContext::Ee, *physical_address));
	reg_dest->write_udword(0, static_cast<sdword>(value));
}

void CEeCoreInterpreter::LWL(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address(word_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, static_cast<sdword>(static_cast<sword>((reg_dest->read_uword(0) & (0x00FFFFFF >> shift)) | (value << (24 - shift)))));
}

void CEeCoreInterpreter::LWR(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address(word_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, static_cast<sdword>(static_cast<sword>((reg_dest->read_uword(0) & (0xFFFFFF00 << (24 - shift))) | (value >> shift))));
}

void CEeCoreInterpreter::LWU(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UW]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source->read_uword(0) + imm;
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uword(BusContext::Ee, *physical_address);
	reg_dest->write_udword(0, static_cast<udword>(value));
}

void CEeCoreInterpreter::LQ(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UQ]. Address error or TLB error generated.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = (reg_source->read_uword(0) + imm);
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uqword(BusContext::Ee, *physical_address);
	reg_dest->write_uqword(value);
}

void CEeCoreInterpreter::LWC1(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Ft = MEM[UQ]. Address error or TLB error generated.
	if (!handle_cop1_usable())
		return;

	auto& reg_dest = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = (reg_source->read_uword(0) + imm);
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uword(BusContext::Ee, *physical_address);
	reg_dest.write_uword(value);
}

void CEeCoreInterpreter::LQC2(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// VU0.vf = GPR. Coprocessor unusable exception.
	if (!handle_cop2_usable())
		return;

	auto& reg_dest = r.ee.vpu.vu.unit_0.vf[inst.rt()];
	auto& reg_source = r.ee.core.r5900.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = (reg_source->read_uword(0) + imm);
	std::optional<uptr> physical_address = translate_address(virtual_address, READ, DATA);
	if (!physical_address)
		return;

	auto value = r.ee.bus.read_uqword(BusContext::Ee, *physical_address);
	reg_dest.write_uqword(value);
}
