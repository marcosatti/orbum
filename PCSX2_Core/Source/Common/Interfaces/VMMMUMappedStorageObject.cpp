#include "stdafx.h"

#include "Common/Interfaces/VMMMUMappedStorageObject.h"

VMMMUMappedStorageObject::VMMMUMappedStorageObject(): mAbsMappedPageIndex(0)
{
}

VMMMUMappedStorageObject::~VMMMUMappedStorageObject()
{
}

u32 VMMMUMappedStorageObject::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void VMMMUMappedStorageObject::setAbsMappedPageIndex(u32 absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
