#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

VUInterpreter::VUInterpreter(VMMain* vmMain, u32 vuUnitIndex) :
	VMExecutionCoreComponent(vmMain),
	mVUUnitIndex(vuUnitIndex)
{
}

VUInterpreter::~VUInterpreter()
{
}

s64 VUInterpreter::executionStep(const ClockSource_t& clockSource)
{
	// TODO: Implement.
	return 1;
}
