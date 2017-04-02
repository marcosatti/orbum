#include "stdafx.h"

#include "Common/Types/Registers/Register8_t.h"

Register8_t::Register8_t() :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UB(0),
	mMnemonic("")
{
}

Register8_t::Register8_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UB(0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register8_t::Register8_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	UB(0),
	mMnemonic(mnemonic)
{
}
#endif

u8 Register8_t::readByte(const System_t context)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8, Value = 0x%X.", getSystemStr(context), getMnemonic(), UB);
#else
		log(Debug, "%s: %s Read u8, Value = %d.", getSystemStr(context), getMnemonic(), UB);
#endif
	}
#endif

	return UB;
}

void Register8_t::writeByte(const System_t context, u8 value)
{
	UB = value;

#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8, Value = 0x%X.", getSystemStr(context), getMnemonic(), UB);
#else
		log(Debug, "%s: %s Write u8, Value = %d.", getSystemStr(context), getMnemonic(), UB);
#endif
	}
#endif
}

const char* Register8_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void Register8_t::initalise()
{
	UB = 0;
}
