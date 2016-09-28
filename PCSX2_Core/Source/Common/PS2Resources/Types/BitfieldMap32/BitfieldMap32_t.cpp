#include "stdafx.h"
#include "Common/PS2Resources/Types/BitfieldMap32/BitfieldMap32_t.h"


BitfieldMap32_t::BitfieldMap32_t(const bool & autoSync) :
	mAutoSync(autoSync)
{
}


BitfieldMap32_t::~BitfieldMap32_t()
{
}

void BitfieldMap32_t::registerField(const char* fieldName, const u8& fieldStartPosition, const u8& fieldLength, const u32& fieldInitialValue)
{
	setBitRange32(fieldStartPosition, fieldLength, fieldInitialValue);
	mFieldMap[fieldName] = { fieldName, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue };
}

u32 BitfieldMap32_t::getFieldValue(const char* fieldName)
{
	return mFieldMap.at(fieldName).mFieldValue;
}

void BitfieldMap32_t::setFieldValue(const char* fieldName, const u32& value)
{
	BitfieldProperties_t & props = mFieldMap.at(fieldName);
	props.mFieldValue = value;
	if (mAutoSync)
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

void BitfieldMap32_t::initaliseAllFields()
{
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = props.mInitialFieldValue;
		if (mAutoSync)
			setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
	}
}

void BitfieldMap32_t::initaliseField(const char* fieldName)
{
	BitfieldProperties_t & props = mFieldMap[fieldName];
	props.mFieldValue = props.mInitialFieldValue;
	if (mAutoSync)
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

void BitfieldMap32_t::syncMapFromMemory()
{
	for (auto& field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = getBitRange32(props.mFieldStartPosition, props.mFieldLength);
	}
}

void BitfieldMap32_t::syncMemoryFromMap()
{
	for (auto &field : mFieldMap)
	{
		const BitfieldProperties_t & props = field.second;
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
	}
}
