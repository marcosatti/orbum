#pragma once

#include "Common/Global/Globals.h"
#include "Common/Types/Register/Register128_t.h"

/*
ConstantRegister128_t is used as a register with a constant value. Any writes are discarded, and any reads are the value set at creation.
By default set to all 0.
*/
class ConstantRegister128_t : public Register128_t
{
public:
	ConstantRegister128_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u128 Q = 0);

	/*
	Overwritten write functions that discard any value.
	*/
	void writeByte(const System_t context, size_t arrayIndex, u8 value) override;
	void writeHword(const System_t context, size_t arrayIndex, u16 value) override;
	void writeWord(const System_t context, size_t arrayIndex, u32 value) override;
	void writeDword(const System_t context, size_t arrayIndex, u64 value) override;
	void writeQword(const System_t context, u128 value) override;

	/*
	Initalise register (set to do nothing).
	*/
	void initalise() override;
};

