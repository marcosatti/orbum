#include "Common/Global/Globals.h"
#include "Common/Types/Register/ConstantRegister128_t.h"

ConstantRegister128_t::ConstantRegister128_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u128 Q) :
	Register128_t(mnemonic, debugReads, debugWrites)
{
	UQ = Q;
}

void ConstantRegister128_t::writeByte(const Context_t context, const size_t arrayIndex, const u8 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeHword(const Context_t context, const size_t arrayIndex, const u16 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeWord(const Context_t context, const size_t arrayIndex, const u32 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeDword(const Context_t context, const size_t arrayIndex, const u64 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::writeQword(const Context_t context, const u128 value)
{
	// Do not write value (constant register).
}

void ConstantRegister128_t::initialise()
{
}
