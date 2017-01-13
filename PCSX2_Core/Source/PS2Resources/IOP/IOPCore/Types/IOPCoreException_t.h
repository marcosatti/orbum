#pragma once

/*
Lists all of the 20 exceptions that can be encountered when running the IOP. For reference, see MIPS R3000 docs.
Due to macro issues caused by <math>, all of the exceptions have EX_ as a prefix.

See the IOPCoreExceptionHandler class for how they are handled, and the EE Core Users Manual.

NOTE: Do NOT change the order - they are sync'd with the IOPCoreExceptionsTable::ExceptionProperties[] array. If you change one you must reflect the changes in the other.
*/
enum class IOPCoreException_t {
	EX_INTERRUPT = 0,
	EX_TLB_MODIFIED = 1,
	EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD = 2,
	EX_TLB_REFILL_STORE = 3,
	EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD = 4,
	EX_ADDRESS_ERROR_STORE = 5,
	EX_BUS_ERROR_INSTRUCTION_FETCH = 6,
	EX_BUS_ERROR_LOAD_STORE = 7,
	EX_SYSTEMCALL = 8,
	EX_BREAK = 9,
	EX_RESERVED_INSTRUCTION = 10,
	EX_COPROCESSOR_UNUSABLE = 11,
	EX_OVERFLOW = 12,
	EX_RESET = 13 // Not documented as a type but used for resetting the R3000 state.
};
