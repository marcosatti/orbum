#include "stdafx.h"

#include "Common/Types/ByteMMU/MapperBaseObjectByteMMU_t.h"

MapperBaseObjectByteMMU_t::MapperBaseObjectByteMMU_t(const u32 physicalAddress) : 
	mMappedPhysicalAddress(physicalAddress)
{
}

const u32 MapperBaseObjectByteMMU_t::getMappedPhysicalAddress() const
{
	return mMappedPhysicalAddress;
}