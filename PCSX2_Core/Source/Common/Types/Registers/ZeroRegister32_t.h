#pragma once
#include "Common/Types/Registers/Register32_t.h"

/*
ZeroRegister32_t is used as a register with a constant 0 value. Any writes are discarded, and any reads are always 0.
*/

class ZeroRegister32_t : public Register32_t
{
public:
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

