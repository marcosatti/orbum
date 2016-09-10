#pragma once

#include <memory>

#include "Common/Interfaces/VMExecutionCoreComponent.h"

/*
InterpreterEE is responsible for anything under the EE scope that is not directly under the EE Core.
This includes for example, the DMAC, INTC, Timer{0,1,2,3}, VU1, IPU etc.
*/

class INTCHandler;

class InterpreterEE : public VMExecutionCoreComponent
{
public:
	explicit InterpreterEE(const VMMain* const vmMain);

	void executionStep() override;

	void initalise() override;

private:

	// Component state.

	/*
	The INTC handler, responsible for producing an interrupt exception whenever the conditions are set.
	See EE Users Manual page 27 onwards.
	*/
	const std::unique_ptr<INTCHandler> mINTCHandler;
};