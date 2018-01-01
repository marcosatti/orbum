#pragma once

#include "Common/Types/Mips/MipsCoprocessor.hpp"

/// MIPS coprocessor 0 (system control) interface.
class MipsCoprocessor0 : public MipsCoprocessor
{
public:
	/// Coprocessor 0 operating context.
	enum class OperatingContext
	{
		Kernel,
		Supervisor,
		User
	};

	/// Used to check the operating context - Kernel mode, Supervisor mode, or User mode.
	/// Set to a virtual function as the COP0 register formats are not always compatible.
	virtual	OperatingContext operating_context() = 0;
};

