#include "stdafx.h"

#include "Common/Types/PhysicalMMU/PhysicalMapped_t.h"

PhysicalMapped_t::PhysicalMapped_t(const u32 physicalAddress) : 
	mPhysicalAddress(physicalAddress),
	mAbsMappedPageIndex(0) 
{
}

const u32 PhysicalMapped_t::getMappedPhysicalAddress() const
{
	return mPhysicalAddress;
}

size_t PhysicalMapped_t::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void PhysicalMapped_t::setAbsMappedPageIndex(const size_t absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
