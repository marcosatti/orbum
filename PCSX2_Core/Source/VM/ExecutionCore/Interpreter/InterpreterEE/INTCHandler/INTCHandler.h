#pragma once

#include "Common/Interfaces/VMExecutionCoreComponent.h"

class INTCHandler : public VMExecutionCoreComponent
{
public:
	explicit INTCHandler(const VMMain* const vmMain);

	/*
	Checks the I_STAT register for any pending interrupts. If there are, AND's it with the I_MASK register and checks for any
	interrupts to send to the EE Core to process.
	*/
	void checkInterrupt() const;
};

