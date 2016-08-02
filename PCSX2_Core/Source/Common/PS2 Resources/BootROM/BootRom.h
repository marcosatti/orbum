#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"

class BootROM_t
{
public:
	BootROM_t() : bootROM(new u8[PS2Constants::SIZE_BOOT_ROM])
	{
	}

	~BootROM_t()
	{
		delete bootROM;
	}

	INLINE void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(bootROM);
	}
private:
	u8 *const bootROM;
};
