#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register32_t.h"

Register32_t::Register32_t() : 
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UW(0),
	mMnemonic("")
{
}

Register32_t::Register32_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UW(0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register32_t::Register32_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	UW(0),
	mMnemonic(mnemonic)
{
}
#endif

u8 Register32_t::readByte(const System_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", getSystemStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Read u8[%d], Value = %d.", getSystemStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register32_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", getSystemStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Write u8[%d], Value = %d.", getSystemStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register32_t::readHword(const System_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", getSystemStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Read u16[%d], Value = %d.", getSystemStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register32_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", getSystemStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Write u16[%d], Value = %d.", getSystemStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register32_t::readWord(const System_t context)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32, Value = 0x%X.", getSystemStr(context), getMnemonic(), UW);
#else
		log(Debug, "%s: %s Read u32, Value = %d.", getSystemStr(context), getMnemonic(), UW);
#endif
	}
#endif

	return UW;
}

void Register32_t::writeWord(const System_t context, u32 value)
{
	UW = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32, Value = 0x%X.", getSystemStr(context), getMnemonic(), UW);
#else
		log(Debug, "%s: %s Write u32, Value = %d.", getSystemStr(context), getMnemonic(), UW);
#endif
	}
#endif
}

f32 Register32_t::readFloat(const System_t context)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read f32, Value = %A.", getSystemStr(context), getMnemonic(), F);
#else
		log(Debug, "%s: %s Read f32, Value = %F.", getSystemStr(context), getMnemonic(), F);
#endif
	}
#endif

	return F;
}

void Register32_t::writeFloat(const System_t context, f32 value)
{
	F = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write f32, Value = %A.", getSystemStr(context), getMnemonic(), F);
#else
		log(Debug, "%s: %s Write f32, Value = %F.", getSystemStr(context), getMnemonic(), F);
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
