#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROMemory_t.h"

ROMemory_t::ROMemory_t(const size_t& size, const char* mnemonic) :
	Memory_t(size, mnemonic)
{
}

ROMemory_t::~ROMemory_t()
{
}

void ROMemory_t::writeByte(u32 storageIndex, u8 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeHword(u32 storageIndex, u16 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeWord(u32 storageIndex, u32 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeDword(u32 storageIndex, u64 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, Value = %d).", getMnemonic(), storageIndex, value);
#endif
}

void ROMemory_t::writeQword(u32 storageIndex, u128 value)
{
#if DEBUG_LOG_RO_MM_WRITES
	logDebug("%s: Tried to perform a write to a RO mapped memory object - discarded! (Offset = 0x%08X, ValueLSB = %d, ValueMSB = %d).", getMnemonic(), storageIndex, value.lo, value.hi);
#endif
}
