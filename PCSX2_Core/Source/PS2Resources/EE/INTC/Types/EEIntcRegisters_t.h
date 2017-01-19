#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

#include "PS2Constants/PS2Constants.h"

/*
The EE INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
Bits are reversed by writing 1 (through EE context).
*/
class EEIntcRegister_MASK_t : public BitfieldRegister32_t
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

	/*
	(EE) Reverses any bits written to.
	*/
	void writeWord(const Context_t& context, u32 value) override;
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

		/*
		Array of IRQ line keys.
		*/
		static constexpr u8 IRQ_KEYS[PS2Constants::EE::INTC::NUMBER_IRQ_LINES] = { GS, SBUS, VBON, VIF0, VIF1, VU0, VU1, IPU, TIM0, TIM1, TIM2, TIM3, SFIFO, VU0WD };
	};

	explicit EEIntcRegister_STAT_t(const std::shared_ptr<EEIntcRegister_MASK_t> & mask);

	/*
	(EE context) Clears any bits written to.
	Sets the internal flag after, if an interrupt should be raised (caches result).
	*/
	void writeWord(const Context_t& context, u32 value) override;

	/*
	Writes to the IRQ line stat bit and sets the internal flag if there should be an interrupt raised (caches result).
	*/
	void raiseIRQLine(const u8 & irqLine);

	/*
	Returns if there is a pending interrupt that should be raised.
	*/
	bool isInterrupted() const;

private:
	/*
	Reference to the associated mask register, needed for checking interrupt status.
	*/
	std::shared_ptr<EEIntcRegister_MASK_t> mMask;

	/*
	Checks for interrupt conditions and sets the mIsInterrupted flag.
	See the formula listed at page 28 of the EE Users Manual.
	*/
	void handleInterruptCheck();

	/*
	See handleInterruptCheck() and isInterrupted() above.
	*/
	bool mIsInterrupted;
};
