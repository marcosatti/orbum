#include "stdafx.h"

#include "VM/ExecutionCore/Interpreter/EE/VPU/VUInterpreter/VUInterpreter.h"

VUInterpreter::VUInterpreter(VMMain* vmMain, u32 vuUnitIndex) :
	VMExecutionCoreComponent(vmMain),
	mClockSources{ ClockSource_t::BUSCLK },
	mVUUnitIndex(vuUnitIndex)
{
}

VUInterpreter::~VUInterpreter()
{
}

const std::vector<ClockSource_t>& VUInterpreter::getClockSources()
{
	return mClockSources;
}
