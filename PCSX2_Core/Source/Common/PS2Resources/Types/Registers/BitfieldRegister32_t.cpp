#include "stdafx.h"


#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

BitfieldRegister32_t::BitfieldRegister32_t()
{
}

void BitfieldRegister32_t::registerField(const char * fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue)
{
	mFieldMap.insert({ fieldName, { fieldName, fieldStartPosition, fieldLength, fieldInitialValue } });
}

u32 BitfieldRegister32_t::getFieldValue(const char * fieldName)
{
	return mFieldMap[fieldName].mFieldValue;
}

void BitfieldRegister32_t::setFieldValue(const char * fieldName, const u32 & value)
{
	mFieldMap[fieldName].mFieldValue = value;
}

u32 BitfieldRegister32_t::getRegisterValue()
{
	// Need to sync Register value with the individual fields first.
	for(auto &field : mFieldMap)
	{
		const BitfieldProperties_t & props = field.second;
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
	}

	// Return the bitfield value;
	return this->UW;
}

void BitfieldRegister32_t::setRegisterValue(const u32 & value)
{
	// Need to sync the parsed value with the Register first.
	this->UW = value;

	// Set fields based on UW value.
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = getBitRange32(props.mFieldStartPosition, props.mFieldLength);
	}
}

void BitfieldRegister32_t::initaliseAllFields()
{
	// Initialse all fields to its initial value.
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = props.mInitialFieldValue;
	}
}

void BitfieldRegister32_t::initaliseField(const char * fieldName)
{
	BitfieldProperties_t & props = mFieldMap[fieldName];
	props.mFieldValue = props.mInitialFieldValue;
}
