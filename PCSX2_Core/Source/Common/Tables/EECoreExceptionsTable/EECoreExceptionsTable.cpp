#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Tables/EECoreExceptionsTable/EECoreExceptionsTable.h"

const EECoreExceptionsTable::ExceptionProperties_t * EECoreExceptionsTable::getExceptionInfo(ExType exception)
{
	return &ExceptionProperties[static_cast<u8>(exception)];
}
