#pragma once

#include <vector>

#include "Common/Types/Memory/HwordMemory.hpp"

/// Array backed hword-addressed memory.
/// Can be optionally initialised with a hword value, copied across the whole array.
class ArrayHwordMemory : public HwordMemory
{
public:
	ArrayHwordMemory(const size_t size, const uhword initial_value = 0, const bool read_only = false);

	/// Initialise memory.
	void initialise() override;

	/// Read in a raw file to the memory (hword copy).
	/// For Core use only! Do not use within the controller logic.
	void read_from_file(const std::string & path, const size_t file_length);

	/// Dumps the memory contents to a file.
	/// For Core use only! Do not use within the controller logic.
	void write_to_file(const std::string & path);

	/// Read or write a value of a given type, to the specified hword index (offset).
	uhword read_uhword(const size_t offset) override;
	void write_uhword(const size_t offset, const uhword value) override;
	uword read_uword(const size_t offset) override;
	void write_uword(const size_t offset, const uword value) override;
	udword read_udword(const size_t offset) override;
	void write_udword(const size_t offset, const udword value) override;
	uqword read_uqword(const size_t offset) override;
	void write_uqword(const size_t offset, const uqword value) override;

    /// Get a reference to the memory storage.
    /// Used for the emulator: sometimes we need to peek and poke directly.
    std::vector<uhword> & get_memory();

private:
	/// Total size of the hword memory.
    size_t size;
    
	/// Array backend for the hword memory.
	std::vector<uhword> memory;

	/// Initial value.
	uhword initial_value;

	/// Read-only flag.
	/// Writes are silently discarded if turned on.
	bool read_only;
};

