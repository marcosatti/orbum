#pragma once

#include <string>

#include "Common/Global/Globals.h"

#include "Common/Interfaces/VMMMUMappedStorageObject.h"

/*
A simple storage object which is constructed to the size specified, and optional name (mnemonic) which is used for debugging/logging.
*/
class StorageObject_t : public VMMMUMappedStorageObject
{
public:
	explicit StorageObject_t(const size_t & size, const std::string mnemonic);
	virtual ~StorageObject_t();

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
	Gets the storage length, needed by the VM MMU handler in order to map it.
	*/
	size_t getStorageSize() override;

	/*
	Gets the base client memory address, needed for special VM functions such as loading the BIOS (BootROM). Not normally used, and should never
	 be used in favour of the above read/write functions unless you absolutely have to.
	*/
	void * getClientMemoryAddress() const;

private:
	size_t mStorageSize;
	u8 *const mStorage;
	const std::string mMnemonic;
};

