#include "VM/VM.h"
#include "VM/Systems/EE/VPU/VUInterpreter/VUInterpreter_s.h"

#include "Resources/RResources.hpp"
#include "Resources/Ee/REe.hpp"
#include "Resources/EE/VPU/RVpu.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/Ee/Vpu/VuCores.hpp"

VUInterpreter_s::VUInterpreter_s(VM * vm, const int vuCoreIndex) :
	VMSystem_t(vm, vuCoreIndex == 0 ? Context_t::VU0 : Context_t::VU1),
	mVUCoreIndex(vuCoreIndex),
	mVUInstruction(0)
{
	mVUCore = getVM()->getResources()->EE->VPU->VU->VU_CORES[vuCoreIndex];
}

void VUInterpreter_s::initialise()
{
}

int VUInterpreter_s::step(const Event_t & event)
{
	// TODO: Implement.
	return event.mQuantity;
}
