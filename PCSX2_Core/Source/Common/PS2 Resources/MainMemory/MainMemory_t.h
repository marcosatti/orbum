#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/Interfaces/VMMMUMappedStorageObject.h"

class MainMemory_t : public PS2ResourcesSubobject, public VMMMUMappedStorageObject
{
public:
	explicit MainMemory_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mMainMemory(new u8[PS2Constants::SIZE_MAIN_MEMORY])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "MainMemory allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getClientMemoryAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getClientMemoryAddress(), 0, getClientMemoryLength());
	}

	~MainMemory_t()
	{
		delete[] mMainMemory;
	}

	// Memory Mapped IO functionality.
	void* getClientMemoryAddress() override
	{
		return reinterpret_cast<void*>(mMainMemory);
	}

	size_t getClientMemoryLength() override
	{
		return PS2Constants::SIZE_MAIN_MEMORY;
	}
private:
	u8 *const mMainMemory;
};
