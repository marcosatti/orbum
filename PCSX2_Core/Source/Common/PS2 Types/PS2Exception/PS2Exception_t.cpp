#include "stdafx.h"

#include "Common/PS2 Types/PS2Exception/PS2Exception_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

PS2Exception_t::PS2Exception_t(const ExceptionType & exceptionType) :
	mExceptionType(exceptionType),
	mExceptionMessage(nullptr),
	mResourcesDump(nullptr)
{
}

PS2Exception_t::PS2Exception_t(const ExceptionType & exceptionType, const std::string & exceptionMessage) :
	mExceptionType(exceptionType),
	mExceptionMessage(exceptionMessage),
	mResourcesDump(nullptr)
{
}

PS2Exception_t::PS2Exception_t(const ExceptionType & exceptionType, const std::string & exceptionMessage, const PS2Resources_t & resourcesState) :
	mExceptionType(exceptionType),
	mExceptionMessage(exceptionMessage),
	mResourcesDump(std::make_unique<PS2Resources_t>(resourcesState))
{
}

PS2Exception_t::~PS2Exception_t()
{
}

const PS2Exception_t::ExceptionType & PS2Exception_t::getExceptionType() const
{
	return mExceptionType;
}

const std::string & PS2Exception_t::getExceptionMessage() const
{
	return mExceptionMessage;
}
