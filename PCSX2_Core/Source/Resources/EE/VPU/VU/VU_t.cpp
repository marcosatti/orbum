#include "stdafx.h"

#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "Resources/EE/VPU/VU/Types/VURegisters_t.h"

VU_t::VU_t() :
	VU0(nullptr),
	VU1(std::make_shared<VuUnit_VU1_t>()),
	VU_UNITS{},
	FBRST(std::make_shared<VURegister_FBRST_t>())
{
}