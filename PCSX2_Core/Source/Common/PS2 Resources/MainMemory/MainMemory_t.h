#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"

class MainMemory_t
{
public:
	MainMemory_t() : mainMemory(std::make_shared<u8*>(new u8[PS2Constants::SIZE_MAIN_MEMORY]))
	{
	}

	void * getBaseAddress() const
	{
		return reinterpret_cast<void*>(mainMemory.get());
	}

private:
	const std::shared_ptr<u8*> mainMemory;
};
