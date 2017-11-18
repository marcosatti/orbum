#pragma once

#include <vector>

#include "Common/Types/Primitive.hpp"
#include "Common/Types/Bitfield.hpp"
#include "Common/Types/Bus/BusContext.hpp"

struct ByteBusMappable;

/*
ByteBus is responsible for converting the PS2's physical memory into host memory.
It is byte-addressable, and can map up to 4 GiB (full 32-bit space).
The mapping method is actually just a 2 level (directory and pages) page table!

* Why is two levels used instead of one?
Some mapped storage such as the EE registers are separated only by 16 bytes. This means that in order to support every register, the page size would have to be 16B.
This creates a sort of wasteful memory problem, as we would need to have 4GB / 16B = 268,435,456 page table entries (pointers).
At 8 bytes a pointer (running in 64-bit mode), we would use up 2GB of memory, just for pointers! This is wasteful.
Instead, if we use a two level structure with for example a directory size of 4MB, we only allocate pointers for the directories used.
For the directory table, we require 4GB / 4MB = 1,024 directories, and 1,024 * 8B = 8KB of memory.
For a single directory, we require 4M * 8B = 32MB of memory for pointers. Still not ideal, but certainly not as bad.
However, this works well with the EE physical map, where registers are often clumped together. This means that typically only a handful of directories are created.
The advantage of keeping a page size of 16B is we have more fine grained control of memory, rather than having to allocate a big block of memory.
A similar situation occurs for the IOP's bus space.
*/
class ByteBus
{
public:
	ByteBus(const int page_mask_length, const int offset_mask_length);

	/*
	Map an object onto the bus, starting at the given address.
	The map size is dependant on the object. See ByteBusMappable::bus_size().
	*/
	void map(const uptr address, ByteBusMappable * object);

	/*
	Read or write to a mapped object. 
	*/
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

private:
	
	/// Internal bus parameters used when accessing it in order to calcualate
	/// the correct address. Making them const provides the compiler optimisation
	/// chances (bus will never be initialised again anyway).
	const Bitfield directory_mask;
    const Bitfield page_mask;
    const Bitfield offset_mask;

	/*
	Returns (using this bus' context):
	- VDN (virtual directory number).
	- VPN (virtual page number).
	- Offset.
	*/
	struct AddressProperties
	{
		usize vdn;
		usize vpn;
		usize offset;
	};
	AddressProperties address_properties(const uptr address) const;

	/*
	Mapping table.
	Structure: [directories] -> [pages] -> mapping object.
	The base address is kept to work out the correct offset later.
	*/
	struct Mapping
	{
		uptr base_address;
		ByteBusMappable * object;
	};
	std::vector<std::vector<Mapping>> page_table;

	/*
	Given the address properties, performs a lookup in the page table and returns the mapped entry.
	On a nullptr object being retrieved, a runtime_error is thrown (debug builds only).
	*/
	const Mapping & mapping_at(const AddressProperties & properties);
};
