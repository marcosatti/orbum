#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"


class COP0ResourcesSubobject : public PS2ResourcesSubobject
{
public:
	explicit COP0ResourcesSubobject(const PS2Resources_t* const PS2Resources);

	/*
	Checks if the COP1 is usable by checking the Status.CU[1] bit or for kernel mode. Will throw PS2Exception_t coprocessor unavailable if not usable.
	*/
	void checkCOP0Usable() const;
};
