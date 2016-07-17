#pragma once

#include "Globals.h"
#include "VMBaseComponent.h"

class VMMain;

/*
The MMU component interface.
The PS2 uses address translation to map virtual addresses to physical addresses.
*/
class VMMMUComponent : public VMBaseComponent
{
public:
	explicit VMMMUComponent(const VMMain* _mainVM)
		: VMBaseComponent(_mainVM)
	{
	}

	/*
	Read and write to virtual memory addresses.
	Programs (such as the PS2 OS for the most part and games) will interface with the functions below, as far as they are concerned.
	*/
	virtual u8 readByte(u32 virtualAddress) = 0;
	virtual void writeByte(u32 virtualAddress, u8 value) = 0;
	virtual u16 readHword(u32 virtualAddress) = 0;
	virtual void writeHword(u32 virtualAddress, u16 value) = 0;
	virtual u32 readWord(u32 virtualAddress) = 0;
	virtual void writeWord(u32 virtualAddress, u32 value) = 0;
	virtual u64 readDword(u32 virtualAddress) = 0;
	virtual void writeDword(u32 virtualAddress, u64 value) = 0;
};