#include "Resources/Iop/Intc/IopIntcRegisters.hpp"

uword IopIntcRegister_Ctrl::byte_bus_read_uword(const BusContext context, const usize offset)
{
    auto temp = SizedWordRegister::read_uword();

    if (context == BusContext::Iop)
        write_uword(0);

    return temp;
}

void IopIntcRegister_Stat::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
    auto _lock = scope_lock();

    uword temp = value;

    // Preprocessing for IOP: AND with old value (acknowledge bits).
    if (context == BusContext::Iop)
        temp = read_uword() & value;

    write_uword(temp);
}
