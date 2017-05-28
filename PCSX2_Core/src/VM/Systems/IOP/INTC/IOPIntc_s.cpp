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
	VMSystem_t(vm, Context_t::IOPIntc)
{
	mIOPCOP0 = getVM()->getResources()->IOP->IOPCore->COP0;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void IOPIntc_s::initialise()
{
	mINTC->CTRL->initialise();
	mINTC->STAT->initialise();
	mINTC->MASK->initialise();
}

int IOPIntc_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (mINTC->CTRL->readWord(getContext()) > 0)
	{
		if (mINTC->STAT->readWord(getContext()) & mINTC->MASK->readWord(getContext()))
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		mIOPCOP0->Cause->setIRQLine(getContext(), 2);
	else
		mIOPCOP0->Cause->clearIRQLine(getContext(), 2);

	// INTC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	return ticksAvailable;
#else
	return 1;
#endif
}
