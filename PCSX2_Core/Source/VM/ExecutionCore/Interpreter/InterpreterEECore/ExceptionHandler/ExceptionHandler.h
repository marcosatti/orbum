#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Types/PS2Exception/PS2Exception_t.h"
#include "Common/PS2 Constants/PS2Constants.h"

class VMMain;

class ExceptionHandler : public VMExecutionCoreComponent
{
public:
	explicit ExceptionHandler(const VMMain *const vmMain);

	// TODO: Check again for any missed settings that the individual exceptions require to be set. IE: Coprocessor unusable requires Cause.CE set to the coprocessor that caused it.
	
	/*
	Handles a given exception by:
	 1. Running the specific exception operation ("EX_HANDLER_*" defined below). This is done before 2. below.
	 2. Running the general exception handler (level 1 or 2) based on the exception properties defined.
	*/
	void handleException(const PS2Exception_t& PS2Exception);

private:
	/*
	The level 1 or level 2 exception handler, which is called by the base handleException() function.
	They have been adapted from the code in the EE Core Users Manual page 91 & 92.
	*/
	struct ExceptionProperties_t; // Forward declaration - see below for definition.
	void handleException_L1(const ExceptionProperties_t & exceptionProperties) const;
	void handleException_L2(const ExceptionProperties_t & exceptionProperties) const;

	/*
	As a part of the exception handling, there is additional actions that each type of exception requires.
	See EE Core Users manual page 95 onwards. They are prefixed with EX_HANDLER, and are pointed to by the ExceptionProperties[].
	NOTE: You do not need to put in anything that is done automatically by the general exception handelr algorithms (level 1 or 2).
	*/
	void EX_HANDLER_RESET();
	void EX_HANDLER_NMI();
	void EX_HANDLER_PERFORMANCE_COUNTER();
	void EX_HANDLER_DEBUG();
	void EX_HANDLER_INTERRUPT();
	void EX_HANDLER_TLB_MODIFIED();
	void EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD();
	void EX_HANDLER_TLB_REFILL_STORE();
	void EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD();
	void EX_HANDLER_TLB_INVALID_STORE();
	void EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD();
	void EX_HANDLER_ADDRESS_ERROR_STORE();
	void EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH();
	void EX_HANDLER_BUS_ERROR_LOAD_STORE();
	void EX_HANDLER_SYSTEMCALL();
	void EX_HANDLER_BREAK();
	void EX_HANDLER_RESERVED_INSTRUCTION();
	void EX_HANDLER_COPROCESSOR_UNUSABLE();
	void EX_HANDLER_OVERFLOW();
	void EX_HANDLER_TRAP();

	/*
	ExceptionProperties_t & ExceptionProperties[] describes the exception context parameters to be set when an exception of that type is handled.
	These properties are common to all exceptions. See page 94 of the EE Core Users Manual.
	There is an additional field to run the exception specific handler, which are defined in the "Operation" section in each exception of the manual.
	*/
	struct ExceptionProperties_t
	{
		PS2Exception_t::ExceptionType mExceptionType;
		u8							  mLevel;
		s8							  mExeCode;
		s8							  mEXC2;
		void						  (ExceptionHandler::*ExceptionHandlerFunction)();
	};
	const ExceptionProperties_t ExceptionProperties[PS2Constants::EE::EECore::Exceptions::NUMBER_EXCEPTIONS] = {
		{ PS2Exception_t::EX_RESET,                                2, -1,  0, EX_HANDLER_RESET },
		{ PS2Exception_t::EX_NMI,                                  2, -1,  1, EX_HANDLER_NMI },
		{ PS2Exception_t::EX_PERFORMANCE_COUNTER,                  2, -1,  2, EX_HANDLER_PERFORMANCE_COUNTER },
		{ PS2Exception_t::EX_DEBUG,                                2, -1,  4, EX_HANDLER_DEBUG },
		{ PS2Exception_t::EX_INTERRUPT,                            1,  0, -1, EX_HANDLER_INTERRUPT },
		{ PS2Exception_t::EX_TLB_MODIFIED,                         1,  1, -1, EX_HANDLER_TLB_MODIFIED },
		{ PS2Exception_t::EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD,    1,  2, -1, EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD },
		{ PS2Exception_t::EX_TLB_REFILL_STORE,                     1,  3, -1, EX_HANDLER_TLB_REFILL_STORE },
		{ PS2Exception_t::EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD,   1,  2, -1, EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD },
		{ PS2Exception_t::EX_TLB_INVALID_STORE,                    1,  3, -1, EX_HANDLER_TLB_INVALID_STORE },
		{ PS2Exception_t::EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD, 1,  4, -1, EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD },
		{ PS2Exception_t::EX_ADDRESS_ERROR_STORE,                  1,  5, -1, EX_HANDLER_ADDRESS_ERROR_STORE },
		{ PS2Exception_t::EX_BUS_ERROR_INSTRUCTION_FETCH,          1,  6, -1, EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH },
		{ PS2Exception_t::EX_BUS_ERROR_LOAD_STORE,                 1,  7, -1, EX_HANDLER_BUS_ERROR_LOAD_STORE },
		{ PS2Exception_t::EX_SYSTEMCALL,                           1,  8, -1, EX_HANDLER_SYSTEMCALL },
		{ PS2Exception_t::EX_BREAK,                                1,  9, -1, EX_HANDLER_BREAK },
		{ PS2Exception_t::EX_RESERVED_INSTRUCTION,                 1, 10, -1, EX_HANDLER_RESERVED_INSTRUCTION },
		{ PS2Exception_t::EX_COPROCESSOR_UNUSABLE,                 1, 11, -1, EX_HANDLER_COPROCESSOR_UNUSABLE },
		{ PS2Exception_t::EX_OVERFLOW,                             1, 12, -1, EX_HANDLER_OVERFLOW },
		{ PS2Exception_t::EX_TRAP,                                 1, 13, -1, EX_HANDLER_TRAP }
	};

	// Debug for counting the number of exceptions raised/handled.
#if defined(BUILD_DEBUG)
	u32 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif
};

