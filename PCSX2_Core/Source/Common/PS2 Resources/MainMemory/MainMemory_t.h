#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class MainMemory_t : public PS2ResourcesSubobject
{
public:
	explicit MainMemory_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mMainMemory(new u8[PS2Constants::SIZE_MAIN_MEMORY])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "MainMemory allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getBaseAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getBaseAddress(), 0, PS2Constants::SIZE_MAIN_MEMORY);
	}

	~MainMemory_t()
	{
		delete[] mMainMemory;
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(mMainMemory);
	}

private:
	u8 *const mMainMemory;
};
