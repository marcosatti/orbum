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
}

s64 IOPIntc::executionStep(const ClockSource_t & clockSource)
{
	auto& COP0 = getResources()->IOP->IOPCore->COP0;
	auto& CTRL = getResources()->IOP->INTC->CTRL;

	// First check the master CTRL register.
	bool interrupt = false;
	if (CTRL->readWord(Context_t::RAW) > 0)
	{
		auto& STAT = getResources()->IOP->INTC->STAT;
		auto& MASK = getResources()->IOP->INTC->MASK;

		// If any of the I_STAT with logical AND I_MASK bits are 1, then an interrupt may be generated.
		if (STAT->readWord(Context_t::RAW) & MASK->readWord(Context_t::RAW))
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		COP0->Cause->setIRQLine(2);
	else
		COP0->Cause->clearIRQLine(2);

	// INTC has completed 1 cycle.
	return 1;
}
