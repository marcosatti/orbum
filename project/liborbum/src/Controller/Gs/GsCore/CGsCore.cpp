

#include "VM/Systems/GS/GSCore/GSCore_s.h"

GSCore_s::GSCore_s(VM * vm) :
	VMSystem_t(vm, Context_t::GSCore)
{
}

void GSCore_s::initialise()
{
}

int GSCore_s::step(const Event_t & event)
{
	return event.mQuantity;
}
