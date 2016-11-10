#pragma once

#include <string>

#include "Common/Types/Memory/ROMemory_t.h"

/*
A memory object that exposes the loadBIOS() function to load in the BIOS image.
It should be loaded before emulation starts.
*/
class BootROM_t : public ROMemory_t
{
public:
	BootROM_t();

	/*
	Reads in the BIOS at the given path and stores it in the raw underlying memory.
	*/
	void loadBIOS(const std::string & biosPath) const;
};

