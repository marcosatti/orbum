#pragma once

#include <memory>

class IOPCoreR3000_t;
class IOPCoreCOP0_t;
class ByteMemory_t;

class IOPCore_t
{
public:
	explicit IOPCore_t();

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
	std::shared_ptr<ByteMemory_t> ScratchpadMemory;

};

