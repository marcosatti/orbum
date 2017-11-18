#include "Common/Types/FifoQueue/SpscFifoQueue.hpp"

#include "Resources/Cdvd/CdvdRegisters.hpp"

CdvdRegister_Ns_Command::CdvdRegister_Ns_Command() :
	write_latch(false)
{
}

void CdvdRegister_Ns_Command::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	auto _lock = scope_lock();

	if (write_latch)
		throw std::runtime_error("CdvdRegister_Ns_Command already had write_latch set... Oops!");

	write_latch = true;
	SizedByteRegister::write_ubyte(value);
}


CdvdRegister_Ns_Rdy_Din::CdvdRegister_Ns_Rdy_Din(const size_t size) :
	data_in(size)
{
}

void CdvdRegister_Ns_Rdy_Din::initialise()
{
	ready.initialise();
	data_in.initialise();
}

ubyte CdvdRegister_Ns_Rdy_Din::read_ubyte()
{		
	return ready.read_ubyte();
}

void CdvdRegister_Ns_Rdy_Din::write_ubyte(const ubyte value)
{
	data_in.write_ubyte(value);
}

usize CdvdRegister_Ns_Rdy_Din::byte_bus_map_size() const
{
	return static_cast<usize>(NUMBER_BYTES_IN_WORD);
}