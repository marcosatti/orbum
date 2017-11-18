#pragma once

#include "Common/Constants.hpp"

#include "Resources/Ee/Vpu/VifCores.hpp"
#include "Resources/Ee/Vpu/VuCores.hpp"
#include "Resources/Ee/Vpu/VpuRegisters.hpp"
#include "Resources/Ee/Vpu/VuRegisters.hpp"

/// RVpu declares the collective VIF structure and collective VU structure of the EE.
class RVpu
{
public:
	RVpu();

	/// Shared registers.
	VpuRegister_Stat stat;

	/// VIF structure.
	VifCore_Base vif0;
	VifCore_Base vif1;
	VifCore_Base * vif_cores[Constants::EE::VPU::VIF::NUMBER_VIF_CORES];

	/// VU structure.
	VuCore_Vu0 vu0;
	VuCore_Vu1 vu1;
	VuCore_Base * vu_cores[Constants::EE::VPU::VU::NUMBER_VU_CORES];
	
	/// Shared VU registers.
	VuRegister_Fbrst fbrst;
};