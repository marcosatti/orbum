#include "stdafx.h"

#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"
#include "Common/Types/Registers/FPRegister128_t.h"
#include "Common/Types/Registers/FPRegister32_t.h"
#include "Common/Types/Registers/Register16_t.h"
#include "Common/Types/Registers/PCRegister16_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/ZeroFPRegister128_t.h"
#include "Common/Types/Registers/ZeroRegister16_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0Registers_t.h"

VuUnit_t::VuUnit_t(const PS2Resources_t* const PS2Resources, const u32 & unitID) :
	PS2ResourcesSubobject(PS2Resources),
	mUnitID(unitID),
	VF{ std::make_shared<ZeroFPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(),
		std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>(), std::make_shared<FPRegister128_t>() },
	VI{ std::make_shared<ZeroRegister16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(),
		std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>(), std::make_shared<Register16_t>() },
	ACC(std::make_shared<FPRegister128_t>()),
	I(std::make_shared<FPRegister32_t>()),
	Q(std::make_shared<FPRegister32_t>()),
	R(std::make_shared<FPRegister32_t>()),
	P(std::make_shared<FPRegister32_t>()),
	Status(std::make_shared<VuUnitRegister_Status_t>()),
	MAC(std::make_shared<VuUnitRegister_MAC_t>(Status)),
	Clipping(std::make_shared<VuUnitRegister_Clipping_t>()),
	PC(std::make_shared<PCRegister16_t>()),
	CMSAR(std::make_shared<VuUnitRegister_CMSAR_t>()),
	MemPhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_32KB, Constants::SIZE_4KB, Constants::SIZE_16B)),
	MEMORY_Micro(nullptr),
	MEMORY_Mem(nullptr)
{
}

VuUnit_VU0_t::VuUnit_VU0_t(const PS2Resources_t* const PS2Resources) :
	VuUnit_t(PS2Resources, UNIT_ID)
{
	MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Micro Mem");
	MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_4KB, "VU0 Main Mem");
}

bool VuUnit_VU0_t::isCoprocessorUsable() const
{
	// Check that CU[bit 2] == 1 (ie: >0) in the status register.
	if ((getRoot()->EE->EECore->COP0->Status->getFieldValue(EECoreCOP0Register_Status_t::Fields::CU) & 0x4) > 0)
		return true;
	else
		return false;
}

VuUnit_VU1_t::VuUnit_VU1_t(const PS2Resources_t* const PS2Resources) :
	VuUnit_t(PS2Resources, UNIT_ID)
{
	MEMORY_Micro = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Micro Mem");
	MEMORY_Mem = std::make_shared<Memory_t>(Constants::SIZE_16KB, "VU1 Main Mem");
}
