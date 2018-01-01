#include "Resources/Spu2/Spu2CoreRegisters.hpp"

Spu2CoreRegister_Attr::Spu2CoreRegister_Attr() :
	dma_offset(0)
{
}

void Spu2CoreRegister_Attr::byte_bus_write_uhword(const BusContext context, const usize offset, const uhword value)
{
	auto _lock = scope_lock();

	if (context == BusContext::Iop)
	{
		// Reset DMA context parameters.
		dma_offset = 0;
	}

	write_uhword(value);
}

Spu2CoreRegister_Admas::Spu2CoreRegister_Admas() :
	core_id(nullptr)
{
}

void Spu2CoreRegister_Admas::set_adma_running(const bool running)
{
	if (running)
		write_uhword(read_uhword() & 0x3);
	else 
		write_uhword(read_uhword() | (~0x3));
}

bool Spu2CoreRegister_Admas::is_adma_enabled()
{
	return (read_uhword() & (1 << *core_id)) > 0;
}