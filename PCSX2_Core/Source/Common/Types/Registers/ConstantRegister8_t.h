#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register8_t.h"

/*
ConstantRegister8_t is used as a register with a constant value. Any writes are discarded, and any reads are the value set at creation.
By default set to all 0.
*/
class ConstantRegister8_t : public Register8_t
{
public:
	ConstantRegister8_t(const u8 B = 0);
	
	/*
	Overwritten write functions that discard any value.
	*/
	void writeByte(u8 value) override;
};

