#pragma once

#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"

/*
XORStorageObject_t is a toggle storage object - each write toggles the stored bits with the set bits from the parsed value (XOR'd).
For an example of its use, see the INTC: I_MASK register on page 31 of the EE Users Manual.
*/

class XORStorageObject_t : public StorageObject_t
{
public:
	XORStorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	~XORStorageObject_t();

	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	void writeDwordS(u32 storageIndex, s64 value) override;
};

