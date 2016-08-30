#include "stdafx.h"

#include <string>

#include "Common/Global/Globals.h"

#include "Common/PS2 Resources/PS2Resources_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"

void RegisterCount_t::increment(u32 value)
{
	setFieldValue(RegisterCount_t::Fields::Count, getFieldValue(RegisterCount_t::Fields::Count) + value);
}

void RegisterCompare_t::setFieldValue(const std::string& fieldName, const u32& value)
{
	getRootResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setFieldValue(fieldName, value);
}

void RegisterCompare_t::setRegisterValue(u32 value)
{
	getRootResources()->EE->EECore->COP0->Cause->setFieldValue(RegisterCause_t::Fields::IP7, 0);
	BitfieldRegister32_t::setRegisterValue(value);
}
