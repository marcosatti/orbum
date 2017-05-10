#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register16_t.h"
#include <memory>

/*
A (low) 16-bit register to be used as part of a "pair" with another Register16_t (high) to make a hybrid 32-bit register.
This is essentially a wrapper class that provides ways to read and write 32-bit values (similar a "word", disregarding the PS2 context), taking care of the splitting.

Usage example:
// Create objects.
std::shared_ptr<Register16_t> mHighRegister;
std::shared_ptr<PairRegister16_t> mLowRegister;

// Use only the low register to manipulate a 32-bit value or inc/decrement. 
// Any changes directly to the high register will be reflected in the functions defined.
mLowRegister->writeWord(getContext(), 0x1234ABCD);
u16 highValue = mHighRegister->readHword(getContext()); // Equal to 0x1234.
u16 lowValue = mLowRegister->readHword(getContext()); // Equal to 0xABCD.
*/
class PairRegister16_t : public Register16_t
{
public:
	PairRegister16_t(const char* mnemonic, bool debugReads, bool debugWrites, const std::shared_ptr<Register16_t> & highRegister16);

	/*
	Read or write a 32-bit value, which is automatically combined/split across the two 16-bit registers.
	*/
	virtual u32 readWord(const System_t context);
	virtual void writeWord(const System_t context, u32 value);

private:
	/*
	Reference to the high 16-bit register of the pair.
	*/
	std::shared_ptr<Register16_t> mHighRegister16;
};