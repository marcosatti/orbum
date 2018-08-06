#pragma once

#include <fstream>

#include <cereal/types/vector.hpp>

#include "Common/Types/Memory/HwordMemory.hpp"

/// Array backed hword-addressed memory.
/// Can be optionally initialised with a hword value, copied across the whole array.
class ArrayHwordMemory : public HwordMemory
{
public:
    ArrayHwordMemory(const size_t size, const uhword initial_value = 0, const bool read_only = false) :
        size(size),
        memory(size, initial_value),
        initial_value(initial_value),
        read_only(read_only)
    {
    }

    /// Initialise memory.
    void initialize() override
    {
        std::vector<uhword>(size, initial_value).swap(memory);
    }

    /// Read in a raw file to the memory (hword copy).
    /// For Core use only! Do not use within the controller logic.
    void read_from_file(const std::string& path, const size_t file_length)
    {
        std::ifstream file(path, std::ios_base::binary);
        if (!file)
            throw std::runtime_error("Unable to read file");
        file.read(reinterpret_cast<char*>(&memory[0]), file_length * NUMBER_BYTES_IN_HWORD);
    }

    /// Dumps the memory contents to a file.
    /// For Core use only! Do not use within the controller logic.
    void write_to_file(const std::string& path)
    {
        std::ofstream file(path, std::ios_base::binary);
        if (!file)
            throw std::runtime_error("Unable to write file");
        file.write(reinterpret_cast<char*>(&memory[0]), size * NUMBER_BYTES_IN_HWORD);
    }

    /// Read or write a value of a given type, to the specified hword index (offset).
    uhword read_uhword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        return *reinterpret_cast<uhword*>(&memory[offset]);
    }

    void write_uhword(const size_t offset, const uhword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        if (!read_only)
            *reinterpret_cast<uhword*>(&memory[offset]) = value;
    }

    uword read_uword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        return *reinterpret_cast<uword*>(&memory[offset]);
    }

    void write_uword(const size_t offset, const uword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        if (!read_only)
            *reinterpret_cast<uword*>(&memory[offset]) = value;
    }

    udword read_udword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        return *reinterpret_cast<udword*>(&memory[offset]);
    }

    void write_udword(const size_t offset, const udword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        if (!read_only)
            *reinterpret_cast<udword*>(&memory[offset]) = value;
    }

    uqword read_uqword(const size_t offset) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        return *reinterpret_cast<uqword*>(&memory[offset]);
    }

    void write_uqword(const size_t offset, const uqword value) override
    {
#if defined(BUILD_DEBUG)
        if (offset >= size)
            throw std::runtime_error("Tried to access ArrayHwordMemory with an invalid offset.");
#endif

        if (!read_only)
            *reinterpret_cast<uqword*>(&memory[offset]) = value;
    }

    /// Get a reference to the memory storage.
    /// Used for the emulator: sometimes we need to peek and poke directly.
    std::vector<uhword>& get_memory()
    {
        return memory;
    }

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

public:
    template<class Archive>
    void save(Archive & archive) const
    {
        archive.saveBinaryValue(reinterpret_cast<const char*>(memory.data()), memory.size() * sizeof(uhword), "memory");
    }

    template<class Archive>
    void load(Archive & archive)
    {     
        archive.loadBinaryValue(reinterpret_cast<const char*>(memory.data()), memory.size() * sizeof(uhword), "memory");
    }
};
