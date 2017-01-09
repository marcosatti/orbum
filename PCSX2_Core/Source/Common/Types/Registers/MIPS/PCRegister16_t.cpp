#include "stdafx.h"

#include "Common/Types/Registers/MIPS/PCRegister16_t.h"

void PCRegister16_t::setPCValueRelative(const s16 & relativeLocation)
{
	writeHword(Context_t::RAW, readHword(Context_t::RAW) + relativeLocation);
}

void PCRegister16_t::setPCValueAbsolute(const u16 & absoluteLocation)
{
	writeHword(Context_t::RAW, absoluteLocation);
}

void PCRegister16_t::setPCValueNext(const u16 instructionSize)
{
	setPCValueRelative(instructionSize);
}
