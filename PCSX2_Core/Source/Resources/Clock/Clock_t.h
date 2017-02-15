#pragma once

#include <map>

#include "Common/Global/Globals.h"

/*
Clock_t helps with synchronisation across components.
*/
class Clock_t
{
public:
	explicit Clock_t();

	/*
	Controls the pixel clock speed.
	*/
	void setPixelClockSpeed(const int & resX, const double & fH);
	const double & getPixelClockSpeed() const;

private:
	double mPixelClockSpeed;
};

