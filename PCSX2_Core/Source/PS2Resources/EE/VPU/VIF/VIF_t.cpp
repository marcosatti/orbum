#include "stdafx.h"

#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VIFUnits_t.h"

VIF_t::VIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	VIF0(std::make_shared<VifUnit_VIF0_t>()),
	VIF1(std::make_shared<VifUnit_VIF1_t>()),
	VIF_UNITS{ VIF0, VIF1 }
{
}
