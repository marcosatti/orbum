#include "stdafx.h"

#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter.h"

VUInterpreter::VUInterpreter(VMMain* vmMain, u32 vuUnitIndex) :
	VMSystem_t(vmMain, vuUnitIndex == 0 ? System_t::VU0 : System_t::VU1),
	mVUUnitIndex(vuUnitIndex)
{
}

VUInterpreter::~VUInterpreter()
{
}

double VUInterpreter::executeStep(const ClockSource_t& clockSource, const double& ticksAvailable)
{
	// TODO: Implement.
	return 1;
}