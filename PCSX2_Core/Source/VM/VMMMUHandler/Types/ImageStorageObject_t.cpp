#include "stdafx.h"

#include "VM/VMMMUHandler/Types/ImageStorageObject_t.h"
#include "VM/VMMMUHandler/VMMMUHandler.h"

ImageStorageObject_t::ImageStorageObject_t(const char* const mnemonic, const u32 & PS2PhysicalAddress, const size_t& imageSize, const size_t & size, const u32 & imagePS2PhysicalAddress, std::shared_ptr<VMMMUHandler> vmMMUHandler) :
	StorageObject_t(0, mnemonic, PS2PhysicalAddress),
	mImageSize(imageSize),
	mTotalSize(size),
	mImagePS2PhysicalAddress(imagePS2PhysicalAddress),
	mVMMMUHandler(vmMMUHandler)
{
}

ImageStorageObject_t::~ImageStorageObject_t()
{
}

u8 ImageStorageObject_t::readByteU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readByteU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeByteU(u32 storageIndex, u8 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeByteU(mImagePS2PhysicalAddress + storageIndex, value);
}

s8 ImageStorageObject_t::readByteS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readByteS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeByteS(u32 storageIndex, s8 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeByteS(mImagePS2PhysicalAddress + storageIndex, value);
}

u16 ImageStorageObject_t::readHwordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readHwordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeHwordU(u32 storageIndex, u16 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeHwordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s16 ImageStorageObject_t::readHwordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readHwordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeHwordS(u32 storageIndex, s16 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeHwordS(mImagePS2PhysicalAddress + storageIndex, value);
}

u32 ImageStorageObject_t::readWordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readWordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeWordU(u32 storageIndex, u32 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeWordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s32 ImageStorageObject_t::readWordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readWordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeWordS(u32 storageIndex, s32 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeWordS(mImagePS2PhysicalAddress + storageIndex, value);
}

u64 ImageStorageObject_t::readDwordU(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readDwordU(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeDwordU(u32 storageIndex, u64 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeDwordU(mImagePS2PhysicalAddress + storageIndex, value);
}

s64 ImageStorageObject_t::readDwordS(u32 storageIndex)
{
	if (storageIndex < mImageSize)
		return mVMMMUHandler->readDwordS(mImagePS2PhysicalAddress + storageIndex);
	else
		return 0;
}

void ImageStorageObject_t::writeDwordS(u32 storageIndex, s64 value)
{
	if (storageIndex < mImageSize)
		mVMMMUHandler->writeDwordS(mImagePS2PhysicalAddress + storageIndex, value);
}

size_t ImageStorageObject_t::getStorageSize()
{
	return mTotalSize;
}
