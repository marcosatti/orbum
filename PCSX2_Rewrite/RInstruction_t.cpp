#include "stdafx.h"

#include "Globals.h"
#include "PS2Types.h"
#include "Instruction_t.h"
#include "RInstruction_t.h"

namespace PS2 {
	namespace EE {

		/*
		Construct an R instruction. See base class Instruction constructor.
		For all function documentation, see the RInstruction_t.h header.
		*/
		RInstruction_t::RInstruction_t(u32 r_instruction) : Instruction_t(r_instruction)
		{
		}

		u8 RInstruction_t::getRs()
		{
			return ((u8)(instruction >> 21) & 0x1F);
		}

		u8 RInstruction_t::getRt()
		{
			return ((u8)(instruction >> 16) & 0x1F);
		}

		u8 RInstruction_t::getRd()
		{
			return ((u8)(instruction >> 11) & 0x1F);
		}

		u8 RInstruction_t::getShamt()
		{
			return ((u8)(instruction >> 6) & 0x1F);
		}

		u8 RInstruction_t::getFunct()
		{
			return ((u8)(instruction) & 0x3F);
		}

	} // namespace EE
} // namespace PS2
