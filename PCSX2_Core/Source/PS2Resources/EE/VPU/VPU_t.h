#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
VPU_t declares the collective VIF structure and collective VU structure of the EE.
*/

class VIF_t;
class VU_t;
class VPURegister_STAT_t;

class VPU_t : public PS2ResourcesSubobject
{
public:
	explicit VPU_t(const PS2Resources_t *const PS2Resources);

	// VIF structure.
	std::shared_ptr<VIF_t> VIF;
	std::shared_ptr<VU_t>  VU;

	// VPU-STAT shared register.
	std::shared_ptr<VPURegister_STAT_t> STAT;
};