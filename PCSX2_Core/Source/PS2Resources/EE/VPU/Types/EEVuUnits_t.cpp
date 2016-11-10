#include "stdafx.h"

#include "PS2Resources/EE/VPU/Types/EEVuUnits_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Memory/Memory_t.h"

EEVuUnit_t::EEVuUnit_t(const u32 & unitID) :
	mUnitID(unitID),
	VF{ std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>() },
	VI{ std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(),
		std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>() },
	MemPhysicalMMU(nullptr),
	VU_MEMORY_Micro(nullptr),
	VU_MEMORY_Mem(nullptr)
{
}

EEVuUnit_0_t::EEVuUnit_0_t() :
	EEVuUnit_t(UNIT_ID)
{
	VU_MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Micro Mem");
	VU_MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Main Mem");
}

EEVuUnit_1_t::EEVuUnit_1_t() :
	EEVuUnit_t(UNIT_ID)
{
	VU_MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Micro Mem");
	VU_MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Main Mem");
}
