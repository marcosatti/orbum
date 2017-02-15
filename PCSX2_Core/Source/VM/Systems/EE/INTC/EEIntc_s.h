#pragma once

#include "VM/Types/VMSystem_s.h"

class EECoreCOP0_t;
class EEIntc_t;

/*
Checks the I_STAT register for any pending interrupts. If there are, AND's it with the I_MASK register and checks for any
interrupts to send to the EE Core to process.

Note that the maximum time resolution that this can run at is limited to BUSCLK - the reason for this being that all interrupt sources run
at BUSCLK or less. Therefore it should be included with the BUSCLK events in the main emulation loop.
*/
class EEIntc_s : public VMSystem_s
{
public:
	explicit EEIntc_s(VM * vmMain);
	virtual ~EEIntc_s();

	void run(const double & time) override;

	int step(const ClockEvent_t& event) override;

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<EECoreCOP0_t> mEECOP0;
	std::shared_ptr<EEIntc_t> mINTC;
};

