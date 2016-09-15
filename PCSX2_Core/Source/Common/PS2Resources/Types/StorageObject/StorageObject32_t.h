#pragma once

#include <string>

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"

/*
A 32-bit storage object (StorageObject_t::mSize = 4), which may only be accessed when storageIndex = 0.
This is provided to mimic the PS2 alginment conditions, for example, with the EE registers defined in the EE Users Manual.
*/
class StorageObject32_t : public StorageObject_t
{
public:
	explicit StorageObject32_t(const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~StorageObject32_t();

	/*
	Read or write a 32-bit value, where storageIndex must be 0 (only the functions [read/write]Word[U/S](0) are allowed to be called). 
	All other combinations throw a runtime error.
	*/
	u8 readByteU(u32 storageIndex) override;
	void writeByteU(u32 storageIndex, u8 value) override;
	s8 readByteS(u32 storageIndex) override;
	void writeByteS(u32 storageIndex, s8 value) override;
	u16 readHwordU(u32 storageIndex) override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	s16 readHwordS(u32 storageIndex) override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	u32 readWordU(u32 storageIndex) override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) override;
	void writeWordS(u32 storageIndex, s32 value) override;
	u64 readDwordU(u32 storageIndex) override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	s64 readDwordS(u32 storageIndex) override;
	void writeDwordS(u32 storageIndex, s64 value) override;

private:
};

