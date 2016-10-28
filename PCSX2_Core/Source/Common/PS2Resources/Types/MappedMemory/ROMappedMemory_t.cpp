#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/PS2Resources/Types/MappedMemory/ROMappedMemory_t.h"

ROMappedMemory_t::ROMappedMemory_t(const size_t& size, const char* const mnemonic, const u32& PS2PhysicalAddress) :
	MappedMemory_t(size, mnemonic, PS2PhysicalAddress)
{
}

ROMappedMemory_t::~ROMappedMemory_t()
{
}

void ROMappedMemory_t::writeByteU(u32 storageIndex, u8 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeByteS(u32 storageIndex, s8 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeWordU(u32 storageIndex, u32 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeWordS(u32 storageIndex, s32 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMappedMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}
