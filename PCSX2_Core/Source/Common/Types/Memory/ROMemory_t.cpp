#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROMemory_t.h"

ROMemory_t::ROMemory_t(const size_t& size) :
	Memory_t(size)
{
}

ROMemory_t::~ROMemory_t()
{
}

void ROMemory_t::writeByte(const Context& context, size_t storageIndex, u8 value)
{
	// Do not write (read only).
}

void ROMemory_t::writeHword(const Context& context, size_t storageIndex, u16 value)
{
	// Do not write (read only).
}

void ROMemory_t::writeWord(const Context& context, size_t storageIndex, u32 value)
{
	// Do not write (read only).
}

void ROMemory_t::writeDword(const Context& context, size_t storageIndex, u64 value)
{
	// Do not write (read only).
}

void ROMemory_t::writeQword(const Context& context, size_t storageIndex, u128 value)
{
	// Do not write (read only).
}
