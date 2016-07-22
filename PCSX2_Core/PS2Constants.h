#pragma once

#include "Globals.h"

class PS2Constants
{
public:
	struct EE
	{
		struct EECore
		{
			static constexpr u32 ADDRESS_EXCEPTION_BASE_LVL1 = 0x80000000;
			static constexpr u32 ADDRESS_EXCEPTION_BASE_LVL2 = 0xBFC00000;
		};
	};
};

