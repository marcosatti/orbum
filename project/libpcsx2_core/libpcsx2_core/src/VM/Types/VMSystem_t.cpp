#include "VM/VM.h"
#include "VM/Types/VMSystem_t.h"

#include "Resources/Resources_t.h"
#include "Resources/Events/Events_t.h"

VMSystem_t::VMSystem_t(VM * vm, const Context_t system) :
	mVM(vm),
	mContext(system)
{
	mEvents = getVM()->getResources()->Events;
}

VM * VMSystem_t::getVM() const
{
	return mVM;
}

Context_t VMSystem_t::getContext() const
{
	return mContext;
}

void VMSystem_t::initialise()
{
}

void VMSystem_t::run()
{
	auto& queue = mEvents->getEvents(mContext);

	// Execute event.
	Event_t event;
	while (queue->pop(event))
	{
		while (event.mQuantity > 0)
			event.mQuantity -= step(event);
	}
}
