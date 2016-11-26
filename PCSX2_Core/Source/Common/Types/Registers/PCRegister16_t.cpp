#include "stdafx.h"

#include "Common/Types/Registers/PCRegister16_t.h"

u16 PCRegister16_t::getPCValue()
{
	return readHwordU();
}

void PCRegister16_t::setPCValueRelative(const s16 & relativeLocation)
{
	writeHwordU(getPCValue() + relativeLocation);
}

void PCRegister16_t::setPCValueAbsolute(const u16 & absoluteLocation)
{
	writeHwordU(absoluteLocation);
}

void PCRegister16_t::setPCValueNext(const u16 instructionSize)
{
	setPCValueRelative(instructionSize);
}
