#pragma once

#include "Resources/Ee/Vpu/Vif/RVif.hpp"
#include "Resources/Ee/Vpu/Vu/RVu.hpp"
#include "Resources/Ee/Vpu/VpuRegisters.hpp"

/// RVpu declares the collective VPU structure.
class RVpu
{
public:
	/// Shared registers.
	VpuRegister_Stat stat;

	/// VIF structure.
	RVif vif;

	/// VU structure.
	RVu vu;
};