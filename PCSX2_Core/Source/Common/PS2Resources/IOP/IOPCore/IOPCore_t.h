#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class R3000_t;
class IOPCoreCOP0_t;
class IOPCoreExceptions_t;
class DebugMMemory_t;

class IOPCore_t : public PS2ResourcesSubobject
{
public:
	explicit IOPCore_t(const PS2Resources_t *const PS2Resources);

	/*
	The R3000 CPU.
	*/
	std::shared_ptr<R3000_t> R3000;

	/*
	COP0 coprocessor.
	*/
	std::shared_ptr<IOPCoreCOP0_t> COP0;

	/*
	Exception/Interrupt State.
	*/
	std::shared_ptr<IOPCoreExceptions_t> Exceptions;

	/*
	Scratchpad memory (1KB). Allocated at 0x1F000000.
	*/
	std::shared_ptr<DebugMMemory_t> ScratchpadMemory;

};

