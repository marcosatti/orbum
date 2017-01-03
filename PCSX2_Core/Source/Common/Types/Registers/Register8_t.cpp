#include "stdafx.h"

#include "Common/Types/Registers/Register8_t.h"

Register8_t::Register8_t() :
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UB(0),
	mMnemonic("")
{
}

Register8_t::Register8_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebug(false),
#endif
	UB(0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register8_t::Register8_t(const char* mnemonic, bool debug) :
	mDebug(debug),
	UB(0),
	mMnemonic(mnemonic)
{
}
#endif

Register8_t::~Register8_t()
{
}

u8 Register8_t::readByte(const Context_t& context)
{
#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Read u8, Value = 0x%X.", getContextStr(context), getMnemonic(), UB);
#else
		logDebug("%s: %s Read u8, Value = %d.", getContextStr(context), getMnemonic(), UB);
#endif
	}
#endif

	return UB;
}

void Register8_t::writeByte(const Context_t& context, u8 value)
{
	UB = value;

#if defined(BUILD_DEBUG)
	if (mDebug)
	{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
		logDebug("%s: %s Write u8, Value = 0x%X.", getContextStr(context), getMnemonic(), UB);
#else
		logDebug("%s: %s Write u8, Value = %d.", getContextStr(context), getMnemonic(), UB);
#endif
	}
#endif
}

const char* Register8_t::getMnemonic() const
{
	return mMnemonic.c_str();
}
