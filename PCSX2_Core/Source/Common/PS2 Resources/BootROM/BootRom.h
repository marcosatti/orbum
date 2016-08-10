#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"

class BootROM_t
{
public:
	BootROM_t() : bootROM(std::make_shared<u8*>(new u8[PS2Constants::SIZE_BOOT_ROM]))
	{
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(bootROM.get());
	}
private:
	const std::shared_ptr<u8*> bootROM;
};
