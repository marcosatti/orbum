#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMBaseComponent.h"

/*
TODO: Fill in documentation.
*/

class VMMain;

class VMExecutionCoreComponent : public VMBaseComponent
{
public:
	explicit VMExecutionCoreComponent(VMMain * vmMain);

	virtual ~VMExecutionCoreComponent();

	/*
	For each execution core component, this is called as a way to update the state of individual components. 
	This does not have to be implemented for all components (ie: for reactive components).
	*/
	virtual void executionStep();

	/*
	For each execution core component, this is called as a way to initalise/reset the state.
	This does not have to be implemented for all components (ie: for reactive components).
	*/
	virtual void initalise();
private:
};

