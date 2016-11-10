#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
VPU_t declares the VIF units and VU units of the EE.
*/

class EEVifUnit_0_t;
class EEVifUnit_1_t;
class EEVuUnit_0_t;
class EEVuUnit_1_t;

class VPU_t : public PS2ResourcesSubobject
{
public:
	explicit VPU_t(const PS2Resources_t *const PS2Resources);

	// VIF units.
	std::shared_ptr<EEVifUnit_0_t> VIF0;
	std::shared_ptr<EEVifUnit_1_t> VIF1;

	// VU units.
	std::shared_ptr<EEVuUnit_0_t> VU0;
	std::shared_ptr<EEVuUnit_1_t> VU1;

};