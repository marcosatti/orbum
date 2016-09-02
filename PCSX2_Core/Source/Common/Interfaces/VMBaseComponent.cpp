#include "stdafx.h"

#include "Common/Interfaces/VMBaseComponent.h"

VMBaseComponent::VMBaseComponent(const VMMain* const vmMain): mVMMain(vmMain)
{
}

VMBaseComponent::~VMBaseComponent()
{
}

const VMMain *const & VMBaseComponent::getVM() const
{
	return mVMMain;
}
