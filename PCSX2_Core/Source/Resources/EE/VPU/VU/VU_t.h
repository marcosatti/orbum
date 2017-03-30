#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class VUCore_VU0_t;
class VUCore_VU1_t;
class VUCore_t; 
class VURegister_FBRST_t;

/*
TODO: finish writing documentation.
VU_t declares the vector units of the EE (VU0 and VU1).
VU0 is connected to the EE Core as COP2.
*/
class VU_t
{
public:
	explicit VU_t();

	// VU units.
	std::shared_ptr<VUCore_VU0_t> VU0;
	std::shared_ptr<VUCore_VU1_t> VU1;
	std::shared_ptr<VUCore_t>     VU_CORES[Constants::EE::VPU::VU::NUMBER_VU_CORES];

	// FBRST shared register.
	std::shared_ptr<VURegister_FBRST_t> FBRST;
};