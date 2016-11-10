#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROMemory_t.h"

ROMemory_t::ROMemory_t(const size_t& size, const char* const mnemonic) :
	Memory_t(size, mnemonic)
{
}

ROMemory_t::~ROMemory_t()
{
}

void ROMemory_t::writeByteU(u32 storageIndex, u8 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeByteS(u32 storageIndex, s8 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeWordU(u32 storageIndex, u32 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeWordS(u32 storageIndex, s32 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}
