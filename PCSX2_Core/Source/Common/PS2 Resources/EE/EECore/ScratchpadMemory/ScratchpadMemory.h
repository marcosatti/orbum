#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Types/StorageObject/StorageObject_t.h"

class ScratchpadMemory_t : public StorageObject_t
{
public:

	static constexpr char * MEMORY_REGION_NAME = "Scratchpad Memory";

	explicit ScratchpadMemory_t() : 
		StorageObject_t(PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, MEMORY_REGION_NAME)
	{
	}

private:

};
