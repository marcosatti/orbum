#include "stdafx.h"

#include "Resources/EE/VPU/VIF/VIF_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFUnits_t.h"

VIF_t::VIF_t() :
	VIF0(std::make_shared<VifUnit_VIF0_t>()),
	VIF1(std::make_shared<VifUnit_VIF1_t>()),
	VIF_UNITS{ VIF0, VIF1 }
{
}
