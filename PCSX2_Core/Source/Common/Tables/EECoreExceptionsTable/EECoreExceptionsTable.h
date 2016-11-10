#pragma once

#include "Common/Global/Globals.h"
#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"
#include "PS2Constants/PS2Constants.h"

using ExType = EECoreException_t::ExType;

class EECoreExceptionsTable
{
public:
	/*
	ExceptionProperties_t and ExceptionProperties[] describes the exception context parameters to be set when an exception of that type is handled.
	These properties are common to all exceptions. See page 94 of the EE Core Users Manual.
	There is an additional field (function index) to run the exception specific handler, which are defined in the "Operation" section in each exception of the manual.
	NOTE: Do NOT change the order - they are sync'd with the EECoreException_t::ExType enum order. If you change one you must reflect the changes in the other.
	*/
	struct ExceptionProperties_t
	{
		const char * mMnemonic;
		u8	         mLevel;
		s8	         mExeCode;
		s8	         mEXC2;
		u8	         mImplementationIndex;
	};
	static constexpr ExceptionProperties_t ExceptionProperties[PS2Constants::EE::EECore::Exceptions::NUMBER_EXCEPTIONS] =
	{
		{ "EX_RESET",                                2, -1,  0, 0  },
		{ "EX_NMI",                                  2, -1,  1, 1  },
		{ "EX_PERFORMANCE_COUNTER",                  2, -1,  2, 2  },
		{ "EX_DEBUG",                                2, -1,  4, 3  },
		{ "EX_INTERRUPT",                            1,  0, -1, 4  },
		{ "EX_TLB_MODIFIED",                         1,  1, -1, 5  },
		{ "EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD",    1,  2, -1, 6  },
		{ "EX_TLB_REFILL_STORE",                     1,  3, -1, 7  },
		{ "EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD",   1,  2, -1, 8  },
		{ "EX_TLB_INVALID_STORE",                    1,  3, -1, 9  },
		{ "EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD", 1,  4, -1, 10 },
		{ "EX_ADDRESS_ERROR_STORE",                  1,  5, -1, 11 },
		{ "EX_BUS_ERROR_INSTRUCTION_FETCH",          1,  6, -1, 12 },
		{ "EX_BUS_ERROR_LOAD_STORE",                 1,  7, -1, 13 },
		{ "EX_SYSTEMCALL",                           1,  8, -1, 14 },
		{ "EX_BREAK",                                1,  9, -1, 15 },
		{ "EX_RESERVED_INSTRUCTION",                 1, 10, -1, 16 },
		{ "EX_COPROCESSOR_UNUSABLE",                 1, 11, -1, 17 },
		{ "EX_OVERFLOW",                             1, 12, -1, 18 },
		{ "EX_TRAP",                                 1, 13, -1, 19 }
	};

	/*
	Returns the exception info above given the exception type.
	*/
	static const ExceptionProperties_t * getExceptionInfo(ExType exception);
};

