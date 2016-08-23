#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/Interfaces/VMMMUMappedStorageObject.h"

class BootROM_t : public PS2ResourcesSubobject, public VMMMUMappedStorageObject
{
public:
	explicit BootROM_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mBootROM(new u8[PS2Constants::SIZE_BOOT_ROM])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "BootROM allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getClientMemoryAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getClientMemoryAddress(), 0, getClientMemoryLength());
	}

	~BootROM_t()
	{
		delete[] mBootROM;
	}

	// Memory Mapped IO functionality.
	void* getClientMemoryAddress() override
	{
		return reinterpret_cast<void*>(mBootROM);
	}

	size_t getClientMemoryLength() override
	{
		return PS2Constants::SIZE_BOOT_ROM;
	}
private:
	u8 *const mBootROM;
};
