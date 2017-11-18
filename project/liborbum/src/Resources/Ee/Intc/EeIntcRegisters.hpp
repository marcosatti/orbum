#pragma once

#include "Common/Constants.hpp"
#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Register/SizedWordRegister.hpp"

/// The EE INTC I_MASK register, which holds a set of flags determining if the interrupt source is masked.
/// Bits are reversed by writing 1 (through EE context).
class EeIntcRegister_Mask : public SizedWordRegister
{
public:
	static constexpr Bitfield GS = Bitfield(0, 1);
	static constexpr Bitfield SBUS = Bitfield(1, 1);
	static constexpr Bitfield VBON = Bitfield(2, 1);
	static constexpr Bitfield VBOF = Bitfield(3, 1);
	static constexpr Bitfield VIF0 = Bitfield(4, 1);
	static constexpr Bitfield VIF1 = Bitfield(5, 1);
	static constexpr Bitfield VU0 = Bitfield(6, 1);
	static constexpr Bitfield VU1 = Bitfield(7, 1);
	static constexpr Bitfield IPU = Bitfield(8, 1);
	static constexpr Bitfield TIM0 = Bitfield(9, 1);
	static constexpr Bitfield TIM1 = Bitfield(10, 1);
	static constexpr Bitfield TIM2 = Bitfield(11, 1);
	static constexpr Bitfield TIM3 = Bitfield(12, 1);
	static constexpr Bitfield SFIFO = Bitfield(13, 1);
	static constexpr Bitfield VU0WD = Bitfield(14, 1);

	/// (EE) Reverses any bits written to.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};

/// The EE INTC I_STAT register, which holds a set of flags determining if a component caused an interrupt.
/// Bits are cleared by writing 1 (through EE context).
class EeIntcRegister_Stat : public SizedWordRegister
{
public:
	static constexpr Bitfield GS = Bitfield(0, 1);
	static constexpr Bitfield SBUS = Bitfield(1, 1);
	static constexpr Bitfield VBON = Bitfield(2, 1);
	static constexpr Bitfield VBOF = Bitfield(3, 1);
	static constexpr Bitfield VIF0 = Bitfield(4, 1);
	static constexpr Bitfield VIF1 = Bitfield(5, 1);
	static constexpr Bitfield VU0 = Bitfield(6, 1);
	static constexpr Bitfield VU1 = Bitfield(7, 1);
	static constexpr Bitfield IPU = Bitfield(8, 1);
	static constexpr Bitfield TIM0 = Bitfield(9, 1);
	static constexpr Bitfield TIM1 = Bitfield(10, 1);
	static constexpr Bitfield TIM2 = Bitfield(11, 1);
	static constexpr Bitfield TIM3 = Bitfield(12, 1);
	static constexpr Bitfield SFIFO = Bitfield(13, 1);
	static constexpr Bitfield VU0WD = Bitfield(14, 1);

	static constexpr Bitfield IRQ_KEYS[Constants::EE::INTC::NUMBER_IRQ_LINES] = { GS, SBUS, VBON, VBOF, VIF0, VIF1, VU0, VU1, IPU, TIM0, TIM1, TIM2, TIM3, SFIFO, VU0WD };
	static constexpr Bitfield VIF_KEYS[Constants::EE::VPU::VIF::NUMBER_VIF_CORES] = { VIF0, VIF1 };
	static constexpr Bitfield VU_KEYS[Constants::EE::VPU::VU::NUMBER_VU_CORES] = { VU0, VU1 };
	static constexpr Bitfield TIM_KEYS[Constants::EE::Timers::NUMBER_TIMERS] = { TIM0, TIM1, TIM2, TIM3 };

	/// (EE context) Clears any bits written to.
	void byte_bus_write_uword(const BusContext context, const usize offset, const uword value) override;
};
