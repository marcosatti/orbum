#include "stdafx.h"

#include <string>
#include <vector>

#include "Common/PS2Resources/Types/BitfieldMap32/BitfieldMap32_t.h"


BitfieldMap32_t::BitfieldMap32_t(const bool & autoSync) :
	mAutoSync(autoSync)
{
}


BitfieldMap32_t::~BitfieldMap32_t()
{
}

void BitfieldMap32_t::registerField(const u8& fieldIndex, const std::string & fieldName, const u8& fieldStartPosition, const u8& fieldLength, const u32& fieldInitialValue)
{
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");

	setBitRange32(fieldStartPosition, fieldLength, fieldInitialValue);
	mFieldMap[fieldIndex] = { fieldName, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue };
}

const u32 & BitfieldMap32_t::getFieldValue(const u8& fieldIndex)
{
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");

	return mFieldMap[fieldIndex].mFieldValue;
}

void BitfieldMap32_t::setFieldValue(const u8& fieldIndex, const u32& value)
{
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");

	BitfieldProperties_t & props = mFieldMap[fieldIndex];
	props.mFieldValue = value;

	if (mAutoSync)
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

void BitfieldMap32_t::initaliseAllFields()
{
	for (auto &field : mFieldMap)
	{
		field.mFieldValue = field.mInitialFieldValue;
		if (mAutoSync)
			setBitRange32(field.mFieldStartPosition, field.mFieldLength, field.mFieldValue);
	}
}

void BitfieldMap32_t::initaliseField(const u8& fieldIndex)
{
	auto& field = mFieldMap[fieldIndex];
	field.mFieldValue = field.mInitialFieldValue;

	if (mAutoSync)
		setBitRange32(field.mFieldStartPosition, field.mFieldLength, field.mFieldValue);
}

void BitfieldMap32_t::syncMapFromMemory()
{
	for (auto& field : mFieldMap)
		field.mFieldValue = getBitRange32(field.mFieldStartPosition, field.mFieldLength);
}

void BitfieldMap32_t::syncMemoryFromMap()
{
	for (auto &field : mFieldMap)
		setBitRange32(field.mFieldStartPosition, field.mFieldLength, field.mFieldValue);
}
