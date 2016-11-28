#include "stdafx.h"

#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VURegisters_t.h"

VU_t::VU_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	VU0(std::make_shared<VuUnit_VU0_t>(getRootResources())),
	VU1(std::make_shared<VuUnit_VU1_t>(getRootResources())),
	VU_UNITS{ VU0, VU1 },
	FBRST(std::make_shared<VURegister_FBRST_t>())
{
}
