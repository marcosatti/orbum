#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

/*
The exception handler provides 2 main points of functionality:
 1. Handles the exception state for the EE Core.
 2. Handles exceptions using the documentation provided in EE Core Users Manual chapter 4.
*/

using ExceptionProperties_t = EECoreExceptionsTable::ExceptionProperties_t;

class VMMain;

class EECoreExceptionHandler : public VMExecutionCoreComponent
{
public:
	explicit EECoreExceptionHandler(VMMain * vmMain);

	/*
	Check the exception state (PS2Resources->EE->EECore->Exceptions), and make a call to handleException if one is set (and not masked).
	*/
	void checkExceptionState();

	/*
	Handles a given exception by:
	1. Running the specific exception operation ("EX_HANDLER_*" defined below). This is done before 2. below.
	2. Running the general exception handler (level 1 or 2) based on the exception properties defined.

	This is made public as a direct way to reset the PS2 state from the VM.
	*/
	void handleException(const EECoreException_t& PS2Exception);

private:
	// Debug for counting the number of exceptions raised/handled and string representations.
#if defined(BUILD_DEBUG)
	u64 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	/*
	State variables, needed by functions below.
	*/
	const EECoreException_t * mEECoreException;
	const ExceptionProperties_t * mExceptionProperties;

	/*
	The level 1 or level 2 exception handler, which is called by the base handleException() function.
	They have been adapted from the code in the EE Core Users Manual page 91 & 92.
	*/
	
	void handleException_L1() const;
	void handleException_L2() const;

	/*
	As a part of the exception handling, there is additional actions that each type of exception requires.
	See EE Core Users manual page 95 onwards. They are prefixed with EX_HANDLER.
	NOTE: You do not need to put in anything that is done automatically by the general exception handler algorithms (level 1 or 2).
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
	Static arrays needed to call the appropriate exception handler function. Based upon EECoreExceptionsTable::ExceptionProperties_t::mImplementationIndex.
	*/
	void(EECoreExceptionHandler::*const EXCEPTION_HANDLERS[PS2Constants::EE::EECore::Exceptions::NUMBER_EXCEPTIONS])() =
	{
		&EECoreExceptionHandler::EX_HANDLER_RESET,
		&EECoreExceptionHandler::EX_HANDLER_NMI,
		&EECoreExceptionHandler::EX_HANDLER_PERFORMANCE_COUNTER,
		&EECoreExceptionHandler::EX_HANDLER_DEBUG,
		&EECoreExceptionHandler::EX_HANDLER_INTERRUPT,
		&EECoreExceptionHandler::EX_HANDLER_TLB_MODIFIED,
		&EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD,
		&EECoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE,
		&EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_INSTRUCTION_FETCH_LOAD,
		&EECoreExceptionHandler::EX_HANDLER_TLB_INVALID_STORE,
		&EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD,
		&EECoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE,
		&EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH,
		&EECoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE,
		&EECoreExceptionHandler::EX_HANDLER_SYSTEMCALL,
		&EECoreExceptionHandler::EX_HANDLER_BREAK,
		&EECoreExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION,
		&EECoreExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE,
		&EECoreExceptionHandler::EX_HANDLER_OVERFLOW,
		&EECoreExceptionHandler::EX_HANDLER_TRAP
	};
};

