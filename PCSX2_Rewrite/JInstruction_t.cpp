#include "stdafx.h"

#include "Globals.h"
#include "PS2Types.h"
#include "Instruction_t.h"
#include "JInstruction_t.h"

namespace PS2 {
	namespace EE {

		/*
		Construct an J instruction. See base class Instruction constructor.
		For all function documentation, see the JInstruction_t.h header.
		*/
		JInstruction_t::JInstruction_t(u32 j_instruction) : Instruction_t(j_instruction)
		{
		}

		u32 JInstruction_t::getPAddress()
		{
			return (instruction & 0x03ffffff);
		}

		u32 JInstruction_t::getJumpAddress(Register32 PC)
		{
			u32 address = getPAddress();
			return ((address << 2) + (PC.UW & 0xf0000000));
		}

	} // namespace EE
} // namespace PS2


