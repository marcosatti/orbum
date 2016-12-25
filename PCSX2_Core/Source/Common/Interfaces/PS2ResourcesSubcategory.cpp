#include "stdafx.h"

#include "Common/Interfaces/PS2ResourcesSubcategory.h"

PS2ResourcesSubcategory::PS2ResourcesSubcategory(const PS2Resources_t* PS2Resources):
	mPS2Resources(PS2Resources)
{
}

PS2ResourcesSubcategory::~PS2ResourcesSubcategory()
{
}

void PS2ResourcesSubcategory::postResourcesInit()
{
}

const PS2Resources_t* PS2ResourcesSubcategory::getRoot() const
{
	return mPS2Resources;
}
