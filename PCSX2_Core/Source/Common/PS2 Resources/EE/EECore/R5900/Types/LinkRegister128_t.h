#pragma once

#include  "Common/Global/Globals.h"

#include "Common/Types/Registers/Register128_t.h"
#include "Common/PS2 Resources/EE/EECore/R5900/Types/R5900ResourcesSubobject.h"


class LinkRegister128_t : public Register128_t, public R5900ResourcesSubobject
{
public:
	explicit LinkRegister128_t(const PS2Resources_t* const PS2Resources)
		: R5900ResourcesSubobject(PS2Resources)
	{
	}

	/*
	Sets the return (link) address, which is equal to the current PC + 8.
	*/
	void setLinkAddress();
};

