#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/IOP/SIO0/SIO0_s.h"

#include "Resources/Resources_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/SIO0/SIO0_t.h"

SIO0_s::SIO0_s(VM * vm) : 
	VMSystem_t(vm, Context_t::SIO0)
{
	mSIO0 = getVM()->getResources()->IOP->SIO0;
	mINTC = getVM()->getResources()->IOP->INTC;
}

void SIO0_s::initialise()
{
}

int SIO0_s::step(const Event_t & event)
{
	return event.mQuantity;
}