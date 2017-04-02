#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Util/FPUUtil/FPUUtil.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter_s::ADD_S()
{
	// Fd = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) + source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(), result);
}

void EECoreInterpreter_s::ADDA_S()
{
	// ACC = Fs + Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) + source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(), result);
}

void EECoreInterpreter_s::MADD_S()
{
	// Fd = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& source3Reg = mEECore->FPU->ACC; // ACC
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source3Reg->readFloat(getContext()) + (source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext())), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MADDA_S()
{
	// ACC = ACC + (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(destReg->readFloat(getContext()) + (source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext())), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MUL_S()
{
	// Fd = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MULA_S()
{
	// ACC = Fs * Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::DIV_S()
{
	// Fd = Fs / Ft (Exception on FPU unusable).
	// TODO: Check if status bits need to be set.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Set flags when special conditions occur.
	f32 result;
	CSR->clearFlags(getContext());
	if (source1Reg->readFloat(getContext()) != 0 && source2Reg->readFloat(getContext()) == 0)
	{
		CSR->setFieldValueSticky(getContext(), EECoreFPURegister_CSR_t::Fields::D, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else if (source1Reg->readFloat(getContext()) == 0 && source2Reg->readFloat(getContext()) == 0)
	{
		CSR->setFieldValueSticky(getContext(), EECoreFPURegister_CSR_t::Fields::I, 1);
		result = static_cast<f32>(Constants::EE::EECore::FPU::FMAX_POS);
	}
	else
	{
		// Calculate value and update flags.
		FPUFlags_t flags;
		result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) / source2Reg->readFloat(getContext()), flags);
		CSR->updateResultFlags(getContext(), flags);
	}

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MSUB_S()
{
	// Fd = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& source3Reg = mEECore->FPU->ACC; // ACC
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source3Reg->readFloat(getContext()) - (source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext())), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::MSUBA_S()
{
	// ACC = ACC - (Fs * Ft) (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	// TODO: Check if this needs to be done in 2 stages (with checks), where stage 1 does multiply, stage 2 does addition. Old PCSX2 clamps/rounds all values before doing anything and only checks conditions at the end.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(destReg->readFloat(getContext()) - (source1Reg->readFloat(getContext()) * source2Reg->readFloat(getContext())), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::SUB_S()
{
	// Fd = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->FPR[mEECoreInstruction.getRShamt()]; // Fd
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) - source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

void EECoreInterpreter_s::SUBA_S()
{
	// ACC = Fs - Ft (Exception on FPU unusable).
	// FPU status bits set on exponent overflow/underflow (no exception generated).
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& destReg = mEECore->FPU->ACC; // ACC
	auto& CSR = mEECore->FPU->CSR;

	// Calculate value and update flags.
	FPUFlags_t flags;
	f32 result = FPUUtil::formatIEEEToPS2Float(source1Reg->readFloat(getContext()) - source2Reg->readFloat(getContext()), flags);
	CSR->clearFlags(getContext());
	CSR->updateResultFlags(getContext(), flags);

	destReg->writeFloat(getContext(),result);
}

