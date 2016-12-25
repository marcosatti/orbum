#include "stdafx.h"

#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/Types/VPURegisters_t.h"

VPU_t::VPU_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	VIF(std::make_shared<VIF_t>(getRoot())),
	VU(std::make_shared<VU_t>(getRoot())),
	STAT(std::make_shared<VPURegister_STAT_t>())
{
}

void VPU_t::postResourcesInit()
{
	VIF->postResourcesInit();
	VU->postResourcesInit();
}
