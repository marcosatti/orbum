#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register8_t.h"

/*
ZeroRegister8_t is used as a register with a constant 0 value. Any writes are discarded, and any reads are always 0.
*/

class ZeroRegister8_t : public Register8_t
{
public:
	/*
	Overwritten write functions that discard any value.
	*/
	void writeByteU(u8 value) override;
	void writeByteS(s8 value) override;
};

