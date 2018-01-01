#include <cmath>
#include <cstdlib>

#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::PABSH(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		shword val_source2 = static_cast<shword>(reg_source2->read_uhword(i));
		if (val_source2 == VALUE_SHWORD_MIN) // Need to account for when the value is at the minimum for shword, as the absolute value will not fit in an shword. In this case it is set to abs(S16_MIN) - 1 aka S16_MAX.
			reg_dest->write_uhword(i, VALUE_SHWORD_MAX);
		else
			reg_dest->write_uhword(i, std::abs(val_source2));
	}
}

void CEeCoreInterpreter::PABSW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions.
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source2 = r.ee.core.r5900.gpr[inst.rt()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		sword val_source2 = static_cast<sword>(reg_source2->read_uword(i));
		if (val_source2 == VALUE_SWORD_MIN) // Need to account for when the value is at the minimum for sword, as the absolute value will not fit in an sword. In this case it is set to abs(S32_MIN) - 1 aka S32_MAX.
			reg_dest->write_uword(i, VALUE_SWORD_MAX);
		else
			reg_dest->write_uword(i, std::abs(val_source2));
	}
}

void CEeCoreInterpreter::PLZCW(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Rd = ABS(Rt), No exceptions. I do not understand the manuals operation working...
	auto& reg_dest = r.ee.core.r5900.gpr[inst.rd()];
	auto& reg_source1 = r.ee.core.r5900.gpr[inst.rs()];

	for (auto i = 0; i < NUMBER_WORDS_IN_DWORD; i++)
	{
		uword val_source1 = reg_source1->read_uword(i);
		uword count = count_leading_bits(val_source1) - 1; // Minus 1 as the PS2 spec requires this (exclude the sign bit in the count).
		reg_dest->write_uword(i, count);
	}
}

void CEeCoreInterpreter::ABS_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = ABS(Fs) (Exception on FPU unusable only).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	csr.clear_flags();
	reg_dest.write_float(std::abs(reg_source1.read_float())); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void CEeCoreInterpreter::NEG_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = NEG(Fs) (Exception on FPU unusable only).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	csr.clear_flags();
	reg_dest.write_float(-reg_source1.read_float()); // Do not have to check for IEEE -> PS2 float compatibility as there should never be an invalid float in the register to begin with.
}

void CEeCoreInterpreter::RSQRT_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = RSQRT(Fs, Ft) (Exception on FPU unusable only).
	if (handle_cop1_usable())
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

void CEeCoreInterpreter::SQRT_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = SQRT(Ft) (Exception on FPU unusable only).
	if (handle_cop1_usable())
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

