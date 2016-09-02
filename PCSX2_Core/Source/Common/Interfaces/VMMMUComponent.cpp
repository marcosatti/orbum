#include "stdafx.h"

#include "Common/Interfaces/VMMMUComponent.h"
#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

VMMMUComponent::VMMMUComponent(const VMMain* const vmMain): VMBaseComponent(vmMain)
{
}

void VMMMUComponent::mapMemory(const std::shared_ptr<PS2StorageObject_t>& clientStorage)
{
	mapMemory(clientStorage, clientStorage->getPS2PhysicalAddress());
}
