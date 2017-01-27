#pragma once

#include "Common/Global/Globals.h"

#include "PS2Constants/PS2Constants.h"

#include "PS2Resources/IOP/IOPCore/Types/IOPCoreException_t.h"

class IOPCoreExceptionsTable
{
public:
	/*
	ExceptionProperties_t and ExceptionProperties[] describes the exception context parameters to be set when an exception of that type is handled.
	These properties are common to all exceptions. See R3000 documentation on the internet.
	For example: http://mescal.imag.fr/membres/vania.marangozova-martin/TEACHING/NACHOS/NACHOS_DOC/mips.html#exception
	NOTE: Do NOT change the order - they are sync'd with the IOPCoreException_t::ExType enum order. If you change one you must reflect the changes in the other.
	*/
	struct ExceptionProperties_t
	{
		const char * mMnemonic;
		u8	         mExeCode;
	};
	static constexpr ExceptionProperties_t ExceptionProperties[PS2Constants::IOP::IOPCore::Exceptions::NUMBER_EXCEPTIONS] =
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
	static const ExceptionProperties_t * getExceptionInfo(const IOPCoreException_t & exception);
};

