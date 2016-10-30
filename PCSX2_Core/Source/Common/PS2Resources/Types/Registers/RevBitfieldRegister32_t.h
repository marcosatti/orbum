#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

/*
RevBitfieldRegister32_t provides "reverse bits by writing 1" functionality.
Using the bitfield functions act normally.
*/
class RevBitfieldRegister32_t : public BitfieldRegister32_t
{
public:
	explicit RevBitfieldRegister32_t();
	virtual ~RevBitfieldRegister32_t();

	/*
	Before commiting the value, XOR's the old value with new value, which reverses any bits that 1 is written to.
	*/
	void writeWordU(u32 value) override;
};

