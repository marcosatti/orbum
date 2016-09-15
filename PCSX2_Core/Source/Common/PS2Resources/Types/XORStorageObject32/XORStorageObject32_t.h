#pragma once

#include "Common/PS2Resources/Types/StorageObject/StorageObject32_t.h"

/*
XORStorageObject_t is a toggle storage object - each write toggles the stored bits with the set bits from the parsed value (XOR'd).
For an example of its use, see the INTC: I_MASK register on page 31 of the EE Users Manual.

Within the PS2, it is only used in 32-bit registers.
*/

class XORStorageObject32_t : public StorageObject32_t
{
public:
	XORStorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	~XORStorageObject32_t();

	void writeByteU(u32 storageIndex, u8 value) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	void writeDwordS(u32 storageIndex, s64 value) override;
};

