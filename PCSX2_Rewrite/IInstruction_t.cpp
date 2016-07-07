#include "stdafx.h"

#include "Globals.h"
#include "Register_t.h"
#include "Instruction_t.h"
#include "IInstruction_t.h"

namespace PS2 {
	namespace EE {

		/*
		Construct an I instruction. See base class Instruction constructor.
		For all function documentation, see the IInstruction_t.h header.
		*/
		IInstruction_t::IInstruction_t(u32 i_instruction) : Instruction_t(i_instruction)
		{
		}

		u8 IInstruction_t::getRs()
		{
			return ((u8)(instruction >> 21) & 0x1F);
		}

		u8 IInstruction_t::getRd()
		{
			return ((u8)(instruction >> 16) & 0x1F);
		}

		u16 IInstruction_t::getImmU()
		{
			return ((u16)(instruction) & 0xFFFF);
		}

		s16 IInstruction_t::getImmS()
		{
			return ((s16)(instruction) & 0xFFFF);
		}

		u8 IInstruction_t::getSignBit()
		{
			return ((u8)(instruction >> 15) & 0x1);
		}

		u32 IInstruction_t::getBranchAddress(Register32_t PC)
		{
			s32 IMM32 = (s32)getImmS();
			return (u32)((IMM32 << 2) + PC.UW);
		}

		u16 IInstruction_t::getTrapCode()
		{
			return (u16)((getImmU() >> 6) & 0x3FF);
		}

	} // namespace EE
} // namespace PS2
