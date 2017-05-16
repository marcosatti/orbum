#include "Common/Tables/IOPCoreExceptionsTable.h"

const IOPCoreExceptionsTable::IOPCoreExceptionInfo_t * IOPCoreExceptionsTable::getInfo(const IOPCoreException_t exception)
{
	return &IOPCORE_EXCEPTION_TABLE[static_cast<int>(exception)];
}