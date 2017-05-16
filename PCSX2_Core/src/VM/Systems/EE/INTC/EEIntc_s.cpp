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

void EEIntc_s::initialise()
{
	mINTC->STAT->initialise();
	mINTC->MASK->initialise();
}

int EEIntc_s::step(const ClockSource_t clockSource, const int ticksAvailable)
{
	// Check the interrupt status on the stat register.
	if (mINTC->STAT->readWord(getContext()) & mINTC->MASK->readWord(getContext()))
		mEECOP0->Cause->setIRQLine(getContext(), 2);
	else
		mEECOP0->Cause->clearIRQLine(getContext(), 2);
	
	// INTC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	return ticksAvailable;
#else
	return 1;
#endif
}
