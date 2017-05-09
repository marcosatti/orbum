#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register16_t.h"
#include <memory>

/*
A (low) 16-bit register to be used as part of a "pair" with another Register16_t (high) to make a hybrid 32-bit register.
This is essentially a wrapper class that provides ways to:
 1. Increment/decrement with overflow into the high register.
 2. Read and write 32-bit values (similar a "word", disregarding the PS2 context), taking care of the splitting.

Usage example:
// Create objects.
std::shared_ptr<Register16_t> mHighRegister;
std::shared_ptr<PairRegister16_t> mLowRegister;

// Use low register to manipulate a 32-bit value or inc/decrement.
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

	/*
	Increment or decrement the register pair, which automatically takes care of over or underflow.
	*/
	virtual void increment(const u32 count);
	virtual void decrement(const u32 count);

private:
	/*
	Reference to the high 16-bit register of the pair.
	*/
	std::shared_ptr<Register16_t> mHighRegister16;
};