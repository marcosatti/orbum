#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/EE/EECore/EECoreInterpreter/EECoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/Types/Registers/Register128_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

/*
Integer Addition/Subtraction instruction family.
*/

void EECoreInterpreter::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readWordS(0) + source2Reg->readWordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}
	
	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 imm = getInstruction().getIImmS();

	const s64 result = static_cast<s64>(sourceReg->readWordS(0) + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];

	destReg->writeDwordS(0, static_cast<s64>(sourceReg->readWordS(0) + getInstruction().getIImmS()));
}

void EECoreInterpreter::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordS(0, static_cast<s64>(source1Reg->readWordS(0) + source2Reg->readWordS(0)));
}

void EECoreInterpreter::DADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readDwordS(0) + source2Reg->readDwordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg->readDwordS(0)^source2Reg->readDwordS(0)))&(source1Reg->readDwordS(0)^result)) < 0)
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}
		

	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::DADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];
	const s16 imm = getInstruction().getIImmS();

	const s64 result = static_cast<s64>(sourceReg->readDwordS(0) + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(sourceReg->readDwordS(0) ^ imm))&(sourceReg->readDwordS(0) ^ result)) < 0)
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::DADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getIRs()];

	destReg->writeDwordU(0, static_cast<u64>(sourceReg->readDwordS(0) + getInstruction().getIImmS()));
}

void EECoreInterpreter::DADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordU(0, static_cast<u64>(source1Reg->readDwordS(0) + source2Reg->readDwordS(0)));
}

void EECoreInterpreter::DSUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readDwordS(0) - source2Reg->readDwordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg->readDwordS(0) ^ -source2Reg->readDwordS(0)))&(source1Reg->readDwordS(0) ^ result)) < 0) 
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::DSUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordU(0, static_cast<s64>(source1Reg->readDwordU(0) - source2Reg->readDwordU(0)));
}

void EECoreInterpreter::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readWordS(0) - source2Reg->readWordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		auto& Exceptions = getVM()->getResources()->EE->EECore->Exceptions;
		Exceptions->setException(EECoreException_t(EECoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeDwordS(0, result);
}

void EECoreInterpreter::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	destReg->writeDwordU(0, static_cast<s64>(source1Reg->readWordU(0) - source2Reg->readWordU(0)));
}

void EECoreInterpreter::PADDB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for(auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
		destReg->writeByteS(i, source1Reg->readByteS(i) + source2Reg->readByteS(i));
}

void EECoreInterpreter::PADDH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
		destReg->writeHwordS(i, source1Reg->readHwordS(i) + source2Reg->readHwordS(i));
}

void EECoreInterpreter::PADDSB()
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg->readByteS(i) + source2Reg->readByteS(i);

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByteS(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByteS(i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByteS(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter::PADDSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordS(i) + source2Reg->readHwordS(i);

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHwordS(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHwordS(i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHwordS(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter::PADDSW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg->readWordS(i) + source2Reg->readWordS(i);

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWordS(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWordS(i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWordS(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter::PADDUB()
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u16 result = source1Reg->readByteU(i) + source2Reg->readByteU(i);

		if (result > Constants::VALUE_U8_MAX)
			destReg->writeByteU(i, Constants::VALUE_U8_MAX);
		else
			destReg->writeByteU(i, static_cast<u8>(result));
	}
}

void EECoreInterpreter::PADDUH()
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u32 result = source1Reg->readHwordU(i) + source2Reg->readHwordU(i);

		if (result > Constants::VALUE_U16_MAX)
			destReg->writeHwordU(i, Constants::VALUE_U16_MAX);
		else
			destReg->writeHwordU(i, static_cast<u16>(result));
	}
}

void EECoreInterpreter::PADDUW()
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u64 result = source1Reg->readWordU(i) + source2Reg->readWordU(i);

		if (result > Constants::VALUE_U32_MAX)
			destReg->writeWordU(i, Constants::VALUE_U32_MAX);
		else
			destReg->writeWordU(i, static_cast<u32>(result));
	}
}

void EECoreInterpreter::PADDW()
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordS(i, source1Reg->readWordS(i) + source2Reg->readWordS(i));
	}
}

void EECoreInterpreter::PADSBH()
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) - source2Reg->readHwordS(i));
	}
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) + source2Reg->readHwordS(i));
	}
}

void EECoreInterpreter::PSUBB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		destReg->writeByteS(i, source1Reg->readByteS(i) - source2Reg->readByteS(i));
	}
}

void EECoreInterpreter::PSUBH()
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) - source2Reg->readHwordS(i));
	}
}

void EECoreInterpreter::PSUBSB()
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg->readByteS(i) - source2Reg->readByteS(i);

		if (result > Constants::VALUE_S8_MAX)
			destReg->writeByteS(i, Constants::VALUE_S8_MAX);
		else if (result < Constants::VALUE_S8_MIN)
			destReg->writeByteS(i, Constants::VALUE_S8_MIN);
		else
			destReg->writeByteS(i, static_cast<s8>(result));
	}
}

void EECoreInterpreter::PSUBSH()
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordS(i) - source2Reg->readHwordS(i);

		if (result > Constants::VALUE_S16_MAX)
			destReg->writeHwordS(i, Constants::VALUE_S16_MAX);
		else if (result < Constants::VALUE_S16_MIN)
			destReg->writeHwordS(i, Constants::VALUE_S16_MIN);
		else
			destReg->writeHwordS(i, static_cast<s16>(result));
	}
}

void EECoreInterpreter::PSUBSW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg->readWordS(i) - source2Reg->readWordS(i);

		if (result > Constants::VALUE_S32_MAX)
			destReg->writeWordS(i, Constants::VALUE_S32_MAX);
		else if (result < Constants::VALUE_S32_MIN)
			destReg->writeWordS(i, Constants::VALUE_S32_MIN);
		else
			destReg->writeWordS(i, static_cast<s32>(result));
	}
}

void EECoreInterpreter::PSUBUB()
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg->readByteU(i) - source2Reg->readByteU(i);

		if (result < 0)
			destReg->writeByteU(i, 0);
		else
			destReg->writeByteU(i, static_cast<u8>(result));
	}
}

void EECoreInterpreter::PSUBUH()
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordU(i) - source2Reg->readHwordU(i);

		if (result < 0)
			destReg->writeHwordU(i, 0);
		else
			destReg->writeHwordU(i, static_cast<u16>(result));
	}
}

void EECoreInterpreter::PSUBUW()
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg->readWordU(i) - source2Reg->readWordU(i);

		if (result < 0)
			destReg->writeWordU(i, 0);
		else
			destReg->writeWordU(i, static_cast<u32>(result));
	}
}

void EECoreInterpreter::PSUBW()
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->EE->EECore->R5900->GPR[getInstruction().getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordS(i, source1Reg->readWordS(i) - source2Reg->readWordS(i));
	}
}

