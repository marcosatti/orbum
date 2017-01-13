#pragma once

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMExecutionCoreComponent.h"
#include "Common/Tables/IOPCoreExceptionsTable/IOPCoreExceptionsTable.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

using ExceptionProperties_t = IOPCoreExceptionsTable::ExceptionProperties_t;

class VMMain;

/*
The exception handler provides 2 main points of functionality:
1. Handles the exception state for the IOP.
2. Handles exceptions using the documentation provided for the R3000 on the internet.
See for example: http://mescal.imag.fr/membres/vania.marangozova-martin/TEACHING/NACHOS/NACHOS_DOC/mips.html#exception
*/
class IOPCoreExceptionHandler : public VMExecutionCoreComponent
{
public:
	explicit IOPCoreExceptionHandler(VMMain * vmMain);

	/*
	Handles a given exception by:
	1. Running the specific exception operation ("EX_HANDLER_*" defined below).
	2. Running the general exception handler based on the exception properties defined.
	*/
	void handleException(const IOPCoreException_t& PS2Exception);

private:
	// Debug for counting the number of exceptions raised/handled and string representations.
#if defined(BUILD_DEBUG)
	u64 DEBUG_HANDLED_EXCEPTION_COUNT = 0;
#endif

	/*
	State variables, needed by functions below.
	*/
	IOPCoreException_t mIOPCoreException;
	const ExceptionProperties_t * mExceptionProperties;

	/*
	As a part of the exception handling, there is additional actions that each type of exception requires.
	See EE Core Users manual page 95 onwards. They are prefixed with EX_HANDLER.
	NOTE: You do not need to put in anything that is done automatically by the general exception handler algorithms (level 1 or 2).
	*/
	void EX_HANDLER_INTERRUPT();
	void EX_HANDLER_TLB_MODIFIED();
	void EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD();
	void EX_HANDLER_TLB_REFILL_STORE();
	void EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD();
	void EX_HANDLER_ADDRESS_ERROR_STORE();
	void EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH();
	void EX_HANDLER_BUS_ERROR_LOAD_STORE();
	void EX_HANDLER_SYSTEMCALL();
	void EX_HANDLER_BREAK();
	void EX_HANDLER_RESERVED_INSTRUCTION();
	void EX_HANDLER_COPROCESSOR_UNUSABLE();
	void EX_HANDLER_OVERFLOW();
	void EX_HANDLER_RESET(); // Not documented as an exception but used for resetting the R3000 state within the emulator.

	/*
	Static arrays needed to call the appropriate exception handler function. Based upon IOPCoreExceptionsTable::ExceptionProperties_t::mImplementationIndex.
	*/
	void(IOPCoreExceptionHandler::* EXCEPTION_HANDLERS[PS2Constants::IOP::IOPCore::Exceptions::NUMBER_EXCEPTIONS])() =
	{
		
		&IOPCoreExceptionHandler::EX_HANDLER_INTERRUPT,
		&IOPCoreExceptionHandler::EX_HANDLER_TLB_MODIFIED,
		&IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_INSTRUCTION_FETCH_LOAD,
		&IOPCoreExceptionHandler::EX_HANDLER_TLB_REFILL_STORE,
		&IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD,
		&IOPCoreExceptionHandler::EX_HANDLER_ADDRESS_ERROR_STORE,
		&IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_INSTRUCTION_FETCH,
		&IOPCoreExceptionHandler::EX_HANDLER_BUS_ERROR_LOAD_STORE,
		&IOPCoreExceptionHandler::EX_HANDLER_SYSTEMCALL,
		&IOPCoreExceptionHandler::EX_HANDLER_BREAK,
		&IOPCoreExceptionHandler::EX_HANDLER_RESERVED_INSTRUCTION,
		&IOPCoreExceptionHandler::EX_HANDLER_COPROCESSOR_UNUSABLE,
		&IOPCoreExceptionHandler::EX_HANDLER_OVERFLOW,
		&IOPCoreExceptionHandler::EX_HANDLER_RESET, // Not documented as an exception but used for resetting the R3000 state within the emulator.
	};
};

