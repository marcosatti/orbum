#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/IOP/IOPCore/R3000/R3000_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreCOP0/IOPCoreCOP0_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCoreExceptions/IOPCoreExceptions_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DebugMMemory_t.h"


IOPCore_t::IOPCore_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	R3000(std::make_shared<R3000_t>(getRootResources())),
	COP0(std::make_shared<IOPCoreCOP0_t>(getRootResources())),
	Exceptions(std::make_shared<IOPCoreExceptions_t>(getRootResources())),
	ScratchpadMemory(std::make_shared<DebugMMemory_t>(PS2Constants::IOP::IOPCore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "IOP Core Scratchpad Memory", PS2Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY))
{
}
