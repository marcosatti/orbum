#include "stdafx.h"

#include "VM/VMMMUHandler/Types/VMMMUMappedMemory.h"

VMMMUMappedMemory::VMMMUMappedMemory(): mAbsMappedPageIndex(0)
{
}

VMMMUMappedMemory::~VMMMUMappedMemory()
{
}

u32 VMMMUMappedMemory::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void VMMMUMappedMemory::setAbsMappedPageIndex(u32 absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
