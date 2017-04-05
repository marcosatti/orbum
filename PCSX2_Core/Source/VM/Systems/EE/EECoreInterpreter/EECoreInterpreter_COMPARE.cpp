#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"
#include "Common/Types/Register/Register32_t.h"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter_s::SLT()
{
	// Rd = SignExtended<s64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(getContext(), 0));

	s64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::SLTI()
{
	// Rd = SignExtended<s64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto imm = static_cast<s64>(mEECoreInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(getContext(), 0));

	s64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::SLTIU()
{
	// Rd = SignExtended<u64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto imm = static_cast<u64>(static_cast<s64>(mEECoreInstruction.getIImmS()));

	auto source1Val = static_cast<u64>(source1Reg->readDword(getContext(), 0));

	u64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::SLTU()
{
	// Rd = SignExtended<u64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	auto source1Val = static_cast<u64>(source1Reg->readDword(getContext(), 0));
	auto source2Val = static_cast<u64>(source2Reg->readDword(getContext(), 0));

	u64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDword(getContext(), 0, result);
}

void EECoreInterpreter_s::PCEQB()
{
	// Rd = SignExtended<u8>((Rs == Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByte(getContext(), i);
		u8 source2Val = source2Reg->readByte(getContext(), i);
		u8 result = (source1Val == source2Val) ? 0xFF : 0x00;
		destReg->writeByte(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PCEQH()
{
	// Rd = SignExtended<u16>((Rs == Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHword(getContext(), i);
		u16 source2Val = source2Reg->readHword(getContext(), i);
		u16 result = (source1Val == source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PCEQW()
{
	// Rd = SignExtended<u32>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWord(getContext(), i);
		u32 source2Val = source2Reg->readWord(getContext(), i);
		u32 result = (source1Val == source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWord(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PCGTB()
{
	// Rd = SignExtended<u8>((Rs > Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByte(getContext(), i);
		u8 source2Val = source2Reg->readByte(getContext(), i);
		u8 result = (source1Val > source2Val) ? 0xFF : 0x00;
		destReg->writeByte(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PCGTH()
{
	// Rd = SignExtended<u16>((Rs > Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHword(getContext(), i);
		u16 source2Val = source2Reg->readHword(getContext(), i);
		u16 result = (source1Val > source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHword(getContext(), i, result);
	}
}

void EECoreInterpreter_s::PCGTW()
{
	// Rd = SignExtended<u32>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.getRs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.getRt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWord(getContext(), i);
		u32 source2Val = source2Reg->readWord(getContext(), i);
		u32 result = (source1Val > source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWord(getContext(), i, result);
	}
}

void EECoreInterpreter_s::C_EQ_S()
{
	// (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());

	if (source1Val == source2Val)
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter_s::C_F_S()
{
	// TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
	// (FCR[31] or CSR, C field) = 0
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter_s::C_LE_S()
{
	// (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());

	if (source1Val <= source2Val)
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter_s::C_LT_S()
{
	// (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (handleCOP1Usable())
        return;

	auto& source1Reg = mEECore->FPU->FPR[mEECoreInstruction.getRRd()]; // Fs
	auto& source2Reg = mEECore->FPU->FPR[mEECoreInstruction.getRt()]; // Ft
	auto& CSR = mEECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(getContext());
	f32 source2Val = source2Reg->readFloat(getContext());

	if (source1Val < source2Val)
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(getContext(), EECoreFPURegister_CSR_t::Fields::C, 0);
}


