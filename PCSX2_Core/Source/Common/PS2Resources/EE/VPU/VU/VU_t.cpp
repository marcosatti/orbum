#include "stdafx.h"

#include "Common/PS2Resources/EE/VPU/VU/VU_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BusErrorMMemory_t.h"

VU_t::VU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// Memory.
	VU0_MEM_Micro0(std::make_shared<MappedMemory_t>(0x1000, "VU0: VU0Micro0", 0x11000000)),
	VU0_MEM_Mem0(std::make_shared<MappedMemory_t>(0x1000, "VU0: VU0Mem0", 0x11004000)),
	VU1_MEM_Micro1(std::make_shared<MappedMemory_t>(0x4000, "VU1: VU1Micro1", 0x11008000)),
	VU1_MEM_Mem1(std::make_shared<MappedMemory_t>(0x4000, "VU1: VU1Mem1", 0x1100c000)),
	VU1_MEM_BusErr(std::make_shared<BusErrorMMemory_t>(0x4000, "VU1: VU1BusErr", 0x11010000))
{
}
