#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"


/*
TODO: Fill in documentation, and add threading for sub components. Sub components can be thought of the different manual sections (EE Core, EE, GS, etc) perhaps?
The PCSX2 interpreter. Provides an implementation of a running PS2 system.
Idealy, any sub components in here can run independently of eachother (or spinlock/wait until data is ready).

For timing, InterpreterEECore provides the relative synchronisation, as it is the fastest clocked device in the PS2 (294 MHz).
The EE Core clock is also refered to as the PS2CLK.
All other components can be expressed as ratios of this clock speed.
For example, the BUSCLK is half that of the PS2CLK. Therefore for every 2 executionStep() of the EE Core, 
 1 executionStep() will be be run for the BUSCLK components.
The timing is all implemented in the PS2Resources_t::Clock_t class, which is used here.
*/

class VMMain;
class InterpreterEECore;
class InterpreterDMAC;
class INTCHandler;
class TimerHandler;
//class InterpreterVU;
//class InterpreterGS;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(VMMain * vmMain);

	void executionStep() override;

	void initalise() override;

private:
	const std::unique_ptr<InterpreterEECore> mInterpreterEECore;
	const std::unique_ptr<InterpreterDMAC> mDMACHandler;
	const std::unique_ptr<INTCHandler> mINTCHandler;
	const std::unique_ptr<TimerHandler> mTimerHandler;
	//const std::unique_ptr<InterpreterVU> mInterpreterVU; // TODO: look at putting VU0 and VU1 on a separate thread - looks like a good candidate.
	//const std::unique_ptr<InterpreterGS> mInterpreterGS;
};

