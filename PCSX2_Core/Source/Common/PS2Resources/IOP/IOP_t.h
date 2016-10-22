#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class IOPCore_t;
class MappedMemory_t;
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
	IOP Memory (2MB).
	*/
	std::shared_ptr<MappedMemory_t> IOPMemory;

	/*
	HW mapped registers (64KB)
	DEBUG
	*/
	std::shared_ptr<MappedMemory_t> IOP_HW_Registers;

	/*
	The IOP physical memory space.
	*/
	std::shared_ptr<PhysicalMMU_t> PhysicalMMU;

};
