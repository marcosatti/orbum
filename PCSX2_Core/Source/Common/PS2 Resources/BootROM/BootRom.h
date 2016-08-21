#pragma once

#include <memory>
#include <cstdio>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class BootROM_t : public PS2ResourcesSubobject
{
public:
	explicit BootROM_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mBootROM(new u8[PS2Constants::SIZE_BOOT_ROM])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "BootROM allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getBaseAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getBaseAddress(), 0, PS2Constants::SIZE_BOOT_ROM);
	}

	~BootROM_t()
	{
		delete[] mBootROM;
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(mBootROM);
	}
private:
	u8 *const mBootROM;
};
