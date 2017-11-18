#include "Resources/Iop/Intc/IopIntcRegisters.hpp"

constexpr Bitfield IopIntcRegister_Stat::IRQ_KEYS[Constants::IOP::INTC::NUMBER_IRQ_LINES];
constexpr Bitfield IopIntcRegister_Stat::TMR_KEYS[Constants::IOP::Timers::NUMBER_TIMERS];

uword IopIntcRegister_Ctrl::byte_bus_read_uword(const BusContext context, const usize offset)
{
	auto temp = SizedWordRegister::read_uword();

	if (context == BusContext::Iop)
		write_uword(0);

	return temp;
}

void IopIntcRegister_Stat::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	uword temp = value;

	// Preprocessing for IOP: AND with old value (acknowledge bits).
	if (context == BusContext::Iop)
		temp = read_uword() & value;

	write_uword(temp);
}
