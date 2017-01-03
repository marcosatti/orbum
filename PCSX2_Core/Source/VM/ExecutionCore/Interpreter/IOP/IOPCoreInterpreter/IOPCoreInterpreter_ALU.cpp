#include "stdafx.h"

#include "Common/Types/Context_t.h"
#include "Common/Types/Registers/Register32_t.h"

#include "VM/ExecutionCore/Interpreter/IOP/IOPCoreInterpreter/IOPCoreInterpreter.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreR3000_t.h"

void IOPCoreInterpreter::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));
	
	s32 result = source1Val + source2Val;

	if (!checkNoOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(Context_t::IOP));

	s32 result = sourceVal + imm;

	if (!checkNoOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto& sourceReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto imm = mInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->readWord(Context_t::IOP));

	s32 result = sourceVal + imm;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	s32 result = source1Val + source2Val;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	s32 result = source1Val - source2Val;

	if (!checkNoOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];

	auto source1Val = static_cast<u32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<u32>(source2Reg->readWord(Context_t::IOP));

	u32 result = source1Val - source2Val;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::DIV()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->IOP->IOPCore->R3000->LO;
	auto& HI = getResources()->IOP->IOPCore->R3000->HI;

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Val == Constants::VALUE_S32_MIN &&
		source2Val == -1)
	{
		LO->writeWord(Context_t::IOP, Constants::VALUE_S32_MIN);
		HI->writeWord(Context_t::IOP, static_cast<s32>(0));
	}
	// Check for divide by 0, in which case result is undefined (do nothing).
	else if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
	}
	// Else perform normal operation.
	else
	{
		s32 resultQ = source1Val / source2Val;
		s32 resultR = source1Val % source2Val;

		// Quotient.
		LO->writeWord(Context_t::IOP, resultQ);

		// Remainder.
		HI->writeWord(Context_t::IOP, resultR);
	}
}

void IOPCoreInterpreter::DIVU()
{
	// (LO, HI) = SignExtend<u32>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->IOP->IOPCore->R3000->LO;
	auto& HI = getResources()->IOP->IOPCore->R3000->HI;

	auto source1Val = static_cast<u32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<u32>(source2Reg->readWord(Context_t::IOP));

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		u32 resultQ = source1Val / source2Val;
		u32 resultR = source1Val % source2Val;

		// Quotient.
		LO->writeWord(Context_t::IOP, resultQ);

		// Remainder.
		HI->writeWord(Context_t::IOP, resultR);
	}
}

void IOPCoreInterpreter::MULT()
{
	// (Rd, LO, HI) = SignExtend<s32>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->IOP->IOPCore->R3000->LO;
	auto& HI = getResources()->IOP->IOPCore->R3000->HI;

	auto source1Val = static_cast<s64>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s64>(source2Reg->readWord(Context_t::IOP));

	s64 result = source1Val * source2Val;

	destReg->writeWord(Context_t::IOP, static_cast<s32>(result & 0xFFFFFFFF));
	LO->writeWord(Context_t::IOP, static_cast<s32>(result & 0xFFFFFFFF));
	HI->writeWord(Context_t::IOP, static_cast<s32>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter::MULTU()
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& LO = getResources()->IOP->IOPCore->R3000->LO;
	auto& HI = getResources()->IOP->IOPCore->R3000->HI;

	auto source1Val = static_cast<u64>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<u64>(source2Reg->readWord(Context_t::IOP));

	u64 result = source1Val * source2Val;

	destReg->writeWord(Context_t::IOP, static_cast<u32>(result & 0xFFFFFFFF));
	LO->writeWord(Context_t::IOP, static_cast<u32>(result & 0xFFFFFFFF));
	HI->writeWord(Context_t::IOP, static_cast<u32>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter::SLL()
{
	// Rd = SignExtend<s32>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = mInstruction.getRShamt();

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) << shamt);
}

void IOPCoreInterpreter::SLLV()
{
	// Rd = SignExtend<s32>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(Context_t::IOP, 0) & 0x1F;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) << shamt);
}

void IOPCoreInterpreter::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = mInstruction.getRShamt();

	destReg->writeWord(Context_t::IOP, static_cast<s32>(source1Reg->readWord(Context_t::IOP)) >> shamt);
}

void IOPCoreInterpreter::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(Context_t::IOP, 0) & 0x1F;

	destReg->writeWord(Context_t::IOP, static_cast<s32>(source1Reg->readWord(Context_t::IOP)) >> shamt);
}

void IOPCoreInterpreter::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = mInstruction.getRShamt();

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) >> shamt);
}

void IOPCoreInterpreter::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];
	u8 shamt = source2Reg->readByte(Context_t::IOP, 0) & 0x1F;

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) >> shamt);
}

void IOPCoreInterpreter::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) & source2Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::ANDI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	u32 imm = static_cast<u32>(mInstruction.getIImmU());

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) & imm);
}

void IOPCoreInterpreter::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, ~(source1Reg->readWord(Context_t::IOP) | source2Reg->readWord(Context_t::IOP)));
}

void IOPCoreInterpreter::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) | source2Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::ORI()
{
	// Rd = Rt AND Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	u32 imm = static_cast<u32>(mInstruction.getIImmU());

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) | imm);
}

void IOPCoreInterpreter::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) ^ source2Reg->readWord(Context_t::IOP));
}

void IOPCoreInterpreter::XORI()
{
	// Rd = Rt XOR Extended<u32>(Imm).
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	u32 imm = static_cast<u32>(mInstruction.getIImmU());

	destReg->writeWord(Context_t::IOP, source1Reg->readWord(Context_t::IOP) ^ imm);
}

void IOPCoreInterpreter::SLT()
{
	// Rd = SignExtended<s32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));
	auto source2Val = static_cast<s32>(source2Reg->readWord(Context_t::IOP));

	s32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::SLTI()
{
	// Rd = SignExtended<s32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];
	auto imm = static_cast<s32>(mInstruction.getIImmS());

	auto source1Val = static_cast<s32>(source1Reg->readWord(Context_t::IOP));

	s32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::SLTIU()
{
	// Rd = SignExtended<u32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRs()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getIRt()];

	u32 source1Val = source1Reg->readWord(Context_t::IOP);
	u32 imm = static_cast<u32>(mInstruction.getIImmU());

	u32 result = (source1Val < imm) ? 1 : 0;

	destReg->writeWord(Context_t::IOP, result);
}

void IOPCoreInterpreter::SLTU()
{
	// Rd = SignExtended<u32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRs()];
	auto& source2Reg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRt()];
	auto& destReg = getResources()->IOP->IOPCore->R3000->GPR[mInstruction.getRRd()];

	u32 source1Val = source1Reg->readWord(Context_t::IOP);
	u32 source2Val = source2Reg->readWord(Context_t::IOP);

	u32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->writeWord(Context_t::IOP, result);
}

