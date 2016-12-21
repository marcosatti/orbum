#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Registers/DebugBitfieldRegister32_t.h"

DebugBitfieldRegister32_t::DebugBitfieldRegister32_t(const char* mnemonic) :
	BitfieldRegister32_t(mnemonic)
{
}

DebugBitfieldRegister32_t::~DebugBitfieldRegister32_t()
{
}

u32 DebugBitfieldRegister32_t::readWordU()
{
	auto value = BitfieldRegister32_t::readWordU();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read u32, Value = %d.", getMnemonic(), value);
#endif
	return value;
}

void DebugBitfieldRegister32_t::writeWordU(u32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write u32, Value = %d.", getMnemonic() value);
#endif
	BitfieldRegister32_t::writeWordU(value);
}

s32 DebugBitfieldRegister32_t::readWordS()
{
	auto value = BitfieldRegister32_t::readWordS();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read s32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read s32, Value = %d.", getMnemonic(), value);
#endif
	return value;
}

void DebugBitfieldRegister32_t::writeWordS(s32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write s32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write s32, Value = %d.", getMnemonic(), value);
#endif
	BitfieldRegister32_t::writeWordS(value);
}

#endif