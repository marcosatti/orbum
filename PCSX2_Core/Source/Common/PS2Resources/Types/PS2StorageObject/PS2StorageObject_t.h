#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/StorageObject/StorageObject_t.h"

/*
Storage object which defines a PS2 Physical address that it starts from - used by the VM MMU to map for address translation.
Useful for static memory locations, such as the PS2's main memory, which starts at physical address 0 and never changes.
*/
class PS2StorageObject_t : public StorageObject_t
{
public:
	PS2StorageObject_t(const size_t& size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~PS2StorageObject_t();

	const u32 & getPS2PhysicalAddress() const;

private:
	const u32 mPS2PhysicalAddress;
};

