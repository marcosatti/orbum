#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

class VifUnit_t;
class VifUnit_VIF0_t;
class VifUnit_VIF1_t;

/*
TODO: finish writing documentation.
VIF_t declares the VIF units of the EE (VIF0 and VIF1).
*/
class VIF_t : public PS2ResourcesSubobject
{
public:
	explicit VIF_t(const PS2Resources_t *const PS2Resources);

	// VIF units.
	std::shared_ptr<VifUnit_VIF0_t> VIF0;
	std::shared_ptr<VifUnit_VIF1_t> VIF1;
	std::shared_ptr<VifUnit_t>      VIF_UNITS[PS2Constants::EE::VPU::VIF::NUMBER_VIF_UNITS];
};