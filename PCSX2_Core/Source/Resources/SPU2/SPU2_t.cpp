#include "stdafx.h"

#include "Common/Types/Memory/HwordMemory_t.h"
#include "Common/Types/Register/Register16_t.h"

#include "Resources/SPU2/SPU2_t.h"
#include "Resources/SPU2/Types/SPU2Cores_t.h"
#include "Resources/SPU2/Types/SPU2Registers_t.h"

SPU2_t::SPU2_t() :
	CORE_0(nullptr),
	CORE_1(nullptr),
	CORES{},
	SPDIF_OUT(std::make_shared<Register16_t>("SPU2 SPDIF_OUT", false, false)),
	SPDIF_IRQINFO(std::make_shared<SPU2Register_SPDIF_IRQINFO_t>("SPU2 SPDIF_IRQINFO", false, true)),
	SPDIF_07C4(std::make_shared<Register16_t>("SPU2 SPDIF_07C4", false, false)),
	SPDIF_MODE(std::make_shared<Register16_t>("SPU2 SPDIF_MODE", false, false)),
	SPDIF_MEDIA(std::make_shared<Register16_t>("SPU2 SPDIF_MEDIA", false, false)),
	SPDIF_07CA(std::make_shared<Register16_t>("SPU2 SPDIF_07CA", false, false)),
	SPDIF_PROTECT(std::make_shared<Register16_t>("SPU2 SPDIF_PROTECT", false, false)),
	MainMemory(std::make_shared<HwordMemory_t>("SPU2 MainMem", false, false, Constants::SPU2::SIZE_MAIN_MEMORY)),
{
}
