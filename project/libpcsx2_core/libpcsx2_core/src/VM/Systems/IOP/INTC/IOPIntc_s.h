#pragma once

#include "VM/Types/VMSystem_t.h"

class IOPCoreCOP0_t;
class IOPIntc_t;

/*
Checks the CTRL master register and STAT register for any pending interrupts. If there are, AND's STAT with the MASK register and checks for any
interrupts to send to the IOP Core to process.
TODO: Verify the clock speed. Assumed to be IOP clock speed (~37 MHz), as the max reported bus rate is 137 MB/s and width is 32-bit.
See https://en.wikipedia.org/wiki/PlayStation_technical_specifications and https://en.wikipedia.org/wiki/PlayStation_2_technical_specifications.
*/
class IOPIntc_s : public VMSystem_t
{
public:
	IOPIntc_s(VM * vm);
	virtual ~IOPIntc_s() = default;

	/*
	Initialisation.
	*/
	void initialise() override;

	/*
	Checks through the INTC STAT and MASK bits and sends an interrupt to the IOP Core on the INT2 line.
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

	/*
	Context resources needed.
	*/
	std::shared_ptr<IOPCoreCOP0_t> mIOPCOP0;
	std::shared_ptr<IOPIntc_t> mINTC;
};

