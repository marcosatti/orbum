#include <bitset>


#include "Common/Types/Register/SizedQwordRegister.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

#include "VM/Systems/EE/EECoreInterpreter/EECoreInterpreter_s.h"

#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreR5900.hpp"

void EECoreInterpreter_s::DSRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	destReg->write_udword(0, static_cast<s64>(source1Reg->read_udword(0)) >> shamt);
}

void EECoreInterpreter_s::DSLL()
{
	// Rd = Rt << shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	destReg->write_udword(0, source1Reg->read_udword(0) << shamt);
}

void EECoreInterpreter_s::DSLL32()
{
	// Rd = Rt << shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() + 32;

	destReg->write_udword(0, source1Reg->read_udword(0) << shamt);
}

void EECoreInterpreter_s::DSLLV()
{
	// Rd = Rt << Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x3F;

	destReg->write_udword(0, source1Reg->read_udword(0) << shamt);
}

void EECoreInterpreter_s::DSRA32()
{
	// Rd = Rt >> shamt(32->61). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() + 32;

	destReg->write_udword(0, static_cast<s64>(source1Reg->read_udword(0)) >> shamt);
}

void EECoreInterpreter_s::DSRAV()
{
	// Rd = Rt >> Rs (lowest 6 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x3F;

	destReg->write_udword(0, static_cast<s64>(source1Reg->read_udword(0)) >> shamt);
}

void EECoreInterpreter_s::DSRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	destReg->write_udword(0, source1Reg->read_udword(0) >> shamt);
}

void EECoreInterpreter_s::DSRL32()
{
	// Rd = Rt >> shamt(32->63). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() + 32;

	destReg->write_udword(0, source1Reg->read_udword(0) >> shamt);
}

void EECoreInterpreter_s::DSRLV()
{
	// Rd = Rt >> Rs (lowest 6 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x3F;

	destReg->write_udword(0, source1Reg->read_udword(0) >> shamt);
}

void EECoreInterpreter_s::SLL()
{
	// Rd = SignExtend<s64>(Rt << shamt(0->31)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0) << shamt));
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SLLV()
{
	// Rd = SignExtend<s64>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0) << shamt));
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SRA()
{
	// Rd = Rt >> shamt(0->31). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0)) >> shamt);
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SRAV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0)) >> shamt);
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SRL()
{
	// Rd = Rt >> shamt(0->31). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0) >> shamt));
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::SRLV()
{
	// Rd = Rt >> Rs (lowest 5 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = source2Reg->read_ubyte(0) & 0x1F;

	s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(0) >> shamt));
	destReg->write_udword(0, result);
}

void EECoreInterpreter_s::PSLLH()
{
	// Rd = Rt << shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() & 0xF;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->write_uhword(i, source1Reg->read_uhword(i) << shamt);
	}
}

void EECoreInterpreter_s::PSLLVW()
{
	// Rd = SignExtend<s64>(Rt << Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	
	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		ubyte shamt = source2Reg->read_uword(i) & 0x1F;
		s64 result = static_cast<s64>(source1Reg->read_uword(i) << shamt);
		destReg->write_udword(i / 2, result);
	}
}

void EECoreInterpreter_s::PSLLW()
{
	// Rd = Rt << shamt. Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->write_uword(i, source1Reg->read_uword(i) << shamt);
	}
}

void EECoreInterpreter_s::PSRAH()
{
	// Rd = Rt >> shamt(lowest 4 bits). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() & 0xF;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->write_uhword(i, static_cast<s16>(source1Reg->read_uhword(i)) >> shamt);
	}
}

void EECoreInterpreter_s::PSRAVW()
{
	// Rd = SignExtend<s64>(Rt >> Rs (lowest 5 bits)). Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		ubyte shamt = source2Reg->read_uword(i) & 0x1F;
		s64 result = static_cast<s64>(static_cast<s32>(source1Reg->read_uword(i)) >> shamt);
		destReg->write_udword(i / 2, result);
	}
}

void EECoreInterpreter_s::PSRAW()
{
	// Rd = Rt >> shamt. Arithmetic shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->write_uword(i, static_cast<s32>(source1Reg->read_uword(i)) >> shamt);
	}
}

void EECoreInterpreter_s::PSRLH()
{
	// Rd = Rt >> shamt(lowest 4 bits). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt() & 0xF;

	for (auto i = 0; i < NUMBER_HWORDS_IN_QWORD; i++)
	{
		destReg->write_uhword(i, source1Reg->read_uhword(i) >> shamt);
	}
}

void EECoreInterpreter_s::PSRLVW()
{
	// Rd = SignExtend<s64>(Rt >> Rs (lowest 5 bits)). Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i += 2)
	{
		ubyte shamt = source2Reg->read_uword(i) & 0x1F;
		s64 result = static_cast<s64>(source1Reg->read_uword(i) >> shamt);
		destReg->write_udword(i / 2, result);
	}
}

void EECoreInterpreter_s::PSRLW()
{
	// Rd = Rt >> shamt. Logical shift.
	// No Exceptions generated.
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	ubyte shamt = mEECoreInstruction.shamt();

	for (auto i = 0; i < NUMBER_WORDS_IN_QWORD; i++)
	{
		destReg->write_uword(i, source1Reg->read_uword(i) >> shamt);
	}
}

void EECoreInterpreter_s::QFSRV()
{
	// Rd (lower 128-bits) = (Rs || Rt)(256-bit concatenation) >> SA. Logical shift? Not specified, but assumed to be.
	// No Exceptions generated.
	// TODO: check this instruction... were they high when they created this???
	auto& source1Reg = mEECore->R5900->GPR[mEECoreInstruction.rt()];
	auto& source2Reg = mEECore->R5900->GPR[mEECoreInstruction.rs()];
	auto& destReg = mEECore->R5900->GPR[mEECoreInstruction.getRRd()];
	auto& SAReg = mEECore->R5900->SA;

	uword shamt = SAReg->read_uword(); // From the docs it must be a multiple of bytes or halfwords, as you use the MTSAB or MTSAH instructions to write to the SA register.

	// Can use the STL class "bitset" to perform what we need... MUCH more cleaner than the old PCSX2 code.
	// This forms our 256-bit 'type' from 4 x 64-bits.
	std::bitset<256> result;
	(result |= source1Reg->read_udword(0)) <<= 64;
	(result |= source1Reg->read_udword(1)) <<= 64;
	(result |= source2Reg->read_udword(0)) <<= 64;
	(result |= source2Reg->read_udword(1));

	// Perform the right shift.
	result >>= shamt;

	// Extract the low-order 128-bit result value, 64-bits at a time (unsigned long long, guaranteed to be at least 64-bits), as that is the largest integral size available to the compiler. 
	// Store the extracted value into the destination register. Also need to create a temp bitset to store 64-bits into at one time. N must be the same size as the other bitset otherwise 
	// an error is thrown, but the extra bits are never used.
	for (auto i = 0; i < NUMBER_DWORDS_IN_QWORD; i++)
	{
		std::bitset<256> temp64; 
		temp64 = result >> (64 * i);
		temp64 &= Constants::VALUE_udword_MAX;
		udword resultInt = temp64.to_ullong();
		destReg->write_udword(i, resultInt);
	}
}