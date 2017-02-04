#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/Systems/EE/INTC/EEIntc.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EEIntc::EEIntc(VM * vmMain) :
	VMSystem_t(vmMain, System_t::EEIntc)
{
	mEECOP0 = getResources()->EE->EECore->COP0;
	mINTC = getResources()->EE->INTC;
}

EEIntc::~EEIntc()
{
}

double EEIntc::executeStep(const ClockSource_t & clockSource, const double & ticksAvailable)
{
	// Check the interrupt status on the stat register.
	if (mINTC->STAT->readWord(RAW) & mINTC->MASK->readWord(RAW))
		mEECOP0->Cause->setIRQLine(3);
	else
		mEECOP0->Cause->clearIRQLine(3);
	
	// INTC has completed 1 cycle.
	return 1;
}
