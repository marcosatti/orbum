#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"

class IOPCoreR3000_t;
class IOPCoreCOP0_t;
class Memory_t;

class IOPCore_t : public PS2ResourcesSubcategory
{
public:
	explicit IOPCore_t(const PS2Resources_t * PS2Resources);

	/*
	The R3000 CPU.
	*/
	std::shared_ptr<IOPCoreR3000_t> R3000;

	/*
	COP0 coprocessor.
	*/
	std::shared_ptr<IOPCoreCOP0_t> COP0;

	/*
	Scratchpad memory (1KB). Allocated at 0x1F800000.
	*/
	std::shared_ptr<Memory_t> ScratchpadMemory;

};

