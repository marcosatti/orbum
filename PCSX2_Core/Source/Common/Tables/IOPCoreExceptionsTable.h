#pragma once

#include "Common/Global/Globals.h"

#include "Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

/*
Contains static properties for the IOP Core exception types.
See R3000 documentation, for example: http://mescal.imag.fr/membres/vania.marangozova-martin/TEACHING/NACHOS/NACHOS_DOC/mips.html#exception.
*/
struct IOPCoreExceptionsTable
{
	struct IOPCoreExceptionInfo_t
	{
		const char * mMnemonic;
		int	         mExeCode;
	};
	static constexpr IOPCoreExceptionInfo_t IOPCORE_EXCEPTION_TABLE[Constants::IOP::IOPCore::R3000::NUMBER_EXCEPTIONS] =
	{
		{ "EX_INTERRUPT",                            0   },
		{ "EX_TLB_MODIFIED",                         1   },
		{ "EX_TLB_REFILL_INSTRUCTION_FETCH_LOAD",    2   },
		{ "EX_TLB_REFILL_STORE",                     3   },
		{ "EX_ADDRESS_ERROR_INSTRUCTION_FETCH_LOAD", 4   },
		{ "EX_ADDRESS_ERROR_STORE",                  5   },
		{ "EX_BUS_ERROR_INSTRUCTION_FETCH",          6   },
		{ "EX_BUS_ERROR_LOAD_STORE",                 7   },
		{ "EX_SYSTEMCALL",                           8   },
		{ "EX_BREAK",                                9   },
		{ "EX_RESERVED_INSTRUCTION",                 10  },
		{ "EX_COPROCESSOR_UNUSABLE",                 11  },
		{ "EX_OVERFLOW",                             12  },
		{ "EX_RESET",                                255 }, // Not documented as a type but used for resetting the R3000 state within the emulator.
	};

	/*
	Returns the exception info above given the exception type.
	*/
	static const IOPCoreExceptionInfo_t * getExceptionInfo(const IOPCoreException_t exception);
};

