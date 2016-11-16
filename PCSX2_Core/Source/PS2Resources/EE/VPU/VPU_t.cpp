#include "stdafx.h"

#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/VifUnits_t.h"
#include "PS2Resources/EE/VPU/Types/VuUnits_t.h"

VPU_t::VPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	VIF0(std::make_shared<VifUnit_VIF0_t>()),
	VIF1(std::make_shared<VifUnit_VIF1_t>()),
	VIF_UNITS{ VIF0, VIF1 },
	VU0(std::make_shared<VuUnit_0_t>()),
	VU1(std::make_shared<VuUnit_1_t>()),
	VU_UNITS{ VU0, VU1 }
{
}
