#include "stdafx.h"

#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VIF/VIF_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/Types/VPURegisters_t.h"

VPU_t::VPU_t() :
	VIF(std::make_shared<VIF_t>()),
	VU(std::make_shared<VU_t>()),
	STAT(std::make_shared<VPURegister_STAT_t>())
{
}