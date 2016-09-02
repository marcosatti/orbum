#pragma once

class VMMain;

class VMBaseComponent
{
public:
	explicit VMBaseComponent(const VMMain *const vmMain);

	virtual ~VMBaseComponent();

	const VMMain *const & getVM() const;

private:
	/*
	VMMain pointer in order to callback, grab resources etc.
	Using a raw pointer here is ok, as VMMain will be the one creating any objects that are subclassed from VMBaseComponent.
	Ie: VMMain will not be destroyed before any VM component will be, so in theory the pointer will always be valid.
	*/
	const VMMain *const mVMMain;
};
