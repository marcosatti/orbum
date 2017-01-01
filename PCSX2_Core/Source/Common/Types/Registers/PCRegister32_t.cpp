#include "stdafx.h"
#include "Common/Types/Registers/PCRegister32_t.h"
#include "PS2Constants/PS2Constants.h"

void PCRegister32_t::setPCValueRelative(const s32& relativeLocation)
{
	writeWord(readWord() + relativeLocation);
}

void PCRegister32_t::setPCValueAbsolute(const u32& absoluteLocation)
{
	writeWord(absoluteLocation);
}

void PCRegister32_t::setPCValueNext(const u32 instructionSize)
{
	setPCValueRelative(instructionSize);
}
