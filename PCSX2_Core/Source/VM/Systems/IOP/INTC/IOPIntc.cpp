#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/IOP/INTC/IOPIntc.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPIntc::IOPIntc(VMMain * vmMain) : 
	VMSystem_t(vmMain, System_t::IOPIntc)
{
	mIOPCOP0 = getResources()->IOP->IOPCore->COP0;
	mINTC = getResources()->IOP->INTC;
}

IOPIntc::~IOPIntc()
{
}

double IOPIntc::executeStep(const ClockSource_t & clockSource, const double & ticksAvailable)
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
