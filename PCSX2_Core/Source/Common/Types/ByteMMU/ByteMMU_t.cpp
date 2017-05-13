#include "stdafx.h"

#include <memory>
#include <stdexcept>
#include <cmath>

#include "Common/Global/Globals.h"

#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperBaseObjectByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperByteMemoryByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister8ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister16ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister32ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister64ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperRegister128ByteMMU_t.h"
#include "Common/Types/ByteMMU/MapperFIFOQueueByteMMU_t.h"

ByteMMU_t::ByteMMU_t(const int numAddressBits, const int numPageIndexBits, const int numOffsetIndexBits) :
	mNumAddressBits(numAddressBits),
	mNumPageIndexBits(numPageIndexBits),
	mNumOffsetIndexBits(numOffsetIndexBits)
{
	// Check the paramters are valid for a u32 space, and calculate number of directory bits.
	mNumDirectoryIndexBits = mNumAddressBits - (mNumPageIndexBits + mNumOffsetIndexBits);
	if (mNumDirectoryIndexBits < 0)
		throw std::runtime_error("ByteMMU_t initialised with invalid parameters.");
	
	// Calculate directory, page and offset entries (for offset, this is the same thing as a page size in bytes).
	mNumDirectories = (static_cast<size_t>(1) << mNumDirectoryIndexBits);
	mNumPagesPerDirectory = (static_cast<size_t>(1) << mNumPageIndexBits);
	mNumOffsetsPerPage = (static_cast<size_t>(1) << mNumOffsetIndexBits);

	// Calculate mask parameters.
	mDirectoryIndexMask = (static_cast<u32>(mNumDirectories) - 1);
	mPageIndexMask = (static_cast<u32>(mNumPagesPerDirectory) - 1);
	mOffsetIndexMask = static_cast<u32>(mNumOffsetsPerPage) - 1;

	// Allocate base directories.
	mPageTable.resize(mNumDirectories);
}

void ByteMMU_t::mapObject(const std::shared_ptr<MapperBaseObjectByteMMU_t> & mapperObject)
{
	// Get the physical address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(mapperObject->getMappedPhysicalAddress());

	// Throw error if the address is not aligned to a page boundary - a single page can only point to one object, not multiple.
	if (properties.mOffset != 0)
		throw std::runtime_error("Mapping was not aligned to a page boundary - not supported!");

	// Throw error if the mapped address falls outside of the allowable range.
	if (properties.mVDN >= mNumDirectories)
		throw std::runtime_error("Mapping was outside of the allowable address range.");

	// Iterate through the MMU directories and pages to map the object. 
	// Start at the the VDN and VPN from the VAddress properties above.
	// If the size end is not aligned to a page boundary, end the mapping with an additional page (force it to be aligned).
	size_t mapSizeBytesRemaining = ((mapperObject->getSize() + mNumOffsetsPerPage - 1) / mNumOffsetsPerPage) * mNumOffsetsPerPage;
	size_t directoryIndex = properties.mVDN;
	size_t pageIndex = properties.mVPN;
	while (mapSizeBytesRemaining > 0)
	{
		// Allocate pages within directory if needed.
		mPageTable[directoryIndex].resize(mNumPagesPerDirectory);

		// Map object entry.
		while (pageIndex < mNumPagesPerDirectory && mapSizeBytesRemaining > 0)
		{
			auto& mappedObject = mPageTable[directoryIndex][pageIndex];

			// Check for existing map - this is bad!
			if (mappedObject != nullptr)
				throw std::runtime_error("Error: there was an existing map in the MMU.");

			mappedObject = mapperObject;
			pageIndex++;
			mapSizeBytesRemaining -= mNumOffsetsPerPage;
		}		

		// Move to next directory.
		pageIndex = 0;
		directoryIndex++;
	}
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<ByteMemory_t>& memory)
{
	mapObject(std::make_shared<MapperByteMemoryByteMMU_t>(physicalAddress, memory));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register8_t>& register8)
{
	mapObject(std::make_shared<MapperRegister8ByteMMU_t>(physicalAddress, register8));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register16_t>& register16)
{
	mapObject(std::make_shared<MapperRegister16ByteMMU_t>(physicalAddress, register16));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register32_t>& register32)
{
	mapObject(std::make_shared<MapperRegister32ByteMMU_t>(physicalAddress, register32));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register64_t>& register64)
{
	mapObject(std::make_shared<MapperRegister64ByteMMU_t>(physicalAddress, register64));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<Register128_t>& register128)
{
	mapObject(std::make_shared<MapperRegister128ByteMMU_t>(physicalAddress, register128));
}

void ByteMMU_t::mapObject(const u32 physicalAddress, const std::shared_ptr<FIFOQueue_t>& fifoQueue)
{
	mapObject(std::make_shared<MapperFIFOQueueByteMMU_t>(physicalAddress, fifoQueue));
}

ByteMMU_t::VAddressProperties_t ByteMMU_t::getVAddressProperties(u32 address) const
{
	return
	{
		/* VDN    */ (address >> (mNumOffsetIndexBits + mNumPageIndexBits)) & mDirectoryIndexMask,
		/* VPN    */ (address >> mNumOffsetIndexBits) & mPageIndexMask,
		/* Offset */ address & mOffsetIndexMask
	};
}

u8 ByteMMU_t::readByte(const System_t context, const u32 physicalAddress)
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the read on the storage object at the specified index.
	return mappedObject->readByte(context, objectIndex);
}

void ByteMMU_t::writeByte(const System_t context, const u32 physicalAddress, const u8 value)
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the write on the storage object at the specified index.
	mappedObject->writeByte(context, objectIndex, value);
}

u16 ByteMMU_t::readHword(const System_t context, const u32 physicalAddress) 
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the read on the storage object at the specified index.
	return mappedObject->readHword(context, objectIndex);
}

void ByteMMU_t::writeHword(const System_t context, const u32 physicalAddress, const u16 value) 
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the write on the storage object at the specified index.
	mappedObject->writeHword(context, objectIndex, value);
}

u32 ByteMMU_t::readWord(const System_t context, const u32 physicalAddress) 
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the read on the storage object at the specified index.
	return mappedObject->readWord(context, objectIndex);
}

void ByteMMU_t::writeWord(const System_t context, const u32 physicalAddress, const u32 value) 
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the write on the storage object at the specified index.
	mappedObject->writeWord(context, objectIndex, value);
}

u64 ByteMMU_t::readDword(const System_t context, const u32 physicalAddress)
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the read on the storage object at the specified index.
	return mappedObject->readDword(context, objectIndex);
}

void ByteMMU_t::writeDword(const System_t context, const u32 physicalAddress, const u64 value)
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the write on the storage object at the specified index.
	mappedObject->writeDword(context, objectIndex, value);
}

u128 ByteMMU_t::readQword(const System_t context, const u32 physicalAddress) 
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the read on the storage object at the specified index.
	return mappedObject->readQword(context, objectIndex);
}

void ByteMMU_t::writeQword(const System_t context, const u32 physicalAddress, const u128 value)
{
	// Get the virtual address properties, including VDN, VPN and offset.
	auto properties = getVAddressProperties(physicalAddress);

	// Get host storage object and calculate the object index to access.
	const std::shared_ptr<MapperBaseObjectByteMMU_t> & mappedObject = mPageTable[properties.mVDN][properties.mVPN];
	const size_t objectIndex = physicalAddress - mappedObject->getMappedPhysicalAddress();

	// Perform the write on the storage object at the specified index.
	mappedObject->writeQword(context, objectIndex, value);
}
