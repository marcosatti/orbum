#include "stdafx.h"

#include "Common/Interfaces/VMBaseComponent.h"

VMBaseComponent::VMBaseComponent(VMMain * vmMain) : 
	mVMMain(vmMain)
{
}

VMBaseComponent::~VMBaseComponent()
{
}

VMMain * VMBaseComponent::getVM() const
{
	return mVMMain;
}
