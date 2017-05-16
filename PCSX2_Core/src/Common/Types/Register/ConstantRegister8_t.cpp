#include "Common/Global/Globals.h"
#include "Common/Types/Register/ConstantRegister8_t.h"

ConstantRegister8_t::ConstantRegister8_t(const char * mnemonic, const bool debugReads, const bool debugWrites, const u8 B) :
	Register8_t(mnemonic, debugReads, debugWrites)
{
	UB = B;
}

void ConstantRegister8_t::writeByte(const System_t context, const u8 value)
{
	// Do not write value (zero register).
}

void ConstantRegister8_t::initialise()
{
}
