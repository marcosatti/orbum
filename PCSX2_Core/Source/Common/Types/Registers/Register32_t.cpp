#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

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

Register32_t::~Register32_t()
{
}

u8 Register32_t::readByte(const Context& context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Read u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		getVM()->log(Debug, "%s: %s Read u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif

	return UB[arrayIndex];
}

void Register32_t::writeByte(const Context& context, size_t arrayIndex, u8 value)
{
	UB[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Write u8[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#else
		getVM()->log(Debug, "%s: %s Write u8[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UB[arrayIndex]);
#endif
	}
#endif
}

u16 Register32_t::readHword(const Context& context, size_t arrayIndex)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Read u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		getVM()->log(Debug, "%s: %s Read u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif

	return UH[arrayIndex];
}

void Register32_t::writeHword(const Context& context, size_t arrayIndex, u16 value)
{
	UH[arrayIndex] = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Write u16[%d], Value = 0x%X.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#else
		getVM()->log(Debug, "%s: %s Write u16[%d], Value = %d.", getContextStr(context), getMnemonic(), arrayIndex, UH[arrayIndex]);
#endif
	}
#endif
}

u32 Register32_t::readWord(const Context& context)
{
#if defined(BUILD_DEBUG)
	if (mDebugReads)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Read u32, Value = 0x%X.", getContextStr(context), getMnemonic(), UW);
#else
		getVM()->log(Debug, "%s: %s Read u32, Value = %d.", getContextStr(context), getMnemonic(), UW);
#endif
	}
#endif

	return UW;
}

void Register32_t::writeWord(const Context& context, u32 value)
{
	UW = value;

#if defined(BUILD_DEBUG)
	if (mDebugWrites)
	{
#if DEBUG_MEMORY_LOG_VALUE_AS_HEX
		getVM()->log(Debug, "%s: %s Write u32, Value = 0x%X.", getContextStr(context), getMnemonic(), UW);
#else
		getVM()->log(Debug, "%s: %s Write u32, Value = %d.", getContextStr(context), getMnemonic(), UW);
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
