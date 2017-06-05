#include "Common/Tables/IOPCoreExceptionsTable.h"

constexpr IOPCoreExceptionsTable::IOPCoreExceptionInfo_t IOPCoreExceptionsTable::IOPCORE_EXCEPTION_TABLE[Constants::IOP::IOPCore::R3000::NUMBER_EXCEPTIONS];

const IOPCoreExceptionsTable::IOPCoreExceptionInfo_t * IOPCoreExceptionsTable::getInfo(const IOPCoreException_t exception)
{
	return &IOPCORE_EXCEPTION_TABLE[static_cast<int>(exception)];
}