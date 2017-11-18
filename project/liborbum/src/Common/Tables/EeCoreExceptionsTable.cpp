#include "Common/Tables/EECoreExceptionsTable.h"

constexpr EECoreExceptionsTable::EECoreExceptionInfo_t EECoreExceptionsTable::EECORE_EXCEPTION_TABLE[Constants::EE::EECore::R5900::NUMBER_EXCEPTIONS];

const EECoreExceptionsTable::EECoreExceptionInfo_t * EECoreExceptionsTable::getInfo(const EECoreException_t exception)
{
	return &EECORE_EXCEPTION_TABLE[static_cast<int>(exception)];
}