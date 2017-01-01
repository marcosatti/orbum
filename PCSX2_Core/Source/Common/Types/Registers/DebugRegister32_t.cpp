
#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Registers/DebugRegister32_t.h"

DebugRegister32_t::DebugRegister32_t(const char* mnemonic) :
	Register32_t(mnemonic)
{
}

u8 DebugRegister32_t::readByte(u32 storageIndex)
{
	auto value = Register32_t::readByte(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeByte(u32 storageIndex, u8 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeByte(storageIndex, value);
}

u16 DebugRegister32_t::readHword(u32 storageIndex)
{
	auto value = Register32_t::readHword(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeHword(u32 storageIndex, u16 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeHword(storageIndex, value);
}

u32 DebugRegister32_t::readWord()
{
	auto value = Register32_t::readWord();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read u32, Value = %d.", getMnemonic(), value);
#endif
	return value;
}

void DebugRegister32_t::writeWord(u32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write u32, Value = %d.", getMnemonic() value);
#endif
	Register32_t::writeWord(value);
}

#endif