#include <boost/format.hpp>

#include "Core.hpp"

#include "Resources/Iop/Sio2/Sio2Registers.hpp"

Sio2Register_Ctrl::Sio2Register_Ctrl() :
    direction(Direction::TX),
    started(false),
    transfer_port(0),
    transfer_port_count(0),
	write_latch(false)
{
}

void Sio2Register_Ctrl::write_uword(const uword value)
{
    switch (value & 0xF)
    {
    case 0x1:
    {
        direction = Direction::RX;
        break;
    }
    case 0xC:
    {
        direction = Direction::TX;
        break;
    }
    default:
        throw std::runtime_error(str(boost::format("Unknown SIO2 ctrl value: 0x%08X.") % value));
    }

    SizedWordRegister::write_uword(value & ~0xF);
}

void Sio2Register_Ctrl::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();
	
    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "SIO2 write latch was already set - please check (might be ok)!";

	write_uword(value);

    write_latch = true;
}
