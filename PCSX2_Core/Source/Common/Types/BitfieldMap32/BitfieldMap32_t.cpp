#include "stdafx.h"

#include <string>
#include <vector>

#include "Common/Types/BitfieldMap32/BitfieldMap32_t.h"

BitfieldMap32_t::BitfieldMap32_t() :
	// Make sure to zero-initalise the arrays otherwise bogus data may be active if initaliseAllFields() is called (by having fieldLength = 0 it will not change anything). 
	mFieldValues{0},
	mFieldStartPositions{0},
	mFieldLengths{0},
	mFieldInitialValues{0},
	mFieldMnemonics{}
{
}

BitfieldMap32_t::~BitfieldMap32_t()
{
}

void BitfieldMap32_t::registerField(const u8& fieldIndex, const std::string & fieldName, const u8& fieldStartPosition, const u8& fieldLength, const u32& fieldInitialValue)
{
#if ERROR_ON_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif
	
	mFieldMnemonics[fieldIndex] = fieldName;
	mFieldStartPositions[fieldIndex] = fieldStartPosition;
	mFieldLengths[fieldIndex] = fieldLength;
	mFieldInitialValues[fieldIndex] = fieldInitialValue;
	mFieldValues[fieldIndex] = fieldInitialValue;
	setBitRange32(mFieldStartPositions[fieldIndex], mFieldLengths[fieldIndex], mFieldValues[fieldIndex]);
}

void BitfieldMap32_t::initaliseAllFields()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
	{
		mFieldValues[i] = mFieldInitialValues[i];
		setBitRange32(mFieldStartPositions[i], mFieldLengths[i], mFieldValues[i]);
	}
}

void BitfieldMap32_t::initaliseField(const u8& fieldIndex)
{
	mFieldValues[fieldIndex] = mFieldInitialValues[fieldIndex];
	setBitRange32(mFieldStartPositions[fieldIndex], mFieldLengths[fieldIndex], mFieldValues[fieldIndex]);
}

void BitfieldMap32_t::syncMapFromMemory()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFieldValues[i] = getBitRange32(mFieldStartPositions[i], mFieldLengths[i]);
}

void BitfieldMap32_t::syncMemoryFromMap()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		setBitRange32(mFieldStartPositions[i], mFieldLengths[i], mFieldValues[i]);
}