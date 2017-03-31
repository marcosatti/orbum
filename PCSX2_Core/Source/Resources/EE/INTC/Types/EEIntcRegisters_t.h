#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
The EE INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Bits are reversed by writing 1 (through EE context).
*/
class EEIntcRegister_MASK_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int GS = 0;
		static constexpr int SBUS = 1;
		static constexpr int VBON = 2;
		static constexpr int VBOF = 3;
		static constexpr int VIF0 = 4;
		static constexpr int VIF1 = 5;
		static constexpr int VU0 = 6;
		static constexpr int VU1 = 7;
		static constexpr int IPU = 8;
		static constexpr int TIM0 = 9;
		static constexpr int TIM1 = 10;
		static constexpr int TIM2 = 11;
		static constexpr int TIM3 = 12;
		static constexpr int SFIFO = 13;
		static constexpr int VU0WD = 14;
	};

	EEIntcRegister_MASK_t();

	/*
	(EE) Reverses any bits written to.
	*/
	void writeWord(const Context_t context, u32 value) override;
};

/*
The EE INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
Bits are cleared by writing 1 (through EE context).
*/
class EEIntcRegister_STAT_t : public BitfieldRegister32_t
{
public:
	struct Fields
	{
		static constexpr int GS = 0;
		static constexpr int SBUS = 1;
		static constexpr int VBON = 2;
		static constexpr int VBOF = 3;
		static constexpr int VIF0 = 4;
		static constexpr int VIF1 = 5;
		static constexpr int VU0 = 6;
		static constexpr int VU1 = 7;
		static constexpr int IPU = 8;
		static constexpr int TIM0 = 9;
		static constexpr int TIM1 = 10;
		static constexpr int TIM2 = 11;
		static constexpr int TIM3 = 12;
		static constexpr int SFIFO = 13;
		static constexpr int VU0WD = 14;

		static constexpr int IRQ_KEYS[Constants::EE::INTC::NUMBER_IRQ_LINES] = { GS, SBUS, VBON, VBOF, VIF0, VIF1, VU0, VU1, IPU, TIM0, TIM1, TIM2, TIM3, SFIFO, VU0WD };
		static constexpr int VIF_KEYS[Constants::EE::VPU::VIF::NUMBER_VIF_CORES] = { VIF0, VIF1 };
		static constexpr int VU_KEYS[Constants::EE::VPU::VU::NUMBER_VU_CORES] = { VU0, VU1 };
		static constexpr int TIM_KEYS[Constants::EE::Timers::NUMBER_TIMERS] = { TIM0, TIM1, TIM2, TIM3 };
	};

	explicit EEIntcRegister_STAT_t(const std::shared_ptr<EEIntcRegister_MASK_t> & mask);

	/*
	(EE context) Clears any bits written to.
	Sets the internal flag after, if an interrupt should be raised (caches result).
	*/
	void writeWord(const Context_t context, u32 value) override;
};
