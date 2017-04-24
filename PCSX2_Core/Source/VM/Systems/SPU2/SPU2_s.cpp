#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/SPU2/SPU2_s.h"

#include "Resources/Resources_t.h"
#include "Resources/SPU2/SPU2_t.h"

SPU2_s::SPU2_s(VM * vm) : 
	VMSystem_s(vm, System_t::SPU2)
{
	mSPU2 = getVM()->getResources()->SPU2;
}

void SPU2_s::initalise()
{

}

int SPU2_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	return ticksAvailable;
}
