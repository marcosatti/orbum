#include "stdafx.h"

#include "Common/Types/Register/Register8_t.h"

Register8_t::Register8_t(const char* mnemonic, bool debugReads, bool debugWrites, const u8 initalisationValue) :
	DebugBaseObject_t(mnemonic, debugReads, debugWrites),
	UB(initalisationValue),
	mInitalisationValue(initalisationValue)
{
}

u8 Register8_t::readByte(const System_t context)
{
#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugReads)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Read u8, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), UB);
#else
		log(Debug, "%s: %s Read u8, Value = %d.", getSystemStr(context), mMnemonic.c_str(), UB);
#endif
	}
#endif

	return UB;
}

void Register8_t::writeByte(const System_t context, u8 value)
{
	UB = value;

#if defined(DEBUG_LOG_REGISTER_READ_WRITE)
	if (mDebugWrites)
	{
#if DEBUG_LOG_VALUE_AS_HEX
		log(Debug, "%s: %s Write u8, Value = 0x%X.", getSystemStr(context), mMnemonic.c_str(), UB);
#else
		log(Debug, "%s: %s Write u8, Value = %d.", getSystemStr(context), mMnemonic.c_str(), UB);
#endif
	}
#endif
}

void Register8_t::initalise()
{
	UB = mInitalisationValue;
}
