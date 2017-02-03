#pragma once

#include <memory>

class VIF_t;
class VU_t;
class VPURegister_STAT_t;

/*
TODO: finish writing documentation.
VPU_t declares the collective VIF structure and collective VU structure of the EE.
*/
class VPU_t
{
public:
	explicit VPU_t();

	// VIF structure.
	std::shared_ptr<VIF_t> VIF;
	std::shared_ptr<VU_t>  VU;

	// VPU-STAT shared register.
	std::shared_ptr<VPURegister_STAT_t> STAT;
};