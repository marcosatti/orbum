#pragma once

#include "Controller/CController.hpp"

class CSio2 : public CController
{
public:
	CSio2(Core * core);

	void handle_event(const ControllerEvent & event) const override;
	
	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us) const;
	
	int time_step(const int ticks_available) const;

	/// Sets the SIO0 up for a reset.
	void handle_sio0_reset() const;
};

