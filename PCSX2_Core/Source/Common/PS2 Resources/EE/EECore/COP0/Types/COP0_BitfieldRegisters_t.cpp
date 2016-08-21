#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP0/Types/COP0_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

COP0BitfieldRegister32_t::COP0BitfieldRegister32_t(const PS2Resources_t* const PS2Resources) :
	COP0ResourcesSubobject(PS2Resources)
{
}

u32 COP0BitfieldRegister32_t::getFieldValue(const std::string& fieldName)
{
	checkCOP0Usable();
	return BitfieldRegister32_t::getFieldValue(fieldName);
}

u32 COP0BitfieldRegister32_t::getRawFieldValue(const std::string& fieldName)
{
	return BitfieldRegister32_t::getFieldValue(fieldName);
}

void COP0BitfieldRegister32_t::setFieldValue(const std::string& fieldName, const u32& value)
{
	checkCOP0Usable();
	BitfieldRegister32_t::setFieldValue(fieldName, value);
}

void COP0BitfieldRegister32_t::setRawFieldValue(const std::string& fieldName, const u32& value)
{
	BitfieldRegister32_t::setFieldValue(fieldName, value);
}

u32 COP0BitfieldRegister32_t::getRegisterValue()
{
	checkCOP0Usable();
	return BitfieldRegister32_t::getRegisterValue();
}

void COP0BitfieldRegister32_t::setRegisterValue(u32 value)
{
	checkCOP0Usable();
	BitfieldRegister32_t::setRegisterValue(value);
}
