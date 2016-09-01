#pragma once

#include <memory>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"

class VMMain;
class VMMMUMappedStorageObject;
class PS2StorageObject_t;

/*
The VM MMU component interface.
When the PS2 reads or writes to a "PHYSICAL" address, this unit will be consulted for the correct memory read and write location.
For when the PS2 reads or writes to a virtual address, there is another MMU unit within ExecutionCore component - see that for details.
*/
class VMMMUComponent : public VMBaseComponent
{
public:
	explicit VMMMUComponent(const VMMain *const vmMain) 
		: VMBaseComponent(vmMain)
	{
	}

	virtual void mapMemory(const std::shared_ptr<VMMMUMappedStorageObject> & clientStorage, const u32 & PS2MemoryAddress) = 0;
	virtual void mapMemory(const std::shared_ptr<PS2StorageObject_t> & clientStorage); // Convenience function for above.

	/*
	Unfortunately C++ does not allow templated virtual functions... So we have to implement each possible case.
	*/
	virtual u8 readByteU(u32 PS2MemoryAddress) const = 0;
	virtual void writeByteU(u32 PS2MemoryAddress, u8 value) const = 0;
	virtual s8 readByteS(u32 PS2MemoryAddress) const = 0;
	virtual void writeByteS(u32 PS2MemoryAddress, s8 value) const = 0;
	virtual u16 readHwordU(u32 PS2MemoryAddress) const = 0;
	virtual void writeHwordU(u32 PS2MemoryAddress, u16 value) const = 0;
	virtual s16 readHwordS(u32 PS2MemoryAddress) const = 0;
	virtual void writeHwordS(u32 PS2MemoryAddress, s16 value) const = 0;
	virtual u32 readWordU(u32 PS2MemoryAddress) const = 0;
	virtual void writeWordU(u32 PS2MemoryAddress, u32 value) const = 0;
	virtual s32 readWordS(u32 PS2MemoryAddress) const = 0;
	virtual void writeWordS(u32 PS2MemoryAddress, s32 value) const = 0;
	virtual u64 readDwordU(u32 PS2MemoryAddress) const = 0;
	virtual void writeDwordU(u32 PS2MemoryAddress, u64 value) const = 0;
	virtual s64 readDwordS(u32 PS2MemoryAddress) const = 0;
	virtual void writeDwordS(u32 PS2MemoryAddress, s64 value) const = 0;
};