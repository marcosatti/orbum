#pragma once

#include  "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/Registers/Register128_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"


class LinkRegister128_t : public Register128_t, public PS2ResourcesSubobject
{
public:
	explicit LinkRegister128_t(const PS2Resources_t* const PS2Resources)
		: PS2ResourcesSubobject(PS2Resources)
	{
	}

	/*
	Sets the return (link) address, which is equal to the current PC + 8.
	*/
	void setLinkAddress();
};

