#include "Common/Global/Globals.h"
#include "Common/Types/Register/BitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites)
{
}

void BitfieldRegister32_t::initialise()
{
	Register32_t::initialise();
	initialiseAllFields();
}

void BitfieldRegister32_t::initialiseAllFields()
{
	// Using UW directly is OK here - it can only ever be called from within a VM "context" (ie: always called from initialise()).
	for (auto& field : mFields)
		UW = MathUtil::insertMaskedValue32(UW, field.mInitialValue, field.mStartPosition, field.mLength);
}

u8 BitfieldRegister32_t::readByte(const Context_t context, const size_t arrayIndex)
{
	auto temp = Register32_t::readByte(context, arrayIndex);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeByte(const Context_t context, const size_t arrayIndex, const u8 value)
{
	Register32_t::writeByte(context, arrayIndex, value);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u16 BitfieldRegister32_t::readHword(const Context_t context, const size_t arrayIndex)
{
	auto temp = Register32_t::readHword(context, arrayIndex);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeHword(const Context_t context, const size_t arrayIndex, const u16 value)
{
	Register32_t::writeHword(context, arrayIndex, value);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

u32 BitfieldRegister32_t::readWord(const Context_t context)
{
	auto temp = Register32_t::readWord(context);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugReads)
		logDebugAllFields();
#endif

	return temp;
}

void BitfieldRegister32_t::writeWord(const Context_t context, const u32 value)
{
	Register32_t::writeWord(context, value);

#if DEBUG_LOG_REGISTER_READ_WRITE
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u32 fieldInitialValue)
{
	mFields.insert(mFields.begin() + fieldIndex, { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue });
	initialiseAllFields();
}

u32 BitfieldRegister32_t::getFieldValue(const Context_t context, const int fieldIndex)
{
	return MathUtil::extractMaskedValue32(readWord(context), mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength);
}

void BitfieldRegister32_t::setFieldValue(const Context_t context, const int fieldIndex, const u32 value)
{
	writeWord(context, MathUtil::insertMaskedValue32(readWord(context), value, mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength));
}

void BitfieldRegister32_t::logDebugAllFields() const
{
	// Using UW directly is OK here - we are not modifying anything, and it can only ever be called from within a VM "context" (ie: always called from get/setFieldValue()).
	for (auto& field : mFields)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "\t%s = 0x%X.", field.mMnemonic.c_str(), MathUtil::extractMaskedValue32(UW, field.mStartPosition, field.mLength));
#else
		log(Debug, "\t%s = %d.", field.mMnemonic, MathUtil::extractMaskedValue32(UW, field.mStartPosition, field.mLength));
#endif
	}
}