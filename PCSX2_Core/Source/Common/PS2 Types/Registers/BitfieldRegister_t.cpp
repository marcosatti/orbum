#include "stdafx.h"


#include "Common/Global/Globals.h"
#include "Common/PS2 Types/Registers/BitfieldRegister_t.h"

void BitfieldRegister_t::registerField(const std::string & fieldName, const u8 & fieldStartPosition, const u8 & fieldLength, const u32 & fieldInitialValue)
{
	mFieldMap[fieldName] = std::make_shared<BitfieldProperties_t>(fieldName, fieldStartPosition, fieldLength, fieldInitialValue);
}

u32 BitfieldRegister_t::getFieldValue(const std::string & fieldName)
{
	return mFieldMap[fieldName]->mFieldValue;
}

void BitfieldRegister_t::setFieldValue(const std::string & fieldName, const u32 & value)
{
	mFieldMap[fieldName]->mFieldValue = value;
}

u32 BitfieldRegister_t::getBitfieldRegister()
{
	// Need to sync Register value with the individual fields first.
	std::shared_ptr<BitfieldProperties_t> props;
	for(auto &field : mFieldMap)
	{
		props = field.second;
		setBitRange32(props->mFieldStartPosition, props->mFieldLength, props->mFieldValue);
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
	for (auto &field : mFieldMap)
	{
		props = field.second;
		props->mFieldValue = getBitRange32(props->mFieldStartPosition, props->mFieldLength);
	}
}
