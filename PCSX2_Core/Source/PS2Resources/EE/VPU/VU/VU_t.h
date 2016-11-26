#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "PS2Constants/PS2Constants.h"

/*
TODO: finish writing documentation.
VU_t declares the vector units of the EE (VU0 and VU1).

VU0 is connected to the EE Core as COP2.
*/

class VectorUnit_0_t;
class VectorUnit_1_t;
class VectorUnit_t; 
class VURegister_FBRST_t;

class VU_t : public PS2ResourcesSubobject
{
public:
	explicit VU_t(const PS2Resources_t *const PS2Resources);

	// VU units.
	std::shared_ptr<VectorUnit_0_t> VU0;
	std::shared_ptr<VectorUnit_1_t> VU1;
	std::shared_ptr<VectorUnit_t>   VECTOR_UNITS[PS2Constants::EE::VPU::VU::NUMBER_VU_UNITS];

	// FBRST shared register.
	std::shared_ptr<VURegister_FBRST_t> FBRST;
};