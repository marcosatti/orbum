#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/ClrBitfieldRegister32_t.h"
#include "Common/Types/Registers/RevBitfieldRegister32_t.h"

/*
The INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
Bits are cleared by writing 1.
*/
class EEIntcRegister_STAT_t : public ClrBitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 GS = 0;
		static constexpr u8 SBUS = 1;
		static constexpr u8 VBON = 2;
		static constexpr u8 VBOF = 3;
		static constexpr u8 VIF0 = 4;
		static constexpr u8 VIF1 = 5;
		static constexpr u8 VU0 = 6;
		static constexpr u8 VU1 = 7;
		static constexpr u8 IPU = 8;
		static constexpr u8 TIM0 = 9;
		static constexpr u8 TIM1 = 10;
		static constexpr u8 TIM2 = 11;
		static constexpr u8 TIM3 = 12;
		static constexpr u8 SFIFO = 13;
		static constexpr u8 VU0WD = 14;
	};

	EEIntcRegister_STAT_t();
};

/*
The INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Bits are reversed by writing 1.
*/
class EEIntcRegister_MASK_t : public RevBitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr u8 GS = 0;
		static constexpr u8 SBUS = 1;
		static constexpr u8 VBON = 2;
		static constexpr u8 VBOF = 3;
		static constexpr u8 VIF0 = 4;
		static constexpr u8 VIF1 = 5;
		static constexpr u8 VU0 = 6;
		static constexpr u8 VU1 = 7;
		static constexpr u8 IPU = 8;
		static constexpr u8 TIM0 = 9;
		static constexpr u8 TIM1 = 10;
		static constexpr u8 TIM2 = 11;
		static constexpr u8 TIM3 = 12;
		static constexpr u8 SFIFO = 13;
		static constexpr u8 VU0WD = 14;
	};

	EEIntcRegister_MASK_t();
};


