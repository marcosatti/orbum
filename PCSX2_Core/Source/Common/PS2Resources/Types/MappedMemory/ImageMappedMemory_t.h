#pragma once

#include <memory>

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"

class PhysicalMMU_t;

/*
ImageMappedMemory_t is used to mirror/image other regions of the PS2 physical memory space. 
It should only be used internally by the VM, as it does not represent any PS2 physical memory, but rather only redirects
 by another call to the Physical MMU - ie: use this in the function body where memory mappings are done 
 (in this case,  VMMain::initalisePS2PhysicalMemoryMap() ).

imageSize parsed in the constructor represents the mirror region size - it is not allocated in memory (underlying MappedMemory_t 
 gets 0 as the size parameter).
totalSize parsed in the constructor represents the whole memory region size - any attempt the area after the imageSize (and < totalSize),
 will behave as a dead storage.
imagePS2PhysicalAddress is the base physical address that the region provides an image from.
*/
class ImageMappedMemory_t : public MappedMemory_t
{
public:
	ImageMappedMemory_t(const char *const mnemonic, const u32 & PS2PhysicalAddress, const size_t & imageSize, const size_t & totalSize, const u32 & imagePS2PhysicalAddress, std::shared_ptr<PhysicalMMU_t> physicalMMU);
	~ImageMappedMemory_t();

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
	Needed by the Physical MMU handler in order to map it. Instead of the normal MappedMemory_t::getMappedSize(), return the total size set 
	 when the object is created.
	*/
	size_t getMappedSize() override;

private:
	const size_t mImageSize;
	const size_t mTotalSize;
	const u32 mImagePS2PhysicalAddress;
	const std::shared_ptr<PhysicalMMU_t> mPhysicalMMU;
};

