#include "Core.hpp"

#include "Resources/Iop/Sio2/Sio2PortRegisters.hpp"

Sio2PortRegister_Ctrl3::Sio2PortRegister_Ctrl3() :
    write_latch(false),
    port_transfer_started(false)
{
}

void Sio2PortRegister_Ctrl3::byte_bus_write_uword(const BusContext context, const usize offset, const uword value)
{
	auto _lock = scope_lock();

    if (write_latch)
        BOOST_LOG(Core::get_logger()) << "SIO2 CTRL3 write latch was already set - please check (might be ok)!";

	write_uword(value);

    write_latch = true;
}