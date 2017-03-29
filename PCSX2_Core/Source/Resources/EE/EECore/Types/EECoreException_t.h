#pragma once

/*
Lists all of the 20 exceptions that can be encountered when running the EECore. For reference, see EE Core Users Manual page 94.
Enum order sync'd with the exception order in the manual.
*/
enum class EECoreException_t 
{
	EX_RESET = 0,
	EX_NMI = 1,
	EX_PERFORMANCE_COUNTER = 2,
	EX_DEBUG = 3,
	EX_INTERRUPT = 4,
	EX_TLB_MODIFIED = 5,
	EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD = 6,
	EX_TLB_REFILL_STORE = 7,
	EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD = 8,
	EX_TLB_INVALID_STORE = 9,
	EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD = 10,
	EX_ADDRESS_ERROR_STORE = 11,
	EX_BUS_ERROR_INSTRUCTION_FETCH = 12,
	EX_BUS_ERROR_LOAD_STORE = 13,
	EX_SYSTEMCALL = 14,
	EX_BREAK = 15,
	EX_RESERVED_INSTRUCTION = 16,
	EX_COPROCESSOR_UNUSABLE = 17,
	EX_OVERFLOW = 18,
	EX_TRAP = 19
};
