

#include "VM/VM.h"
#include "VM/Systems/IOP/INTC/IOPIntc_s.h"

#include "Resources/RResources.hpp"
#include "Resources/IOP/IOP_t.h"
#include "Resources/Iop/Intc/RIopIntc.hpp"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/Iop/Core/RIopCore.h"
#include "Resources/Iop/Core/IopCoreCop0.h"
#include "Resources/Iop/Core/IopCoreCop0Registers.hpp"

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

int IOPIntc_s::step(const Event_t & event)
{
	// Check the master CTRL register and STAT register.
	bool interrupt = false;
	if (mINTC->CTRL->read_uword() > 0)
	{
		if (mINTC->STAT->read_uword() & mINTC->MASK->read_uword())
			interrupt = true;
	}

	// Set IRQ line 2 on IOP Core if an interrupt occured.
	if (interrupt)
		mIOPCOP0->Cause->set_irq_line(, 2);
	else
		mIOPCOP0->Cause->clear_irq_line(, 2);

	// INTC has completed 1 cycle.
#if ACCURACY_SKIP_TICKS_ON_NO_WORK
	return event.mQuantity;
#else
	return 1;
#endif
}
