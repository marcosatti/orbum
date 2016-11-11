#include "stdafx.h"

#include "PS2Resources/EE/VPU/Types/VuUnits_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

VuUnit_t::VuUnit_t(const u32 & unitID) :
	mUnitID(unitID),
	VF{ std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>() },
	VI{ std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(),
		std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>() },
	MemPhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_32KB, Constants::SIZE_4KB, Constants::SIZE_16B)),
	MEMORY_Micro(nullptr),
	MEMORY_Mem(nullptr)
{
}

VuUnit_0_t::VuUnit_0_t() :
	VuUnit_t(UNIT_ID)
{
	MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Micro Mem");
	MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Main Mem");
}

VuUnit_1_t::VuUnit_1_t() :
	VuUnit_t(UNIT_ID)
{
	MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Micro Mem");
	MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Main Mem");
}
