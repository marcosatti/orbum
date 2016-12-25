#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubcategory.h"
#include "PS2Constants/PS2Constants.h"

class VuUnit_VU0_t;
class VuUnit_VU1_t;
class VuUnit_t; 
class VURegister_FBRST_t;

/*
TODO: finish writing documentation.
VU_t declares the vector units of the EE (VU0 and VU1).

VU0 is connected to the EE Core as COP2.
*/
class VU_t : public PS2ResourcesSubcategory
{
public:
	explicit VU_t(const PS2Resources_t * PS2Resources);
	void postResourcesInit() override;

	// VU units.
	std::shared_ptr<VuUnit_VU0_t> VU0;
	std::shared_ptr<VuUnit_VU1_t> VU1;
	std::shared_ptr<VuUnit_t>     VU_UNITS[PS2Constants::EE::VPU::VU::NUMBER_VU_UNITS];

	// FBRST shared register.
	std::shared_ptr<VURegister_FBRST_t> FBRST;

private:
	/*
	Initalise VU0 with a pointer to the EE Core COP0 coprocessor.
	*/
	void initVU0();

	/*
	Initalise the VU0 (COP2) control register map.
	*/
	void initVU0ControlRegistersMap() const;

	/*
	Initalise the physical memory maps for VU0 and VU1.
	*/
	void initVU0PhysicalMemoryMap() const;
	void initVU1PhysicalMemoryMap() const;
};