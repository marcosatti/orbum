#include <stdexcept>

#include "Resources/SbusRegisters.hpp"

void SbusRegister_Mscom::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (context == BusContext::Ee)
        write_uword(value);
}

void SbusRegister_Msflg::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (context == BusContext::Ee)
        write_uword(read_uword() | value);
    else if (context == BusContext::Iop)
        write_uword(read_uword() & (~value));
    else
        write_uword(value);
}

void SbusRegister_Smflg::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (context == BusContext::Ee)
        write_uword(read_uword() & (~value));
    else if (context == BusContext::Iop)
        write_uword(read_uword() | value);
    else
        write_uword(value);
}

uhword SbusRegister_F240::byte_bus_read_uhword(const BusContext context, const usize offset)
{
    auto _lock = scope_lock();

    if (context == BusContext::Iop && offset == 0)
        return (read_uhword(offset) | 0x2);
    else
        return read_uhword(offset / NUMBER_BYTES_IN_HWORD);
}

uword SbusRegister_F240::byte_bus_read_uword(const BusContext context, const usize offset)
{
    auto _lock = scope_lock();

    if (context == BusContext::Ee)
        return (read_uword() | 0xF0000102);
    else if (context == BusContext::Iop)
        return (read_uword() | 0xF0000002);
    else
        return read_uword();
}

void SbusRegister_F240::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
    auto _lock = scope_lock();

    if (context == BusContext::Iop && offset == 0)
    {
        uhword temp = value & 0xF0;
        if (value & 0x20 || value & 0x80)
        {
            write_uhword(offset, read_uhword(offset) & (~0xF000));
            write_uhword(offset, read_uhword(offset) | 0x2000);
        }

        if (read_uhword(offset) & temp)
            write_uhword(offset, read_uhword(offset) & (~temp));
        else
            write_uhword(offset, read_uhword(offset) | temp);
    }
    else
    {
        write_uhword(offset / NUMBER_BYTES_IN_HWORD, value);
    }
}

void SbusRegister_F240::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    if (context == BusContext::Ee)
    {
        uword temp = read_uword() & 0xFFFFFEFF;
        temp |= value & 0x100;
        write_uword(temp);
    }
    else if (context == BusContext::Iop)
    {
        uword temp = value & 0xF0;
        if (value & 0x20 || value & 0x80)
        {
            SizedWordRegister::write_uword(read_uword() & (~0xF000));
            write_uword(read_uword() | 0x2000);
        }

        if (read_uword() & temp)
            write_uword(read_uword() & (~temp));
        else
            write_uword(read_uword() | temp);
    }
    else
    {
        write_uword(value);
    }
}

uword SbusRegister_F300::byte_bus_read_uword(const BusContext context, const usize offset)
{
    throw std::runtime_error("SBUS_F300 not implemented.");
}

void SbusRegister_F300::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    throw std::runtime_error("SBUS_F300 not implemented.");
}
