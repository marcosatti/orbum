#pragma once

#include "Common/Global/Globals.h"

#include "VM/Component Interfaces/VMBaseComponent.h"

class PS2Exception_t;

class VMExceptionHandlerComponent : public VMBaseComponent
{
public:
	explicit VMExceptionHandlerComponent(const VMMain *const vmMain) : VMBaseComponent(vmMain)
	{
	}

#if defined(BUILD_DEBUG)
	u32 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	/*
	All PS2 VM exception handlers must implement a way to handle PS2 exceptions (duh).
	Yes, this interface is a bit redundant. Although there will only be one component that does this, it allows for expandibility if the situation arises.
	*/ 
	virtual void handleException(const PS2Exception_t& ps2Exception)
	{
#if defined(BUILD_DEBUG)
		DEBUG_HANDLED_EXCEPTION_COUNT += 1;
#endif
	}
};
