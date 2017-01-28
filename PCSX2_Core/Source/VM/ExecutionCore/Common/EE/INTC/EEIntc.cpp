#include "stdafx.h"

#include "Common/Types/Context_t.h"

#include "VM/ExecutionCore/Common/EE/INTC/EEIntc.h"

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EEIntc::EEIntc(VMMain * vmMain) : 
	VMExecutionCoreComponent(vmMain)
{
	mEECOP0 = getResources()->EE->EECore->COP0;
	mSTAT = getResources()->EE->INTC->STAT;
	mMASK = getResources()->EE->INTC->MASK;
	addClockSource(ClockSource_t::EEBus);
}

double EEIntc::executionStep(const ClockSource_t & clockSource, const double & ticksAvailable)
{
	// Check the interrupt status on the stat register.
	if (mSTAT->readWord(RAW) & mMASK->readWord(RAW))
		mEECOP0->Cause->setIRQLine(3);
	else
		mEECOP0->Cause->clearIRQLine(3);
	
	// INTC has completed 1 cycle.
	return 1;
}
