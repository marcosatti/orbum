#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/IOP/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCOP0/IOPCOP0_t.h"
#include "Common/PS2Resources/IOP/IOPExceptions/IOPExceptions_t.h"

IOP_t::IOP_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	R3000(std::make_shared<R3000_t>(getRootResources())),
	COP0(std::make_shared<IOPCOP0_t>(getRootResources())),
	Exceptions(std::make_shared<IOPExceptions_t>(getRootResources())),
	IOPMemory(std::make_shared<MappedMemory_t>(PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, "IOP Memory", PS2Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY))
{
}
