#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/CDVD/CDVD_s.h"

#include "Resources/Resources_t.h"
#include "Resources/CDVD/CDVD_t.h"

CDVD_s::CDVD_s(VM * vm) :
	VMSystem_s(vm, System_t::CDVD)
{
}

void CDVD_s::initalise()
{
}

int CDVD_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	return ticksAvailable;
}
