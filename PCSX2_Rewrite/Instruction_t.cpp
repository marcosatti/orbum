#include "stdafx.h"

#include "Globals.h"
#include "Instruction_t.h"

namespace PS2 {
	namespace EE {

		Instruction_t::Instruction_t(u32 instruction)
		{
			this->instruction = instruction;
		}

		u8 Instruction_t::getOpcode()
		{
			return ((u8)(instruction >> 26) & 0x3F);
		}

	} // namespace EE
} // namespace PS2