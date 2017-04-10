#include "stdafx.h"

#include "Common/Types/Memory/HwordMemory_t.h"
#include "Common/Types/Register/Register16_t.h"

#include "Resources/IOP/SPU2/SPU2_t.h"
#include "Resources/IOP/SPU2/Types/SPU2Cores_t.h"

SPU2_t::SPU2_t() :
	CORE_0(std::make_shared<SPU2Core_C0_t>()),
	CORE_1(std::make_shared<SPU2Core_C1_t>()),
	CORES{ CORE_0,  CORE_1 },
	SPDIF_OUT(std::make_shared<Register16_t>("SPU2 SPDIF_OUT", false, true)),
	SPDIF_IRQINFO(std::make_shared<Register16_t>("SPU2 SPDIF_IRQINFO", false, true)),
	SPDIF_07C4(std::make_shared<Register16_t>("SPU2 SPDIF_07C4", false, true)),
	SPDIF_MODE(std::make_shared<Register16_t>("SPU2 SPDIF_MODE", false, true)),
	SPDIF_MEDIA(std::make_shared<Register16_t>("SPU2 SPDIF_MEDIA", false, true)),
	SPDIF_07CA(std::make_shared<Register16_t>("SPU2 SPDIF_07CA", false, true)),
	SPDIF_PROTECT(std::make_shared<Register16_t>("SPU2 SPDIF_PROTECT", false, true)),
	MainMemory(std::make_shared<HwordMemory_t>("SPU2 MainMem", false, false, Constants::IOP::SPU2::SIZE_MAIN_MEMORY)),
	DebugDummy(std::make_shared<HwordMemory_t>("SPU2 DebugDummy", false, false, 0x2))
{
}
