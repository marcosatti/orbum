#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class MappedMemory_t;
class BusErrorMMemory_t;

class VU_t : public PS2ResourcesSubobject
{
public:
	explicit VU_t(const PS2Resources_t *const PS2Resources);

	/*
	VU memory, defined on page 25 of the EE Users Manual. 
	*/
	// 0x110000000
	std::shared_ptr<MappedMemory_t>    VU0_MEM_Micro0;
	std::shared_ptr<MappedMemory_t>    VU0_MEM_Mem0;

	// 0x11008000
	std::shared_ptr<MappedMemory_t>    VU1_MEM_Micro1;
	std::shared_ptr<MappedMemory_t>    VU1_MEM_Mem1;
	std::shared_ptr<BusErrorMMemory_t> VU1_MEM_BusErr;
};

