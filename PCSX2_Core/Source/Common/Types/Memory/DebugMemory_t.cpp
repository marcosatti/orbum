#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Memory/DebugMemory_t.h"

DebugMemory_t::DebugMemory_t(const size_t& size, const char* const mnemonic) :
	Memory_t(size, mnemonic)
{
}

DebugMemory_t::~DebugMemory_t()
{
}

u8 DebugMemory_t::readByteU(u32 storageIndex)
{
	auto value = Memory_t::readByteU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeByteU(u32 storageIndex, u8 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeByteU(storageIndex, value);
}

s8 DebugMemory_t::readByteS(u32 storageIndex)
{
	auto value = Memory_t::readByteS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeByteS(u32 storageIndex, s8 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeByteS(storageIndex, value);
}

u16 DebugMemory_t::readHwordU(u32 storageIndex)
{
	auto value = Memory_t::readHwordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeHwordU(storageIndex, value);
}

s16 DebugMemory_t::readHwordS(u32 storageIndex)
{
	auto value = Memory_t::readHwordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeHwordS(storageIndex, value);
}

u32 DebugMemory_t::readWordU(u32 storageIndex)
{
	auto value = Memory_t::readWordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeWordU(u32 storageIndex, u32 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeWordU(storageIndex, value);
}

s32 DebugMemory_t::readWordS(u32 storageIndex)
{
	auto value = Memory_t::readWordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeWordS(u32 storageIndex, s32 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeWordS(storageIndex, value);
}

u64 DebugMemory_t::readDwordU(u32 storageIndex)
{
	auto value = Memory_t::readDwordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeDwordU(storageIndex, value);
}

s64 DebugMemory_t::readDwordS(u32 storageIndex)
{
	auto value = Memory_t::readDwordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeDwordS(storageIndex, value);
}

#endif