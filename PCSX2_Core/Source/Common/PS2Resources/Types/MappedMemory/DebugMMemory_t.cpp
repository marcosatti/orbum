#include "stdafx.h"

#include "Common/Global/Globals.h"

#if defined(BUILD_DEBUG)

#include "Common/PS2Resources/Types/MappedMemory/DebugMMemory_t.h"

DebugMMemory_t::DebugMMemory_t(const size_t& size, const char* const mnemonic, const u32& PS2PhysicalAddress) :
	MappedMemory_t(size, mnemonic, PS2PhysicalAddress)
{
}

DebugMMemory_t::~DebugMMemory_t()
{
}

u8 DebugMMemory_t::readByteU(u32 storageIndex)
{
	auto value = MappedMemory_t::readByteU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeByteU(u32 storageIndex, u8 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeByteU(storageIndex, value);
}

s8 DebugMMemory_t::readByteS(u32 storageIndex)
{
	auto value = MappedMemory_t::readByteS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeByteS(u32 storageIndex, s8 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s8 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s8 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeByteS(storageIndex, value);
}

u16 DebugMMemory_t::readHwordU(u32 storageIndex)
{
	auto value = MappedMemory_t::readHwordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeHwordU(storageIndex, value);
}

s16 DebugMMemory_t::readHwordS(u32 storageIndex)
{
	auto value = MappedMemory_t::readHwordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s16 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s16 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeHwordS(storageIndex, value);
}

u32 DebugMMemory_t::readWordU(u32 storageIndex)
{
	auto value = MappedMemory_t::readWordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeWordU(u32 storageIndex, u32 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeWordU(storageIndex, value);
}

s32 DebugMMemory_t::readWordS(u32 storageIndex)
{
	auto value = MappedMemory_t::readWordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeWordS(u32 storageIndex, s32 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s32 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s32 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeWordS(storageIndex, value);
}

u64 DebugMMemory_t::readDwordU(u32 storageIndex)
{
	auto value = MappedMemory_t::readDwordU(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write u64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeDwordU(storageIndex, value);
}

s64 DebugMMemory_t::readDwordS(u32 storageIndex)
{
	auto value = MappedMemory_t::readDwordS(storageIndex);
#if LOG_VALUE_AS_HEX
	logDebug("%s: Read s64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Read s64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	return value;
}

void DebugMMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
#if LOG_VALUE_AS_HEX
	logDebug("%s: Write s64 @ Offset = 0x%08X, Value = 0x%X", getMnemonic(), storageIndex, value);
#else
	logDebug("%s: Write s64 @ Offset = 0x%08X, Value = %d", getMnemonic(), storageIndex, value);
#endif
	MappedMemory_t::writeDwordS(storageIndex, value);
}

#endif