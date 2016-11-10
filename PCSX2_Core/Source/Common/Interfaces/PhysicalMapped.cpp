#include "stdafx.h"

#include "Common/Interfaces/PhysicalMapped.h"

PhysicalMapped::PhysicalMapped(const u32 & physicalAddress) : 
	mPhysicalAddress(physicalAddress),
	mAbsMappedPageIndex(0) 
{
}

PhysicalMapped::~PhysicalMapped()
{
}

const u32& PhysicalMapped::getMappedPhysicalAddress() const
{
	return mPhysicalAddress;
}

u32 PhysicalMapped::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void PhysicalMapped::setAbsMappedPageIndex(u32 absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
