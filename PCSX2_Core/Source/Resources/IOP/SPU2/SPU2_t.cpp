#include "stdafx.h"

#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/HwordMemory_t.h"

#include "Resources/IOP/SPU2/SPU2_t.h"

SPU2_t::SPU2_t() :
	SPU2_REGISTERS(std::make_shared<ByteMemory_t>(0x800, "SPU2 Registers", false, true)),
	MainMemory(std::make_shared<HwordMemory_t>(Constants::IOP::SPU2::SIZE_MAIN_MEMORY, "SPU2 Main Memory", false, true))
{
}
