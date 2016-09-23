#pragma once

#include "Common/Interfaces/VMExecutionCoreComponent.h"

/*
The InterpreterDMAC class controls the execution of the DMAC and transfers through DMA.

It is called InterpreterDMAC as it is actually a micro controller (duh) with its own language (DMAtag)!
Therefore we are still required to interpret these instructions.

The DMAC is synced to the BUSCLK clock source, and at most transfers 8 Qwords every tick (128 bytes).
*/

class InterpreterDMAC : VMExecutionCoreComponent
{
public:
	explicit InterpreterDMAC(const VMMain* const vmMain);
	~InterpreterDMAC();

	void executionStep() override;

private:

};

