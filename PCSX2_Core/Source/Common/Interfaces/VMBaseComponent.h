#pragma once

#include <memory>

/*
Base component interface used by any system that needs access to the emulator state.
*/

class PS2Resources_t;
class VMMain;

class VMBaseComponent
{
public:
	explicit VMBaseComponent(VMMain * vmMain);
	virtual ~VMBaseComponent();

	/*
	Returns the PS2 Resources state object hierarchy (convenience function).
	*/
	inline const std::shared_ptr<PS2Resources_t> & getResources() const;

	/*
	Returns the VM instance that created this object.
	May be used to set the runtime status, VM options, etc.
	*/
	inline VMMain * getVM() const;

private:
	/*
	VMMain pointer in order to callback, grab resources etc.
	Using a raw pointer here is ok, as VMMain will be the one creating any objects that are subclassed from VMBaseComponent.
	Ie: VMMain will not be destroyed before any VM component will be, so in theory the pointer will always be valid.
	*/
	VMMain * mVMMain;

	/*
	Pointer to the PS2 Resources object hierarchy. Initalised from the VM.
	*/
	const std::shared_ptr<PS2Resources_t> mPS2Resources;
};

const std::shared_ptr<PS2Resources_t> & VMBaseComponent::getResources() const
{
	return mPS2Resources;
}

VMMain * VMBaseComponent::getVM() const
{
	return mVMMain;
}