#pragma once

#include "Controller/CController.hpp"

/// Checks the CTRL master register and STAT register for any pending interrupts. If there are, AND's STAT with the MASK register and checks for any
/// interrupts to send to the IOP Core to process.
/// TODO: Verify the clock speed. Assumed to be IOP clock speed (~37 MHz), as the max reported bus rate is 137 MB/s and width is 32-bit.
/// See https://en.wikipedia.org/wiki/PlayStation_technical_specifications and https://en.wikipedia.org/wiki/PlayStation_2_technical_specifications.
class CIopIntc : public CController
{
public:
	CIopIntc(Core * core);

	void handle_event(const ControllerEvent & event) override;

	/// Converts a time duration into the number of ticks that would have occurred.
	int time_to_ticks(const double time_us);
	
	/// Checks through the INTC STAT and MASK bits and sends an interrupt
	/// to the IOP Core on the INT2 line.
	int time_step(const int ticks_available);
};

