#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

/*
TODO: finish writing documentation.
VPU_t declares the VIF units and VU units of the EE.
*/

class VifUnit_t;
class VifUnit_VIF0_t;
class VifUnit_VIF1_t;
class VuUnit_0_t;
class VuUnit_1_t;
class VuUnit_t;

class VPU_t : public PS2ResourcesSubobject
{
public:
	explicit VPU_t(const PS2Resources_t *const PS2Resources);

	// VIF units.
	std::shared_ptr<VifUnit_VIF0_t> VIF0;
	std::shared_ptr<VifUnit_VIF1_t> VIF1;
	std::shared_ptr<VifUnit_t>      VIF_UNITS[PS2Constants::EE::VPU::VIF::NUMBER_VIF_UNITS];

	// VU units.
	std::shared_ptr<VuUnit_0_t> VU0;
	std::shared_ptr<VuUnit_1_t> VU1;
	std::shared_ptr<VuUnit_t>   VU_UNITS[PS2Constants::EE::VPU::VU::NUMBER_VU_UNITS];

};