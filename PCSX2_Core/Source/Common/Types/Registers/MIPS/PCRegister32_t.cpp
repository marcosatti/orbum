#include "stdafx.h"

#include "Common/Types/Registers/MIPS/PCRegister32_t.h"

void PCRegister32_t::setPCValueRelative(const s32& relativeLocation)
{
	writeWord(RAW, readWord(RAW) + relativeLocation);
}

void PCRegister32_t::setPCValueAbsolute(const u32& absoluteLocation)
{
	writeWord(RAW, absoluteLocation);
}

void PCRegister32_t::setPCValueNext(const u32 instructionSize)
{
	setPCValueRelative(instructionSize);
}
