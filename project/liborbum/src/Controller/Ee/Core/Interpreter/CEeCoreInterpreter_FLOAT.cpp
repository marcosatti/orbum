#include "Core.hpp"
#include "Utilities/Utilities.hpp"

#include "Controller/Ee/Core/Interpreter/CEeCoreInterpreter.hpp"

#include "Resources/RResources.hpp"

void CEeCoreInterpreter::ADD_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() + reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::ADDA_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// ACC = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.acc; // ACC
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() + reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MADD_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_source3 = r.ee.core.fpu.acc; // ACC
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source3.read_float() + (reg_source1.read_float() * reg_source2.read_float()), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MADDA_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// ACC = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.acc; // ACC
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_dest.read_float() + (reg_source1.read_float() * reg_source2.read_float()), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MUL_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() * reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MULA_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// ACC = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.acc; // ACC
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() * reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::DIV_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = Fs / Ft (Exception on FPU unusable).
	// TODO: Check if status bits need to be set.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Set flags when special conditions occur.
	f32 result;
	csr.clear_flags();
	if (reg_source1.read_float() != 0 && reg_source2.read_float() == 0)
	{
		csr.set_d_flag_sticky(1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (reg_source1.read_float() == 0 && reg_source2.read_float() == 0)
	{
		csr.set_i_flag_sticky(1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else
	{
		// Calculate value and update flags.
		FpuFlags flags;
		result = to_ps2_float(reg_source1.read_float() / reg_source2.read_float(), flags);
		csr.update_result_flags(flags);
	}

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MSUB_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_source3 = r.ee.core.fpu.acc; // ACC
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source3.read_float() - (reg_source1.read_float() * reg_source2.read_float()), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::MSUBA_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// ACC = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.acc; // ACC
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_dest.read_float() - (reg_source1.read_float() * reg_source2.read_float()), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::SUB_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// Fd = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.fpr[inst.shamt()]; // Fd
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() - reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

void CEeCoreInterpreter::SUBA_S(const EeCoreInstruction inst) const
{
	auto& r = core->get_resources();
	
	// ACC = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handle_cop1_usable())
        return;

	auto& reg_source1 = r.ee.core.fpu.fpr[inst.rd()]; // Fs
	auto& reg_source2 = r.ee.core.fpu.fpr[inst.rt()]; // Ft
	auto& reg_dest = r.ee.core.fpu.acc; // ACC
	auto& csr = r.ee.core.fpu.csr;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = to_ps2_float(reg_source1.read_float() - reg_source2.read_float(), flags);
	csr.clear_flags();
	csr.update_result_flags(flags);

	reg_dest.write_float(result);
}

