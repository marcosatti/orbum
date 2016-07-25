#include "stdafx.h"

#include <stdexcept>

#include "Globals.h"

#include "ExceptionHandler.h"
#include "PS2Exception_t.h"


ExceptionHandler::ExceptionHandler(const VMMain *const vmMain) : VMExceptionHandlerComponent(vmMain)
{
}

void ExceptionHandler::handleException(const PS2Exception_t& PS2Exception)
{
	// Call the super class method. Contains useful debugging info if needed.
	VMExceptionHandlerComponent::handleException(PS2Exception);

	// Call the Level 1 or Level 2 exception handler based on the exception, or throw runtime_error if exception type/properties does not exist.
	const ExceptionProperties_t & exceptionProperties = ExceptionProperties[PS2Exception.getExceptionType()];
	switch(exceptionProperties.mLevel)
	{
	case 1:
		handleException_L1(PS2Exception);
		break;
	case 2:
		handleException_L2(PS2Exception);
		break;
	default:
		throw std::runtime_error("PS2Exception parsed contained an unknown exception type.");
	}
}

void ExceptionHandler::handleException_L1(const PS2Exception_t & PS2Exception)
{
	// Exception level 1 handler code. Adapted from EE Core Users Manual page 91.

}

void ExceptionHandler::handleException_L2(const PS2Exception_t & PS2Exception)
{
	// Exception level 2 handler code. Adapted from EE Core Users Manual page 92.
}
