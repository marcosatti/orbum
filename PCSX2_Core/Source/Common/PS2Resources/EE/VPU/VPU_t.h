#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class VIF_t;
class VU_t;

class VPU_t : public PS2ResourcesSubobject
{
public:
	explicit VPU_t(const PS2Resources_t *const PS2Resources);

	std::shared_ptr<VIF_t> VIF;
	std::shared_ptr<VU_t> VU;
};

