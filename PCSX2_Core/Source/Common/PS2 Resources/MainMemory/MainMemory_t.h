#pragma once

#include "Common/Global/Globals.h"
#include "Common/PS2 Constants/PS2Constants.h"
#include "Common/Types/StorageObject/StorageObject_t.h"

class MainMemory_t : public StorageObject_t
{
public:

	static constexpr char * MEMORY_REGION_NAME = "Main Memory";

	explicit MainMemory_t() :
		StorageObject_t(PS2Constants::MainMemory::SIZE_MAIN_MEMORY, MEMORY_REGION_NAME)
	{
	}

private:

};
