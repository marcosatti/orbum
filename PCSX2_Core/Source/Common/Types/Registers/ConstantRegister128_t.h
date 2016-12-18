#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register128_t.h"

/*
ConstantRegister128_t is used as a register with a constant value. Any writes are discarded, and any reads are the value set at creation.
By default set to all 0.
*/

class ConstantRegister128_t : public Register128_t
{
public:
	ConstantRegister128_t(const u64 D0 = 0, const u64 D1 = 0);

	/*
	Overwritten write functions that discard any value.
	*/
	void writeByteU(u32 arrayIndex, u8 value) override;
	void writeByteS(u32 arrayIndex, s8 value) override;
	void writeHwordU(u32 arrayIndex, u16 value) override;
	void writeHwordS(u32 arrayIndex, s16 value) override;
	void writeWordU(u32 arrayIndex, u32 value) override;
	void writeWordS(u32 arrayIndex, s32 value) override;
	void writeDwordU(u32 arrayIndex, u64 value) override;
	void writeDwordS(u32 arrayIndex, s64 value) override;
	void writeQwordU(u128 value) override;
};

