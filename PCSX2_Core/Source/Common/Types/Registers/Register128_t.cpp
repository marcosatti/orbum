#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

Register128_t::Register128_t() : 
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UQ(0,0),
	mMnemonic("")
{
}

Register128_t::Register128_t(const char* mnemonic) :
#if defined(BUILD_DEBUG)
	mDebugReads(false), mDebugWrites(false),
#endif
	UQ(0,0),
	mMnemonic(mnemonic)
{
}

#if defined(BUILD_DEBUG)
Register128_t::Register128_t(const char* mnemonic, bool debugReads, bool debugWrites) :
	mDebugReads(debugReads), mDebugWrites(debugWrites),
	UQ(0,0),
	mMnemonic(mnemonic)
{
}
#endif

u8 Register128_t::readByte(const Context_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Read u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register128_t::writeByte(const Context_t context, size_t arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Write u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register128_t::readHword(const Context_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Read u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register128_t::writeHword(const Context_t context, size_t arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Write u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register128_t::readWord(const Context_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Read u32[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif

	return UW[arrayIndex];
}

void Register128_t::writeWord(const Context_t context, size_t arrayIndex, u32 value)
{
	UW[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Write u32[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif
}

u64 Register128_t::readDword(const Context_t context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
			log(Debug, "%s: %s Read u64[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UD[arrayIndex]);
#else
			log(Debug, "%s: %s Read u64[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UD[arrayIndex]);
#endif
	}
#endif

	return UD[arrayIndex];
}

void Register128_t::writeDword(const Context_t context, size_t arrayIndex, u64 value)
{
	UD[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UD[arrayIndex]);
#else
		log(Debug, "%s: %s Write u64[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UD[arrayIndex]);
#endif
	}
#endif
}

u128 Register128_t::readQword(const Context_t context)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128, ValueLSB = 0x%X, ValueMSB = 0x%X.", getContextStr(context), getMnemonic(), UQ.lo, UQ.hi);
#else
		log(Debug, "%s: %s Read u128, ValueLSB = %d, ValueMSB = %d.", getContextStr(context), getMnemonic(), UQ.lo, UQ.hi);
#endif
	}
#endif

	return UQ;
}

void Register128_t::writeQword(const Context_t context, u128 value)
{
	UQ = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128, ValueLSB = 0x%X, ValueMSB = 0x%X.", getContextStr(context), getMnemonic(), UQ.lo, UQ.hi);
#else
		log(Debug, "%s: %s Write u128, ValueLSB = %d, ValueMSB = %d.", getContextStr(context), getMnemonic(), UQ.lo, UQ.hi);
#endif
	}
#endif
}

const char* Register128_t::getMnemonic() const
{
	return mMnemonic.c_str();
}

void Register128_t::initalise()
{
	UQ = u128(0, 0);
}
