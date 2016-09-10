#include "stdafx.h"

#include "VM/VMMMUHandler/Types/VMMMUMappedStorageObject.h"

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
