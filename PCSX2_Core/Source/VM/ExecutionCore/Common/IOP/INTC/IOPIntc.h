#pragma once

#include "Common/Interfaces/VMExecutionCoreComponent.h"

/*
Checks the CTRL master register and STAT register for any pending interrupts. If there are, AND's STAT with the MASK register and checks for any
interrupts to send to the IOP Core to process.
TODO: Verify the clock speed. Assumed to be IOP clock speed (~37 MHz), as the max reported bus rate is 137 MB/s and width is 32-bit.
See https://en.wikipedia.org/wiki/PlayStation_technical_specifications and https://en.wikipedia.org/wiki/PlayStation_2_technical_specifications.
*/
class IOPIntc : public VMExecutionCoreComponent
{
public:
	explicit IOPIntc(VMMain * vmMain);

	s64 executionStep(const ClockSource_t & clockSource) override;
};

