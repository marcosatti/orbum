#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister16_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister16_t::BitfieldRegister16_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register16_t(mnemonic, debugReads, debugWrites)
{
}

void BitfieldRegister16_t::initialise()
{
	Register16_t::initialise();
	initialiseAllFields();
}

void BitfieldRegister16_t::initialiseAllFields()
{
	// Using UH directly is OK here - it can only ever be called from within a VM "context".
	for (auto& field : mFields)
		UH = MathUtil::insertMaskedValue16(UH, field.mInitialValue, field.mStartPosition, field.mLength);
}

u8 BitfieldRegister16_t::readByte(const System_t context, const size_t arrayIndex)
{
	auto temp = Register16_t::readByte(context, arrayIndex);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister16_t::writeByte(const System_t context, const size_t arrayIndex, const u8 value)
{
	Register16_t::writeByte(context, arrayIndex, value);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u16 BitfieldRegister16_t::readHword(const System_t context)
{
	auto temp = Register16_t::readHword(context);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister16_t::writeHword(const System_t context, const u16 value)
{
	Register16_t::writeHword(context, value);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister16_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u16 fieldInitialValue)
{
	mFields.insert(mFields.begin() + fieldIndex, { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue });
	initialiseAllFields();
}

u16 BitfieldRegister16_t::getFieldValue(const System_t context, const int fieldIndex)
{
	return MathUtil::extractMaskedValue16(readHword(context), mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength);
}

void BitfieldRegister16_t::setFieldValue(const System_t context, const int fieldIndex, const u16 value)
{
	writeHword(context, MathUtil::insertMaskedValue16(readHword(context), value, mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength));
}

void BitfieldRegister16_t::logDebugAllFields() const
{
	// Using UH directly is OK here - we are not modifying anything, and it can only ever be called from within a VM "context" (ie: always called from get/setFieldValue()).
	for (auto& field : mFields)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "\t%s = 0x%X.", field.mMnemonic.c_str(), MathUtil::extractMaskedValue16(UH, field.mStartPosition, field.mLength));
#else
		log(Debug, "\t%s = %d.", field.mMnemonic, MathUtil::extractMaskedValue16(UH, field.mStartPosition, field.mLength));
#endif
	}
}