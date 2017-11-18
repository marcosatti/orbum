

#include "VM/VM.h"
#include "VM/Systems/IOP/SIO2/SIO2_s.h"

#include "Resources/RResources.hpp"
#include "Resources/IOP/IOP_t.h"
#include "Resources/Iop/Intc/RIopIntc.hpp"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/SIO2/SIO2_t.h"
#include "Resources/IOP/SIO2/Types/SIO2Registers_t.h"

SIO2_s::SIO2_s(VM * vm) : 
	VMSystem_t(vm, Context_t::SIO2)
{
	mSIO2 = getVM()->getResources()->IOP->SIO2;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void SIO2_s::initialise()
{
}

int SIO2_s::step(const Event_t & event)
{
	if (mSIO2->CTRL->mPendingCommand)
	{
		mSIO2->CTRL->mPendingCommand = false; 
		
		/*
		if (mSIO2->CTRL->getFieldValue(, SIO2Register_CTRL_t::Reset) > 0)
		{
		}
		else
		{

		}
		*/

		// Raise IOP IRQ always.
		mINTC->STAT->setFieldValue(, IOPIntcRegister_STAT_t::SIO2, 1);
	}
	return event.mQuantity;
}