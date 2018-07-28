#include <boost/format.hpp>

#include "Resources/Iop/Sio2/Sio2Registers.hpp"

#include "Core.hpp"

using Direction = Sio2Register_Ctrl::Direction;

Sio2Register_Ctrl::Sio2Register_Ctrl() :
    transfer_started(false),
    transfer_port(0),
    transfer_port_count(0),
    write_latch(false)
{
}

Direction Sio2Register_Ctrl::get_direction()
{
    auto value = extract_field(DIRECTION);

    switch (value & 0xF)
    {
    case 0x1:
    case 0xD:
        return Direction::RX;
    case 0xC:
        return Direction::TX;
    default:
        throw std::runtime_error(str(boost::format("Unknown SIO2 ctrl value: 0x%08X.") % value));
    }
}

void Sio2Register_Ctrl::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "SIO2 write latch was already set - please check (might be ok)!";

    write_uword(value);

    write_latch = true;
}
