#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister16_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister16_t::BitfieldRegister16_t() :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	mFields{}
{
}

BitfieldRegister16_t::BitfieldRegister16_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	Register16_t(mnemonic),
	mDebugReads(false),
	mDebugWrites(false),
#else
	Register16_t(mnemonic),
#endif
	mFields{}
{
}

#if defined(BUILD_DEBUG)
BitfieldRegister16_t::BitfieldRegister16_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register16_t(mnemonic, debugReads, debugWrites),
	mDebugReads(debugReads),
	mDebugWrites(debugWrites),
	mFields{}
{
}
#endif

void BitfieldRegister16_t::initalise()
{
	Register16_t::initalise();
	initaliseAllFields();
}

#if defined(BUILD_DEBUG)
void BitfieldRegister16_t::logDebugAllFields() const
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

u8 BitfieldRegister16_t::readByte(const System_t context, size_t arrayIndex)
{
	auto temp = Register16_t::readByte(context, arrayIndex);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}

u16 BitfieldRegister16_t::readHword(const System_t context)
{
	auto temp = Register16_t::readHword(context);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}
#endif

void BitfieldRegister16_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	Register16_t::writeByte(context, arrayIndex, value);
	
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFields[i].mValue = MathUtil::extractMaskedValue16(UH, mFields[i].mStartPosition, mFields[i].mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister16_t::writeHword(const System_t context, u16 value)
{
	Register16_t::writeHword(context, value);
	
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
		mFields[i].mValue = MathUtil::extractMaskedValue16(UH, mFields[i].mStartPosition, mFields[i].mLength);

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister16_t::registerField(const int fieldIndex, const char* fieldMnemonic, const int fieldStartPosition, const int fieldLength, const u16 fieldInitialValue)
{
	mFields[fieldIndex] = { fieldMnemonic, fieldStartPosition, fieldLength, fieldInitialValue, fieldInitialValue };
	UH = MathUtil::insertMaskedValue16(UH, fieldInitialValue, fieldStartPosition, fieldLength);
}

const u16 BitfieldRegister16_t::getFieldValue(const System_t context, const int fieldIndex) const
{
#if DEBUG_ERROR_BR_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif

	return mFields[fieldIndex].mValue;
}

void BitfieldRegister16_t::setFieldValue(const System_t context, const int fieldIndex, const u16 value)
{
#if DEBUG_ERROR_BR_FIELD_INDEX_RANGE
	if (!(fieldIndex < FIELD_MAP_SIZE))
		throw std::runtime_error("Invalid map index.");
#endif

	mFields[fieldIndex].mValue = value;
	UH = MathUtil::insertMaskedValue16(UH, value, mFields[fieldIndex].mStartPosition, mFields[fieldIndex].mLength);
}

void BitfieldRegister16_t::initaliseAllFields()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
	{
		mFields[i].mValue = mFields[i].mInitialValue;
		UH = MathUtil::insertMaskedValue16(UH, mFields[i].mValue, mFields[i].mStartPosition, mFields[i].mLength);
	}
}