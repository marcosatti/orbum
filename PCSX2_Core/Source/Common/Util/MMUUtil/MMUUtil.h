#pragma once

#include "Common/Global/Globals.h"

class MMUUtil
{
public:
	
	/*
	Gets the high 19 bits of the virtual address parsed, stored at the MSB's of the returned u32.
	*/
	static u32 getVirtualAddressHI19(u32 PS2VirtualAddress);
};

