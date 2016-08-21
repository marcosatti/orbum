#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"

class ScratchpadMemory_t : public PS2ResourcesSubobject
{
public:
	explicit ScratchpadMemory_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mScratchpadMemory(new u8[PS2Constants::EE::EECore::SIZE_SCRATCHPAD_MEMORY])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "ScratchpadMemory allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getBaseAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getBaseAddress(), 0, PS2Constants::EE::EECore::SIZE_SCRATCHPAD_MEMORY);
	}

	~ScratchpadMemory_t()
	{
		delete[] mScratchpadMemory;
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(mScratchpadMemory);
	}

private:
	u8 *const mScratchpadMemory;
};
