#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Registers/Register16_t.h"

/*
ZeroRegister16_t is used as a register with a constant 0 value. Any writes are discarded, and any reads are always 0.
*/

class ZeroRegister16_t : public Register16_t
{
public:
	/*
	Overwritten write functions that discard any value.
	*/
	void writeByteU(u32 arrayIndex, u8 value) override;
	void writeByteS(u32 arrayIndex, s8 value) override;
	void writeHwordU(u16 value) override;
	void writeHwordS(s16 value) override;
};

