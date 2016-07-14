#pragma once

#include <string>
#include <memory>

#include "Globals.h"
#include "PS2Resources_t.h"

/*
TODO: Fill in documentation.
*/


class PS2Exception_t
{
public:
	enum ExceptionType
	{
		RESET_NMI,
		TLB_REFILL,
		COUNTER,
		DEBUG,
		COMMON,
		INTERRUPT
	};

	PS2Exception_t(const ExceptionType exceptionType, const std::string exceptionMessage);
	PS2Exception_t(const ExceptionType exceptionType, const std::string exceptionMessage, const PS2Resources_t & resourcesState);
	~PS2Exception_t();

	void raiseException();
	const ExceptionType &getExceptionType() const;
	const std::string &getExceptionMessage() const;

private:
	const ExceptionType _exceptionType;
	const std::string _exceptionMessage;
	const std::unique_ptr<PS2Resources_t> _resources_dump;
};

