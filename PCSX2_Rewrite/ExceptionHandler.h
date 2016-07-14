#pragma once

#include "Globals.h"
#include "VMExceptionHandlerComponent.h"

/*
TODO: Fill in documentation.
*/

class VMMain;
class PS2Exception_t;

class ExceptionHandler : public VMExceptionHandlerComponent
{
public:
	explicit ExceptionHandler(const VMMain *const _mainVM);

	void handleException(PS2Exception_t&& ps2Exception);
};

