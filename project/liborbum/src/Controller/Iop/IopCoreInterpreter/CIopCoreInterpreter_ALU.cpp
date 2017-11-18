
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/IOP/IOPCoreInterpreter/IOPCoreInterpreter_s.h"

#include "Resources/Iop/Core/RIopCore.h"
#include "Resources/Iop/Core/IopCoreR3000.h"

void IOPCoreInterpreter_s::ADD()
{
	// Rd = Rs + Rt (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());
	
	s32 result = source1Val + source2Val;

	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::ADDI()
{
	// Rt = Rs + Imm (signed) (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto imm = mIOPCoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->read_uword());

	s32 result = sourceVal + imm;

	if (handleOverOrUnderflow32(sourceVal, imm))
        return;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::ADDIU()
{
	// Rt = Rs + Imm (signed).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& sourceReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto imm = mIOPCoreInstruction.getIImmS();

	auto sourceVal = static_cast<s32>(sourceReg->read_uword());

	s32 result = sourceVal + imm;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::ADDU()
{
	// Rd = Rs + Rt
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	s32 result = source1Val + source2Val;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::SUB()
{
	// Rd = Rs - Rt (Exception on Integer Overflow).
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	s32 result = source1Val - source2Val;

	if (handleOverOrUnderflow32(source1Val, source2Val))
        return;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::SUBU()
{
	// Rd = Rs - Rt
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];

	auto source1Val = static_cast<uword>(source1Reg->read_uword());
	auto source2Val = static_cast<uword>(source2Reg->read_uword());

	uword result = source1Val - source2Val;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::DIV()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Val == Constants::VALUE_S32_MIN &&
		source2Val == -1)
	{
		LO->write_uword(Constants::VALUE_S32_MIN);
		HI->write_uword(static_cast<s32>(0));
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
		LO->write_uword(resultQ);

		// Remainder.
		HI->write_uword(resultR);
	}
}

void IOPCoreInterpreter_s::DIVU()
{
	// (LO, HI) = SignExtend<uword>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<uword>(source1Reg->read_uword());
	auto source2Val = static_cast<uword>(source2Reg->read_uword());

	// Check for divide by 0, in which case result is undefined (do nothing).
	if (source2Val == 0)
	{
		// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
	}
	// Else perform normal operation.
	else
	{
		uword resultQ = source1Val / source2Val;
		uword resultR = source1Val % source2Val;

		// Quotient.
		LO->write_uword(resultQ);

		// Remainder.
		HI->write_uword(resultR);
	}
}

void IOPCoreInterpreter_s::MULT()
{
	// (LO, HI) = SignExtend<s32>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<s64>(static_cast<s32>(source1Reg->read_uword()));
	auto source2Val = static_cast<s64>(static_cast<s32>(source2Reg->read_uword()));

	s64 result = source1Val * source2Val;

	LO->write_uword(static_cast<s32>(result & 0xFFFFFFFF));
	HI->write_uword(static_cast<s32>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter_s::MULTU()
{
	// (LO, HI) = Rs[UW] * Rt[UW]
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& LO = mIOPCore->R3000->LO;
	auto& HI = mIOPCore->R3000->HI;

	auto source1Val = static_cast<udword>(source1Reg->read_uword());
	auto source2Val = static_cast<udword>(source2Reg->read_uword());

	udword result = source1Val * source2Val;

	LO->write_uword(static_cast<uword>(result & 0xFFFFFFFF));
	HI->write_uword(static_cast<uword>((result >> 32) & 0xFFFFFFFF));
}

void IOPCoreInterpreter_s::SLL()
{
	// Rd = SignExtend<s32>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = mIOPCoreInstruction.shamt();

	destReg->write_uword(source1Reg->read_uword() << shamt);
}

void IOPCoreInterpreter_s::SLLV()
{
	// Rd = SignExtend<s32>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	destReg->write_uword(source1Reg->read_uword() << shamt);
}

void IOPCoreInterpreter_s::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = mIOPCoreInstruction.shamt();

	destReg->write_uword(static_cast<s32>(source1Reg->read_uword()) >> shamt);
}

void IOPCoreInterpreter_s::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	destReg->write_uword(static_cast<s32>(source1Reg->read_uword()) >> shamt);
}

void IOPCoreInterpreter_s::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = mIOPCoreInstruction.shamt();

	destReg->write_uword(source1Reg->read_uword() >> shamt);
}

void IOPCoreInterpreter_s::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	destReg->write_uword(source1Reg->read_uword() >> shamt);
}

void IOPCoreInterpreter_s::AND()
{
	// Rd = Rt AND Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(source1Reg->read_uword() & source2Reg->read_uword());
}

void IOPCoreInterpreter_s::ANDI()
{
	// Rd = Rt AND Extended<uword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	uword imm = static_cast<uword>(mIOPCoreInstruction.getIImmU());

	destReg->write_uword(source1Reg->read_uword() & imm);
}

void IOPCoreInterpreter_s::NOR()
{
	// Rd = NOT (Rt OR Rs).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(~(source1Reg->read_uword() | source2Reg->read_uword()));
}

void IOPCoreInterpreter_s::OR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(source1Reg->read_uword() | source2Reg->read_uword());
}

void IOPCoreInterpreter_s::ORI()
{
	// Rd = Rt AND Extended<uword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	uword imm = static_cast<uword>(mIOPCoreInstruction.getIImmU());

	destReg->write_uword(source1Reg->read_uword() | imm);
}

void IOPCoreInterpreter_s::XOR()
{
	// Rd = Rt OR Rs.
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	destReg->write_uword(source1Reg->read_uword() ^ source2Reg->read_uword());
}

void IOPCoreInterpreter_s::XORI()
{
	// Rd = Rt XOR Extended<uword>(Imm).
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	uword imm = static_cast<uword>(mIOPCoreInstruction.getIImmU());

	destReg->write_uword(source1Reg->read_uword() ^ imm);
}

void IOPCoreInterpreter_s::SLT()
{
	// Rd = SignExtended<s32>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	auto source1Val = static_cast<s32>(source1Reg->read_uword());
	auto source2Val = static_cast<s32>(source2Reg->read_uword());

	s32 result = (source1Val < source2Val) ? 1 : 0;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::SLTI()
{
	// Rd = SignExtended<s32>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto imm = static_cast<s32>(mIOPCoreInstruction.getIImmS());

	auto source1Val = static_cast<s32>(source1Reg->read_uword());

	s32 result = (source1Val < imm) ? 1 : 0;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::SLTIU()
{
	// Rd = SignExtended<uword>((Rs < Imm) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];

	uword source1Val = source1Reg->read_uword();
	uword imm = static_cast<uword>(static_cast<s32>(mIOPCoreInstruction.getIImmS()));

	uword result = (source1Val < imm) ? 1 : 0;

	destReg->write_uword(result);
}

void IOPCoreInterpreter_s::SLTU()
{
	// Rd = SignExtended<uword>((Rs < Rt) ? 1 : 0)
	// No Exceptions generated.
	auto& source1Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rs()];
	auto& source2Reg = mIOPCore->R3000->GPR[mIOPCoreInstruction.rt()];
	auto& destReg = mIOPCore->R3000->GPR[mIOPCoreInstruction.getRRd()];

	uword source1Val = source1Reg->read_uword();
	uword source2Val = source2Reg->read_uword();

	uword result = (source1Val < source2Val) ? 1 : 0;

	destReg->write_uword(result);
}

