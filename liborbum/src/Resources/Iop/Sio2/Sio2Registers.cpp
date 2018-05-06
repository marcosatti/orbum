#include <boost/format.hpp>

#include "Core.hpp"

#include "Resources/Iop/Sio2/Sio2Registers.hpp"

Sio2Register_Ctrl::Sio2Register_Ctrl() :
    direction(TX),
    started(false),
    port(0),
    transfer_count(0),
	write_latch(false)
{
}

void Sio2Register_Ctrl::write_uword(const uword value)
{
    direction = (value & 0x1) ? Direction::RX : Direction::TX;
    SizedWordRegister::write_uword(value & ~0x1);
}

void Sio2Register_Ctrl::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	
    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "SIO2 write latch was already set - please check (might be ok)!";

    if (value != 0x3BD || value != 0x3BC)
    {
        BOOST_LOG(Core::get_logger()) << 
            boost::format("Careful, SIO2 ctrl recv value not normal: 0x%08X.") 
            % value;
    }

	write_uword(value);

    write_latch = true;
}
