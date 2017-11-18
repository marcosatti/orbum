

#include "VM/VM.h"
#include "VM/Systems/EE/INTC/EEIntc_s.h"

#include "Resources/RResources.hpp"
#include "Resources/Ee/REe.hpp"
#include "Resources/Ee/Intc/REeIntc.hpp"
#include "Resources/Ee/Intc/EeIntcRegisters.hpp"
#include "Resources/Ee/Core/REeCore.hpp"
#include "Resources/Ee/Core/EeCoreCop0.hpp"
#include "Resources/Ee/Core/EeCoreCop0Registers.hpp"

EEIntc_s::EEIntc_s(VM * vm) :
	VMSystem_t(vm, Context_t::EEIntc)
{
	mEECOP0 = getVM()->getResources()->EE->EECore->COP0;
	mINTC = getVM()->getResources()->EE->INTC;
}

void EEIntc_s::initialise()
{
	mINTC->STAT->initialise();
	mINTC->MASK->initialise();
}

int EEIntc_s::step(const Event_t & event)
{
	// Check the interrupt status on the stat register.
	if (mINTC->STAT->read_uword() & mINTC->MASK->read_uword())
		mEECOP0->Cause->set_irq_line(, 2);
	else
		mEECOP0->Cause->clear_irq_line(, 2);
	
	// INTC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	return event.mQuantity;
#else
	return 1;
#endif
}
