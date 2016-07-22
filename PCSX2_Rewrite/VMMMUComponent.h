#pragma once

#include "Globals.h"
#include "VMBaseComponent.h"

class VMMain;

/*
The VM MMU component interface.
When the PS2 reads or writes to a "PHYSICAL" address, this unit will be consulted for the correct memory read and write location.
For when the PS2 reads or writes to a virtual address, there is another MMU unit within the Interpreter component - see that for details.
*/
class VMMMUComponent : public VMBaseComponent
{
public:
	explicit VMMMUComponent(const VMMain* vmMain) : VMBaseComponent(vmMain)
	{
	}

	virtual void mapMemory(void* clientMemoryAddress, u32 clientMemoryLength, u32 PS2MemoryAddress) = 0;

	/*
	Unfortunately C++ does not allow templated virtual functions... So we have to implement each possible case.
	*/
	virtual u8 readByteU(u32 virtualAddress) = 0;
	virtual void writeByteU(u32 virtualAddress, u8 value) = 0;
	virtual s8 readByteS(s32 virtualAddress) = 0;
	virtual void writeByteS(s32 virtualAddress, s8 value) = 0;

	virtual u16 readHwordU(u32 virtualAddress) = 0;
	virtual void writeHwordU(u32 virtualAddress, u16 value) = 0;
	virtual s16 readHwordS(s32 virtualAddress) = 0;
	virtual void writeHwordS(s32 virtualAddress, s16 value) = 0;

	virtual u32 readWordU(u32 virtualAddress) = 0;
	virtual void writeWordU(u32 virtualAddress, u32 value) = 0;
	virtual s32 readWordS(s32 virtualAddress) = 0;
	virtual void writeWordS(s32 virtualAddress, s32 value) = 0;

	virtual u64 readDwordU(u32 virtualAddress) = 0;
	virtual void writeDwordU(u32 virtualAddress, u64 value) = 0;
	virtual s64 readDwordS(s32 virtualAddress) = 0;
	virtual void writeDwordS(s32 virtualAddress, s64 value) = 0;
};