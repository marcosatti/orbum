#include "stdafx.h"

#include "Globals.h"

#include "PS2Exception_t.h"

#include "ExceptionHandler.h"


ExceptionHandler::ExceptionHandler(const VMMain *const _mainVM) : VMExceptionHandlerComponent(_mainVM)
{
}

void ExceptionHandler::handleException(const PS2Exception_t& ps2Exception)
{
	VMExceptionHandlerComponent::handleException(ps2Exception);
	//TODO: Implement.
}
