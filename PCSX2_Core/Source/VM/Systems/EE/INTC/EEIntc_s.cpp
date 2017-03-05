#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/EE/INTC/EEIntc_s.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

EEIntc_s::EEIntc_s(VM * vm) :
	VMSystem_s(vm, System_t::EEIntc)
{
	mEECOP0 = getVM()->getResources()->EE->EECore->COP0;
	mINTC = getVM()->getResources()->EE->INTC;
}

EEIntc_s::~EEIntc_s()
{
}

int EEIntc_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check the interrupt status on the stat register.
	if (mINTC->STAT->readWord(RAW) & mINTC->MASK->readWord(RAW))
		mEECOP0->Cause->setIRQLine(2);
	else
		mEECOP0->Cause->clearIRQLine(2);
	
	// INTC has completed 1 cycle.
	return 1;
}
