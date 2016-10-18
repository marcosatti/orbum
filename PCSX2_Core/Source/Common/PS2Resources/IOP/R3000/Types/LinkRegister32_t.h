#pragma once

#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/Interfaces/PS2ResourcesSubobject.h"


class LinkRegister32_t : public Register32_t, public PS2ResourcesSubobject
{
public:
	explicit LinkRegister32_t(const PS2Resources_t* const PS2Resources);

	/*
	Sets the return (link) address, which is equal to the current PC + 8.
	*/
	void setLinkAddress();
};

