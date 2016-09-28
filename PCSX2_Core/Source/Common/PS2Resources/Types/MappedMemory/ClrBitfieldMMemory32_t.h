#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"

/*
ClrBitfieldMMemory32_t provides "clear bits by writing 1" functionality.
Using the bitfield functions act normally.
*/
class ClrBitfieldMMemory32_t : public BitfieldMMemory32_t
{
public:
	explicit ClrBitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~ClrBitfieldMMemory32_t();

	/*
	Before commiting the value, AND's the old value with ~(new value), which clears any bits that 1 is written to.
	*/
	void writeWordU(u32 storageIndex, u32 value) override;
};

