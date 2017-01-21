#pragma once

#include "Common/Interfaces/VMExecutionCoreComponent.h"

class IOPCoreCOP0_t;
class IOPIntcRegister_STAT_t;
class IOPIntcRegister_MASK_t;
class IOPIntcRegister_CTRL_t;

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

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<IOPCoreCOP0_t> mIOPCOP0;
	std::shared_ptr<IOPIntcRegister_STAT_t> mSTAT;
	std::shared_ptr<IOPIntcRegister_MASK_t> mMASK;
	std::shared_ptr<IOPIntcRegister_CTRL_t> mCTRL;
};

