#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCore/IOPCoreInterpreter/IOPCoreInterpreter.h"
#include "VM/VMMain.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/Types/IOPCoreException_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"

void IOPCoreInterpreter::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	// Check for over/under flow. Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
	if (((source2Reg->readWordS() > 0) && (source1Reg->readWordS() > Constants::VALUE_S32_MAX - source2Reg->readWordS()))
		|| ((source2Reg->readWordS() < 0) && (source1Reg->readWordS() < Constants::VALUE_S32_MIN - source2Reg->readWordS())))
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(IOPCoreException_t(IOPCoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeWordS(source1Reg->readWordS() + source2Reg->readWordS());
}

void IOPCoreInterpreter::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	const s16 imm = getInstruction().getIImmS();

	// Check for over/under flow. Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
	if (((imm > 0) && (sourceReg->readWordS() > Constants::VALUE_S32_MAX - imm))
		|| ((imm < 0) && (sourceReg->readWordS() < Constants::VALUE_S32_MIN - imm)))
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(IOPCoreException_t(IOPCoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeWordS(static_cast<s32>(sourceReg->readWordS() + imm));
}

void IOPCoreInterpreter::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	auto& sourceReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];

	destReg->writeWordS(sourceReg->readWordS() + getInstruction().getIImmS());
}

void IOPCoreInterpreter::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	destReg->writeWordS(source1Reg->readWordS() + source2Reg->readWordS());
}

void IOPCoreInterpreter::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	// Check for over/under flow. Thanks to http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
	if (((source2Reg->readWordS() < 0) && (source1Reg->readWordS() > Constants::VALUE_S32_MAX + source2Reg->readWordS()))
		|| ((source2Reg->readWordS() > 0) && (source1Reg->readWordS() < Constants::VALUE_S32_MIN + source2Reg->readWordS())))
	{
		auto& Exceptions = getVM()->getResources()->IOP->IOPCore->Exceptions;
		Exceptions->setException(IOPCoreException_t(IOPCoreException_t::ExType::EX_OVERFLOW));
		return;
	}

	destReg->writeWordS(source1Reg->readWordS() - source2Reg->readWordS());
}

void IOPCoreInterpreter::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	destReg->writeWordU(source1Reg->readWordU() - source2Reg->readWordU());
}

void IOPCoreInterpreter::DIV()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Reg->readWordS() == Constants::VALUE_S32_MIN &&
		source2Reg->readWordS() == -1)
	{
		getVM()->getResources()->IOP->IOPCore->R3000->LO->writeWordS(Constants::VALUE_S32_MIN);
		getVM()->getResources()->IOP->IOPCore->R3000->HI->writeWordS(static_cast<s32>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Reg->readWordS() == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		getVM()->getResources()->IOP->IOPCore->R3000->LO->writeWordS(static_cast<s32>(source1Reg->readWordS() / source2Reg->readWordS()));

		// Remainder.
		getVM()->getResources()->IOP->IOPCore->R3000->HI->writeWordS(static_cast<s32>(source1Reg->readWordS() % source2Reg->readWordS()));
	}
}

void IOPCoreInterpreter::DIVU()
{
	// (LO, HI) = SignExtend<u32>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Reg->readWordU() == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		// Quotient.
		getVM()->getResources()->IOP->IOPCore->R3000->LO->writeWordU(static_cast<u32>(source1Reg->readWordU() / source2Reg->readWordU()));

		// Remainder.
		getVM()->getResources()->IOP->IOPCore->R3000->HI->writeWordU(static_cast<u32>(source1Reg->readWordU() % source2Reg->readWordU()));
	}
}

void IOPCoreInterpreter::MULT()
{
	// (Rd, LO, HI) = SignExtend<s32>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	s64 result = source1Reg->readWordS() * source2Reg->readWordS();
	destReg->writeWordS(static_cast<s32>(result & 0xFFFFFFFF));
	getVM()->getResources()->IOP->IOPCore->R3000->LO->writeWordS(static_cast<s32>(result & 0xFFFFFFFF));
	getVM()->getResources()->IOP->IOPCore->R3000->HI->writeWordS(static_cast<s32>(result >> 32));
}

