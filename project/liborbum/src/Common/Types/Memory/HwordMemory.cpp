#include "Common/Types/Memory/HwordMemory.hpp"

void HwordMemory::read(const size_t offset, uhword * buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		buffer[i] = read_uhword(offset + i);
}

void HwordMemory::write(const size_t offset, const uhword * buffer, const size_t length)
{
	for (size_t i = 0; i < length; i++)
		write_uhword(offset + i, buffer[i]);
}
