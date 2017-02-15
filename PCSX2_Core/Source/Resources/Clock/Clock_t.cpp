#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Resources/Clock/Clock_t.h"

Clock_t::Clock_t() :
	mPixelClockSpeed(Constants::GS::PCRTC::PCRTC_CLK_SPEED_DEFAULT)
{
}

void Clock_t::setPixelClockSpeed(const int& resX, const double& fH)
{
	// Working: period of 1 cycle, divided by half (actual render vs. hblank), divided by number of resX pixels, all inversed for Hz.
	mPixelClockSpeed = 1 / ((1 / fH) / 2 / resX); 
}

const double & Clock_t::getPixelClockSpeed() const
{
	return mPixelClockSpeed;
}
