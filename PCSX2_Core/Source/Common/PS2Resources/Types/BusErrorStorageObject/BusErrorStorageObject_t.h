#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/StorageObject/StorageObject_t.h"

/*
A 'Bus error' storage object, which will generate an exception on access.
The size parameter in the constructor is used only for VM MMU mapping purposes.
The parsed size is not allocated (always set to 0 in the underlying StorageObject_t).
TODO: Currently throws a runtime_error, need to implement the ps2 exception.
*/
class BusErrorStorageObject_t : public StorageObject_t
{
public:
	BusErrorStorageObject_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	~BusErrorStorageObject_t();

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

	/*
	Needed by the VM MMU handler in order to map it. Instead of the normal StorageObject_t::getStorageSize(), return the size set
	when the object is created.
	*/
	size_t getStorageSize() override;

private:
	size_t mSize; 
};

