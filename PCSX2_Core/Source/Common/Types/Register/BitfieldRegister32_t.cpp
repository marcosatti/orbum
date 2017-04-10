#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
}

void BitfieldRegister32_t::initalise()
{
	Register32_t::initalise();
	initaliseAllFields();
}

void BitfieldRegister32_t::initaliseAllFields()
{
	for (auto& field : mFields)
	{
		field.mValue = field.mInitialValue;
		UW = MathUtil::insertMaskedValue32(UW, field.mValue, field.mStartPosition, field.mLength);
	}
}

u8 BitfieldRegister32_t::readByte(const System_t context, size_t arrayIndex)
{
	auto temp = Register32_t::readByte(context, arrayIndex);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	Register32_t::writeByte(context, arrayIndex, value);

	for (auto& field : mFields)
		field.mValue = MathUtil::extractMaskedValue32(UW, field.mStartPosition, field.mLength);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u16 BitfieldRegister32_t::readHword(const System_t context, size_t arrayIndex)
{
	auto temp = Register32_t::readHword(context, arrayIndex);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	Register32_t::writeHword(context, arrayIndex, value);

	for (auto& field : mFields)
		field.mValue = MathUtil::extractMaskedValue32(UW, field.mStartPosition, field.mLength);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u32 BitfieldRegister32_t::readWord(const System_t context)
{
	auto temp = Register32_t::readWord(context);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeWord(const System_t context, u32 value)
{
	Register32_t::writeWord(context, value);
	
	for (auto& field : mFields)
		field.mValue = MathUtil::extractMaskedValue32(UW, field.mStartPosition, field.mLength);

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u32 fieldInitialValue)
{
	mFields.insert(mFields.begin() + fieldIndex, { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue });
	initaliseAllFields();
}

u32 BitfieldRegister32_t::getFieldValue(const System_t context, const int fieldIndex) const
{
	return mFields[fieldIndex].mValue;
}

void BitfieldRegister32_t::setFieldValue(const System_t context, const int fieldIndex, const u32 value)
{
	auto& field = mFields[fieldIndex];
	field.mValue = value;
	UW = MathUtil::insertMaskedValue32(UW, value, field.mStartPosition, field.mLength);
}

void BitfieldRegister32_t::logDebugAllFields() const
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