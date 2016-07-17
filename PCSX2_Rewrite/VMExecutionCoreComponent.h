#pragma once
#include "VMBaseComponent.h"

class VMExecutionCoreComponent : public VMBaseComponent
{
public:
	explicit VMExecutionCoreComponent(const VMMain* _mainVM)
		: VMBaseComponent(_mainVM)
	{
	}

	/*
	All execution cores must implement a looping function to run the virtual machine and process the state.
	Note that the implementation does not need to have a while(true) loop of any sort - this is done though the VM.
	*/
	virtual void executionLoop()
	{
	}
};
