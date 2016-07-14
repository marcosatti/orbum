#include "stdafx.h"
#include "ExceptionHandler.h"


ExceptionHandler::ExceptionHandler(const VMMain *const _mainVM) : VMExceptionHandlerComponent(_mainVM)
{
}

void ExceptionHandler::handleException(PS2Exception_t && ps2Exception)
{
	//TODO: Implement.
}
