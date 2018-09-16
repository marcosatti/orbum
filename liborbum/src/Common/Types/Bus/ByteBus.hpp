#pragma once

#include <limits>
#include <stdexcept>
#include <tuple>
#include <vector>

#include <boost/format.hpp>

#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/BusContext.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"
#include "Common/Types/Primitive.hpp"
#include "Utilities/Utilities.hpp"

#if defined(BUILD_DEBUG)
#define DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS 0
#endif

/// ByteBus is responsible for converting the PS2's physical memory into host memory.
/// It is byte-addressable, and can map the full range of the address type used.
/// The mapping method is actually just a 2 level (directory and pages) page table!
/// The page size is variable per directory, allowing for minimal memory usage.
template <typename AddressTy>
class ByteBus
{
public:
    struct Page
    {
        AddressTy base_address;
        ByteBusMappable* object;
    };

    struct Directory
    {
        Bitfield page_mask;
        int optimal_alignment;
        std::vector<Page> page_table;
    };

    ByteBus(const int directory_mask_length) :
        directory_mask(Bitfield(size_bits<AddressTy>() - directory_mask_length, directory_mask_length)) // Directory mask always occupies most upper bits.
    {
        // Initialise directories, number of directories is fixed.
        // Initially we assume a page size of 1 byte (ie: 0 page index bits),
        // which will later get optimised once everything is mapped. The
        // initial optimal page size is equal to the number of bits left in
        // the 32-bit address (ie: 1 mapping per directory).
        table.resize(static_cast<size_t>(1) << directory_mask.length);
        for (auto& directory : table)
        {
            directory =
                {
                    Bitfield(0, size_bits<AddressTy>() - directory_mask.length),
                    size_bits<AddressTy>() - directory_mask.length,
                    std::vector<Page>()};
        }
    }

    /// Map an object onto the bus, starting at the given address.
    /// The map size is dependant on the object. See ByteBusMappable::bus_size().
    void map(const AddressTy address, ByteBusMappable* object)
    {
        // Who's trying to map a zero-sized object anyway...
        if (!object->byte_bus_map_size())
            throw std::runtime_error("Mapping was a zero-sized object - what are you doing?!");

        // Throw error if the mapped address falls outside of the allowable range.
        // Only need to check VDN, as this is the root level lookup (pages are contiguous).
        const size_t max_vdn = get_vdn(address + object->byte_bus_map_size());
        if (max_vdn >= table.size())
            throw std::runtime_error("Mapping was outside of the allowable address range.");

        // Start mapping the object.
        const int alignment = count_trailing_zeros(address);
        const size_t max_map_size = object->byte_bus_map_size();
        size_t directory_index = get_vdn(address);
        size_t map_size = 0;
        while (true)
        {
            auto& directory = table[directory_index];

            // Check if alignment doesnt fit the current page size.
            // The current directory would need to be resized to accomodate
            // it, but not supported for now.
            if (alignment < directory.page_mask.start)
                throw std::runtime_error("Alignment was smaller than current page size, resizing unsupported.");

            // Resize directory if needed.
            directory.page_table.resize(static_cast<size_t>(1) << directory.page_mask.length);

            // Set the optimal page size.
            directory.optimal_alignment = std::min(directory.optimal_alignment, alignment);

            // Map object entry.
            const size_t page_size = static_cast<size_t>(1) << directory.page_mask.start;
            size_t page_index = directory.page_mask.extract_from(address + map_size);
            while (page_index < directory.page_table.size())
            {
                auto& page = directory.page_table[page_index];

                // Check for existing map - this is bad!
                if (page.object != nullptr)
                    throw std::runtime_error("There was an existing map in the bus.");

                page.base_address = address;
                page.object = object;
                page_index++;

                map_size += page_size;

                if (map_size >= max_map_size)
                    goto finished;
            }

            directory_index++;
        }

    finished:; // Done.
    }

