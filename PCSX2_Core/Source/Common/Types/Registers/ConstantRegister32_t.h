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
	void writeByteU(u32 arrayIndex, u8 value) override;
	void writeByteS(u32 arrayIndex, s8 value) override;
	void writeHwordU(u32 arrayIndex, u16 value) override;
	void writeHwordS(u32 arrayIndex, s16 value) override;
	void writeWordU(u32 value) override;
	void writeWordS(s32 value) override;
};

