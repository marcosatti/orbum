#include "stdafx.h"

#include "Common/Types/ByteMMU/MapperBaseObjectByteMMU_t.h"

MapperBaseObjectByteMMU_t::MapperBaseObjectByteMMU_t(const u32 physicalAddress) : 
	mPhysicalAddress(physicalAddress),
	mAbsMappedPageIndex(0) 
{
}

const u32 MapperBaseObjectByteMMU_t::getMappedPhysicalAddress() const
{
	return mPhysicalAddress;
}

size_t MapperBaseObjectByteMMU_t::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void MapperBaseObjectByteMMU_t::setAbsMappedPageIndex(const size_t absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