void IOPCoreInterpreter::MULTU()
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];

	u64 result = source1Reg->readWordU() * source2Reg->readWordU();
	destReg->writeWordU(static_cast<u32>(result & 0xFFFFFFFF));
	getVM()->getResources()->IOP->IOPCore->R3000->LO->writeWordU(static_cast<u32>(result & 0xFFFFFFFF));
	getVM()->getResources()->IOP->IOPCore->R3000->HI->writeWordU(static_cast<u32>(result >> 32));
}

void IOPCoreInterpreter::SLL()
{
	// Rd = SignExtend<s32>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeWordS(static_cast<s32>(source1Reg->readWordU() << shamt));
}

void IOPCoreInterpreter::SLLV()
{
	// Rd = SignExtend<s32>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	destReg->writeWordS(static_cast<s32>(source1Reg->readWordU() << shamt));
}

void IOPCoreInterpreter::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeWordS(static_cast<s32>(source1Reg->readWordS() >> shamt));
}

void IOPCoreInterpreter::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	destReg->writeWordS(static_cast<s32>(source1Reg->readWordS() >> shamt));
}

void IOPCoreInterpreter::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = getInstruction().getRShamt();

	destReg->writeWordS(static_cast<s32>(source1Reg->readWordU() >> shamt));
}

void IOPCoreInterpreter::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];
	u8 shamt = source2Reg->readByteU(0) & 0x1F;

	s32 result = static_cast<s32>(source1Reg->readWordU() >> shamt);
	destReg->writeWordS(result);
}

void IOPCoreInterpreter::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	destReg->writeWordU(source1Reg->readWordU() & source2Reg->readWordU());
}

void IOPCoreInterpreter::ANDI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	u32 imm = static_cast<u32>(getInstruction().getIImmU());

	destReg->writeWordU(source1Reg->readWordU() & imm);
}

void IOPCoreInterpreter::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	destReg->writeWordU(~(source1Reg->readWordU() | source2Reg->readWordU()));
}

void IOPCoreInterpreter::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	destReg->writeWordU(source1Reg->readWordU() | source2Reg->readWordU());
}

void IOPCoreInterpreter::ORI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	s32 imm = static_cast<s32>(getInstruction().getIImmU());

	destReg->writeWordU(source1Reg->readWordU() | imm);
}

void IOPCoreInterpreter::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	destReg->writeWordU(source1Reg->readWordU() ^ source2Reg->readWordU());
}

void IOPCoreInterpreter::XORI()
{
	// Rd = Rt XOR Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];
	u32 imm = static_cast<u32>(getInstruction().getIImmU());

	destReg->writeWordU(source1Reg->readWordU() ^ imm);
}

void IOPCoreInterpreter::SLT()
{
	// Rd = SignExtended<s32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	s32 source1Val = source1Reg->readWordS();
	s32 source2Val = source2Reg->readWordS();
	s32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWordS(result);
}

void IOPCoreInterpreter::SLTI()
{
	// Rd = SignExtended<s32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];

	s32 source1Val = source1Reg->readWordS();
	s32 imm = static_cast<s32>(getInstruction().getIImmS());
	s32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWordS(result);
}

void IOPCoreInterpreter::SLTIU()
{
	// Rd = SignExtended<u32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRs()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getIRt()];

	u32 source1Val = source1Reg->readWordU();
	u32 imm = static_cast<u32>(getInstruction().getIImmU());
	u32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWordU(result);
}

void IOPCoreInterpreter::SLTU()
{
	// Rd = SignExtended<u32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRs()];
	auto& source2Reg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRt()];
	auto& destReg = getVM()->getResources()->IOP->IOPCore->R3000->GPR[getInstruction().getRRd()];

	u32 source1Val = source1Reg->readWordU();
	u32 source2Val = source2Reg->readWordU();
	u32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWordU(result);
}

