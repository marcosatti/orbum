#include <boost/format.hpp>

#include "Core.hpp"

#include "Controller/Iop/Core/Interpreter/CIopCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CIopCoreInterpreter::LB(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SB]. Address error or TLB error generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, READ);
	if (!physical_address)
		return;

	auto value = static_cast<sbyte>(r.iop.bus.read_ubyte(BusContext::Iop, *physical_address));
	reg_dest.write_uword(static_cast<sword>(value));
}

void CIopCoreInterpreter::LBU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UB]. Address error or TLB error generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_ubyte(BusContext::Iop, *physical_address);
	reg_dest.write_uword(static_cast<uword>(value));
}

void CIopCoreInterpreter::LH(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SH]. Address error or TLB error generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, READ);
	if (!physical_address)
		return;

	auto value = static_cast<shword>(r.iop.bus.read_uhword(BusContext::Iop, *physical_address));
	reg_dest.write_uword(static_cast<sword>(value));
}

void CIopCoreInterpreter::LHU(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[UH]. Address error or TLB error generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uhword(BusContext::Iop, *physical_address);
	reg_dest.write_uword(static_cast<uword>(value));
}

void CIopCoreInterpreter::LUI(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = Imm << 16. No exceptions generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto imm = static_cast<sword>(inst.s_imm());

	sword result = imm << 16;

	reg_dest.write_uword(result);
}

void CIopCoreInterpreter::LW(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = MEM[SW]. Address error or TLB error generated.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uword(BusContext::Iop, *physical_address);
	reg_dest.write_uword(static_cast<sword>(value));
}

void CIopCoreInterpreter::LWL(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address_data(word_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uword(BusContext::Iop, *physical_address);
	reg_dest.write_uword((reg_dest.read_uword() & (0x00FFFFFF >> shift)) | (value << (24 - shift)));
}

void CIopCoreInterpreter::LWR(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// Rd = MEM[SW]. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_dest = r.iop.core.r3000.gpr[inst.rt()];
	auto& reg_source = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source.read_uword() + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address_data(word_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uword(BusContext::Iop, *physical_address);
	reg_dest.write_uword((reg_dest.read_uword() & (0xFFFFFF00 << (24 - shift))) | (value >> shift));
}

void CIopCoreInterpreter::SB(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// MEM[UB] = Rd. Address error or TLB error generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source1.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, WRITE);
	if (!physical_address)
		return;

	r.iop.bus.write_ubyte(BusContext::Iop, *physical_address, reg_source2.read_ubyte(0));
}

void CIopCoreInterpreter::SH(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// MEM[UH] = Rd. Address error or TLB error generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source1.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, WRITE);
	if (!physical_address)
		return;

	r.iop.bus.write_uhword(BusContext::Iop, *physical_address, reg_source2.read_uhword(0));
}

void CIopCoreInterpreter::SW(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// MEM[UW] = Rd. Address error or TLB error generated.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source1.read_uword() + imm;
	std::optional<uptr> physical_address = translate_address_data(virtual_address, WRITE);
	if (!physical_address)
		return;

	r.iop.bus.write_uword(BusContext::Iop, *physical_address, reg_source2.read_uword());
}

void CIopCoreInterpreter::SWL(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source1.read_uword() + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address_data(word_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uword(BusContext::Iop, *physical_address);

	// Need to get phy address again, check for write conditions.
	physical_address = translate_address_data(word_address, WRITE);
	if (!physical_address)
		return;

	r.iop.bus.write_uword(BusContext::Iop, *physical_address, ((reg_source2.read_uword() >> (24 - shift))) | (value & (0xFFFFFF00 << shift)));
}

void CIopCoreInterpreter::SWR(const IopCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// TODO: check this, dont think its right. This should work for little-endian architectures (ie: x86), but not sure about big-endian. Luckily most machines are little-endian today, so this may never be a problem.
	// MEM[UW] = Rd. Address error or TLB error generated.
	// Credit to PCSX2.
	auto& reg_source1 = r.iop.core.r3000.gpr[inst.rs()]; // "Base"
	auto& reg_source2 = r.iop.core.r3000.gpr[inst.rt()];
	const shword imm = inst.s_imm();

	uptr virtual_address = reg_source1.read_uword() + imm;
	uword shift = (virtual_address & 3) << 3;
	uptr word_address = (virtual_address & 0xFFFFFFFC);

	std::optional<uptr> physical_address = translate_address_data(word_address, READ);
	if (!physical_address)
		return;

	auto value = r.iop.bus.read_uword(BusContext::Iop, *physical_address);

	// Need to get phy address again, check for write conditions.
	physical_address = translate_address_data(word_address, WRITE);
	if (!physical_address)
		return;

	r.iop.bus.write_uword(BusContext::Iop, *physical_address, ((reg_source2.read_uword() << shift) | (value & (0x00FFFFFF >> (24 - shift)))));
}

