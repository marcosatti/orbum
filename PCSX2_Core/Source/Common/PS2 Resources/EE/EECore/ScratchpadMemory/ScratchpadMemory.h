#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"

class ScratchpadMemory_t
{
public:
	ScratchpadMemory_t() : scratchpadMemory(new u8[PS2Constants::EE::EECore::SIZE_SCRATCHPAD_MEMORY])
	{
	}

	~ScratchpadMemory_t()
	{
		delete scratchpadMemory;
	}

	INLINE void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(scratchpadMemory);
	}
private:
	u8 *const scratchpadMemory;
};
