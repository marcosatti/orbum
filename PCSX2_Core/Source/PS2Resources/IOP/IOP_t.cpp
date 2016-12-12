#include "stdafx.h"

#include <memory>

#include "Common/Global/Globals.h"
#include "PS2Constants/PS2Constants.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/CDVD/CDVD_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"

#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Memory/DebugMemory_t.h"
#include "PS2Resources/PS2Resources_t.h"

IOP_t::IOP_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	IOPCore(std::make_shared<IOPCore_t>(getRoot())),
	CDVD(std::make_shared<CDVD_t>(getRoot())),
	Timers(std::make_shared<IOPTimers_t>(getRoot())),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_4GB, Constants::SIZE_8KB, 1)),
	MainMemory(std::make_shared<Memory_t>(PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, "IOP Memory")),
	ParallelPort(std::make_shared<DebugMemory_t>(PS2Constants::IOP::ParallelPort::SIZE_PARALLEL_PORT, "IOP Parallel Port"))
{
}
