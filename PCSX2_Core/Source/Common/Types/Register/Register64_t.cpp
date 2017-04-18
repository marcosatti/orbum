#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register64_t.h"

Register64_t::Register64_t(const char* mnemonic, bool debugReads, bool debugWrites, const u64 initalisationValue) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	UD(initalisationValue),
	mInitalisationValue(initalisationValue)
{
}

u8 Register64_t::readByte(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Read u8[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register64_t::writeByte(const System_t context, size_t arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#else
		log(Debug, "%s: %s Write u8[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UB[arrayIndex]);
#endif
}
#endif
}

u16 Register64_t::readHword(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Read u16[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register64_t::writeHword(const System_t context, size_t arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#else
		log(Debug, "%s: %s Write u16[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register64_t::readWord(const System_t context, size_t arrayIndex)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u32[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Read u32[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif

	return UW[arrayIndex];
}

void Register64_t::writeWord(const System_t context, size_t arrayIndex, u32 value)
{
	UW[arrayIndex] = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u32[%d], Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#else
		log(Debug, "%s: %s Write u32[%d], Value = %d.", getSystemStr(context), mMnemonic.c_str(), arrayIndex, UW[arrayIndex]);
#endif
	}
#endif
}

u64 Register64_t::readDword(const System_t context)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u64, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), UD);
#else
		log(Debug, "%s: %s Read u64, Value = %d.", getSystemStr(context), mMnemonic.c_str(), UD);
#endif
	}
#endif

	return UD;
}

void Register64_t::writeDword(const System_t context, u64 value)
{
	UD = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u64, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), UD);
#else
		log(Debug, "%s: %s Write u64, Value = %d.", getSystemStr(context), mMnemonic.c_str(), UD);
#endif
	}
#endif
}

void Register64_t::initalise()
{
	UD = mInitalisationValue;
}
