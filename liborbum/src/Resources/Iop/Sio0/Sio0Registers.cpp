#include "Resources/Iop/Sio0/Sio0Registers.hpp"

void Sio0Register_Ctrl::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
    auto _lock = scope_lock();
    SizedHwordRegister::byte_bus_write_uhword(context, offset, value);
}

void Sio0Register_Stat::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
    auto _lock = scope_lock();
    SizedHwordRegister::byte_bus_write_uhword(context, offset, value);
}

Sio0Register_Data::Sio0Register_Data() :
    stat(nullptr)
{
}

void Sio0Register_Data::initialize()
{
    command_queue.initialize();
    response_queue.initialize();
}

ubyte Sio0Register_Data::read_ubyte()
{
    ubyte data = response_queue.read_ubyte();

    // Toggle the SIO0 FIFO empty bit.
    auto _lock = stat->scope_lock();
    stat->insert_field(Sio0Register_Stat::RX_NONEMPTY, response_queue.has_read_available(1) ? 1 : 0);

    return data;
}

void Sio0Register_Data::write_ubyte(const ubyte data)
{
    command_queue.write_ubyte(data);

    // Toggle the SIO0 FIFO full bit. Also set unset the TX_RDY2 (ie: transfer not finished bit).
    auto _lock = stat->scope_lock();
    stat->insert_field(Sio0Register_Stat::TX_RDY1, command_queue.has_write_available(1) ? 1 : 0); // TODO: this is not right...
    stat->insert_field(Sio0Register_Stat::TX_RDY2, 0);
}
