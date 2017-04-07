#include "stdafx.h"

#include "Common/Types/Register/PCRegister16_t.h"

PCRegister16_t::PCRegister16_t(const char * mnemonic, const bool debugReads, const bool debugWrites) :
	Register16_t(mnemonic, debugReads, debugWrites)
{
}

void PCRegister16_t::setPCValueRelative(const System_t context, const s16 relativeLocation)
{
	writeHword(context, readHword(context) + relativeLocation);
}

void PCRegister16_t::setPCValueAbsolute(const System_t context, const u16 absoluteLocation)
{
	writeHword(context, absoluteLocation);
}

void PCRegister16_t::setPCValueNext(const System_t context, const u16 instructionSize)
{
	setPCValueRelative(context, instructionSize);
}
