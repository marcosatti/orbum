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