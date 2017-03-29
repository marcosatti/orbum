#pragma once

#include "Common/Global/Globals.h"

#include "Resources/EE/EECore/Types/EECoreException_t.h"

/*
Contains static properties for the EE Core exception types.
See page 94 of the EE Core Users Manual.
*/
struct EECoreExceptionsTable
{
	struct EECoreExceptionInfo_t
	{
		const char * mMnemonic;
		int	         mLevel;
		int	         mExeCode;
	};

	static constexpr EECoreExceptionInfo_t EECORE_EXCEPTION_TABLE[Constants::EE::EECore::R5900::NUMBER_EXCEPTIONS] =
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
	static const EECoreExceptionInfo_t * getExceptionInfo(const EECoreException_t exception);
};

