#pragma once

#include <vector>
#include <fstream>

#include "Common/Types/Memory/ByteMemory.hpp"

/// Array backed byte-addressed memory.
/// Can be optionally initialised with a byte value, copied across the whole array.
class ArrayByteMemory : public ByteMemory
{
public:
	ArrayByteMemory(const size_t size, const ubyte initial_value = 0, const bool read_only = false) :
		size(size),
		memory(size, initial_value),
		initial_value(initial_value),
		read_only(read_only)
	{
	}

	/// Initialise memory.
	void initialise() override
	{
		std::vector<ubyte>(size, initial_value).swap(memory);
	}

	/// Read in a raw file to the memory (byte copy).
	/// For Core use only! Do not use within the controller logic.
	void read_from_file(const std::string & path, const size_t file_length)
	{
		std::ifstream file(path, std::ios_base::binary);
		if (!file)
			throw std::runtime_error("Unable to read file");
		file.read(reinterpret_cast<char*>(&memory[0]), file_length);
	}

	/// Dumps the memory contents to a file.
	/// For Core use only! Do not use within the controller logic.
	void write_to_file(const std::string & path)
	{
		std::ofstream file(path, std::ios_base::binary);
		if (!file)
			throw std::runtime_error("Unable to write file");
		file.write(reinterpret_cast<char*>(&memory[0]), size);
	}

	/// Read or write a value of a given type, to the specified byte index (offset).
	ubyte read_ubyte(const size_t offset) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		return *reinterpret_cast<ubyte*>(&memory[offset]);
	}

	void write_ubyte(const size_t offset, const ubyte value) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		if (!read_only)
			*reinterpret_cast<ubyte*>(&memory[offset]) = value;
	}

	uhword read_uhword(const size_t offset) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		return *reinterpret_cast<uhword*>(&memory[offset]);
	}

	void write_uhword(const size_t offset, const uhword value) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		if (!read_only)
			*reinterpret_cast<uhword*>(&memory[offset]) = value;
	}

	uword read_uword(const size_t offset) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		return *reinterpret_cast<uword*>(&memory[offset]);
	}

	void write_uword(const size_t offset, const uword value) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		if (!read_only)
			*reinterpret_cast<uword*>(&memory[offset]) = value;
	}

	udword read_udword(const size_t offset) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		return *reinterpret_cast<udword*>(&memory[offset]);
	}

	void write_udword(const size_t offset, const udword value) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		if (!read_only)
			*reinterpret_cast<udword*>(&memory[offset]) = value;
	}

	uqword read_uqword(const size_t offset) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		return *reinterpret_cast<uqword*>(&memory[offset]);
	}

	void write_uqword(const size_t offset, const uqword value) override
	{
	#if defined(BUILD_DEBUG)
		if (offset >= size)
			throw std::runtime_error("Tried to access ArrayByteMemory with an invalid offset.");
	#endif

		if (!read_only)
			*reinterpret_cast<uqword*>(&memory[offset]) = value;
	}

	/// ByteBusMappable overrides.
	usize byte_bus_map_size() const override
	{
		return static_cast<usize>(size);
	}

    /// Get a reference to the memory storage.
    /// Used for the emulator: sometimes we need to peek and poke directly.
    std::vector<ubyte> & get_memory()
	{
		return memory;
	}

private:
	/// Total size of the byte memory.
	size_t size;

	/// Array backend for the byte memory.
	std::vector<ubyte> memory;

	/// Initial value.
	ubyte initial_value;

	/// Read-only flag.
	/// Writes are silently discarded if turned on.
	bool read_only;
};
