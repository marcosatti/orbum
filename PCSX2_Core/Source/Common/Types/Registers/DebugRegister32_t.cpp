#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Registers/DebugRegister32_t.h"

DebugRegister32_t::DebugRegister32_t(const char* const mnemonic) :
	Register32_t(mnemonic)
{
}

u8 DebugRegister32_t::readByteU(u32 storageIndex)
{
	auto value = Register32_t::readByteU(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeByteU(u32 storageIndex, u8 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeByteU(storageIndex, value);
}

s8 DebugRegister32_t::readByteS(u32 storageIndex)
{
	auto value = Register32_t::readByteS(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read s8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeByteS(u32 storageIndex, s8 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write s8[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s8[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeByteS(storageIndex, value);
}

u16 DebugRegister32_t::readHwordU(u32 storageIndex)
{
	auto value = Register32_t::readHwordU(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeHwordU(u32 storageIndex, u16 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeHwordU(storageIndex, value);
}

s16 DebugRegister32_t::readHwordS(u32 storageIndex)
{
	auto value = Register32_t::readHwordS(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read s16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugRegister32_t::writeHwordS(u32 storageIndex, s16 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write s16[%d], Value = 0x%X.", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s16[%d], Value = %d.", getMnemonic(), storageIndex, value);
#endif
	Register32_t::writeHwordS(storageIndex, value);
}

u32 DebugRegister32_t::readWordU()
{
	auto value = Register32_t::readWordU();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read u32, Value = %d.", getMnemonic(), value);
#endif
	return value;
}

void DebugRegister32_t::writeWordU(u32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write u32, Value = %d.", getMnemonic() value);
#endif
	Register32_t::writeWordU(value);
}

s32 DebugRegister32_t::readWordS()
{
	auto value = Register32_t::readWordS();
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read s32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Read s32, Value = %d.", getMnemonic(), value);
#endif
	return value;
}

void DebugRegister32_t::writeWordS(s32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write s32, Value = 0x%X.", getMnemonic(), value);
#else
	logDebug("%s: Write s32, Value = %d.", getMnemonic(), value);
#endif
	Register32_t::writeWordS(value);
}

#endif