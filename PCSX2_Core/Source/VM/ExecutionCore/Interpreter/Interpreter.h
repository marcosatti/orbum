#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"


/*
TODO: Fill in documentation, and add threading for sub components. Sub components can be thought of the different manual sections (EE Core, EE, GS, etc) perhaps?
The PCSX2 interpreter. Provides an implementation of a PS2 system.
Idealy, any sub components in here are threaded - that is, they can run independently of eachother (or spinlock/wait until data is ready).
*/

class VMMain;
class InterpreterEE;
class InterpreterEECore;
//class InterpreterVU;
//class InterpreterGS;

class Interpreter : public VMExecutionCoreComponent
{
public:
	explicit Interpreter(const VMMain *const vmMain);

	void executionStep() override;

	void initalise() override;

private:
	const std::unique_ptr<InterpreterEE> mInterpreterEE;
	const std::unique_ptr<InterpreterEECore> mInterpreterEECore;
	//const std::unique_ptr<InterpreterVU> mInterpreterVU; // TODO: look at putting VU0 and VU1 on a separate thread - looks like a good candidate.
	//const std::unique_ptr<InterpreterGS> mInterpreterGS;
};

