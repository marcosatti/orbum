#pragma once

#include <string>

#include "Common/Global/Globals.h"

#include "VM/VMMMUHandler/Types/VMMMUMappedMemory.h"

/*
A simple storage object which is constructed to the size specified, and optional name (mnemonic) which is used for debugging/logging.
Also defines a PS2 Physical address that it starts from - used by the VM MMU to map for address translation.

The primary difference between a MappedMemory type and a Register type is that storage objects are accessed by the byte index, not by the size index.
For example, a writeWordU(0, value) will write to the first 0-31 bits, while writeWordU(1, value) will write to bits 8-39 (ie: it will overwrite).
See the Register type for the counter-example.
*/
class MappedMemory_t : public VMMMUMappedMemory
{
public:
	explicit MappedMemory_t(const size_t & size, const char *const mnemonic, const u32 & PS2PhysicalAddress);
	virtual ~MappedMemory_t();

	/*
	Read or write a value of a given type, to the specified byte index (storageIndex).
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

	/*
	Gets the storage length, needed by the VM MMU handler in order to map it.
	*/
	size_t getStorageSize() override;

	/*
	Gets the base client memory address, needed for special VM functions such as loading the BIOS (BootROM). Not normally used, and should never
	 be used in favour of the above read/write functions unless you absolutely have to.
	*/
	virtual void * getClientMemoryAddress() const;

	/*
	Get the storage mnemonic, used for debug.
	*/
	const char * getMnemonic() const override;

	/*
	Gets the PS2 physical address this storage object was assigned at creation.
	*/
	virtual const u32 & getPS2PhysicalAddress() const;

private:
	size_t mStorageSize;
	u8 *const mStorage;
	const std::string mMnemonic;
	const u32 mPS2PhysicalAddress;
};

