#include "Common/Types/FifoQueue/DmaFifoQueue.hpp"

#include "Resources/Cdvd/CdvdRegisters.hpp"

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

CdvdRegister_Ns_Command::CdvdRegister_Ns_Command() :
	write_latch(false)
{
}

void CdvdRegister_Ns_Command::byte_bus_write_ubyte(const BusContext context, const usize offset, const ubyte value)
{
	if (write_latch)
		throw std::runtime_error("Cdvd N/S Command write latch already set");

	write_ubyte(value);
	ns_rdy_din->ready.insert_field(CdvdRegister_Ns_Rdy_Din::READY_BUSY, 1);

	write_latch = true;
}