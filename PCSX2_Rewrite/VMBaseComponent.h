#pragma once

#include "Globals.h"

/*
I apologise for the awful looking const syntax - it is valid c++ however and I can't see a better way to declare it.
Basically what it means is, any component that extends this class is not allowed to point anywhere else or modify the VMMain object the pointer references.
*/

class VMMain;
class VMBaseComponent
{
public:
	explicit VMBaseComponent(const VMMain *const vmMain) : _vmMain(vmMain)
	{
	}

	virtual ~VMBaseComponent()
	{
	}

	INLINE const VMMain *const &getVM() const
	{
		return _vmMain;
	}

private:
	/*
	VMMain pointer in order to callback, grab resources etc.
	Using a raw pointer here is ok, as VMMain will be the one creating any objects that are subclassed from VMBaseComponent.
	Ie: VMMain will not be destroyed before any VM component will be, so in theory the pointer will always be valid.
	*/
	const VMMain *const _vmMain;
};
