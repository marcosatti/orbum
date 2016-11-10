#include "stdafx.h"

#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/EEVifUnits_t.h"
#include "PS2Resources/EE/VPU/Types/EEVuUnits_t.h"

VPU_t::VPU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	VIF0(std::make_shared<EEVifUnit_0_t>()),
	VIF1(std::make_shared<EEVifUnit_1_t>()),
	VU0(std::make_shared<EEVuUnit_0_t>()),
	VU1(std::make_shared<EEVuUnit_1_t>())
{
}
