#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

/*
A register class that is meant to be used as a boolean toggle (with value non-zero or 0).
Whenever the register field is read from using getToggle(), the register is cleared to 0.
To set the register, use setToggle()
*/
class ToggleRegister32_t : public Register32_t
{
public:

	/*
	Get and set the register toggle status.
	*/
	void setToggle();
	bool getToggle();
};
