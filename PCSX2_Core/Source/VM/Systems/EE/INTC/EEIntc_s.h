#pragma once

#include "VM/Types/VMSystem_s.h"

class EECoreCOP0_t;
class EEIntc_t;

/*
Checks the I_STAT register for any pending interrupts. If there are, AND's it with the I_MASK register and checks for any interrupts to send to the EE Core to process.
Note that the maximum time resolution that this can run at is limited to BUSCLK - the reason for this being that all interrupt sources runat BUSCLK or less. 
Therefore it should be included with the BUSCLK events in the main emulation loop.
*/
class EEIntc_s : public VMSystem_s
{
public:
	explicit EEIntc_s(VM * vm);
	virtual ~EEIntc_s() = default;

	/*
	Checks the INTC STAT and MASK registers and sends an interrupt to the EE Core on the INT0 line.
	See EE Core Users Manual page 73-75 for the EE Core details. Note that on page 75, there is a typo, where the INTx lines are mixed up on bits 10 and 11 (verified through running through bios code).
	*/
	int step(const ClockSource_t clockSource, const int ticksAvailable) override;

private:
	/*
	Context resources needed.
	*/
	std::shared_ptr<EECoreCOP0_t> mEECOP0;
	std::shared_ptr<EEIntc_t> mINTC;
};

