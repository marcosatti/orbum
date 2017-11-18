
#include "Common/Types/Register/SizedWordRegister.hpp"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreFpu.hpp"
#include "Resources/Ee/Core/EeCoreFpuRegisters.hpp"

void EECoreInterpreter_s::ADD_S()
{
	// Fd = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() + source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(, result);
}

void EECoreInterpreter_s::ADDA_S()
{
	// ACC = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() + source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(, result);
}

void EECoreInterpreter_s::MADD_S()
{
	// Fd = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& source3Reg = mEECore->FPU->ACC; // ACC
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source3Reg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat()), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MADDA_S()
{
	// ACC = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(destReg->readFloat() + (source1Reg->readFloat() * source2Reg->readFloat()), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MUL_S()
{
	// Fd = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() * source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MULA_S()
{
	// ACC = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() * source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::DIV_S()
{
	// Fd = Fs / Ft (Exception on FPU unusable).
	// TODO: Check if status bits need to be set.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Set flags when special conditions occur.
	f32 result;
	CSR->clear_flags();
	if (source1Reg->readFloat() != 0 && source2Reg->readFloat() == 0)
	{
		CSR->setFieldValueSticky(, EeCoreFpuRegister_Csr::D, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source1Reg->readFloat() == 0 && source2Reg->readFloat() == 0)
	{
		CSR->setFieldValueSticky(, EeCoreFpuRegister_Csr::I, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else
	{
		// Calculate value and update flags.
		FpuFlags flags;
		result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() / source2Reg->readFloat(), flags);
		CSR->update_result_flags(flags);
	}

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MSUB_S()
{
	// Fd = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& source3Reg = mEECore->FPU->ACC; // ACC
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source3Reg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat()), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::MSUBA_S()
{
	// ACC = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(destReg->readFloat() - (source1Reg->readFloat() * source2Reg->readFloat()), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::SUB_S()
{
	// Fd = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.shamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() - source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

void EECoreInterpreter_s::SUBA_S()
{
	// ACC = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.rt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FpuFlags flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat() - source2Reg->readFloat(), flags);
	CSR->clear_flags();
	CSR->update_result_flags(flags);

	destReg->writeFloat(,result);
}

