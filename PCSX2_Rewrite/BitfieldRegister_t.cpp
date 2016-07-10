#include "stdafx.h"

#include "Globals.h"
#include "BitfieldRegister_t.h"

void BitfieldRegister_t::registerField(const std::string & fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue)
{
	fieldMap[fieldName] = std::make_shared<BitfieldProperties_t>(fieldName, fieldStartPosition, fieldLength, fieldInitialValue);
}

u32 BitfieldRegister_t::getFieldValue(const std::string & fieldName)
{
	return fieldMap[fieldName]->value;
}

void BitfieldRegister_t::setFieldValue(const std::string & fieldName, const u32 & value)
{
	fieldMap[fieldName]->value = value;
}

u32 BitfieldRegister_t::getBitfieldRegister()
{
	// Need to sync Register value with the individual fields first.
	std::shared_ptr<BitfieldProperties_t> props;
	for(auto &field : fieldMap)
	{
		props = field.second;
		setBitRange32(props->startPosition, props->length, props->value);
	}

	// Return the bitfield value;
	return this->UW;
}

void BitfieldRegister_t::setBitfieldRegister(u32 value)
{
	// Need to sync the parsed value with the Register first.
	this->UW = value;

	// Set fields based on UW value.
	std::shared_ptr<BitfieldProperties_t> props;
	for (auto &field : fieldMap)
	{
		props = field.second;
		props->value = getBitRange32(props->startPosition, props->length);
	}
}
