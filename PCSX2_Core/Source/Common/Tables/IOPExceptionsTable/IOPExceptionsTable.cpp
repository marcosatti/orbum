#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/Tables/IOPExceptionsTable/IOPExceptionsTable.h"

const IOPExceptionsTable::ExceptionProperties_t * IOPExceptionsTable::getExceptionInfo(ExType exception)
{
	return &ExceptionProperties[static_cast<u8>(exception)];
}
