#include <cmath>
#include <cstdlib>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PABSH(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	shword value0 = static_cast<shword>(reg_source1->read_uhword(0));
	shword value1 = static_cast<shword>(reg_source1->read_uhword(1));
	shword value2 = static_cast<shword>(reg_source1->read_uhword(2));
	shword value3 = static_cast<shword>(reg_source1->read_uhword(3));
	shword value4 = static_cast<shword>(reg_source1->read_uhword(4));
	shword value5 = static_cast<shword>(reg_source1->read_uhword(5));
	shword value6 = static_cast<shword>(reg_source1->read_uhword(6));
	shword value7 = static_cast<shword>(reg_source1->read_uhword(7));

	reg_dest->write_uhword(0, static_cast<uhword>(value0 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value0)));
	reg_dest->write_uhword(1, static_cast<uhword>(value1 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value1)));
	reg_dest->write_uhword(2, static_cast<uhword>(value2 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value2)));
	reg_dest->write_uhword(3, static_cast<uhword>(value3 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value3)));
	reg_dest->write_uhword(4, static_cast<uhword>(value4 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value4)));
	reg_dest->write_uhword(5, static_cast<uhword>(value5 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value5)));
	reg_dest->write_uhword(6, static_cast<uhword>(value6 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value6)));
	reg_dest->write_uhword(7, static_cast<uhword>(value7 == VALUE_SHWORD_MIN ? VALUE_SHWORD_MAX : std::abs(value7)));
}

void CEeCoreInterpreter::PABSW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rt()];

	sword value0 = static_cast<sword>(reg_source1->read_uword(0));
	sword value1 = static_cast<sword>(reg_source1->read_uword(1));
	sword value2 = static_cast<sword>(reg_source1->read_uword(2));
	sword value3 = static_cast<sword>(reg_source1->read_uword(3));

	reg_dest->write_uword(0, static_cast<uword>(value0 == VALUE_SWORD_MIN ? VALUE_SWORD_MAX : std::abs(value0)));
	reg_dest->write_uword(1, static_cast<uword>(value0 == VALUE_SWORD_MIN ? VALUE_SWORD_MAX : std::abs(value1)));
	reg_dest->write_uword(2, static_cast<uword>(value0 == VALUE_SWORD_MIN ? VALUE_SWORD_MAX : std::abs(value2)));
	reg_dest->write_uword(3, static_cast<uword>(value0 == VALUE_SWORD_MIN ? VALUE_SWORD_MAX : std::abs(value3)));
}

void CEeCoreInterpreter::PLZCW(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions. 
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];

	// Count = count - 1 as the PS2 spec requires this (exclude the sign bit in the count).
	uword value0 = count_leading_bits(reg_source1->read_uword(0)) - 1;
	uword value1 = count_leading_bits(reg_source1->read_uword(1)) - 1;

	reg_dest->write_uword(0, value0);
	reg_dest->write_uword(1, value1);
}

void CEeCoreInterpreter::ABS_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = ABS(Fs) (Exception on FPU unusable only).
	if (!handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	csr.clear_flags();
	reg_dest.write_float(std::abs(reg_source1.read_float())); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void CEeCoreInterpreter::NEG_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = NEG(Fs) (Exception on FPU unusable only).
	if (!handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	csr.clear_flags();
	reg_dest.write_float(-reg_source1.read_float()); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void CEeCoreInterpreter::RSQRT_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = RSQRT(Fs, Ft) (Exception on FPU unusable only).
	if (!handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	f32 val_source1 = reg_source1.read_float();
	f32 val_source2 = reg_source2.read_float();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	csr.clear_flags();
	if (val_source2 == 0.0F)
	{
		csr.set_d_flag_sticky(1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (val_source2 < 0.0F)
	{
		csr.set_i_flag_sticky(1);
		result = val_source1 / std::sqrt(std::abs(val_source2));
	}
	else
	{
		result = val_source1 / std::sqrt(val_source2);
	}

	// Update flags.
	FpuFlags flags;
	result = to_ps2_float(result, flags);
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::SQRT_S(const EeCoreInstruction inst)
{
	auto& r = core->get_resources();
	
	// Fd = SQRT(Ft) (Exception on FPU unusable only).
	if (!handle_cop1_usable())
        return;

	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	f32 val_source2 = reg_source2.read_float();
	f32 result;

	// Set flags and special values, writes a result to the above variable.
	csr.clear_flags();
	if (val_source2 == 0.0F && val_source2 < 0.0F)
	{
		result = -0.0F;
	}
	else if (val_source2 < 0.0F)
	{
		csr.set_i_flag_sticky(1);
		result = std::sqrt(std::abs(val_source2));
	}
	else
	{
		result = std::sqrt(reg_source2.read_float());
	}

	// Update flags.
	FpuFlags flags;
	result = to_ps2_float(result, flags);
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

