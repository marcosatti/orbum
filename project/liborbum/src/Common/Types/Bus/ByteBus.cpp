#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>

#include "Utilities/Utilities.hpp"

#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"

ByteBus::ByteBus(const int directory_mask_length) :
	directory_mask(Bitfield((sizeof(uptr) * CHAR_BIT) -  directory_mask_length, directory_mask_length)),
	table(1 << directory_mask.length)
{
	const int initial_page_bits = 0;
	const int initial_optimal_page_bits = (sizeof(uptr) * CHAR_BIT) - directory_mask_length;

	for (auto& directory : table)
	{
		directory = std::make_tuple(
			initial_page_bits,
			initial_optimal_page_bits,
			std::vector<std::tuple<uptr, ByteBusMappable*>>()
		);
	}
}

void ByteBus::map(const uptr address, ByteBusMappable * object)
{
	// Who's trying to map a zero-sized object anyway...
	if (!object->byte_bus_map_size())
		throw std::runtime_error("Mapping was a zero-sized object - what are you doing?!");

	// Throw error if the mapped address falls outside of the allowable range.
	// Only need to check VDN, as this is the root level lookup (pages are contiguous).
	const size_t max_vdn = get_vdn(address + object->byte_bus_map_size());
	if (max_vdn >= (1 << directory_mask.length))
		throw std::runtime_error("Mapping was outside of the allowable address range.");

	// Start mapping the object.
	const int alignment = count_trailing_zeros(address);
	const size_t max_map_size = object->byte_bus_map_size();
	size_t directory_index = get_vdn(address);
	size_t map_size = 0;
	while (true)
	{
		auto&[current_page_size, optimal_page_size, page_table] = table[directory_index];

		// Check if alignment doesnt fit the current page size.
		// The current directory would need to be resized to accomodate it, but not supported for now.
		if (alignment < current_page_size)
			throw std::runtime_error("Alignment was smaller than current page size, resizing unsupported.");

		const size_t max_page_bits = (sizeof(uptr) * CHAR_BIT) - directory_mask.length - current_page_size;
		const size_t max_page_size = static_cast<size_t>(1) << (max_page_bits);

		// Resize directory if needed.
		page_table.resize(max_page_size);

		// Set the optimal page size.
		optimal_page_size = std::min(optimal_page_size, alignment);

		// Map object entry.
		size_t page_index = Bitfield(0, max_page_bits).extract_from(address + map_size);
		while (page_index < max_page_size)
		{
			auto&[mapping_base_address, mapping_object] = page_table[page_index];

			// Check for existing map - this is bad!
			if (mapping_object != nullptr)
				throw std::runtime_error("There was an existing map in the bus.");

			mapping_base_address = address;
			mapping_object = object;
			page_index++;

			map_size += (1 << current_page_size);

			if (map_size >= max_map_size)
				goto finished;
		}		

		directory_index++;
	}

finished:
	; // Done.
}

const std::tuple<uptr, ByteBusMappable*> & ByteBus::get_mapping(const uptr address)
{
	auto&[current_page_size, optimal_page_size, page_table] = table[get_vdn(address)];
	size_t page_index = Bitfield(current_page_size, (sizeof(uptr) * CHAR_BIT) - directory_mask.length - current_page_size).extract_from(address);
	auto&[base_address, object] = page_table[page_index];

#if defined(BUILD_DEBUG)
	if (object == nullptr)
	{
		throw std::runtime_error("ByteBus nullptr lookup.");
		//uptr address = (properties.vdn << (page_mask.length + offset_mask.length)) 
		//	| (properties.vpn << offset_mask.length) 
		//	| (properties.offset);
		//std::string message = str(boost::format("ByteBus nullptr lookup, address (inc. offset) = 0x%08X.") % address);
		//throw std::runtime_error(message);
	}
#endif

	return page_table[page_index];
}

ubyte ByteBus::read_ubyte(const BusContext context, const uptr address)
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;
	return object->byte_bus_read_ubyte(context, offset);
}

void ByteBus::write_ubyte(const BusContext context, const uptr address, const ubyte value)
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;
	object->byte_bus_write_ubyte(context, offset, value);
}

uhword ByteBus::read_uhword(const BusContext context, const uptr address) 
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return object->byte_bus_read_uhword(context, offset);
}

void ByteBus::write_uhword(const BusContext context, const uptr address, const uhword value) 
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	object->byte_bus_write_uhword(context, offset, value);
}

uword ByteBus::read_uword(const BusContext context, const uptr address) 
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return object->byte_bus_read_uword(context, offset);
}

void ByteBus::write_uword(const BusContext context, const uptr address, const uword value) 
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	object->byte_bus_write_uword(context, offset, value);
}

udword ByteBus::read_udword(const BusContext context, const uptr address)
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return object->byte_bus_read_udword(context, offset);
}

void ByteBus::write_udword(const BusContext context, const uptr address, const udword value)
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	object->byte_bus_write_udword(context, offset, value);
}

uqword ByteBus::read_uqword(const BusContext context, const uptr address) 
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return object->byte_bus_read_uqword(context, offset);
}

void ByteBus::write_uqword(const BusContext context, const uptr address, const uqword value)
{
	auto&[base_address, object] = get_mapping(address);
	usize offset = address - base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	object->byte_bus_write_uqword(context, offset, value);
}

void ByteBus::cull_memory()
{
	for (auto& directory : table)
	{
		auto&[current_page_size, optimal_page_size, page_table] = directory;

		if (current_page_size != optimal_page_size)
		{
			int optimal_max_pages = (sizeof(uptr) * CHAR_BIT) - directory_mask.length - optimal_page_size;
			auto optimal_page_table = std::vector<std::tuple<uptr, ByteBusMappable*>>(static_cast<size_t>(1) << optimal_max_pages);

			int index_delta = static_cast<size_t>(1) << optimal_page_size;
			for (size_t index = 0; index < page_table.size(); index += index_delta)
				optimal_page_table[index / index_delta] = page_table[index];

			page_table.swap(optimal_page_table);
			current_page_size = optimal_page_size;
		}

		page_table.shrink_to_fit();
	}

	table.shrink_to_fit();
}

size_t ByteBus::get_vdn(const uptr address) const
{
	return directory_mask.extract_from(address);
}
