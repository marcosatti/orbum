#pragma once

#include "Controller/CController.hpp"

class CGsCore : public CController
{
public:
	CGsCore(Core * core);

	void handle_event(const ControllerEvent & event) const override;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us) const;
	
	int time_step(const int ticks_available) const;
};

