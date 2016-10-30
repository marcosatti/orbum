#pragma once

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/Types/Registers/BitfieldRegister32_t.h"

/*
ClrBitfieldRegister32_t provides "clear bits by writing 1" functionality.
Using the bitfield functions act normally.
*/
class ClrBitfieldRegister32_t : public BitfieldRegister32_t
{
public:
	explicit ClrBitfieldRegister32_t();
	virtual ~ClrBitfieldRegister32_t();

	/*
	Before commiting the value, AND's the old value with ~(new value), which clears any bits that 1 is written to.
	*/
	void writeWordU(u32 value) override;
};

