#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"

class ScratchpadMemory_t
{
public:
	ScratchpadMemory_t() : scratchpadMemory(std::make_shared<u8*>(new u8[PS2Constants::EE::EECore::SIZE_SCRATCHPAD_MEMORY]))
	{
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(scratchpadMemory.get());
	}

private:
	const std::shared_ptr<u8*> scratchpadMemory;
};
