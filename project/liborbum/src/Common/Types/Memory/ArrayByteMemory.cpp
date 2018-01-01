#include <fstream>

#include "Common/Types/Memory/ArrayByteMemory.hpp"

ArrayByteMemory::ArrayByteMemory(const size_t size, const ubyte initial_value, const bool read_only) :
	size(size),
	memory(size, initial_value),
	initial_value(initial_value),
	read_only(read_only)
{
}

void ArrayByteMemory::initialise()
{
	std::vector<ubyte>(size, initial_value).swap(memory);
}

void ArrayByteMemory::read_from_file(const std::string & path, const size_t file_length)
{
	std::ifstream file(path, std::ios_base::binary);
	if (!file)
		throw std::runtime_error("Unable to read file");
	file.read(reinterpret_cast<char*>(&memory[0]), file_length);
}

void ArrayByteMemory::write_to_file(const std::string & path)
{
	std::ofstream file(path, std::ios_base::binary);
	if (!file)
		throw std::runtime_error("Unable to write file");
	file.write(reinterpret_cast<char*>(&memory[0]), size);
}

ubyte ArrayByteMemory::read_ubyte(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	return *reinterpret_cast<ubyte*>(&memory[offset]);
}

void ArrayByteMemory::write_ubyte(const size_t offset, const ubyte value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<ubyte*>(&memory[offset]) = value;
}

uhword ArrayByteMemory::read_uhword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uhword*>(&memory[offset]);
}

void ArrayByteMemory::write_uhword(const size_t offset, const uhword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uhword*>(&memory[offset]) = value;
}

uword ArrayByteMemory::read_uword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uword*>(&memory[offset]);
}

void ArrayByteMemory::write_uword(const size_t offset, const uword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uword*>(&memory[offset]) = value;
}

udword ArrayByteMemory::read_udword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	return *reinterpret_cast<udword*>(&memory[offset]);
}

void ArrayByteMemory::write_udword(const size_t offset, const udword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<udword*>(&memory[offset]) = value;
}

uqword ArrayByteMemory::read_uqword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uqword*>(&memory[offset]);
}

void ArrayByteMemory::write_uqword(const size_t offset, const uqword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uqword*>(&memory[offset]) = value;
}

usize ArrayByteMemory::byte_bus_map_size() const
{
	return static_cast<usize>(size);
}