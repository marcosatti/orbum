#include "Common/Global/Globals.h"

#include "VM/VM.h"
#include "VM/Systems/SIO2/SIO2_s.h"

#include "Resources/Resources_t.h"
#include "Resources/SIO2/SIO2_t.h"

SIO2_s::SIO2_s(VM * vm) : 
	VMSystem_t(vm, Context_t::SIO2)
{
	mSIO2 = getVM()->getResources()->SIO2;
}

void SIO2_s::initialise()
{
}

int SIO2_s::step(const Event_t & event)
{
	return event.mQuantity;
}