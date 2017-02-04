#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class VuUnit_VU0_t;
class VuUnit_VU1_t;
class VuUnit_t; 
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
	std::shared_ptr<VuUnit_VU0_t> VU0;
	std::shared_ptr<VuUnit_VU1_t> VU1;
	std::shared_ptr<VuUnit_t>     VU_UNITS[Constants::EE::VPU::VU::NUMBER_VU_UNITS];

	// FBRST shared register.
	std::shared_ptr<VURegister_FBRST_t> FBRST;
};