#include "stdafx.h"

#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VURegisters_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/VPURegisters_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"
#include "Common/Types/Registers/Wrapper/WrapperR16Register32_t.h"
#include "Common/Types/Registers/PCRegister16_t.h"
#include "Common/Types/Registers/Wrapper/WrapperF32Register32_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"

VU_t::VU_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	VU0(nullptr),
	VU1(std::make_shared<VuUnit_VU1_t>()),
	VU_UNITS{},
	FBRST(std::make_shared<VURegister_FBRST_t>())
{
}

void VU_t::postResourcesInit()
{
	initVU0();
	initVU0ControlRegistersMap();
	initVU0PhysicalMemoryMap();
	initVU1PhysicalMemoryMap();
}

void VU_t::initVU0()
{
	VU0 = std::make_shared<VuUnit_VU0_t>(getRoot()->EE->EECore->COP0);
	
	VU_UNITS[0] = VU0;
	VU_UNITS[1] = VU1;
}

void VU_t::initVU0ControlRegistersMap() const
{
	auto& VPU = getRoot()->EE->VPU;

	// Init the CCR array, which contains the list of registers used by some EE Core COP2 instructions.
	// See VU Users Manual page 200 for the list. There are 32 registers total.
	VU0->CCR[0] = std::make_shared<WrapperR16Register32_t>(VU0->VI[0]);
	VU0->CCR[1] = std::make_shared<WrapperR16Register32_t>(VU0->VI[1]);
	VU0->CCR[2] = std::make_shared<WrapperR16Register32_t>(VU0->VI[2]);
	VU0->CCR[3] = std::make_shared<WrapperR16Register32_t>(VU0->VI[3]);
	VU0->CCR[4] = std::make_shared<WrapperR16Register32_t>(VU0->VI[4]);
	VU0->CCR[5] = std::make_shared<WrapperR16Register32_t>(VU0->VI[5]);
	VU0->CCR[6] = std::make_shared<WrapperR16Register32_t>(VU0->VI[6]);
	VU0->CCR[7] = std::make_shared<WrapperR16Register32_t>(VU0->VI[7]);
	VU0->CCR[8] = std::make_shared<WrapperR16Register32_t>(VU0->VI[8]);
	VU0->CCR[9] = std::make_shared<WrapperR16Register32_t>(VU0->VI[9]);
	VU0->CCR[10] = std::make_shared<WrapperR16Register32_t>(VU0->VI[10]);
	VU0->CCR[11] = std::make_shared<WrapperR16Register32_t>(VU0->VI[11]);
	VU0->CCR[12] = std::make_shared<WrapperR16Register32_t>(VU0->VI[12]);
	VU0->CCR[13] = std::make_shared<WrapperR16Register32_t>(VU0->VI[13]);
	VU0->CCR[14] = std::make_shared<WrapperR16Register32_t>(VU0->VI[14]);
	VU0->CCR[15] = std::make_shared<WrapperR16Register32_t>(VU0->VI[15]);
	VU0->CCR[16] = VU0->Status;
	VU0->CCR[17] = VU0->MAC;
	VU0->CCR[18] = VU0->Clipping;
	VU0->CCR[19] = nullptr;
	VU0->CCR[20] = std::make_shared<WrapperF32Register32_t>(VU0->R);
	VU0->CCR[21] = std::make_shared<WrapperF32Register32_t>(VU0->I);
	VU0->CCR[22] = std::make_shared<WrapperF32Register32_t>(VU0->Q);
	VU0->CCR[23] = nullptr;
	VU0->CCR[24] = nullptr;
	VU0->CCR[25] = nullptr;
	VU0->CCR[26] = std::make_shared<WrapperR16Register32_t>(VU0->PC); // TPC.
	VU0->CCR[27] = VU0->CMSAR;
	VU0->CCR[28] = FBRST;
	VU0->CCR[29] = VPU->STAT;
	VU0->CCR[30] = nullptr;
	VU0->CCR[31] = VU1->CMSAR;
}

void VU_t::initVU0PhysicalMemoryMap() const
{
	// VU0 Memory.
	{
		VU0->MemPhysicalMMU->mapObject(0x0000, VU0->MEMORY_Mem);
		VU0->MemPhysicalMMU->mapObject(0x1000, VU0->MEMORY_Mem);
		VU0->MemPhysicalMMU->mapObject(0x2000, VU0->MEMORY_Mem);
		VU0->MemPhysicalMMU->mapObject(0x3000, VU0->MEMORY_Mem);
	}

	// VU1 Registers, see VU Users Manual page 222. 
	{
		// VF Registers.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
			VU0->MemPhysicalMMU->mapObject(0x4000 + i * Constants::NUMBER_BYTES_IN_QWORD, VU1->VF[i]);

		// VI Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded! 
		// NOT mapped as the true register size of 16-bit (need to do a Register32_t wrapping)! 
		// See EE Users Manual page 84.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
			VU0->MemPhysicalMMU->mapObject(0x4200 + i * Constants::NUMBER_BYTES_IN_QWORD, std::make_shared<WrapperR16Register32_t>(VU1->VI[i]));

		// Misc Registers.
		VU0->MemPhysicalMMU->mapObject(0x4300, VU1->Status);
		VU0->MemPhysicalMMU->mapObject(0x4310, VU1->MAC);
		VU0->MemPhysicalMMU->mapObject(0x4320, VU1->Clipping);
		VU0->MemPhysicalMMU->mapObject(0x4340, VU1->R);
		VU0->MemPhysicalMMU->mapObject(0x4350, VU1->I);
		VU0->MemPhysicalMMU->mapObject(0x4360, VU1->Q);
		VU0->MemPhysicalMMU->mapObject(0x4370, VU1->P);
		VU0->MemPhysicalMMU->mapObject(0x43A0, VU1->PC); // TPC.
	}
}

void VU_t::initVU1PhysicalMemoryMap() const
{
	// VU1 Memory.
	VU1->MemPhysicalMMU->mapObject(0x0000, VU1->MEMORY_Mem);
}
