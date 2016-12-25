#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"

/*
A constant memory object, where reads return the constant u64 value (downcasted where appropriate) set at creation and writes do nothing.
For a 128-bit read, the u64 is returned in the lower and upper 64-bits.
Currently used for 'reserved' memory regions (ie: some EE registers) and debugging purposes.
The size parameter in the constructor is used only for Physical MMU mapping purposes.
The parsed size is not allocated (always set to 0 in the underlying Memory_t).
*/
class ConstantMemory_t : public Memory_t
{
public:
	ConstantMemory_t(const size_t & size, const char * mnemonic, const u64 D = 0);
	~ConstantMemory_t();

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
	u128 readQwordU(u32 storageIndex) override;
	void writeQwordU(u32 storageIndex, u128 value) override;

	/*
	Needed by the Physical MMU handler in order to map it. Instead of the normal MappedMemory_t::getSize(), return the size set
	when the object is created.
	*/
	size_t getSize() override;

private:
	const size_t mSize; // Provided for debug only.
	const u64 mConstantValue; // Set at creation, returned in the read function calls.
};

