
#include "Common/Types/Register/SizedQwordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::DIV()
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SW])
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<s32>(source1Reg->read_uword(0));
	auto source2Val = static_cast<s32>(source2Reg->read_uword(0));

	// Check for VALUE_S32_MIN / -1 (special condition).
	if (source1Val == Constants::VALUE_S32_MIN &&
		source2Val == -1)
	{
		LO->write_udword(0, static_cast<s64>(Constants::VALUE_S32_MIN));
		HI->write_udword(0, static_cast<s64>(0));
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
		LO->write_udword(0, static_cast<s64>(resultQ));

		// Remainder.
		HI->write_udword(0, static_cast<s64>(resultR));
	}
}

void EECoreInterpreter_s::DIV1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIV();
}

void EECoreInterpreter_s::DIVU()
{
	// (LO, HI) = SignExtend<udword>(Rs[UW] / Rt[UW])
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<uword>(source1Reg->read_uword(0));
	auto source2Val = static_cast<uword>(source2Reg->read_uword(0));

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
		mEECore->R5900->LO->write_udword(0, static_cast<s64>(static_cast<s32>(resultQ)));

		// Remainder.
		mEECore->R5900->HI->write_udword(0, static_cast<s64>(static_cast<s32>(resultR)));
	}
}

void EECoreInterpreter_s::DIVU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	DIVU();
}

void EECoreInterpreter_s::MULT()
{
	// (Rd, LO, HI) = SignExtend<s64>(Rs[SW] * Rt[SW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0)));
	auto source2Val = static_cast<s64>(static_cast<s32>(source2Reg->read_uword(0)));

	s64 result = source1Val * source2Val;

	destReg->write_udword(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	LO->write_udword(0, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
	HI->write_udword(0, static_cast<s64>(static_cast<s32>(result >> 32)));
}

void EECoreInterpreter_s::MULT1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULT();
}

void EECoreInterpreter_s::MULTU()
{
	// (Rd, LO, HI) = SignExtend<s64>(Rs[UW] * Rt[UW])
	// LO = Lower 32 bits, HI = Higher 32 bits. No Exceptions generated.
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source1Val = static_cast<udword>(source1Reg->read_uword(0));
	auto source2Val = static_cast<udword>(source2Reg->read_uword(0));

	udword result = source1Val * source2Val;

	destReg->write_udword(0, static_cast<udword>(static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF))));
	LO->write_udword(0, static_cast<udword>(static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF))));
	HI->write_udword(0, static_cast<udword>(static_cast<s64>(static_cast<s32>(result >> 32))));
}

void EECoreInterpreter_s::MULTU1()
{
	// Pipeline 1 instruction - delegate to normal instruction.
	MULTU();
}

void EECoreInterpreter_s::PDIVBW()
{
	// (LO, HI) = SignExtend<s64>(Rs[SW] / Rt[SH,0]) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated, but special condition for VALUE_S32_MIN / -1.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	auto source2Val = static_cast<s16>(source2Reg->read_uhword(0)); // Constant.

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Val == Constants::VALUE_S32_MIN &&
			source2Val == -1)
		{
			LO->write_uword(i, static_cast<s32>(Constants::VALUE_S32_MIN));
			HI->write_uword(i, static_cast<s32>(0));
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
			LO->write_uword(i, resultQ);

			// Remainder.
			HI->write_uword(i, resultR);
		}
	}
}

void EECoreInterpreter_s::PDIVUW()
{
	// (LO, HI)(0,1) = SignExtend<udword>(Rs[UW](0,2) / Rt[UW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<uword>(source1Reg->read_uword(i));
		auto source2Val = static_cast<uword>(source2Reg->read_uword(i));

		// Check for divide by 0, in which case result is undefined (do nothing).
		if (source2Val == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to -1).
		}
		// Else perform normal operation.
		else
		{
			udword resultQ = source1Val / source2Val;
			udword resultR = source1Val % source2Val;

			// Quotient.
			LO->write_udword(i / 2, resultQ);

			// Remainder.
			HI->write_udword(i / 2, resultR);
		}
	}
}

