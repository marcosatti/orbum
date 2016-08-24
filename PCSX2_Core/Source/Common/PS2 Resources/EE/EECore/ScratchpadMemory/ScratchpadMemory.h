#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/Interfaces/VMMMUMappedStorageObject.h"

class ScratchpadMemory_t : public PS2ResourcesSubobject, public VMMMUMappedStorageObject
{
public:
	explicit ScratchpadMemory_t(const PS2Resources_t *const PS2Resources) : 
		PS2ResourcesSubobject(PS2Resources),
		mScratchpadMemory(new u8[PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY])
	{
#if defined(BUILD_DEBUG)
		char message[1000];
		sprintf_s(message, 1000, "ScratchpadMemory allocated at 0x%016llX.", reinterpret_cast<uintptr_t>(getClientMemoryAddress()));
		logDebug(message);
#endif

		// Set memory to zero.
		memset(getClientMemoryAddress(), 0, getClientMemoryLength());
	}

	~ScratchpadMemory_t()
	{
		delete[] mScratchpadMemory;
	}

	// Memory Mapped IO functionality.
	void* getClientMemoryAddress() override
	{
		return reinterpret_cast<void*>(mScratchpadMemory);
	}

	size_t getClientMemoryLength() override
	{
		return PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY;
	}
private:
	u8 *const mScratchpadMemory;
};
