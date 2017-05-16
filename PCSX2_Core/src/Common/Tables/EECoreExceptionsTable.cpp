#include "Common/Tables/EECoreExceptionsTable.h"

const EECoreExceptionsTable::EECoreExceptionInfo_t * EECoreExceptionsTable::getInfo(const EECoreException_t exception)
{
	return &EECORE_EXCEPTION_TABLE[static_cast<int>(exception)];
}