void EECoreInterpreter_s::PDIVW()
{
	// (LO, HI)(0,1) = SignExtend<s64>(Rs[SW](0,2) / Rt[SW](0,2)) Parallel.
	// LO = Quotient, HI = Remainder. No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<uword>(source1Reg->read_uword(i));
		auto source2Val = static_cast<uword>(source2Reg->read_uword(i));

		// Check for VALUE_S32_MIN / -1 (special condition).
		if (source1Val == Constants::VALUE_S32_MIN &&
			source2Val == -1)
		{
			LO->write_udword(i / 2, static_cast<s64>(Constants::VALUE_S32_MIN));
			HI->write_udword(i / 2, static_cast<s64>(0));
		}
		// Check for divide by 0, in which case result is undefined (do nothing).
		else if (source2Val == 0)
		{
			// TODO: check if old PCSX2 code is required (sets HI to the dividend and LO to 1 or -1 depending on if divisor is positive or negative).
		}
		// Else perform normal operation.
		else
		{
			udword resultQ = source1Val / source2Val;
			udword resultR = source1Val % source2Val;

			// Quotient.
			LO->write_udword(i / 2, resultQ);

			// Remainder.
			HI->write_udword(i / 2, resultR);
		}
	}
}

void EECoreInterpreter_s::PMULTH()
{
	// (LO, HI, Rd) = SignExtend<s32>(Rs[SH] * Rt[SH]) (varying indexes - see EE Core Instruction Manual page 246).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()]; // "A"
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()]; // "B"
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		auto source1Val = static_cast<s16>(source1Reg->read_uhword(i));
		auto source2Val = static_cast<s16>(source2Reg->read_uhword(i));
		s32 result = source1Val * source2Val;

		if (i % 2 == 0)
			destReg->write_uword(i / 2, result); // Write to Rd for even indexes. A0xB0, A2xB2, A4xB4, A6xB6.

		if ((i / 2) % 2 == 0)
			LO->write_uword(((i / 2 > 0) ? i - 2 : i), result); // A0xB0, A1xB1, A4xB4, A5xB5. Array ternary operator is to select the correct index from 0 -> 3.
		else
			HI->write_uword(((i / 2 > 1) ? i - 4 : i - 2), result); // A2xB2, A3xB3, A6xB6, A7xB7. Array ternary operator is to select the correct index from 0 -> 3.
	}
}

void EECoreInterpreter_s::PMULTUW()
{
	// (LO, HI, Rd) = SignExtend<udword>(Rs[UW] * Rt[UW]) (varying indexes - see EE Core Instruction Manual page 248).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<uword>(source1Reg->read_uword(i));
		auto source2Val = static_cast<uword>(source2Reg->read_uword(i));
		udword result = source1Val * source2Val;

		LO->write_udword(i / 2, static_cast<udword>(static_cast<uword>(result & 0xFFFFFFFF)));
		HI->write_udword(i / 2, static_cast<udword>(static_cast<uword>(result >> 32)));
		destReg->write_udword(i / 2, result);
	}
}

void EECoreInterpreter_s::PMULTW()
{
	// (LO, HI, Rd) = SignExtend<s64>(Rs[SW] * Rt[SW]) (varying indexes - see EE Core Instruction Manual page 250).
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& LO = mEECore->R5900->LO;
	auto& HI = mEECore->R5900->HI;

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		auto source1Val = static_cast<s32>(source1Reg->read_uword(i));
		auto source2Val = static_cast<s32>(source2Reg->read_uword(i));
		s64 result = source1Val * source2Val;

		LO->write_udword(i / 2, static_cast<s64>(static_cast<s32>(result & 0xFFFFFFFF)));
		HI->write_udword(i / 2, static_cast<s64>(static_cast<s32>(result >> 32)));
		destReg->write_udword(i / 2, result);
	}
}