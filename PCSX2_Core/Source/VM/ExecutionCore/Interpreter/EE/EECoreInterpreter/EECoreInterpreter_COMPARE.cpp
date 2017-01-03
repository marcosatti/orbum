#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"

#include "VM/ExecutionCore/Interpreter/EE/EECoreInterpreter/EECoreInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPURegisters_t.h"

void EECoreInterpreter::SLT()
{
	// Rd = SignExtended<s64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<s64>(source2Reg->readDword(Context_t::EE, 0));

	s64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDword(Context_t::EE, 0, result);
}

void EECoreInterpreter::SLTI()
{
	// Rd = SignExtended<s64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto imm = static_cast<s64>(mInstruction.getIImmS());

	auto source1Val = static_cast<s64>(source1Reg->readDword(Context_t::EE, 0));

	s64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDword(Context_t::EE, 0, result);
}

void EECoreInterpreter::SLTIU()
{
	// Rd = SignExtended<u64>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getIRt()];
	auto imm = static_cast<u64>(mInstruction.getIImmU());

	auto source1Val = static_cast<u64>(source1Reg->readDword(Context_t::EE, 0));

	u64 result = (source1Val < imm) ? 1 : 0;

	destReg->writeDword(Context_t::EE, 0, result);
}

void EECoreInterpreter::SLTU()
{
	// Rd = SignExtended<u64>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	auto source1Val = static_cast<u64>(source1Reg->readDword(Context_t::EE, 0));
	auto source2Val = static_cast<u64>(source2Reg->readDword(Context_t::EE, 0));

	u64 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeDword(Context_t::EE, 0, result);
}

void EECoreInterpreter::PCEQB()
{
	// Rd = SignExtended<u8>((Rs == Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByte(Context_t::EE, i);
		u8 source2Val = source2Reg->readByte(Context_t::EE, i);
		u8 result = (source1Val == source2Val) ? 0xFF : 0x00;
		destReg->writeByte(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PCEQH()
{
	// Rd = SignExtended<u16>((Rs == Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHword(Context_t::EE, i);
		u16 source2Val = source2Reg->readHword(Context_t::EE, i);
		u16 result = (source1Val == source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHword(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PCEQW()
{
	// Rd = SignExtended<u32>((Rs == Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWord(Context_t::EE, i);
		u32 source2Val = source2Reg->readWord(Context_t::EE, i);
		u32 result = (source1Val == source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWord(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PCGTB()
{
	// Rd = SignExtended<u8>((Rs > Rt) ? 0xFF : 0x00)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u8 source1Val = source1Reg->readByte(Context_t::EE, i);
		u8 source2Val = source2Reg->readByte(Context_t::EE, i);
		u8 result = (source1Val > source2Val) ? 0xFF : 0x00;
		destReg->writeByte(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PCGTH()
{
	// Rd = SignExtended<u16>((Rs > Rt) ? 0xFFFF : 0x0000)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u16 source1Val = source1Reg->readHword(Context_t::EE, i);
		u16 source2Val = source2Reg->readHword(Context_t::EE, i);
		u16 result = (source1Val > source2Val) ? 0xFFFF : 0x0000;
		destReg->writeHword(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::PCGTW()
{
	// Rd = SignExtended<u32>((Rs > Rt) ? 0xFFFFFFFF : 0x00000000)
	// No Exceptions generated.
	auto& source1Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->EE->EECore->R5900->GPR[mInstruction.getRRd()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u32 source1Val = source1Reg->readWord(Context_t::EE, i);
		u32 source2Val = source2Reg->readWord(Context_t::EE, i);
		u32 result = (source1Val > source2Val) ? 0xFFFFFFFF : 0x00000000;
		destReg->writeWord(Context_t::EE, i, result);
	}
}

void EECoreInterpreter::C_EQ_S()
{
	// (FCR[31] or CSR, C field) = (Fs == Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!checkCOP1Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(Context_t::EE);
	f32 source2Val = source2Reg->readFloat(Context_t::EE);

	if (source1Val == source2Val)
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter::C_F_S()
{
	// TODO: Whats the point of this instruction? Docs say something about a comparison but it always sets the C field to 0 regardless...
	// (FCR[31] or CSR, C field) = 0
	// No Exceptions generated, except for coprocessor unavailable.
	if (!checkCOP1Usable())
        return;

	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter::C_LE_S()
{
	// (FCR[31] or CSR, C field) = (Fs <= Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!checkCOP1Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(Context_t::EE);
	f32 source2Val = source2Reg->readFloat(Context_t::EE);

	if (source1Val <= source2Val)
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 0);
}

void EECoreInterpreter::C_LT_S()
{
	// (FCR[31] or CSR, C field) = (Fs < Ft) ? 1 : 0)
	// No Exceptions generated, except for coprocessor unavailable.
	if (!checkCOP1Usable())
        return;

	auto& source1Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRd()]; // Fs
	auto& source2Reg = getResources()->EE->EECore->FPU->FPR[mInstruction.getRRt()]; // Ft
	auto& CSR = getResources()->EE->EECore->FPU->CSR; // FCR[31] aka control status register.

	f32 source1Val = source1Reg->readFloat(Context_t::EE);
	f32 source2Val = source2Reg->readFloat(Context_t::EE);

	if (source1Val < source2Val)
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 1);
	else
		CSR->setFieldValue(EECoreFPURegister_CSR_t::Fields::C, 0);
}


