#include <fstream>

#include "Common/Types/Memory/ArrayHwordMemory.hpp"

ArrayHwordMemory::ArrayHwordMemory(const size_t size, const uhword initial_value, const bool read_only) :
	size(size),
	memory(size, initial_value),
	initial_value(initial_value),
	read_only(read_only)
{
}

void ArrayHwordMemory::initialise()
{
	std::vector<uhword>(size, initial_value).swap(memory);
}

uhword ArrayHwordMemory::read_uhword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uhword*>(&memory[offset]);
}

void ArrayHwordMemory::write_uhword(const size_t offset, const uhword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uhword*>(&memory[offset]) = value;
}

uword ArrayHwordMemory::read_uword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uword*>(&memory[offset]);
}

void ArrayHwordMemory::write_uword(const size_t offset, const uword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uword*>(&memory[offset]) = value;
}

udword ArrayHwordMemory::read_udword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	return *reinterpret_cast<udword*>(&memory[offset]);
}

void ArrayHwordMemory::write_udword(const size_t offset, const udword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<udword*>(&memory[offset]) = value;
}

uqword ArrayHwordMemory::read_uqword(const size_t offset)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	return *reinterpret_cast<uqword*>(&memory[offset]);
}

void ArrayHwordMemory::write_uqword(const size_t offset, const uqword value)
{
#if defined(BUILD_DEBUG)
	if (offset >= size)
		throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

	if (!read_only)
		*reinterpret_cast<uqword*>(&memory[offset]) = value;
}

void ArrayHwordMemory::read_from_file(const std::string & path, const size_t file_length)
{
	std::ifstream file(path, std::ios_base::binary);
	if (!file)
		throw std::runtime_error("Unable to read file");
	file.read(reinterpret_cast<char*>(&memory[0]), file_length * NUMBER_BYTES_IN_HWORD);
}

void ArrayHwordMemory::write_to_file(const std::string & path)
{
	std::ofstream file(path, std::ios_base::binary);
	if (!file)
		throw std::runtime_error("Unable to write file");
	file.write(reinterpret_cast<char*>(&memory[0]), size * NUMBER_BYTES_IN_HWORD);
}