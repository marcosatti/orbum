#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/INTC/IOPIntc_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPIntc_s::IOPIntc_s(VM * vm) : 
	VMSystem_s(vm, System_t::IOPIntc)
{
	mIOPCOP0 = getVM()->getResources()->IOP->IOPCore->COP0;
	mINTC = getVM()->getResources()->IOP->INTC;
}

IOPIntc_s::~IOPIntc_s()
{
}

int IOPIntc_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (mINTC->CTRL->readWord(RAW) > 0)
	{
		if (mINTC->STAT->readWord(RAW) & mINTC->MASK->readWord(RAW))
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		mIOPCOP0->Cause->setIRQLine(2);
	else
		mIOPCOP0->Cause->clearIRQLine(2);

	// INTC has completed 1 cycle.
	return 1;
}
