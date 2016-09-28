#include "stdafx.h"

#include "VM/VMMMUHandler/Types/ImageMappedMemory_t.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"

ImageMappedMemory_t::ImageMappedMemory_t(const char* const mnemonic, const u32 & PS2PhysicalAddress, const size_t& imageSize, const size_t & size, const u32 & imagePS2PhysicalAddress, std::shared_ptr<VMMMUHandler> vmMMUHandler) :
	MappedMemory_t(0, mnemonic, PS2PhysicalAddress),
	mImageSize(imageSize),
	mTotalSize(size),
	mImagePS2PhysicalAddress(imagePS2PhysicalAddress),
	mVMMMUHandler(vmMMUHandler)
{
}

ImageMappedMemory_t::~ImageMappedMemory_t()
{
}

u8 ImageMappedMemory_t::readByteU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readByteU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeByteU(mImagePS2PhysicalAddress + storageIndex, value);
}

s8 ImageMappedMemory_t::readByteS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readByteS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeByteS(mImagePS2PhysicalAddress + storageIndex, value);
}

u16 ImageMappedMemory_t::readHwordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readHwordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeHwordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s16 ImageMappedMemory_t::readHwordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readHwordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeHwordS(mImagePS2PhysicalAddress + storageIndex, value);
}

u32 ImageMappedMemory_t::readWordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readWordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeWordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s32 ImageMappedMemory_t::readWordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readWordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeWordS(mImagePS2PhysicalAddress + storageIndex, value);
}

u64 ImageMappedMemory_t::readDwordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readDwordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeDwordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s64 ImageMappedMemory_t::readDwordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readDwordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageMappedMemory_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeDwordS(mImagePS2PhysicalAddress + storageIndex, value);
}

size_t ImageMappedMemory_t::getStorageSize()
{
	return mTotalSize;
}
