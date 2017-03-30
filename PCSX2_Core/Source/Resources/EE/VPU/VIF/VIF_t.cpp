#include "stdafx.h"

#include "Resources/EE/VPU/VIF/VIF_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCores_t.h"

VIF_t::VIF_t() :
	VIF0(std::make_shared<VIFCore_VIF0_t>()),
	VIF1(std::make_shared<VIFCore_VIF1_t>()),
	VIF_CORES{ VIF0, VIF1 }
{
}
