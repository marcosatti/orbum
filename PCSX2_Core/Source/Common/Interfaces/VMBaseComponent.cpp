#include "stdafx.h"

#include "Common/Interfaces/VMBaseComponent.h"
#include "VM/VMMain.h"

VMBaseComponent::VMBaseComponent(VMMain * vmMain) : 
	mVMMain(vmMain),
	mPS2Resources(vmMain->getResources())
{
}

VMBaseComponent::~VMBaseComponent()
{
}