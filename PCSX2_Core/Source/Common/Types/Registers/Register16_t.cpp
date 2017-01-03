#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register16_t.h"

Register16_t::Register16_t() : 
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UH(0),
	mMnemonic("")
{
}

Register16_t::Register16_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UH(0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register16_t::Register16_t(const char* mnemonic, bool debug) :
	mDebug(debug),
	UH(0),
	mMnemonic(mnemonic)
{
}
#endif

Register16_t::~Register16_t()
{
}

u8 Register16_t::readByte(const Context_t& context, u32 arrayIndex)
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

void Register16_t::writeByte(const Context_t& context, u32 arrayIndex, u8 value)
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

u16 Register16_t::readHword(const Context_t& context)
{
#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Read u16, Value = 0x%X.", getContextStr(context), getMnemonic(), UH);
#else
		logDebug("%s: %s Read u16, Value = %d.", getContextStr(context), getMnemonic(), UH);
#endif
	}
#endif

	return UH;
}

void Register16_t::writeHword(const Context_t& context, u16 value)
{
	UH = value;

#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Write u16, Value = 0x%X.", getContextStr(context), getMnemonic(), UH);
#else
		logDebug("%s: %s Write u16, Value = %d.", getContextStr(context), getMnemonic(), UH);
#endif
	}
#endif
}

const char* Register16_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
