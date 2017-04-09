#include "stdafx.h"

#include "Common/Types/Memory/HwordMemory_t.h"

#include "Resources/IOP/SPU2/SPU2_t.h"
#include "Resources/IOP/SPU2/Types/SPU2Cores_t.h"

SPU2_t::SPU2_t() :
	CORES{ std::make_shared<SPU2Core_C0_t>(), std::make_shared<SPU2Core_C1_t>() },
	MainMemory(std::make_shared<HwordMemory_t>("SPU2 MainMem", false, false, Constants::IOP::SPU2::SIZE_MAIN_MEMORY)),
	DebugDummy(std::make_shared<HwordMemory_t>("SPU2 DebugDummy", false, false, 0x2))
{
}
