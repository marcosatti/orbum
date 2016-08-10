#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/ExecutionCore/Interpreter/InterpreterEECore/InterpreterEECore.h"
#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/Util/EECoreInstructionUtil/EECoreInstructionUtil.h"
#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"

/*
Integer Addition/Subtraction instruction family.
*/

void InterpreterEECore::ADD(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readWordS(0) + source2Reg->readWordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}
	
	destReg->writeDwordS(0, result);
}

void InterpreterEECore::ADDI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];
	const s16 imm = instruction.getIImmS();

	const s64 result = static_cast<s64>(sourceReg->readWordS(0) + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
	{
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);
	}

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::ADDIU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rt = Rs + Imm (signed).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];

	destReg->writeDwordS(0, static_cast<s64>(sourceReg->readWordS(0) + instruction.getIImmS()));
}

void InterpreterEECore::ADDU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs + Rt
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	destReg->writeDwordS(0, static_cast<s64>(source1Reg->readWordS(0) + source2Reg->readWordS(0)));
}

void InterpreterEECore::DADD(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readDwordS(0) + source2Reg->readDwordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg->readDwordS(0)^source2Reg->readDwordS(0)))&(source1Reg->readDwordS(0)^result)) < 0) 
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::DADDI(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];
	const s16 imm = instruction.getIImmS();

	const s64 result = static_cast<s64>(sourceReg->readDwordS(0) + imm);

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(sourceReg->readDwordS(0) ^ imm))&(sourceReg->readDwordS(0) ^ result)) < 0)
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::DADDIU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rt = Rs + Imm (signed).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRd()];
	auto& sourceReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getIRs()];

	destReg->writeDwordS(0, static_cast<s64>(sourceReg->readDwordS(0) + instruction.getIImmS()));
}

void InterpreterEECore::DADDU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs + Rt
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	destReg->writeDwordU(0, static_cast<s64>(source1Reg->readDwordU(0) + source2Reg->readDwordU(0)));
}

void InterpreterEECore::DSUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readDwordS(0) - source2Reg->readDwordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// Let's all give gigahertz a big round of applause for finding this gem, which apparently works, and generates compact/fast asm code too.
	if (((~(source1Reg->readDwordS(0) ^ -source2Reg->readDwordS(0)))&(source1Reg->readDwordS(0) ^ result)) < 0) 
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::DSUBU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs - Rt
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	destReg->writeDwordU(0, static_cast<s64>(source1Reg->readDwordU(0) - source2Reg->readDwordU(0)));
}

void InterpreterEECore::SUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	const s64 result = static_cast<s64>(source1Reg->readWordS(0) - source2Reg->readWordS(0));

	// Check for over/under flow. Logic adapted from old PCSX2.
	// This 32 bit method relies on the MIPS documented method of checking for overflow, which when adapted, involves comparing bit 32 against bit 31.
	// If bit 32 != bit 31 then we have an overflow.
	if (((result >> 31) & 1) != ((result >> 32) & 1)) 
		throw PS2Exception_t(PS2Exception_t::ExceptionType::EX_OVERFLOW);

	destReg->writeDwordS(0, result);
}

void InterpreterEECore::SUBU(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Rd = Rs - Rt
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	destReg->writeDwordU(0, static_cast<s64>(source1Reg->readWordU(0) - source2Reg->readWordU(0)));
}

void InterpreterEECore::PADDB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for(auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
		destReg->writeByteS(i, source1Reg->readByteS(i) + source2Reg->readByteS(i));
}

void InterpreterEECore::PADDH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
		destReg->writeHwordS(i, source1Reg->readHwordS(i) + source2Reg->readHwordS(i));
}

void InterpreterEECore::PADDSB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] + Rt[SB] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PADDSH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PADDSW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PADDUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UB] = Rs[UB] + Rt[UB]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		u16 result = source1Reg->readByteU(i) + source2Reg->readByteU(i);

		if (result > Constants::VALUE_U8_MAX)
			destReg->writeByteU(i, Constants::VALUE_U8_MAX);
		else
			destReg->writeByteU(i, static_cast<u8>(result));
	}
}

void InterpreterEECore::PADDUH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UH] = Rs[UH] + Rt[UH]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		u32 result = source1Reg->readHwordU(i) + source2Reg->readHwordU(i);

		if (result > Constants::VALUE_U16_MAX)
			destReg->writeHwordU(i, Constants::VALUE_U16_MAX);
		else
			destReg->writeHwordU(i, static_cast<u16>(result));
	}
}

void InterpreterEECore::PADDUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UW] = Rs[UW] + Rt[UW] 
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		u64 result = source1Reg->readWordU(i) + source2Reg->readWordU(i);

		if (result > Constants::VALUE_U32_MAX)
			destReg->writeWordU(i, Constants::VALUE_U32_MAX);
		else
			destReg->writeWordU(i, static_cast<u32>(result));
	}
}

void InterpreterEECore::PADDW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] + Rt[SW]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordS(i, source1Reg->readWordS(i) + source2Reg->readWordS(i));
	}
}

void InterpreterEECore::PADSBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] -/+ Rt[SH] (minus for lower hwords, plus for higher hwords)
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD / 2; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) - source2Reg->readHwordS(i));
	}
	for (auto i = Constants::NUMBER_HWORDS_IN_QWORD / 2; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) + source2Reg->readHwordS(i));
	}
}

void InterpreterEECore::PSUBB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		destReg->writeByteS(i, source1Reg->readByteS(i) - source2Reg->readByteS(i));
	}
}

void InterpreterEECore::PSUBH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] - Rt[SH]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->writeHwordS(i, source1Reg->readHwordS(i) - source2Reg->readHwordS(i));
	}
}

void InterpreterEECore::PSUBSB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SB] = Rs[SB] - Rt[SB] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PSUBSH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SH] = Rs[SH] + Rt[SH] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PSUBSW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW] Saturated
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

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

void InterpreterEECore::PSUBUB(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UB] = Rs[UB] - Rt[UB]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_BYTES_IN_QWORD; i++)
	{
		s16 result = source1Reg->readByteU(i) - source2Reg->readByteU(i);

		if (result < 0)
			destReg->writeByteU(i, 0);
		else
			destReg->writeByteU(i, static_cast<u8>(result));
	}
}

void InterpreterEECore::PSUBUH(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UH] = Rs[UH] - Rt[UH]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_HWORDS_IN_QWORD; i++)
	{
		s32 result = source1Reg->readHwordU(i) - source2Reg->readHwordU(i);

		if (result < 0)
			destReg->writeHwordU(i, 0);
		else
			destReg->writeHwordU(i, static_cast<u16>(result));
	}
}

void InterpreterEECore::PSUBUW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[UW] = Rs[UW] - Rt[UW] 
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		s64 result = source1Reg->readWordU(i) - source2Reg->readWordU(i);

		if (result < 0)
			destReg->writeWordU(i, 0);
		else
			destReg->writeWordU(i, static_cast<u32>(result));
	}
}

void InterpreterEECore::PSUBW(const MIPSInstruction_t & instruction, std::shared_ptr<PS2Resources_t> & PS2Resources)
{
	// Parallel Rd[SW] = Rs[SW] - Rt[SW]
	auto& destReg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRd()];
	auto& source1Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRs()];
	auto& source2Reg = PS2Resources->EE->EECore->R5900->GPR[instruction.getRRt()];

	for (auto i = 0; i < Constants::NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->writeWordS(i, source1Reg->readWordS(i) - source2Reg->readWordS(i));
	}
}

