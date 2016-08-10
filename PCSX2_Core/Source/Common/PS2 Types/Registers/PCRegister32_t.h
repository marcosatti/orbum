#pragma once

#include  "Common/Global/Globals.h"

#include "Common/PS2 Types/Registers/Register32_t.h"

class PCRegister32_t : public Register32_t
{
public:

	/*
	Returns the current PC value.
	*/
	u32 getPCValue();

	/*
	Set the PC to a relative value.
	*/
	void setPCValueRelative(const s32& relativeLocation);

	/*
	Set the PC to an absolute value.
	*/
	void setPCValueAbsolute(const u32& absoluteLocation);

	/*
	Increments the PC by 4.
	*/
	void setPCValueNext();
};

