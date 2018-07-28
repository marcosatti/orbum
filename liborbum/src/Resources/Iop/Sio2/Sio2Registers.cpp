#include "Resources/Iop/Sio2/Sio2Registers.hpp"

#include "Core.hpp"

Sio2Register_Ctrl::Sio2Register_Ctrl() :
    write_latch(false)
{
}

void Sio2Register_Ctrl::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "SIO2 write latch was already set - please check (might be ok)!";

    write_uword(value);

    write_latch = true;
}

Sio2Register_Data::Sio2Register_Data() :
    data_fifo(nullptr)
{
}

void Sio2Register_Data::initialise()
{
    data_fifo->initialise();
}

ubyte Sio2Register_Data::read_ubyte()
{
    return data_fifo->read_ubyte();
}

void Sio2Register_Data::write_ubyte(const ubyte value)
{
    data_fifo->write_ubyte(value);
}
