#pragma once

#include "Common/Global/Globals.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/EE/EECore/Types/EECoreException_t.h"

/*
Contains static properties for the EE Core exception types.
*/
class EECoreExceptionsTable
{
public:
	/*
	ExceptionProperties_t and ExceptionProperties[] describes the exception context parameters to be set when an exception of that type is handled.
	These properties are common to all exceptions. See page 94 of the EE Core Users Manual.
	NOTE: Do NOT change the order - they are sync'd with the EECoreException_t enum order. If you change one you must reflect the changes in the other.
	NOTE2: mExeCode can refer to level 1 'ExeCode' field or the level 2 'EXC2' field, depending on the associated level.
	*/
	struct ExceptionProperties_t
	{
		const char * mMnemonic;
		u8	         mLevel;
		u8	         mExeCode;
	};
	static constexpr ExceptionProperties_t ExceptionProperties[PS2Constants::EE::EECore::R5900::NUMBER_EXCEPTIONS] =
	{
		{ "EX_RESET",                                2, 0  },
		{ "EX_NMI",                                  2, 1  },
		{ "EX_PERFORMANCE_COUNTER",                  2, 2  },
		{ "EX_DEBUG",                                2, 4  },
		{ "EX_INTERRUPT",                            1, 0  },
		{ "EX_TLB_MODIFIED",                         1, 1  },
		{ "EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD",    1, 2  },
		{ "EX_TLB_REFILL_STORE",                     1, 3  },
		{ "EX_TLB_INVALID_INSTRUCTION_FETCH_LOAD",   1, 2  },
		{ "EX_TLB_INVALID_STORE",                    1, 3  },
		{ "EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD", 1, 4  },
		{ "EX_ADDRESS_ERROR_STORE",                  1, 5  },
		{ "EX_BUS_ERROR_INSTRUCTION_FETCH",          1, 6  },
		{ "EX_BUS_ERROR_LOAD_STORE",                 1, 7  },
		{ "EX_SYSTEMCALL",                           1, 8  },
		{ "EX_BREAK",                                1, 9  },
		{ "EX_RESERVED_INSTRUCTION",                 1, 10 },
		{ "EX_COPROCESSOR_UNUSABLE",                 1, 11 },
		{ "EX_OVERFLOW",                             1, 12 },
		{ "EX_TRAP",                                 1, 13 }
	};

	/*
	Returns the exception info above given the exception type.
	*/
	static const ExceptionProperties_t * getExceptionInfo(const EECoreException_t & exception);
};

