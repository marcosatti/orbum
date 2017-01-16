#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"
#include "Common/Util/MathUtil/MathUtil.h"

BitfieldRegister32_t::BitfieldRegister32_t()
#if defined(BUILD_DEBUG)
	: mDebugReads(false), mDebugWrites(false)
#endif
{
}

BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	Register32_t(mnemonic),
	mDebugReads(false),
	mDebugWrites(false)
#else
	Register32_t(mnemonic)
#endif
{
}

#if defined(BUILD_DEBUG)
BitfieldRegister32_t::BitfieldRegister32_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	Register32_t(mnemonic, debugReads, debugWrites),
	mDebugReads(debugReads), 
	mDebugWrites(debugWrites)
{
}


void BitfieldRegister32_t::logDebugAllFields()
{
	for (auto i = 0; i < FIELD_MAP_SIZE; i++)
	{
		// I'll assume that when an empty mnemonic is encountered, its because the rest of the fields arent defined.
		// I'm also sorry in advance if anyone has to debug the debug function :) .
		if (mFieldMnemonics[i].empty())
			break;

#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("\t%s = 0x%X.", mFieldMnemonics[i].c_str(), mFieldValues[i]);
#else
		logDebug("\t%s = %d.", field.mFieldName.c_str(), field.mFieldValue);
#endif
	}
}

u8 BitfieldRegister32_t::readByte(const Context_t& context, u32 arrayIndex)
{
	auto temp = Register32_t::readByte(context, arrayIndex);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}

u16 BitfieldRegister32_t::readHword(const Context_t& context, u32 arrayIndex)
{
	auto temp = Register32_t::readHword(context, arrayIndex);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}

u32 BitfieldRegister32_t::readWord(const Context_t& context)
{
	auto temp = Register32_t::readWord(context);

	if (mDebugReads)
		logDebugAllFields();

	return temp;
}
#endif

BitfieldRegister32_t::~BitfieldRegister32_t()
{
}

u32 BitfieldRegister32_t::getBitRange32(u8 startPosition, u8 bitLength)
{
	return MathUtil::extractMaskedValue32(UW, startPosition, bitLength);
}

void BitfieldRegister32_t::setBitRange32(u8 startPosition, u8 bitLength, u32 value)
{
	UW = MathUtil::insertMaskedValue32(UW, value, startPosition, bitLength);
}

void BitfieldRegister32_t::writeByte(const Context_t& context, u32 arrayIndex, u8 value)
{
	Register32_t::writeByte(context, arrayIndex, value);
	BitfieldMap32_t::syncMapFromMemory();

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::writeHword(const Context_t& context, u32 arrayIndex, u16 value)
{
	Register32_t::writeHword(context, arrayIndex, value);
	BitfieldMap32_t::syncMapFromMemory();

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::writeWord(const Context_t& context, u32 value)
{
	Register32_t::writeWord(context, value);
	BitfieldMap32_t::syncMapFromMemory();

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
		logDebugAllFields();
#endif
}

void BitfieldRegister32_t::initalise()
{
	Register32_t::initalise();
	BitfieldMap32_t::initaliseAllFields();
}
