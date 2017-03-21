#include "stdafx.h"

#include "Common/Types/Memory/Memory_t.h"

#include "Resources/IOP/SPU2/SPU2_t.h"

SPU2_t::SPU2_t() :
	SPU2_REGISTERS(std::make_shared<Memory_t>(0x800, "SPU2 Registers", true, true))
{
}
