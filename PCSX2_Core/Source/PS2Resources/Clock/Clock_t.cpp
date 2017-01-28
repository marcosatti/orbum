#include "stdafx.h"

#include "PS2Resources/Clock/Clock_t.h"
#include "PS2Constants/PS2Constants.h"

Clock_t::Clock_t(const PS2Resources_t * PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	mClockSpeeds {
		PS2Constants::EE::EECore::EECORE_CLK_SPEED,
		PS2Constants::EE::EEBUS_CLK_SPEED,
		PS2Constants::EE::EEBUS16_CLK_SPEED,
		PS2Constants::EE::EEBUS256_CLK_SPEED,
		PS2Constants::IOP::IOPCore::IOPCORE_CLK_SPEED,
		PS2Constants::IOP::IOPBUS_CLK_SPEED,
		PS2Constants::IOP::IOPBUS8_CLK_SPEED,
		PS2Constants::IOP::IOPBUS16_CLK_SPEED,
		PS2Constants::IOP::IOPBUS256_CLK_SPEED,
		PS2Constants::GS::HBLNK_CLK_SPEED
	}
{
}

