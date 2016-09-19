#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/BitfieldStorageObject32_t.h"


BitfieldStorageObject32_t::BitfieldStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress) :
	StorageObject32_t(mnemonic, PS2PhysicalAddress)
{
}

BitfieldStorageObject32_t::~BitfieldStorageObject32_t()
{
}

void BitfieldStorageObject32_t::registerField(const char* fieldName, const u8& fieldStartPosition, const u8& fieldLength, const u32& fieldInitialValue)
{
	mFieldMap.insert({ fieldName,{ fieldName, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue } });
	BitfieldProperties_t & props = mFieldMap[fieldName];
	setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

u32 BitfieldStorageObject32_t::getFieldValue(const char* fieldName)
{
	return mFieldMap[fieldName].mFieldValue;
}

void BitfieldStorageObject32_t::setFieldValue(const char* fieldName, const u32& value)
{
	BitfieldProperties_t & props = mFieldMap[fieldName];
	props.mFieldValue = value;
	setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

void BitfieldStorageObject32_t::initaliseAllFields()
{
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = props.mInitialFieldValue;
		setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
	}
}

void BitfieldStorageObject32_t::initaliseField(const char* fieldName)
{
	BitfieldProperties_t & props = mFieldMap[fieldName];
	props.mFieldValue = props.mInitialFieldValue;
	setBitRange32(props.mFieldStartPosition, props.mFieldLength, props.mFieldValue);
}

void BitfieldStorageObject32_t::writeWordU(u32 storageIndex, u32 value)
{
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = getBitRange32(props.mFieldStartPosition, props.mFieldLength);
	}
}

void BitfieldStorageObject32_t::writeWordS(u32 storageIndex, s32 value)
{
	for (auto &field : mFieldMap)
	{
		BitfieldProperties_t & props = field.second;
		props.mFieldValue = getBitRange32(props.mFieldStartPosition, props.mFieldLength);
	}
}
