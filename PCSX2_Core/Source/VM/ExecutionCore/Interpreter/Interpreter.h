#pragma once

#include <memory>
#include <vector>

#include "Common/Interfaces/VMExecutionCore.h"
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

class VUInterpreter;
class VIF;
class VMMain;
class EECoreInterpreter;
class EEDmac;
class EEIntc;
class EETimers;
class IOPCoreInterpreter;
class IOPIntc;
class IOPDmac;
class IOPTimers;

class Interpreter : public VMExecutionCore
{
public:
	explicit Interpreter(VMMain * vmMain);
	~Interpreter();

	/*
	Delegates to all components by calling mComponents[i]->intialise().
	*/
	void initalise() override;

	/*
	Always runs the EE Core.
	For the other components, first checks if they should be run and then controls their timing.
	*/
	void execute() override;

private:
	std::shared_ptr<VUInterpreter> mInterpreterVU0;
	std::shared_ptr<VUInterpreter> mInterpreterVU1;
	std::shared_ptr<VIF> mVIF0;
	std::shared_ptr<VIF> mVIF1;
	std::shared_ptr<EECoreInterpreter> mEECoreInterpreter;
	std::shared_ptr<EEDmac> mEEDmac;
	std::shared_ptr<EEIntc> mEEIntc;
	std::shared_ptr<EETimers> mEETimers;
	std::shared_ptr<IOPCoreInterpreter> mIOPCoreInterpreter;
	std::shared_ptr<IOPIntc> mIOPIntc;
	std::shared_ptr<IOPDmac> mIOPDmac;
	std::shared_ptr<IOPTimers> mIOPTimers;

	/*
	Used to iterate through all components, for initalsation.
	*/
	std::vector<std::shared_ptr<VMExecutionCoreComponent>> mComponents;
};

