#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/MappedMemory/BitfieldMMemory32_t.h"

/*
RevBitfieldMMemory32_t provides "reverse bits by writing 1" functionality.
Using the bitfield functions act normally.
*/
class RevBitfieldMMemory32_t : public BitfieldMMemory32_t
{
public:
	explicit RevBitfieldMMemory32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~RevBitfieldMMemory32_t();

	/*
	Before commiting the value, XOR's the old value with new value, which reverses any bits that 1 is written to.
	*/
	void writeWordU(u32 storageIndex, u32 value) override;
};

