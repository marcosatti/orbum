#include "stdafx.h"

#include "VM/VM.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"

VUInterpreter_s::VUInterpreter_s(VM * vm, u32 vuUnitIndex) :
	VMSystem_s(vm, vuUnitIndex == 0 ? System_t::VU0 : System_t::VU1),
	mVUUnitIndex(vuUnitIndex),
	mVUInstruction(0)
{
	mVuUnit = getVM()->getResources()->EE->VPU->VU->VU_UNITS[vuUnitIndex];
}

int VUInterpreter_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// TODO: Implement.
	return ticksAvailable;
}
