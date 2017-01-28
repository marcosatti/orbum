#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

VUInterpreter::VUInterpreter(VMMain* vmMain, u32 vuUnitIndex) :
	VMExecutionCoreComponent(vmMain),
	mVUUnitIndex(vuUnitIndex)
{
	addClockSource(ClockSource_t::EEBus);
}

VUInterpreter::~VUInterpreter()
{
}

double VUInterpreter::executionStep(const ClockSource_t& clockSource, const double& ticksAvailable)
{
	// TODO: Implement.
	return static_cast<double>(1);
}