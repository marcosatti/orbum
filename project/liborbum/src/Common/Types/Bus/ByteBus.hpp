#pragma once

#include <vector>
#include <tuple>
#include <limits>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/BusContext.hpp"

struct ByteBusMappable;

/// ByteBus is responsible for converting the PS2's physical memory into host memory.
/// It is byte-addressable, and can map up to 4 GiB (full 32-bit space).
/// The mapping method is actually just a 2 level (directory and pages) page table!
/// The page size is variable per directory, allowing for minimal memory usage.
class ByteBus
{
public:
	ByteBus(const int directory_mask_length);

	/// Map an object onto the bus, starting at the given address.
	/// The map size is dependant on the object. See ByteBusMappable::bus_size().
	void map(const uptr address, ByteBusMappable * object);

	/// Read or write to a mapped object. 
	ubyte read_ubyte(const BusContext context, const uptr address) const;
	void write_ubyte(const BusContext context, const uptr address, const ubyte value) const;
	uhword read_uhword(const BusContext context, const uptr address) const;
	void write_uhword(const BusContext context, const uptr address, const uhword value) const;
	uword read_uword(const BusContext context, const uptr address) const;
	void write_uword(const BusContext context, const uptr address, const uword value) const;
	udword read_udword(const BusContext context, const uptr address) const;
	void write_udword(const BusContext context, const uptr address, const udword value) const;
	uqword read_uqword(const BusContext context, const uptr address) const;
	void write_uqword(const BusContext context, const uptr address, const uqword value) const;

	/// Culls the page table to reduce memory footprint.
	/// Achieves this by resizing all page tables to use the optimal alignment.
	void optimise();

private:
	struct Page
	{
		uptr base_address;
		ByteBusMappable * object;
	};

	struct Directory
	{
		Bitfield page_mask;
		int optimal_alignment;
		std::vector<Page> page_table;
	};

	/// Returns the VDN (virtual directory number) for the address 
	/// given using this Bus' context.
	size_t get_vdn(const uptr address) const;

	/// Given the address properties, performs a lookup in the page
	/// table and returns the mapped entry. On a nullptr object being 
	/// retrieved, a runtime_error is thrown (debug builds only).
	const Page & get_page(const uptr address) const;

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
