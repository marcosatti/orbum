#include "stdafx.h"

#include "Globals.h"

#include "PS2Exception_t.h"

#include "ExceptionHandler.h"


ExceptionHandler::ExceptionHandler(const VMMain *const vmMain) : VMExceptionHandlerComponent(vmMain)
{
}

void ExceptionHandler::handleException(const PS2Exception_t& PS2Exception)
{
	VMExceptionHandlerComponent::handleException(PS2Exception);
	//TODO: Implement.
}
