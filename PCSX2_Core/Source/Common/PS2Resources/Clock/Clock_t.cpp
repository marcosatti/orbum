#include "stdafx.h"

#include "Common/PS2Resources/Clock/Clock_t.h"
#include "Common/PS2Constants/PS2Constants.h"

Clock_t::Clock_t() : 
	RATIO_PS2CLK { 
		1,
		1, 
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK, 
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK16, 
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK256, 
		0xFFFFFFFF, // Set at runtime by the GS. Initially set to a really high value so that the clock event wont be triggered.
		PS2Constants::IOP::RATIO_PS2CLK_IOP 
	}
{
}
