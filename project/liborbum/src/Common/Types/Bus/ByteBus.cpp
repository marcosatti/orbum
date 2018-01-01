#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>

#include "Common/Types/Bus/ByteBus.hpp"
#include "Common/Types/Bus/ByteBusMappable.hpp"

ByteBus::ByteBus(const int page_mask_length, const int offset_mask_length) :
	offset_mask(Bitfield(0, offset_mask_length)),
	page_mask(Bitfield(offset_mask_length, page_mask_length)),
	directory_mask(Bitfield(page_mask_length + offset_mask_length, (sizeof(uptr) * CHAR_BIT) - (page_mask_length + offset_mask_length))),
	page_table(static_cast<size_t>(1) << directory_mask.length)
{
	// Note: compile time checks will occur in the Bitfield class, that will raise an error if parameters are not valid.
}

void ByteBus::map(const uptr address, ByteBusMappable * object)
{
	// Who's trying to map a zero-sized object anyway...
	if (!object->byte_bus_map_size())
		throw std::runtime_error("Mapping was a zero-sized object - what are you doing?!");

	// Get the physical address properties, including VDN, VPN and offset.
	auto properties = address_properties(address);

	// Throw error if the address is not aligned to a page boundary - a single page can only point to one object, not multiple.
	if (properties.offset != 0)
		throw std::runtime_error("Mapping was not aligned to a page boundary - not supported!");

	// Throw error if the mapped address falls outside of the allowable range.
	// Only need to check VDN, as this is the root level lookup.
	usize max_vdn = address_properties(address + object->byte_bus_map_size()).vdn;
	if (max_vdn >= (static_cast<usize>(1) << directory_mask.length))
		throw std::runtime_error("Mapping was outside of the allowable address range.");

	// All checks ok - map the object.
	usize map_size = 0;
	usize max_map_size = object->byte_bus_map_size();
	usize max_pages_size = static_cast<usize>(1) << page_mask.length;
	usize page_size = static_cast<usize>(1) << offset_mask.length;
	usize directory_index = properties.vdn;
	usize page_index = properties.vpn;
	while (true)
	{
		// Allocate pages within directory if needed.
		page_table[directory_index].resize(static_cast<size_t>(max_pages_size));

		// Map object entry.
		while (page_index < max_pages_size)
		{
			auto& mapping = page_table[directory_index][page_index];

			// Check for existing map - this is bad!
			if (mapping.object != nullptr)
				throw std::runtime_error("There was an existing map in the bus.");

			mapping.base_address = address;
			mapping.object = object;
			page_index++;

			map_size += page_size;

			if (map_size >= max_map_size)
				goto finished;
		}		

		page_index = 0;
		directory_index++;
	}

finished:
	; // Done.
}

ByteBus::AddressProperties ByteBus::address_properties(const uptr address) const
{
	return
	{
		/* VDN    */ (address >> (page_mask.length + offset_mask.length)) & directory_mask.unshifted_mask<uword>(),
		/* VPN    */ (address >> offset_mask.length) & page_mask.unshifted_mask<uword>(),
		/* Offset */ address & offset_mask.unshifted_mask<uword>()
	};
}

const ByteBus::Mapping & ByteBus::mapping_at(const AddressProperties & properties)
{
	auto& mapping = page_table[properties.vdn][properties.vpn];

#if defined(BUILD_DEBUG)
	if (mapping.object == nullptr)
	{
		uptr address = (properties.vdn << (page_mask.length + offset_mask.length)) 
			| (properties.vpn << offset_mask.length) 
			| (properties.offset);
		std::string message = str(boost::format("ByteBus nullptr lookup, address (inc. offset) = 0x%08X.") % address);
		throw std::runtime_error(message);
	}
#endif

	return mapping;
}

ubyte ByteBus::read_ubyte(const BusContext context, const uptr address)
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;
	return mapping.object->byte_bus_read_ubyte(context, offset);
}

void ByteBus::write_ubyte(const BusContext context, const uptr address, const ubyte value)
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;
	mapping.object->byte_bus_write_ubyte(context, offset, value);
}

uhword ByteBus::read_uhword(const BusContext context, const uptr address) 
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return mapping.object->byte_bus_read_uhword(context, offset);
}

void ByteBus::write_uhword(const BusContext context, const uptr address, const uhword value) 
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_HWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	mapping.object->byte_bus_write_uhword(context, offset, value);
}

uword ByteBus::read_uword(const BusContext context, const uptr address) 
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return mapping.object->byte_bus_read_uword(context, offset);
}

void ByteBus::write_uword(const BusContext context, const uptr address, const uword value) 
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_WORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	mapping.object->byte_bus_write_uword(context, offset, value);
}

udword ByteBus::read_udword(const BusContext context, const uptr address)
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return mapping.object->byte_bus_read_udword(context, offset);
}

void ByteBus::write_udword(const BusContext context, const uptr address, const udword value)
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_DWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	mapping.object->byte_bus_write_udword(context, offset, value);
}

uqword ByteBus::read_uqword(const BusContext context, const uptr address) 
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	return mapping.object->byte_bus_read_uqword(context, offset);
}

void ByteBus::write_uqword(const BusContext context, const uptr address, const uqword value)
{
	auto properties = address_properties(address);
	auto& mapping = mapping_at(properties);
	usize offset = address - mapping.base_address;

#if defined(BUILD_DEBUG)
	if (offset % NUMBER_BYTES_IN_QWORD != 0)
		throw std::runtime_error("Tried to access ByteBus with an unaligned offset.");
#endif

	mapping.object->byte_bus_write_uqword(context, offset, value);
}

void ByteBus::cull_memory()
{
	page_table.shrink_to_fit();
}
