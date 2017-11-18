#include <stdexcept>

#include "Resources/Iop/Sio2/Sio2Registers.hpp"

Sio2Register_Ctrl::Sio2Register_Ctrl() :
	write_latch(false)
{
}

void Sio2Register_Ctrl::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	
	if (write_latch)
		throw std::runtime_error("Sio2 write latch already set!");

	write_latch = true;
	
	write_uword(value);
}