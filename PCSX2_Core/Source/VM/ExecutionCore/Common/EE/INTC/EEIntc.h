#pragma once

#include "Common/Interfaces/VMExecutionCoreComponent.h"

class EECoreCOP0_t;
class EEIntcRegister_STAT_t;
class EEIntcRegister_MASK_t;

/*
Checks the I_STAT register for any pending interrupts. If there are, AND's it with the I_MASK register and checks for any
interrupts to send to the EE Core to process.

Note that the maximum time resolution that this can run at is limited to BUSCLK - the reason for this being that all interrupt sources run
at BUSCLK or less. Therefore it should be included with the BUSCLK events in the main emulation loop.
*/
class EEIntc : public VMExecutionCoreComponent
{
public:
	explicit EEIntc(VMMain * vmMain);

	double executionStep(const ClockSource_t & clockSource, const double & ticksAvailable) override;

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<EECoreCOP0_t> mEECOP0;
	std::shared_ptr<EEIntcRegister_STAT_t> mSTAT;
	std::shared_ptr<EEIntcRegister_MASK_t> mMASK;
};

