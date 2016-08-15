#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class BootROM_t : public PS2ResourcesSubobject
{
public:
	explicit BootROM_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		bootROM(std::make_shared<u8*>(new u8[PS2Constants::SIZE_BOOT_ROM]))
	{
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(bootROM.get());
	}
private:
	const std::shared_ptr<u8*> bootROM;
};
