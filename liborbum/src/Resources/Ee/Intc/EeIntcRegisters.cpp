#include "Resources/Ee/Intc/EeIntcRegisters.hpp"

void EeIntcRegister_Stat::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	
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
