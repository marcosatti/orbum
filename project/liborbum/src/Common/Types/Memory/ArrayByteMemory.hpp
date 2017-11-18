#pragma once

#include <vector>

#include "Common/Types/Memory/ByteMemory.hpp"

/*
Array backed byte-addressed memory.
Can be optionally initialised with a byte value, copied across the whole array.
*/
class ArrayByteMemory : public ByteMemory
{
public:
	ArrayByteMemory(const size_t size, const ubyte initial_value = 0, const bool read_only = false);

	/*
	Initialise memory.
	*/
	void initialise() override;

	/*
	Read in a raw file to the memory (byte copy).
	For VM use only! Do not use within the system logic.
	*/
	void read_from_file(const char * file_path, const size_t file_length);

	/*
	Dumps the memory contents to a file.
	For VM use only! Do not use within the system logic.
	*/
	void write_to_file(const char * file_path);

	/*
	Read or write a value of a given type, to the specified byte index (offset).
	*/
	ubyte read_ubyte(const size_t offset) override;
	void write_ubyte(const size_t offset, const ubyte value) override;
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;
	udword read_udword(const size_t offset) override;
	void write_udword(const size_t offset, const udword value) override;
	uqword read_uqword(const size_t offset) override;
	void write_uqword(const size_t offset, const uqword value) override;

	/*
	ByteBusMappable overrides.
	*/
	usize byte_bus_map_size() const override;

private:
	/*
	Total size of the byte memory.
	*/
	size_t size;

	/*
	Array backend for the byte memory.
	*/
	std::vector<ubyte> memory;

	/*
	Initial value.
	*/
	ubyte initial_value;

	/*
	Read-only flag.
	Writes are silently discarded if turned on.
	*/
	bool read_only;
};

