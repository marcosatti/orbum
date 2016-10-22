#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"


/*
TODO: Fill in documentation, and add threading for sub components. Sub components can be thought of the different manual sections (EE Core, EE, GS, etc) perhaps?
The PCSX2 interpreter. Provides an implementation of a running PS2 system.
Idealy, any sub components in here can run independently of eachother (or spinlock/wait until data is ready).

For timing, EECoreInterpreter provides the relative synchronisation, as it is the fastest clocked device in the PS2 (294 MHz).
The EE Core clock is also refered to as the PS2CLK.
All other components can be expressed as ratios of this clock speed.
For example, the BUSCLK is half that of the PS2CLK. Therefore for every 2 executionStep() of the EE Core, 
 1 executionStep() will be be run for the BUSCLK components.
The timing is all implemented in the PS2Resources_t::Clock_t class, which is used here.
*/

class VMMain;
class EECoreInterpreter;
class DMACInterpreter;
class INTCHandler;
class TimersHandler;
class IOPCoreInterpreter;
//class InterpreterVU;
//class InterpreterGS;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(VMMain * vmMain);

	/*
	See VMExecutionCoreComponent for documentation.
	*/
	std::vector<ClockSource_t> mClockSources;
	const std::vector<ClockSource_t> & getClockSources() override;

	/*
	Always runs the EE Core.
	For the other components, first checks if they should be run and then controls their timing.
	*/
	s64 executionStep(const ClockSource_t & clockSource) override;

	/*
	Delegates to all components by calling mComponents::intialise().
	*/
	void initalise() override;

private:

	std::shared_ptr<EECoreInterpreter> mEECoreInterpreter;
	std::shared_ptr<DMACInterpreter> mDMACInterpreter;
	std::shared_ptr<INTCHandler> mINTCHandler;
	std::shared_ptr<TimersHandler> mTimerHandler;
	//std::unique_ptr<InterpreterVU> mInterpreterVU; 
	//std::unique_ptr<InterpreterGS> mInterpreterGS;
	std::shared_ptr<IOPCoreInterpreter> mIOPInterpreter;

	/*
	Used to iterate through all components except the EE Core interpreter.
	*/
	std::vector<std::shared_ptr<VMExecutionCoreComponent>> mComponents;
};

