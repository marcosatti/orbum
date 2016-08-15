#include "stdafx.h"

#include "Common/PS2 Resources/EE/EECore/COP1/Types/COP1_BitfieldRegisters_t.h"
#include "Common/PS2 Resources/PS2Resources_t.h"

COP1BitfieldRegister32_t::COP1BitfieldRegister32_t(const PS2Resources_t* const PS2Resources) : 
	COP1ResourcesSubobject(PS2Resources)
{
}

u32 COP1BitfieldRegister32_t::getFieldValue(const std::string& fieldName)
{
	checkCOP1Usable();
	return BitfieldRegister32_t::getFieldValue(fieldName);
}

void COP1BitfieldRegister32_t::setFieldValue(const std::string& fieldName, const u32& value)
{
	checkCOP1Usable();
	BitfieldRegister32_t::setFieldValue(fieldName, value);
}

u32 COP1BitfieldRegister32_t::getRegisterValue()
{
	checkCOP1Usable();
	return BitfieldRegister32_t::getRegisterValue();
}

void COP1BitfieldRegister32_t::setRegisterValue(u32 value)
{
	checkCOP1Usable();
	BitfieldRegister32_t::setRegisterValue(value);
}
