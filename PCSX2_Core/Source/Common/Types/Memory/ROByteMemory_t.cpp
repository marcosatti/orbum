#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ROByteMemory_t.h"

ROByteMemory_t::ROByteMemory_t(const size_t& size) :
	ByteMemory_t(size)
{
}

void ROByteMemory_t::writeByte(const System_t context, size_t byteOffset, u8 value)
{
	// Do not write (read only).
}

void ROByteMemory_t::writeHword(const System_t context, size_t byteOffset, u16 value)
{
	// Do not write (read only).
}

void ROByteMemory_t::writeWord(const System_t context, size_t byteOffset, u32 value)
{
	// Do not write (read only).
}

void ROByteMemory_t::writeDword(const System_t context, size_t byteOffset, u64 value)
{
	// Do not write (read only).
}

void ROByteMemory_t::writeQword(const System_t context, size_t byteOffset, u128 value)
{
	// Do not write (read only).
}
