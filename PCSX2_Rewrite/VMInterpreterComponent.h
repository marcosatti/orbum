#pragma once

#include "Globals.h"

#include "VMExecutionCoreComponent.h"

/*
TODO: Fill in documentation.
*/

class VMMain;
class Interpreter;

class VMInterpreterComponent : public VMBaseComponent
{
public:
	explicit VMInterpreterComponent(const VMMain *const _mainVM, const Interpreter *const _interpreter) :
		VMBaseComponent(_mainVM),
		interpreter(_interpreter)
	{
	}

	~VMInterpreterComponent()
	{
	}

	INLINE const Interpreter *const &getInterpreter() const
	{
		return interpreter;
	}

	/*
	For each interpreter component, this is called as a way to update the state of individual components.
	*/
	virtual void runInterpreterComponent()
	{
	}
private:
	/*
	Interpreter pointer in order to communicate with the other interpreter components if required.
	*/
	const Interpreter *const interpreter;
};

