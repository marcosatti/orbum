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