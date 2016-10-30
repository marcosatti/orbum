#include "stdafx.h"

#include "Common/Interfaces/PhysicalMapped.h"

PhysicalMapped::PhysicalMapped() : 
	mAbsMappedPageIndex(0) 
{
}

PhysicalMapped::~PhysicalMapped()
{
}

u32 PhysicalMapped::getAbsMappedPageIndex() const
{
	return mAbsMappedPageIndex;
}

void PhysicalMapped::setAbsMappedPageIndex(u32 absPageIndex)
{
	mAbsMappedPageIndex = absPageIndex;
}
