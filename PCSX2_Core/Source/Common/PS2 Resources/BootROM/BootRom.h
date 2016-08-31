#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Types/StorageObject/StorageObject_t.h"

class BootROM_t : public StorageObject_t
{
public:

	static constexpr char * MEMORY_REGION_NAME = "Boot ROM";

	explicit BootROM_t() :
		StorageObject_t(PS2Constants::BootROM::SIZE_BOOT_ROM, MEMORY_REGION_NAME)
	{
	}

private:

};
