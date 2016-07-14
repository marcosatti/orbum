#include "stdafx.h"

#include "Globals.h"

#include "PS2Exception_t.h"

PS2Exception_t::PS2Exception_t(const ExceptionType exceptionType, const std::string exceptionMessage) :
	_exceptionType(exceptionType),
	_exceptionMessage(exceptionMessage),
	_resources_dump(nullptr)
{
}

PS2Exception_t::PS2Exception_t(const ExceptionType exceptionType, const std::string exceptionMessage, const PS2Resources_t & resourcesState) :
	_exceptionType(exceptionType),
	_exceptionMessage(exceptionMessage),
	_resources_dump(std::make_unique<PS2Resources_t>(resourcesState))
{
}

const PS2Exception_t::ExceptionType & PS2Exception_t::getExceptionType() const
{
	return _exceptionType;
}

const std::string & PS2Exception_t::getExceptionMessage() const
{
	return _exceptionMessage;
}
