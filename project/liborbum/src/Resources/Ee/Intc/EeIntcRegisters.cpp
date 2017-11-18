#include "Resources/Ee/Intc/EeIntcRegisters.hpp"

constexpr Bitfield EeIntcRegister_Stat::IRQ_KEYS[Constants::EE::INTC::NUMBER_IRQ_LINES];
constexpr Bitfield EeIntcRegister_Stat::VIF_KEYS[Constants::EE::VPU::VIF::NUMBER_VIF_CORES];
constexpr Bitfield EeIntcRegister_Stat::VU_KEYS[Constants::EE::VPU::VU::NUMBER_VU_CORES];
constexpr Bitfield EeIntcRegister_Stat::TIM_KEYS[Constants::EE::Timers::NUMBER_TIMERS];

void EeIntcRegister_Stat::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	uword temp = value;
	if (context == BusContext::Ee)
		temp = read_uword() & (~value);
		
	SizedWordRegister::write_uword(temp);
}

void EeIntcRegister_Mask::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	if (context == BusContext::Ee)
		SizedWordRegister::write_uword(read_uword() ^ value);
	else
		SizedWordRegister::write_uword(value);
}
