#include "stdafx.h"

#include <stdexcept>

#include "PS2Resources/Clock/Clock_t.h"
#include "PS2Constants/PS2Constants.h"

Clock_t::Clock_t(const PS2Resources_t * PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	mClockRatio {
		1,
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK,
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK16,
		PS2Constants::EE::RATIO_PS2CLK_BUSCLK256,
		0xFFFFFFFF, // Set at runtime by the GS. Initially set to a really high value so that the clock event wont be triggered.
		PS2Constants::IOP::RATIO_PS2CLK_IOP
	}
{
}