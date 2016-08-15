#pragma once

#include <memory>
#include <unordered_map>

/*
See chapter 4 in EE Core Users Manual for all the info relating to exceptions.
Encompasses all of the exceptions the PS2 system might generate.
An exception always causes kernel mode to be invoked, and can be generated from user, supervisor or kernel mode.
An exception vector located at a fixed address will be used to handle exceptions, which in emulation is handled by the bios.
However, there is still a need for the correct context to be set (setting cause and status registers), which is what this 
 exception class combined with the VM exception handler will do.
*/

class PS2Resources_t;

class PS2Exception_t
{
public:
	/*
	Lists all of the 20 exceptions that can be encountered when running a PS2 system. For reference, see EE Core Users Manual page 94.
	Due to macro issues caused by <math>, all of the exceptions have EX_ as a prefix.
	*/
	enum ExceptionType
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

	PS2Exception_t(const ExceptionType & exceptionType);
	PS2Exception_t(const ExceptionType & exceptionType, const std::string & exceptionMessage); // Useful for debugging.
	PS2Exception_t(const ExceptionType & exceptionType, const std::string & exceptionMessage, const PS2Resources_t & resourcesState); // Useful for debugging.
	~PS2Exception_t();

	const ExceptionType & getExceptionType() const;
	const std::string & getExceptionMessage() const;

private:
	const ExceptionType mExceptionType;
	const std::string mExceptionMessage;
	const std::shared_ptr<PS2Resources_t> mResourcesDump;
};

