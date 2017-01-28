#include "stdafx.h"

#include "Common/Types/Context_t.h"

#include "VM/ExecutionCore/Common/IOP/INTC/IOPIntc.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0_t.h"
#include "PS2Resources/IOP/IOPCore/Types/IOPCoreCOP0Registers_t.h"

IOPIntc::IOPIntc(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain)
{
	mIOPCOP0 = getResources()->IOP->IOPCore->COP0;
	mSTAT = getResources()->IOP->INTC->STAT;
	mMASK = getResources()->IOP->INTC->MASK;
	mCTRL = getResources()->IOP->INTC->CTRL;
	addClockSource(ClockSource_t::IOPBus);
}

double IOPIntc::executionStep(const ClockSource_t & clockSource, const double & ticksAvailable)
{
	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (mCTRL->readWord(RAW) > 0)
	{
		if (mSTAT->readWord(RAW) & mMASK->readWord(RAW))
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
