#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/Types/Memory/DebugMemory_t.h"

DebugMemory_t::DebugMemory_t(const size_t& size, const char* mnemonic) :
	Memory_t(size, mnemonic)
{
}

DebugMemory_t::~DebugMemory_t()
{
}

u8 DebugMemory_t::readByte(u32 storageIndex)
{
	auto value = Memory_t::readByte(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeByte(u32 storageIndex, u8 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeByte(storageIndex, value);
}

u16 DebugMemory_t::readHword(u32 storageIndex)
{
	auto value = Memory_t::readHword(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeHword(u32 storageIndex, u16 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeHword(storageIndex, value);
}

u32 DebugMemory_t::readWord(u32 storageIndex)
{
	auto value = Memory_t::readWord(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeWord(u32 storageIndex, u32 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeWord(storageIndex, value);
}

u64 DebugMemory_t::readDword(u32 storageIndex)
{
	auto value = Memory_t::readDword(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMemory_t::writeDword(u32 storageIndex, u64 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	Memory_t::writeDword(storageIndex, value);
}

u128 DebugMemory_t::readQword(u32 storageIndex)
{
	auto value = Memory_t::readQword(storageIndex);
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Read u64 @ Offset = 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X", getMnemonic(), storageIndex, value.lo, value.hi);
#else
	logDebug("%s: Read u64 @ Offset = 0x%08X, ValueLSB = %d, ValueMSB = %d", getMnemonic(), storageIndex, value.lo, value.hi);
#endif
	return value;
}

void DebugMemory_t::writeQword(u32 storageIndex, u128 value)
{
#if DEBUG_MEM_LOG_VALUE_AS_HEX
	logDebug("%s: Write u64 @ Offset = 0x%08X, ValueLSB = 0x%X, ValueMSB = 0x%X", getMnemonic(), storageIndex, value.lo, value.hi);
#else
	logDebug("%s: Write u64 @ Offset = 0x%08X, ValueLSB = %d, ValueMSB = %d", getMnemonic(), storageIndex, value.lo, value.hi);
#endif
	Memory_t::writeQword(storageIndex, value);
}

#endif
