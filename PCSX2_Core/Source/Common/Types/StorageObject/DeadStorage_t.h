#pragma once

#include "Common/Types/StorageObject/StorageObject_t.h"

/*
A 'dead' storage object, where reads return 0 and writes do nothing.
Currently used for 'reserved' memory regions (ie: some EE registers) and debugging purposes.
*/
class DeadStorage_t : public StorageObject_t
{
public:
	DeadStorage_t(const size_t & size, const std::string mnemonic);
	~DeadStorage_t();

	u8 readByteU(u32 storageIndex) const override;
	void writeByteU(u32 storageIndex, u8 value) override;
	s8 readByteS(u32 storageIndex) const override;
	void writeByteS(u32 storageIndex, s8 value) override;
	u16 readHwordU(u32 storageIndex) const override;
	void writeHwordU(u32 storageIndex, u16 value) override;
	s16 readHwordS(u32 storageIndex) const override;
	void writeHwordS(u32 storageIndex, s16 value) override;
	u32 readWordU(u32 storageIndex) const override;
	void writeWordU(u32 storageIndex, u32 value) override;
	s32 readWordS(u32 storageIndex) const override;
	void writeWordS(u32 storageIndex, s32 value) override;
	u64 readDwordU(u32 storageIndex) const override;
	void writeDwordU(u32 storageIndex, u64 value) override;
	s64 readDwordS(u32 storageIndex) const override;
	void writeDwordS(u32 storageIndex, s64 value) override;
};

