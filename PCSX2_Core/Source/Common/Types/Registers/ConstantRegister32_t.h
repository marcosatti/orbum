#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register32_t.h"

/*
ConstantRegister32_t is used as a register with a constant value. Any writes are discarded, and any reads are the value set at creation.
By default set to all 0.
*/

class ConstantRegister32_t : public Register32_t
{
public:
	ConstantRegister32_t(const u32 W = 0);

	/*
	Overwritten write functions that discard any value.
	*/
	void writeByte(u32 arrayIndex, u8 value) override;
	void writeHword(u32 arrayIndex, u16 value) override;
	void writeWord(u32 value) override;
};

