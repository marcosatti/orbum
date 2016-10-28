#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/IOP/IOP_t.h"
#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DebugMMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ImageMappedMemory_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"

IOP_t::IOP_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	IOPCore(std::make_shared<IOPCore_t>(getRootResources())),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_4GB, Constants::SIZE_4MB, Constants::SIZE_16B)),
	MainMemory(std::make_shared<MappedMemory_t>(PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, "IOP Memory", PS2Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY)),
	ParallelPort(std::make_shared<DebugMMemory_t>(PS2Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT, "IOP Parallel Port", PS2Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT)),
	IOP_HW_REGISTERS(std::make_shared<DebugMMemory_t>(0x2000, "IOP HW Memory", 0x1F801000))
{
}
