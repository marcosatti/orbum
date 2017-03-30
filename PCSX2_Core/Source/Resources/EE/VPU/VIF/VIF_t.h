#pragma once

#include <memory>

#include "Common/Global/Globals.h"

class VIFCore_t;
class VIFCore_VIF0_t;
class VIFCore_VIF1_t;

/*
TODO: finish writing documentation.
VIF_t declares the VIF units of the EE (VIF0 and VIF1).
*/
class VIF_t
{
public:
	explicit VIF_t();

	// VIF units.
	std::shared_ptr<VIFCore_VIF0_t> VIF0;
	std::shared_ptr<VIFCore_VIF1_t> VIF1;
	std::shared_ptr<VIFCore_t>      VIF_CORES[Constants::EE::VPU::VIF::NUMBER_VIF_CORES];
};