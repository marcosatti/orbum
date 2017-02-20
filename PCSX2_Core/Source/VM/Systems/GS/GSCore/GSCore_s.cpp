#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/GS/GSCore/GSCore_s.h"

GSCore_s::GSCore_s(VM * vm) :
	VMSystem_s(vm, System_t::GSCore)
{
}

GSCore_s::~GSCore_s()
{
}

int GSCore_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	return 1;
}
