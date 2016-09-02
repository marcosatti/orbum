#pragma once

#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

/*
A 'dead' storage object, where reads return 0 and writes do nothing.
Currently used for 'reserved' memory regions (ie: some EE registers) and debugging purposes.
*/
class PS2DeadStorageObject_t : public PS2StorageObject_t
{
public:
	PS2DeadStorageObject_t(const size_t & size, const std::string mnemonic, const u32 & PS2PhysicalAddress);
	~PS2DeadStorageObject_t();

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
};

