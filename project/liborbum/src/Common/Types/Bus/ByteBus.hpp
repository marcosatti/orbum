#pragma once

#include <vector>
#include <tuple>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/BusContext.hpp"

struct ByteBusMappable;

/// ByteBus is responsible for converting the PS2's physical memory into host memory.
/// It is byte-addressable, and can map up to 4 GiB (full 32-bit space).
/// The mapping method is actually just a 2 level (directory and pages) page table!
/// The page size is variable (per directory), allowing for minimal memory usage.
class ByteBus
{
public:
	ByteBus(const int directory_mask_length);

	/// Map an object onto the bus, starting at the given address.
	/// The map size is dependant on the object. See ByteBusMappable::bus_size().
	void map(const uptr address, ByteBusMappable * object);

	/// Read or write to a mapped object. 
	ubyte read_ubyte(const BusContext context, const uptr address);
	void write_ubyte(const BusContext context, const uptr address, const ubyte value);
	uhword read_uhword(const BusContext context, const uptr address);
	void write_uhword(const BusContext context, const uptr address, const uhword value);
	uword read_uword(const BusContext context, const uptr address);
	void write_uword(const BusContext context, const uptr address, const uword value);
	udword read_udword(const BusContext context, const uptr address);
	void write_udword(const BusContext context, const uptr address, const udword value);
	uqword read_uqword(const BusContext context, const uptr address);
	void write_uqword(const BusContext context, const uptr address, const uqword value);

	/// Culls the page table to reduce memory footprint.
	/// Use after all mappings are initialised. Reduces the directories 
	/// overall sizes by cutting off any unused end, and resizes the pages
	/// for the optimal page size within a directory.
	void cull_memory();

private:
	/// Internal bus parameters used.
	const Bitfield directory_mask;

	/// Returns the VDN (virtual directory number) for the address 
	/// given using the Bus' context.
	size_t get_vdn(const uptr address) const;

	/// Mapping table.
	/// Structure: [directories] -> [pages] -> mapping object.
	/// The base address is kept to work out the correct offset later.
	/// Initially it is assumed that all pages are using 1 byte page sizes.
	/// Call cull_memory() after all mappings have been made to increase
	/// this page size to the optimal value.
	///                Current  Optimal  Pages           BaseAddr  Object
	std::vector<std::tuple<int, int, std::vector<std::tuple<uptr, ByteBusMappable*>>>> table;

	/// Given the address properties, performs a lookup in the page
	/// table and returns the mapped entry. On a nullptr object being 
	/// retrieved, a runtime_error is thrown (debug builds only).
	const std::tuple<uptr, ByteBusMappable*> & get_mapping(const uptr address);
};
