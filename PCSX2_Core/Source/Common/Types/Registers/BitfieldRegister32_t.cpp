#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister32_t::BitfieldRegister32_t() :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mFields{}
{
}

BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	Register32_t(mnemonic),
	mDebugReads(false),
	mDebugWrites(false),
#else
	Register32_t(mnemonic),
#endif
	mFields{}
{
}

#if defined(BUILD_DEBUG)
BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mDebugReads(debugReads),
	mDebugWrites(debugWrites),
	mFields{}
{
}
#endif

void BitfieldRegister32_t::initalise()
{
	Register32_t::initalise();
	initaliseAllFields();
}

#if defined(BUILD_DEBUG)
void BitfieldRegister32_t::logDebugAllFields() const
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
	{
		// I'll assume that when an empty mnemonic is encountered, its because the rest of the fields arent defined.
		// I'm also sorry in advance if anyone has to debug the debug function :) .
		if (mFields[i].mMnemonic == "")
			break;

#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "\t%s = 0x%X.", mFields[i].mMnemonic.c_str(), mFields[i].mValue);
#else
		log(Debug, "\t%s = %d.", mFields[i].mMnemonic, mFields[i].mValue);
#endif
	}
}

u8 BitfieldRegister32_t::readByte(const System_t context, size_t arrayIndex)
{
	auto temp = Register32_t::readByte(context, arrayIndex);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}

u16 BitfieldRegister32_t::readHword(const System_t context, size_t arrayIndex)
{
	auto temp = Register32_t::readHword(context, arrayIndex);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}

u32 BitfieldRegister32_t::readWord(const System_t context)
{
	auto temp = Register32_t::readWord(context);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}
#endif

void BitfieldRegister32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	Register32_t::writeByte(context, arrayIndex, value);
	
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFields[i].mValue = MathUtil::extractMaskedValue32(UW, mFields[i].mStartPosition, mFields[i].mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	Register32_t::writeHword(context, arrayIndex, value);
	
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFields[i].mValue = MathUtil::extractMaskedValue32(UW, mFields[i].mStartPosition, mFields[i].mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::writeWord(const System_t context, u32 value)
{
	Register32_t::writeWord(context, value);
	
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFields[i].mValue = MathUtil::extractMaskedValue32(UW, mFields[i].mStartPosition, mFields[i].mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u32 fieldInitialValue)
{
	mFields[fieldIndex] = { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue };
	UW = MathUtil::insertMaskedValue32(UW, fieldInitialValue, fieldStartPosition, fieldLength);
}

const u32 BitfieldRegister32_t::getFieldValue(const System_t context, const int fieldIndex) const
{
#if DEBUG_ERROR_BR32_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif

	return mFields[fieldIndex].mValue;
}

void BitfieldRegister32_t::setFieldValue(const System_t context, const int fieldIndex, const u32 value)
{
#if DEBUG_ERROR_BR32_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif

	mFields[fieldIndex].mValue = value;
	UW = MathUtil::insertMaskedValue32(UW, value, mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength);
}

void BitfieldRegister32_t::initaliseAllFields()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
	{
		mFields[i].mValue = mFields[i].mInitialValue;
		UW = MathUtil::insertMaskedValue32(UW, mFields[i].mValue, mFields[i].mStartPosition, mFields[i].mLength);
	}
}