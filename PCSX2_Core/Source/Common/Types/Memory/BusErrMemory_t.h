#pragma once

#include "Common/Global/Globals.h"

#include "Common/Types/Memory/Memory_t.h"

/*
A 'Bus error' storage object, which will generate an exception on access.
The size parameter in the constructor is used only for Physical MMU mapping purposes.
The parsed size is not allocated (always set to 0 in the underlying MappedMemory_t).
TODO: Currently throws a runtime_error, need to implement the ps2 exception.
*/
class BusErrMemory_t : public Memory_t
{
public:
	BusErrMemory_t(const size_t & size, const char * mnemonic);
	~BusErrMemory_t();

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
	size_t mSize; 
};

