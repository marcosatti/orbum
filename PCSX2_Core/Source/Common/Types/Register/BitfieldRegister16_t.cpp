#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister16_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister16_t::BitfieldRegister16_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register16_t(mnemonic, debugReads, debugWrites)
{
}

void BitfieldRegister16_t::initalise()
{
	Register16_t::initalise();
	initaliseAllFields();
}

void BitfieldRegister16_t::initaliseAllFields()
{
	for (auto& field : mFields)
	{
		field.mValue = field.mInitialValue;
		UH = MathUtil::insertMaskedValue16(UH, field.mValue, field.mStartPosition, field.mLength);
	}
}

u8 BitfieldRegister16_t::readByte(const System_t context, size_t arrayIndex)
{
	auto temp = Register16_t::readByte(context, arrayIndex);

#if defined(BUILD_DEBUG)
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister16_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	Register16_t::writeByte(context, arrayIndex, value);

	for (auto& field : mFields)
		field.mValue = MathUtil::extractMaskedValue16(UH, field.mStartPosition, field.mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u16 BitfieldRegister16_t::readHword(const System_t context)
{
	auto temp = Register16_t::readHword(context);

#if defined(BUILD_DEBUG)
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister16_t::writeHword(const System_t context, u16 value)
{
	Register16_t::writeHword(context, value);
	
	for (auto& field : mFields)
		field.mValue = MathUtil::extractMaskedValue16(UH, field.mStartPosition, field.mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister16_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u16 fieldInitialValue)
{
	mFields.insert(mFields.begin() + fieldIndex, { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue });
	UH = MathUtil::insertMaskedValue16(UH, fieldInitialValue, fieldStartPosition, fieldLength);
}

u16 BitfieldRegister16_t::getFieldValue(const System_t context, const int fieldIndex) const
{
#if DEBUG_ERROR_BR_FIELD_INDEX_RANGE
	return mFields.at(fieldIndex).mValue;
#else
	return mFields[fieldIndex].mValue;
#endif
}

void BitfieldRegister16_t::setFieldValue(const System_t context, const int fieldIndex, const u16 value)
{
#if DEBUG_ERROR_BR_FIELD_INDEX_RANGE
	auto& field = mFields.at(fieldIndex);
#else
	auto& field = mFields[fieldIndex];
#endif

	field.mValue = value;
	UH = MathUtil::insertMaskedValue16(UH, value, field.mStartPosition, field.mLength);
}

void BitfieldRegister16_t::logDebugAllFields() const
{
	for (auto& field : mFields)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "\t%s = 0x%X.", field.mMnemonic.c_str(), field.mValue);
#else
		log(Debug, "\t%s = %d.", field.mMnemonic, field.mValue);
#endif
	}
}