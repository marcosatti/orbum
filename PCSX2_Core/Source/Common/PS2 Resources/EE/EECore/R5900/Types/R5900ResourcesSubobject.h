#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"

class R5900ResourcesSubobject : public PS2ResourcesSubobject
{
public:
	explicit R5900ResourcesSubobject(const PS2Resources_t* const PS2Resources) :
		PS2ResourcesSubobject(PS2Resources)
	{
	}
};
