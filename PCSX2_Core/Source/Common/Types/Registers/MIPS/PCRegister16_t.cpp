#include "stdafx.h"

#include "Common/Types/Registers/MIPS/PCRegister16_t.h"

void PCRegister16_t::setPCValueRelative(const s16 & relativeLocation)
{
	writeHword(RAW, readHword(RAW) + relativeLocation);
}

void PCRegister16_t::setPCValueAbsolute(const u16 & absoluteLocation)
{
	writeHword(RAW, absoluteLocation);
}

void PCRegister16_t::setPCValueNext(const u16 instructionSize)
{
	setPCValueRelative(instructionSize);
}
