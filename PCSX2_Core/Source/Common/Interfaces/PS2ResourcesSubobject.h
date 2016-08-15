#pragma once

#include "Common/Global/Globals.h"

class PS2Resources_t;
class PS2ResourcesSubobject
{
public:
	explicit PS2ResourcesSubobject(const PS2Resources_t *const PS2Resources) :
		mPS2Resources(PS2Resources)
	{
	}

	virtual ~PS2ResourcesSubobject()
	{
	}

	/*
	Returns the root resources object.
	*/
	const PS2Resources_t * getRootResources() const
	{
		return mPS2Resources;
	}

private:
	const PS2Resources_t *const mPS2Resources;
};
