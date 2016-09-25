#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/BitfieldStorageObject32_t.h"

/*
ClrBitfieldStorageObject32_t provides "clear bits by writing 1" functionality.
Using the bitfield functions act normally.
*/
class ClrBitfieldStorageObject32_t : public BitfieldStorageObject32_t
{
public:
	explicit ClrBitfieldStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~ClrBitfieldStorageObject32_t();

	/*
	Before commiting the value, AND's the old value with ~(new value), which clears any bits that 1 is written to.
	*/
	void writeWordU(u32 storageIndex, u32 value) override;
};

