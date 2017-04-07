#include "stdafx.h"

#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/HwordMemory_t.h"

#include "Resources/IOP/SPU2/SPU2_t.h"

SPU2_t::SPU2_t() :
	SPU2_REGISTERS(std::make_shared<ByteMemory_t>("SPU2 Registers", false, true, 0x800)),
	MainMemory(std::make_shared<HwordMemory_t>("SPU2 MainMem", false, false, Constants::IOP::SPU2::SIZE_MAIN_MEMORY)),
	DebugDummy(std::make_shared<HwordMemory_t>("SPU2 DebugDummy", false, false, 0x2))
{
}
