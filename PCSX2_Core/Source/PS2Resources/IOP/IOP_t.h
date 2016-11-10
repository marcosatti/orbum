#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class IOPCore_t;
class Memory_t;
class DebugMemory_t;
class PhysicalMMU_t;

class IOP_t : public PS2ResourcesSubobject
{
public:
	explicit IOP_t(const PS2Resources_t *const PS2Resources);

	/*
	The IOP core
	*/
	std::shared_ptr<IOPCore_t> IOPCore;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;

	/*
	IOP Main Memory (2MB). Allocated at 0x00000000.
	*/
	std::shared_ptr<Memory_t> MainMemory;

	/*
	IOP Parallel Port IO (?, 64KB). Allocated at 0x1F000000.
	*/
	std::shared_ptr<Memory_t> ParallelPort;

	/*
	HW mapped registers (64KB or 8KB?). Allocated at 0x1F801000.
	DEBUG
	*/
	std::shared_ptr<Memory_t> IOP_HW_REGISTERS;


};
