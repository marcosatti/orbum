#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/VPU/VU/Types/VURegisters_t.h"

VU_t::VU_t() :
	VU0(nullptr),
	VU1(std::make_shared<VUCore_VU1_t>()),
	VU_CORES{},
	FBRST(std::make_shared<VURegister_FBRST_t>("VU FBRST", false, false))
{
}