    /// Read or write to a mapped object.
    ubyte read_ubyte(const BusContext context, const AddressTy address) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;
        return page.object->byte_bus_read_ubyte(context, offset);
    }

    void write_ubyte(const BusContext context, const AddressTy address, const ubyte value) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;
        page.object->byte_bus_write_ubyte(context, offset, value);
    }

    uhword read_uhword(const BusContext context, const AddressTy address) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_HWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        return page.object->byte_bus_read_uhword(context, offset);
    }

    void write_uhword(const BusContext context, const AddressTy address, const uhword value) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_HWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        page.object->byte_bus_write_uhword(context, offset, value);
    }

    uword read_uword(const BusContext context, const AddressTy address) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_WORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        return page.object->byte_bus_read_uword(context, offset);
    }

    void write_uword(const BusContext context, const AddressTy address, const uword value) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_WORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        page.object->byte_bus_write_uword(context, offset, value);
    }

    udword read_udword(const BusContext context, const AddressTy address) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_DWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        return page.object->byte_bus_read_udword(context, offset);
    }

    void write_udword(const BusContext context, const AddressTy address, const udword value) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_DWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        page.object->byte_bus_write_udword(context, offset, value);
    }

    uqword read_uqword(const BusContext context, const AddressTy address) const
    {
        auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_QWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        return page.object->byte_bus_read_uqword(context, offset);
    }

    void write_uqword(const BusContext context, const AddressTy address, const uqword value) const
    {
        const auto& page = get_page(address);
        usize offset = address - page.base_address;

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (offset % NUMBER_BYTES_IN_QWORD != 0)
            throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

        page.object->byte_bus_write_uqword(context, offset, value);
    }

    /// Culls the page table to reduce memory footprint.
    /// Achieves this by resizing all page tables to use the optimal alignment.
    void optimise()
    {
        // Make the page table within each directory have a page size
        // as coarse as possible (page size becomes optimal alignment).
        for (auto& directory : table)
        {
            if (directory.page_mask.start != directory.optimal_alignment)
            {
                const Bitfield optimal_page_mask = Bitfield(directory.optimal_alignment, size_bits<AddressTy>() - directory_mask.length - directory.optimal_alignment);
                auto optimal_page_table = std::vector<Page>(static_cast<size_t>(1) << optimal_page_mask.length);

                const size_t index_offset = static_cast<size_t>(1) << directory.optimal_alignment;
                for (size_t index = 0; index < directory.page_table.size(); index += index_offset)
                    optimal_page_table[index / index_offset] = directory.page_table[index];

                directory.page_table.swap(optimal_page_table);
                directory.page_mask = optimal_page_mask;
            }
        }
    }

private:
    /// Given the address properties, performs a lookup in the page
    /// table and returns the mapped entry. On a nullptr object being
    /// retrieved, a runtime_error is thrown (debug builds only).
    const Page& get_page(const AddressTy address) const
    {
        const size_t vdn = get_vdn(address);

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (vdn >= table.size())
            throw std::runtime_error(str(boost::format("ByteBus lookup: no directory exists, address = 0x%08X.") % address));
#endif

        const auto& directory = table[vdn];
        const size_t page_index = directory.page_mask.extract_from(address);

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (page_index >= directory.page_table.size())
            throw std::runtime_error(str(boost::format("ByteBus lookup: no page exists (probably culled), address = 0x%08X.") % address));
#endif

        const auto& page = directory.page_table[page_index];

#if DEBUG_BYTEBUS_RUNTIME_LOOKUP_CHECKS
        if (page.object == nullptr)
            throw std::runtime_error(str(boost::format("ByteBus lookup: nullptr object, address = 0x%08X.") % address));
#endif

        return page;
    }

    /// Returns the VDN (virtual directory number) for the address
    /// given using this Bus' context.
    size_t get_vdn(const AddressTy address) const
    {
        return directory_mask.extract_from(address);
    }

    /// Constant directory mask (set at construction). This can't change
    /// once set.
    const Bitfield directory_mask;

    /// Mapping table.
    /// Structure: [directories] -> [pages] -> mapping object.
    /// The base address is kept to work out the correct offset later.
    /// Initially it is assumed that all pages are using 1 byte page sizes.
    /// Call cull_memory() after all mappings have been made to increase
    /// this page size to the optimal value.
    std::vector<Directory> table;
};
