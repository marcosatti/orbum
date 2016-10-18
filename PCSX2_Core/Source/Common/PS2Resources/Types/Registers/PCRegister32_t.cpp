#include "stdafx.h"
#include "Common/PS2Resources/Types/Registers/PCRegister32_t.h"
#include "Common/PS2Constants/PS2Constants.h"

u32 PCRegister32_t::getPCValue()
{
	return readWordU();
}

void PCRegister32_t::setPCValueRelative(const s32& relativeLocation)
{
	writeWordU(getPCValue() + relativeLocation);
}

void PCRegister32_t::setPCValueAbsolute(const u32& absoluteLocation)
{
	writeWordU(absoluteLocation);
}

void PCRegister32_t::setPCValueNext()
{
	setPCValueRelative(Constants::SIZE_MIPS_INSTRUCTION);
}
