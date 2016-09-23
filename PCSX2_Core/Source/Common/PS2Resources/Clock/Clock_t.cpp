#include "stdafx.h"

#include "Common/PS2Resources/Clock/Clock_t.h"
#include <Common/PS2Constants/PS2Constants.h>

Clock_t::Clock_t() : 
	RATIO_PS2CLK_HBLNK(0xFFFFFFFF), 
	NumTicksBUSCLK(0), 
	NumTicksBUSCLK16(0), 
	NumTicksBUSCLK256(0), 
	NumTicksHBLNK(0)
{
}

void Clock_t::updateClocks(const u32 & numClocksPS2CLK)
{
	NumTicksBUSCLK += numClocksPS2CLK;
	NumTicksBUSCLK16 += numClocksPS2CLK;
	NumTicksBUSCLK256 += numClocksPS2CLK;
	NumTicksHBLNK += numClocksPS2CLK;
}

bool Clock_t::isTickedBUSCLK()
{
	if ((NumTicksBUSCLK / PS2Constants::EE::RATIO_PS2CLK_BUSCLK) > 0)
	{
		NumTicksBUSCLK -= PS2Constants::EE::RATIO_PS2CLK_BUSCLK;
		return true;
	}

	return false;
}

bool Clock_t::isTickedBUSCLK16()
{
	if ((NumTicksBUSCLK16 / PS2Constants::EE::RATIO_PS2CLK_BUSCLK16) > 0)
	{
		NumTicksBUSCLK16 -= PS2Constants::EE::RATIO_PS2CLK_BUSCLK16;
		return true;
	}

	return false;
}

bool Clock_t::isTickedBUSCLK256()
{
	if ((NumTicksBUSCLK256 / PS2Constants::EE::RATIO_PS2CLK_BUSCLK256) > 0)
	{
		NumTicksBUSCLK256 -= PS2Constants::EE::RATIO_PS2CLK_BUSCLK256;
		return true;
	}

	return false;
}

bool Clock_t::isTickedHBLNK()
{
	// Note: RATIO_PS2CLK_HBLNK is set at runtime, and can be changed dynamically by the GS.
	if ((NumTicksHBLNK / RATIO_PS2CLK_HBLNK) > 0)
	{
		NumTicksHBLNK -= RATIO_PS2CLK_HBLNK;
		return true;
	}

	return false;
}
