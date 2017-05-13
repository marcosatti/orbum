#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"

Register128_t::Register128_t(const char* mnemonic, bool debugReads, bool debugWrites, const u128 initalisationValue) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	UQ(initalisationValue),
	mInitalisationValue(initalisationValue)
{
}

u8 Register128_t::readByte(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Read u8[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register128_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Write u8[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register128_t::readHword(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Read u16[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register128_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Write u16[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register128_t::readWord(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Read u32[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif

	return UW[arrayIndex];
}

void Register128_t::writeWord(const System_t context, size_t arrayIndex, u32 value)
{
	UW[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Write u32[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif
}

u64 Register128_t::readDword(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
			log(Debug, "%s: %s Read u64[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UD[arrayIndex]);
#else
			log(Debug, "%s: %s Read u64[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UD[arrayIndex]);
#endif
	}
#endif

	return UD[arrayIndex];
}

void Register128_t::writeDword(const System_t context, size_t arrayIndex, u64 value)
{
	UD[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64[%d], Value = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UD[arrayIndex]);
#else
		log(Debug, "%s: %s Write u64[%d], Value = %d.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, UD[arrayIndex]);
#endif
	}
#endif
}

u128 Register128_t::readQword(const System_t context)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u128, ValueLSB = 0x%X, ValueMSB = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), UQ.lo, UQ.hi);
#else
		log(Debug, "%s: %s Read u128, ValueLSB = %d, ValueMSB = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UQ.lo, UQ.hi);
#endif
	}
#endif

	return UQ;
}

void Register128_t::writeQword(const System_t context, u128 value)
{
	UQ = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u128, ValueLSB = 0x%X, ValueMSB = 0x%X.", SYSTEM_STR[context], mMnemonic.c_str(), UQ.lo, UQ.hi);
#else
		log(Debug, "%s: %s Write u128, ValueLSB = %d, ValueMSB = %d.", SYSTEM_STR[context], mMnemonic.c_str(), UQ.lo, UQ.hi);
#endif
	}
#endif
}

f32 Register128_t::readFloat(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read f32[%d], Value = %A.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, F[arrayIndex]);
#else
		log(Debug, "%s: %s Read f32[%d], Value = %F.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, F[arrayIndex]);
#endif
	}
#endif

	return F[arrayIndex];
}

void Register128_t::writeFloat(const System_t context, size_t arrayIndex, f32 value)
{
	F[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write f32[%d], Value = %A.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, F[arrayIndex]);
#else
		log(Debug, "%s: %s Write f32[%d], Value = %F.", SYSTEM_STR[context], mMnemonic.c_str(), arrayIndex, F[arrayIndex]);
#endif
	}
#endif
}

void Register128_t::initialise()
{
	UQ = mInitalisationValue;
}
