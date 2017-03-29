#include "stdafx.h"

#include "Common/Tables/EECoreExceptionsTable.h"

const EECoreExceptionsTable::EECoreExceptionInfo_t * EECoreExceptionsTable::getExceptionInfo(const EECoreException_t exception)
{
	return &EECORE_EXCEPTION_TABLE[static_cast<int>(exception)];
}