#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

Register32_t::Register32_t() : 
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UW(0),
	mMnemonic("")
{
}

Register32_t::Register32_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UW(0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register32_t::Register32_t(const char* mnemonic, bool debug) :
	mDebug(debug),
	UW(0),
	mMnemonic(mnemonic)
{
}
#endif

Register32_t::~Register32_t()
{
}

u8 Register32_t::readByte(const Context_t& context, u32 arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Read u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		logDebug("%s: %s Read u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register32_t::writeByte(const Context_t& context, u32 arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Write u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		logDebug("%s: %s Write u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register32_t::readHword(const Context_t& context, u32 arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Read u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		logDebug("%s: %s Read u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register32_t::writeHword(const Context_t& context, u32 arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Write u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		logDebug("%s: %s Write u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register32_t::readWord(const Context_t& context)
{
#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Read u32, Value = 0x%X.", getContextStr(context), getMnemonic(), UW);
#else
		logDebug("%s: %s Read u32, Value = %d.", getContextStr(context), getMnemonic(), UW);
#endif
	}
#endif

	return UW;
}

void Register32_t::writeWord(const Context_t& context, u32 value)
{
	UW = value;

#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Write u32, Value = 0x%X.", getContextStr(context), getMnemonic(), UW);
#else
		logDebug("%s: %s Write u32, Value = %d.", getContextStr(context), getMnemonic(), UW);
#endif
	}
#endif
}

const char* Register32_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void Register32_t::initalise()
{
	UW = 0;
}
