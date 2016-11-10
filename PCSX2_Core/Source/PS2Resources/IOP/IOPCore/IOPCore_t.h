#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class IOPCoreR3000_t;
class IOPCoreCOP0_t;
class IOPCoreExceptions_t;
class Memory_t;

class IOPCore_t : public PS2ResourcesSubobject
{
public:
	explicit IOPCore_t(const PS2Resources_t *const PS2Resources);

	/*
	The R3000 CPU.
	*/
	std::shared_ptr<IOPCoreR3000_t> R3000;

	/*
	COP0 coprocessor.
	*/
	std::shared_ptr<IOPCoreCOP0_t> COP0;

	/*
	Exception/Interrupt State.
	*/
	std::shared_ptr<IOPCoreExceptions_t> Exceptions;

	/*
	Scratchpad memory (1KB). Allocated at 0x1F800000.
	*/
	std::shared_ptr<Memory_t> ScratchpadMemory;

};

