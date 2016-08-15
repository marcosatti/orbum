#pragma once

#include "Common/Interfaces/PS2ResourcesSubobject.h"


class COP1ResourcesSubobject : public PS2ResourcesSubobject
{
public:
	explicit COP1ResourcesSubobject(const PS2Resources_t* const PS2Resources);

	/*
	Checks if the COP1 is usable by checking the Status.CU[1] bit. Will throw PS2Exception_t coprocessor unavailable if not usable.
	*/
	void checkCOP1Usable() const;
};
