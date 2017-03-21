#include "stdafx.h"

#include <memory>

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/Wrapper/WrapperR16Register32_t.h"
#include "Common/Types/Registers/Wrapper/WrapperF32Register32_t.h"
#include "Common/Types/Registers/MIPS/PCRegister16_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister8_t.h"
#include "Common/Types/Registers/Constant/ConstantRegister32_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/ROMemory_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"

#include "Resources/Resources_t.h"
#include "Resources/Clock/Clock_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/GS/GS_t.h"
#include "Resources/IOP/IOP_t.h"
#include "Resources/Common/Common_t.h"

#include "Resources/Common/Common_t.h"
#include "Resources/Common/Types/SBUSRegisters_t.h"
#include "Resources/Common/Types/SBUSFIFOQueues_t.h"

#include "Resources/EE/Types/EERegisters_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/DMAC/EEDmac_t.h"
#include "Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "Resources/EE/Timers/EETimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimers_t.h"
#include "Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "Resources/EE/IPU/IPU_t.h"
#include "Resources/EE/GIF/GIF_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "Resources/EE/VPU/VPU_t.h"
#include "Resources/EE/VPU/Types/VPURegisters_t.h"
#include "Resources/EE/VPU/VIF/VIF_t.h"
#include "Resources/EE/VPU/VIF/Types/VifUnits_t.h"
#include "Resources/EE/VPU/VIF/Types/VifUnitRegisters_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "Resources/EE/VPU/VU/Types/VURegisters_t.h"
#include "Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/CDVD/CDVD_t.h"
#include "Resources/IOP/SPU2/SPU2_t.h"
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

Resources_t::Resources_t() :
	Clock(std::make_shared<Clock_t>()),
	Common(std::make_shared<Common_t>()),
	GS(std::make_shared<GS_t>()),
	EE(std::make_shared<EE_t>()),
	IOP(std::make_shared<IOP_t>())
{
	postInit_EE_DMAC();
	postInit_EE_VPU_VU();
	postInit_EE();
	postInit_IOP_DMAC();
	postInit_IOP();
}

void Resources_t::postInit_EE_DMAC() const
{
	// Initalise DMAC channels.
	{
		EE->DMAC->CHANNEL_VIF0 = std::make_shared<EEDmacChannel_VIF0_t>(Common->FIFO_VIF0);
		EE->DMAC->CHANNEL_VIF1 = std::make_shared<EEDmacChannel_VIF1_t>(Common->FIFO_VIF1);
		EE->DMAC->CHANNEL_GIF = std::make_shared<EEDmacChannel_GIF_t>(Common->FIFO_GIF);
		EE->DMAC->CHANNEL_fromIPU = std::make_shared<EEDmacChannel_fromIPU_t>(Common->FIFO_fromIPU);
		EE->DMAC->CHANNEL_toIPU = std::make_shared<EEDmacChannel_toIPU_t>(Common->FIFO_toIPU);
		EE->DMAC->CHANNEL_SIF0 = std::make_shared<EEDmacChannel_SIF0_t>(Common->FIFO_SIF0, Common->SBUS_F240);
		EE->DMAC->CHANNEL_SIF1 = std::make_shared<EEDmacChannel_SIF1_t>(Common->FIFO_SIF1, Common->SBUS_F240);
		EE->DMAC->CHANNEL_SIF2 = std::make_shared<EEDmacChannel_SIF2_t>(Common->FIFO_SIF2, Common->SBUS_F240);
		EE->DMAC->CHANNEL_fromSPR = std::make_shared<EEDmacChannel_fromSPR_t>();
		EE->DMAC->CHANNEL_toSPR = std::make_shared<EEDmacChannel_toSPR_t>();

		EE->DMAC->CHANNELS[0] = EE->DMAC->CHANNEL_VIF0;
		EE->DMAC->CHANNELS[1] = EE->DMAC->CHANNEL_VIF1;
		EE->DMAC->CHANNELS[2] = EE->DMAC->CHANNEL_GIF;
		EE->DMAC->CHANNELS[3] = EE->DMAC->CHANNEL_fromIPU;
		EE->DMAC->CHANNELS[4] = EE->DMAC->CHANNEL_toIPU;
		EE->DMAC->CHANNELS[5] = EE->DMAC->CHANNEL_SIF0;
		EE->DMAC->CHANNELS[6] = EE->DMAC->CHANNEL_SIF1;
		EE->DMAC->CHANNELS[7] = EE->DMAC->CHANNEL_SIF2;
		EE->DMAC->CHANNELS[8] = EE->DMAC->CHANNEL_fromSPR;
		EE->DMAC->CHANNELS[9] = EE->DMAC->CHANNEL_toSPR;
	}
}

void Resources_t::postInit_EE_VPU_VU() const
{
	// Initalise VU0 & the CCR registers.
	{
		EE->VPU->VU->VU0 = std::make_shared<VuUnit_VU0_t>(EE->EECore->COP0);
		EE->VPU->VU->VU0->CCR[0] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[0]);
		EE->VPU->VU->VU0->CCR[1] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[1]);
		EE->VPU->VU->VU0->CCR[2] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[2]);
		EE->VPU->VU->VU0->CCR[3] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[3]);
		EE->VPU->VU->VU0->CCR[4] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[4]);
		EE->VPU->VU->VU0->CCR[5] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[5]);
		EE->VPU->VU->VU0->CCR[6] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[6]);
		EE->VPU->VU->VU0->CCR[7] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[7]);
		EE->VPU->VU->VU0->CCR[8] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[8]);
		EE->VPU->VU->VU0->CCR[9] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[9]);
		EE->VPU->VU->VU0->CCR[10] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[10]);
		EE->VPU->VU->VU0->CCR[11] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[11]);
		EE->VPU->VU->VU0->CCR[12] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[12]);
		EE->VPU->VU->VU0->CCR[13] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[13]);
		EE->VPU->VU->VU0->CCR[14] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[14]);
		EE->VPU->VU->VU0->CCR[15] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->VI[15]);
		EE->VPU->VU->VU0->CCR[16] = EE->VPU->VU->VU0->Status;
		EE->VPU->VU->VU0->CCR[17] = EE->VPU->VU->VU0->MAC;
		EE->VPU->VU->VU0->CCR[18] = EE->VPU->VU->VU0->Clipping;
		EE->VPU->VU->VU0->CCR[19] = nullptr;
		EE->VPU->VU->VU0->CCR[20] = std::make_shared<WrapperF32Register32_t>(EE->VPU->VU->VU0->R);
		EE->VPU->VU->VU0->CCR[21] = std::make_shared<WrapperF32Register32_t>(EE->VPU->VU->VU0->I);
		EE->VPU->VU->VU0->CCR[22] = std::make_shared<WrapperF32Register32_t>(EE->VPU->VU->VU0->Q);
		EE->VPU->VU->VU0->CCR[23] = nullptr;
		EE->VPU->VU->VU0->CCR[24] = nullptr;
		EE->VPU->VU->VU0->CCR[25] = nullptr;
		EE->VPU->VU->VU0->CCR[26] = std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU0->PC); // TPC.
		EE->VPU->VU->VU0->CCR[27] = EE->VPU->VU->VU0->CMSAR;
		EE->VPU->VU->VU0->CCR[28] = EE->VPU->VU->FBRST;
		EE->VPU->VU->VU0->CCR[29] = EE->VPU->STAT;
		EE->VPU->VU->VU0->CCR[30] = nullptr;
		EE->VPU->VU->VU0->CCR[31] = EE->VPU->VU->VU1->CMSAR;
	}

	// Initalise VU units array.
	{
		EE->VPU->VU->VU_UNITS[0] = EE->VPU->VU->VU0;
		EE->VPU->VU->VU_UNITS[1] = EE->VPU->VU->VU1;
	}

	// Initalise VU0 and VU1 physical memory map.
	{
		// VU0 Memory.
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x0000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x1000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x2000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x3000, EE->VPU->VU->VU0->MEMORY_Mem);

		// VU1.VF Registers, see VU Users Manual page 222. 
		for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
			EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4000 + i * Constants::NUMBER_BYTES_IN_QWORD, EE->VPU->VU->VU1->VF[i]);

		// VU1.VI Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded! 
		// NOT mapped as the true register size of 16-bit (need to do a Register32_t wrapping)! 
		// See EE Users Manual page 84.
		for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
			EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4200 + i * Constants::NUMBER_BYTES_IN_QWORD, std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU1->VI[i]));

		// Misc Registers.
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4300, EE->VPU->VU->VU1->Status);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4310, EE->VPU->VU->VU1->MAC);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4320, EE->VPU->VU->VU1->Clipping);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4340, EE->VPU->VU->VU1->R);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4350, EE->VPU->VU->VU1->I);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4360, EE->VPU->VU->VU1->Q);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4370, EE->VPU->VU->VU1->P);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x43A0, EE->VPU->VU->VU1->PC); // TPC.

																				   // VU1 Memory.
		EE->VPU->VU->VU1->MemPhysicalMMU->mapObject(0x0000, EE->VPU->VU->VU1->MEMORY_Mem);
	}
}

void Resources_t::postInit_EE() const
{
	// Initalise physical memory map of EE.
	{
		// EE Memory.
		{
			// Main Memory.
			EE->PhysicalMMU->mapObject(Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY, EE->MainMemory);

			// Scratchpad Memory.
			EE->PhysicalMMU->mapObject(Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, EE->EECore->ScratchpadMemory);

			// Various ROMs.
			EE->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
			EE->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);
			EE->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_EROM, EE->EROM);
			EE->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_ROM2, EE->ROM2);

			// Unknown memory.
			EE->PhysicalMMU->mapObject(0x1A000000, EE->UNKNOWN_1A000000);
		}

		// EE Registers.
		{
			// MISC EE registers.
			EE->PhysicalMMU->mapObject(0x1000F100, EE->MEMORY_SIO);
			EE->PhysicalMMU->mapObject(0x1000f400, EE->REGISTER_F400);
			EE->PhysicalMMU->mapObject(0x1000f410, EE->MEMORY_F410);
			EE->PhysicalMMU->mapObject(0x1000f420, EE->REGISTER_F420);
			EE->PhysicalMMU->mapObject(0x1000F430, EE->MEMORY_MCH);
			EE->PhysicalMMU->mapObject(0x1000f450, EE->MEMORY_F450);

			// Timers Registers.
			EE->PhysicalMMU->mapObject(0x10000000, EE->Timers->TIMER_0->COUNT);
			EE->PhysicalMMU->mapObject(0x10000010, EE->Timers->TIMER_0->MODE);
			EE->PhysicalMMU->mapObject(0x10000020, EE->Timers->TIMER_0->COMP);
			EE->PhysicalMMU->mapObject(0x10000030, EE->Timers->TIMER_0->HOLD);
			EE->PhysicalMMU->mapObject(0x10000800, EE->Timers->TIMER_1->COUNT);
			EE->PhysicalMMU->mapObject(0x10000810, EE->Timers->TIMER_1->MODE);
			EE->PhysicalMMU->mapObject(0x10000820, EE->Timers->TIMER_1->COMP);
			EE->PhysicalMMU->mapObject(0x10000830, EE->Timers->TIMER_1->HOLD);
			EE->PhysicalMMU->mapObject(0x10001000, EE->Timers->TIMER_2->COUNT);
			EE->PhysicalMMU->mapObject(0x10001010, EE->Timers->TIMER_2->MODE);
			EE->PhysicalMMU->mapObject(0x10001020, EE->Timers->TIMER_2->COMP);
			EE->PhysicalMMU->mapObject(0x10001800, EE->Timers->TIMER_3->COUNT);
			EE->PhysicalMMU->mapObject(0x10001810, EE->Timers->TIMER_3->MODE);
			EE->PhysicalMMU->mapObject(0x10001820, EE->Timers->TIMER_3->COMP);

			// IPU Registers.
			EE->PhysicalMMU->mapObject(0x10002000, EE->IPU->CMD);
			EE->PhysicalMMU->mapObject(0x10002010, EE->IPU->CTRL);
			EE->PhysicalMMU->mapObject(0x10002020, EE->IPU->BP);
			EE->PhysicalMMU->mapObject(0x10002030, EE->IPU->TOP);

			// GIF Registers.
			EE->PhysicalMMU->mapObject(0x10003000, EE->GIF->CTRL);
			EE->PhysicalMMU->mapObject(0x10003010, EE->GIF->MODE);
			EE->PhysicalMMU->mapObject(0x10003020, EE->GIF->STAT);
			EE->PhysicalMMU->mapObject(0x10003040, EE->GIF->TAG0);
			EE->PhysicalMMU->mapObject(0x10003050, EE->GIF->TAG1);
			EE->PhysicalMMU->mapObject(0x10003060, EE->GIF->TAG2);
			EE->PhysicalMMU->mapObject(0x10003070, EE->GIF->TAG3);
			EE->PhysicalMMU->mapObject(0x10003080, EE->GIF->CNT);
			EE->PhysicalMMU->mapObject(0x10003090, EE->GIF->P3CNT);
			EE->PhysicalMMU->mapObject(0x100030a0, EE->GIF->P3TAG);

			// VIF0 Registers.
			EE->PhysicalMMU->mapObject(0x10003800, EE->VPU->VIF->VIF0->STAT);
			EE->PhysicalMMU->mapObject(0x10003810, EE->VPU->VIF->VIF0->FBRST);
			EE->PhysicalMMU->mapObject(0x10003820, EE->VPU->VIF->VIF0->ERR);
			EE->PhysicalMMU->mapObject(0x10003830, EE->VPU->VIF->VIF0->MARK);
			EE->PhysicalMMU->mapObject(0x10003840, EE->VPU->VIF->VIF0->CYCLE);
			EE->PhysicalMMU->mapObject(0x10003850, EE->VPU->VIF->VIF0->MODE);
			EE->PhysicalMMU->mapObject(0x10003860, EE->VPU->VIF->VIF0->NUM);
			EE->PhysicalMMU->mapObject(0x10003870, EE->VPU->VIF->VIF0->MASK);
			EE->PhysicalMMU->mapObject(0x10003880, EE->VPU->VIF->VIF0->CODE);
			EE->PhysicalMMU->mapObject(0x10003890, EE->VPU->VIF->VIF0->ITOPS);
			EE->PhysicalMMU->mapObject(0x100038d0, EE->VPU->VIF->VIF0->ITOP);
			EE->PhysicalMMU->mapObject(0x10003900, EE->VPU->VIF->VIF0->R0);
			EE->PhysicalMMU->mapObject(0x10003910, EE->VPU->VIF->VIF0->R1);
			EE->PhysicalMMU->mapObject(0x10003920, EE->VPU->VIF->VIF0->R2);
			EE->PhysicalMMU->mapObject(0x10003930, EE->VPU->VIF->VIF0->R3);
			EE->PhysicalMMU->mapObject(0x10003940, EE->VPU->VIF->VIF0->C0);
			EE->PhysicalMMU->mapObject(0x10003950, EE->VPU->VIF->VIF0->C1);
			EE->PhysicalMMU->mapObject(0x10003960, EE->VPU->VIF->VIF0->C2);
			EE->PhysicalMMU->mapObject(0x10003970, EE->VPU->VIF->VIF0->C3);

			// VIF1 Registers.
			EE->PhysicalMMU->mapObject(0x10003c00, EE->VPU->VIF->VIF1->STAT);
			EE->PhysicalMMU->mapObject(0x10003c10, EE->VPU->VIF->VIF1->FBRST);
			EE->PhysicalMMU->mapObject(0x10003c20, EE->VPU->VIF->VIF1->ERR);
			EE->PhysicalMMU->mapObject(0x10003c30, EE->VPU->VIF->VIF1->MARK);
			EE->PhysicalMMU->mapObject(0x10003c40, EE->VPU->VIF->VIF1->CYCLE);
			EE->PhysicalMMU->mapObject(0x10003c50, EE->VPU->VIF->VIF1->MODE);
			EE->PhysicalMMU->mapObject(0x10003c60, EE->VPU->VIF->VIF1->NUM);
			EE->PhysicalMMU->mapObject(0x10003c70, EE->VPU->VIF->VIF1->MASK);
			EE->PhysicalMMU->mapObject(0x10003c80, EE->VPU->VIF->VIF1->CODE);
			EE->PhysicalMMU->mapObject(0x10003c90, EE->VPU->VIF->VIF1->ITOPS);
			EE->PhysicalMMU->mapObject(0x10003ca0, EE->VPU->VIF->VIF1->BASE);
			EE->PhysicalMMU->mapObject(0x10003cb0, EE->VPU->VIF->VIF1->OFST);
			EE->PhysicalMMU->mapObject(0x10003cc0, EE->VPU->VIF->VIF1->TOPS);
			EE->PhysicalMMU->mapObject(0x10003cd0, EE->VPU->VIF->VIF1->ITOP);
			EE->PhysicalMMU->mapObject(0x10003ce0, EE->VPU->VIF->VIF1->TOP);
			EE->PhysicalMMU->mapObject(0x10003d00, EE->VPU->VIF->VIF1->R0);
			EE->PhysicalMMU->mapObject(0x10003d10, EE->VPU->VIF->VIF1->R1);
			EE->PhysicalMMU->mapObject(0x10003d20, EE->VPU->VIF->VIF1->R2);
			EE->PhysicalMMU->mapObject(0x10003d30, EE->VPU->VIF->VIF1->R3);
			EE->PhysicalMMU->mapObject(0x10003d40, EE->VPU->VIF->VIF1->C0);
			EE->PhysicalMMU->mapObject(0x10003d50, EE->VPU->VIF->VIF1->C1);
			EE->PhysicalMMU->mapObject(0x10003d60, EE->VPU->VIF->VIF1->C2);
			EE->PhysicalMMU->mapObject(0x10003d70, EE->VPU->VIF->VIF1->C3);

			// FIFO Registers.
			EE->PhysicalMMU->mapObject(0x10004000, Common->FIFO_VIF0);
			EE->PhysicalMMU->mapObject(0x10005000, Common->FIFO_VIF1);
			EE->PhysicalMMU->mapObject(0x10006000, Common->FIFO_GIF);
			EE->PhysicalMMU->mapObject(0x10007000, Common->FIFO_fromIPU);
			EE->PhysicalMMU->mapObject(0x10007010, Common->FIFO_toIPU);

			// DMAC registers.
			EE->PhysicalMMU->mapObject(0x10008000, EE->DMAC->CHANNEL_VIF0->CHCR);
			EE->PhysicalMMU->mapObject(0x10008010, EE->DMAC->CHANNEL_VIF0->MADR);
			EE->PhysicalMMU->mapObject(0x10008020, EE->DMAC->CHANNEL_VIF0->QWC);
			EE->PhysicalMMU->mapObject(0x10008030, EE->DMAC->CHANNEL_VIF0->TADR);
			EE->PhysicalMMU->mapObject(0x10008040, EE->DMAC->CHANNEL_VIF0->ASR0);
			EE->PhysicalMMU->mapObject(0x10008050, EE->DMAC->CHANNEL_VIF0->ASR1);
			EE->PhysicalMMU->mapObject(0x10008060, EE->DMAC->CHANNEL_VIF0->MEMORY_8060);
			EE->PhysicalMMU->mapObject(0x10009000, EE->DMAC->CHANNEL_VIF1->CHCR);
			EE->PhysicalMMU->mapObject(0x10009010, EE->DMAC->CHANNEL_VIF1->MADR);
			EE->PhysicalMMU->mapObject(0x10009020, EE->DMAC->CHANNEL_VIF1->QWC);
			EE->PhysicalMMU->mapObject(0x10009030, EE->DMAC->CHANNEL_VIF1->TADR);
			EE->PhysicalMMU->mapObject(0x10009040, EE->DMAC->CHANNEL_VIF1->ASR0);
			EE->PhysicalMMU->mapObject(0x10009050, EE->DMAC->CHANNEL_VIF1->ASR1);
			EE->PhysicalMMU->mapObject(0x10009060, EE->DMAC->CHANNEL_VIF1->MEMORY_9060);
			EE->PhysicalMMU->mapObject(0x1000a000, EE->DMAC->CHANNEL_GIF->CHCR);
			EE->PhysicalMMU->mapObject(0x1000a010, EE->DMAC->CHANNEL_GIF->MADR);
			EE->PhysicalMMU->mapObject(0x1000a020, EE->DMAC->CHANNEL_GIF->QWC);
			EE->PhysicalMMU->mapObject(0x1000a030, EE->DMAC->CHANNEL_GIF->TADR);
			EE->PhysicalMMU->mapObject(0x1000a040, EE->DMAC->CHANNEL_GIF->ASR0);
			EE->PhysicalMMU->mapObject(0x1000a050, EE->DMAC->CHANNEL_GIF->ASR1);
			EE->PhysicalMMU->mapObject(0x1000a060, EE->DMAC->CHANNEL_GIF->MEMORY_A060);
			EE->PhysicalMMU->mapObject(0x1000b000, EE->DMAC->CHANNEL_fromIPU->CHCR);
			EE->PhysicalMMU->mapObject(0x1000b010, EE->DMAC->CHANNEL_fromIPU->MADR);
			EE->PhysicalMMU->mapObject(0x1000b020, EE->DMAC->CHANNEL_fromIPU->QWC);
			EE->PhysicalMMU->mapObject(0x1000b030, EE->DMAC->CHANNEL_fromIPU->MEMORY_B030);
			EE->PhysicalMMU->mapObject(0x1000b400, EE->DMAC->CHANNEL_toIPU->CHCR);
			EE->PhysicalMMU->mapObject(0x1000b410, EE->DMAC->CHANNEL_toIPU->MADR);
			EE->PhysicalMMU->mapObject(0x1000b420, EE->DMAC->CHANNEL_toIPU->QWC);
			EE->PhysicalMMU->mapObject(0x1000b430, EE->DMAC->CHANNEL_toIPU->TADR);
			EE->PhysicalMMU->mapObject(0x1000b440, EE->DMAC->CHANNEL_toIPU->MEMORY_B440);
			EE->PhysicalMMU->mapObject(0x1000c000, EE->DMAC->CHANNEL_SIF0->CHCR);
			EE->PhysicalMMU->mapObject(0x1000c010, EE->DMAC->CHANNEL_SIF0->MADR);
			EE->PhysicalMMU->mapObject(0x1000c020, EE->DMAC->CHANNEL_SIF0->QWC);
			EE->PhysicalMMU->mapObject(0x1000c030, EE->DMAC->CHANNEL_SIF0->MEMORY_C030);
			EE->PhysicalMMU->mapObject(0x1000c400, EE->DMAC->CHANNEL_SIF1->CHCR);
			EE->PhysicalMMU->mapObject(0x1000c410, EE->DMAC->CHANNEL_SIF1->MADR);
			EE->PhysicalMMU->mapObject(0x1000c420, EE->DMAC->CHANNEL_SIF1->QWC);
			EE->PhysicalMMU->mapObject(0x1000c430, EE->DMAC->CHANNEL_SIF1->TADR);
			EE->PhysicalMMU->mapObject(0x1000c440, EE->DMAC->CHANNEL_SIF1->MEMORY_C440);
			EE->PhysicalMMU->mapObject(0x1000c800, EE->DMAC->CHANNEL_SIF2->CHCR);
			EE->PhysicalMMU->mapObject(0x1000c810, EE->DMAC->CHANNEL_SIF2->MADR);
			EE->PhysicalMMU->mapObject(0x1000c820, EE->DMAC->CHANNEL_SIF2->QWC);
			EE->PhysicalMMU->mapObject(0x1000c830, EE->DMAC->CHANNEL_SIF2->MEMORY_C830);
			EE->PhysicalMMU->mapObject(0x1000d000, EE->DMAC->CHANNEL_fromSPR->CHCR);
			EE->PhysicalMMU->mapObject(0x1000d010, EE->DMAC->CHANNEL_fromSPR->MADR);
			EE->PhysicalMMU->mapObject(0x1000d020, EE->DMAC->CHANNEL_fromSPR->QWC);
			EE->PhysicalMMU->mapObject(0x1000d030, EE->DMAC->CHANNEL_fromSPR->MEMORY_D030);
			EE->PhysicalMMU->mapObject(0x1000d080, EE->DMAC->CHANNEL_fromSPR->SADR);
			EE->PhysicalMMU->mapObject(0x1000d090, EE->DMAC->CHANNEL_fromSPR->MEMORY_D090);
			EE->PhysicalMMU->mapObject(0x1000d400, EE->DMAC->CHANNEL_toSPR->CHCR);
			EE->PhysicalMMU->mapObject(0x1000d410, EE->DMAC->CHANNEL_toSPR->MADR);
			EE->PhysicalMMU->mapObject(0x1000d420, EE->DMAC->CHANNEL_toSPR->QWC);
			EE->PhysicalMMU->mapObject(0x1000d430, EE->DMAC->CHANNEL_toSPR->TADR);
			EE->PhysicalMMU->mapObject(0x1000d440, EE->DMAC->CHANNEL_toSPR->MEMORY_D440);
			EE->PhysicalMMU->mapObject(0x1000d480, EE->DMAC->CHANNEL_toSPR->SADR);
			EE->PhysicalMMU->mapObject(0x1000d490, EE->DMAC->CHANNEL_toSPR->MEMORY_D490);
			EE->PhysicalMMU->mapObject(0x1000e000, EE->DMAC->CTRL);
			EE->PhysicalMMU->mapObject(0x1000e010, EE->DMAC->STAT);
			EE->PhysicalMMU->mapObject(0x1000e020, EE->DMAC->PCR);
			EE->PhysicalMMU->mapObject(0x1000e030, EE->DMAC->SQWC);
			EE->PhysicalMMU->mapObject(0x1000e040, EE->DMAC->RBSR);
			EE->PhysicalMMU->mapObject(0x1000e050, EE->DMAC->RBOR);
			EE->PhysicalMMU->mapObject(0x1000e060, EE->DMAC->STADR);

			// INTC registers.
			EE->PhysicalMMU->mapObject(0x1000f000, EE->INTC->STAT);
			EE->PhysicalMMU->mapObject(0x1000f010, EE->INTC->MASK);

			// DMAC registers (extended).
			EE->PhysicalMMU->mapObject(0x1000f500, EE->DMAC->MEMORY_F500);
			EE->PhysicalMMU->mapObject(0x1000f520, EE->DMAC->ENABLER);
			EE->PhysicalMMU->mapObject(0x1000f590, EE->DMAC->ENABLEW);
		}

		// VU0/1 Memory.
		{
			EE->PhysicalMMU->mapObject(0x11000000, EE->VPU->VU->VU0->MEMORY_Micro);
			EE->PhysicalMMU->mapObject(0x11004000, EE->VPU->VU->VU0->MEMORY_Mem);
			EE->PhysicalMMU->mapObject(0x11008000, EE->VPU->VU->VU1->MEMORY_Micro);
			EE->PhysicalMMU->mapObject(0x1100c000, EE->VPU->VU->VU1->MEMORY_Mem);
		}

		// GS Privileged Registers.
		{
			EE->PhysicalMMU->mapObject(0x12000000, GS->PMODE);
			EE->PhysicalMMU->mapObject(0x12000010, GS->SMODE1);
			EE->PhysicalMMU->mapObject(0x12000020, GS->SMODE2);
			EE->PhysicalMMU->mapObject(0x12000030, GS->SRFSH);
			EE->PhysicalMMU->mapObject(0x12000040, GS->SYNCH1);
			EE->PhysicalMMU->mapObject(0x12000050, GS->SYNCH2);
			EE->PhysicalMMU->mapObject(0x12000060, GS->SYNCV);
			EE->PhysicalMMU->mapObject(0x12000070, GS->DISPFB1);
			EE->PhysicalMMU->mapObject(0x12000080, GS->DISPLAY1);
			EE->PhysicalMMU->mapObject(0x12000090, GS->DISPFB2);
			EE->PhysicalMMU->mapObject(0x120000a0, GS->DISPLAY2);
			EE->PhysicalMMU->mapObject(0x120000b0, GS->EXTBUF);
			EE->PhysicalMMU->mapObject(0x120000c0, GS->EXTDATA);
			EE->PhysicalMMU->mapObject(0x120000d0, GS->EXTWRITE);
			EE->PhysicalMMU->mapObject(0x120000e0, GS->BGCOLOR);

			EE->PhysicalMMU->mapObject(0x12001000, GS->CSR);
			EE->PhysicalMMU->mapObject(0x12001010, GS->IMR);
			EE->PhysicalMMU->mapObject(0x12001040, GS->BUSDIR);
			EE->PhysicalMMU->mapObject(0x12001080, GS->SIGLBLID);
		}

		// IOP Mirrors.
		{
			// Misc IOP Registers.
			EE->PhysicalMMU->mapObject(0x1F80141C, IOP->HW_SSBUS_DEV9_DELAY3);
			EE->PhysicalMMU->mapObject(0x1F801470, IOP->REGISTER_1470);
			EE->PhysicalMMU->mapObject(0x1F803800, IOP->REGISTER_3800);

			// Main Memory.
			EE->PhysicalMMU->mapObject(0x1C000000, IOP->MainMemory);
		}

		// SIF Registers.
		{
			EE->PhysicalMMU->mapObject(0x1000F200, Common->SBUS_MSCOM);
			EE->PhysicalMMU->mapObject(0x1000F210, Common->SBUS_SMCOM);
			EE->PhysicalMMU->mapObject(0x1000F220, Common->SBUS_MSFLG);
			EE->PhysicalMMU->mapObject(0x1000F230, Common->SBUS_SMFLG);
			EE->PhysicalMMU->mapObject(0x1000F240, Common->SBUS_F240);
			EE->PhysicalMMU->mapObject(0x1000F250, Common->SBUS_F250);
			EE->PhysicalMMU->mapObject(0x1000F260, Common->SBUS_F260);
			EE->PhysicalMMU->mapObject(0x1000F300, Common->SBUS_F300);
			EE->PhysicalMMU->mapObject(0x1000F380, Common->SBUS_F380);
		}
	}
}

void Resources_t::postInit_IOP_DMAC() const
{
	IOP->DMAC->CHANNEL_fromMDEC = std::make_shared<IOPDmacChannel_fromMDEC_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_toMDEC = std::make_shared<IOPDmacChannel_toMDEC_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_SIF2 = std::make_shared<IOPDmacChannel_SIF2_t>(Common->FIFO_SIF2, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_CDROM = std::make_shared<IOPDmacChannel_CDROM_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_SPU2c1 = std::make_shared<IOPDmacChannel_SPU2c1_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_PIO = std::make_shared<IOPDmacChannel_PIO_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_OTClear = std::make_shared<IOPDmacChannel_OTClear_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_SPU2c2 = std::make_shared<IOPDmacChannel_SPU2c2_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_DEV9 = std::make_shared<IOPDmacChannel_DEV9_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_SIF0 = std::make_shared<IOPDmacChannel_SIF0_t>(Common->FIFO_SIF0, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_SIF1 = std::make_shared<IOPDmacChannel_SIF1_t>(Common->FIFO_SIF1, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_fromSIO2 = std::make_shared<IOPDmacChannel_fromSIO2_t>(Common->FIFO_DEBUG);
	IOP->DMAC->CHANNEL_toSIO2 = std::make_shared<IOPDmacChannel_toSIO2_t>(Common->FIFO_DEBUG);

	IOP->DMAC->CHANNELS[0] = IOP->DMAC->CHANNEL_fromMDEC;
	IOP->DMAC->CHANNELS[1] = IOP->DMAC->CHANNEL_toMDEC;
	IOP->DMAC->CHANNELS[2] = IOP->DMAC->CHANNEL_SIF2;
	IOP->DMAC->CHANNELS[3] = IOP->DMAC->CHANNEL_CDROM;
	IOP->DMAC->CHANNELS[4] = IOP->DMAC->CHANNEL_SPU2c1;
	IOP->DMAC->CHANNELS[5] = IOP->DMAC->CHANNEL_PIO;
	IOP->DMAC->CHANNELS[6] = IOP->DMAC->CHANNEL_OTClear;
	IOP->DMAC->CHANNELS[7] = IOP->DMAC->CHANNEL_SPU2c2;
	IOP->DMAC->CHANNELS[8] = IOP->DMAC->CHANNEL_DEV9;
	IOP->DMAC->CHANNELS[9] = IOP->DMAC->CHANNEL_SIF0;
	IOP->DMAC->CHANNELS[10] = IOP->DMAC->CHANNEL_SIF1;
	IOP->DMAC->CHANNELS[11] = IOP->DMAC->CHANNEL_fromSIO2;
	IOP->DMAC->CHANNELS[12] = IOP->DMAC->CHANNEL_toSIO2;
}

void Resources_t::postInit_IOP() const
{
	// Initalise physical memory map of IOP.
	{
		// IOP Memory.
		{
			// Main Memory.
			IOP->PhysicalMMU->mapObject(Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY, IOP->MainMemory);

			// Various ROMs.
			IOP->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
			IOP->PhysicalMMU->mapObject(Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);

			// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation. TODO: related to cache control (this is probably very wrong), investigate.
			IOP->PhysicalMMU->mapObject(0xFFC00000, EE->BootROM);

			// Scratchpad Memory.
			IOP->PhysicalMMU->mapObject(Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, IOP->IOPCore->ScratchpadMemory);
		}

		// IOP Registers.
		{
			// Misc IOP Registers.
			IOP->PhysicalMMU->mapObject(0x1F801000, IOP->HW_SSBUS_SPD_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F801004, IOP->HW_SSBUS_PIO_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F801008, IOP->HW_SSBUS_SPD_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F80100C, IOP->HW_SSBUS_DEV1_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801010, IOP->HW_SSBUS_ROM_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801014, IOP->HW_SSBUS_SPU_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801018, IOP->HW_SSBUS_DEV5_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F80101C, IOP->HW_SSBUS_PIO_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801020, IOP->HW_SSBUS_COM_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801060, IOP->HW_RAM_SIZE);
			IOP->PhysicalMMU->mapObject(0x1F801400, IOP->HW_SSBUS_DEV1_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F801404, IOP->HW_SSBUS_SPU_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F801408, IOP->HW_SSBUS_DEV5_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F80140C, IOP->HW_SSBUS_SPU1_ADDR);
			IOP->PhysicalMMU->mapObject(0x1F801410, IOP->HW_SSBUS_DEV9_ADDR3);
			IOP->PhysicalMMU->mapObject(0x1F801414, IOP->HW_SSBUS_SPU1_DELAY);
			IOP->PhysicalMMU->mapObject(0x1F801418, IOP->HW_SSBUS_DEV9_DELAY2);
			IOP->PhysicalMMU->mapObject(0x1F80141C, IOP->HW_SSBUS_DEV9_DELAY3);
			IOP->PhysicalMMU->mapObject(0x1F801420, IOP->HW_SSBUS_DEV9_DELAY1);
			IOP->PhysicalMMU->mapObject(0x1F801450, IOP->HW_ICFG);
			IOP->PhysicalMMU->mapObject(0x1F801560, IOP->REGISTER_1560);
			IOP->PhysicalMMU->mapObject(0x1F801564, IOP->REGISTER_1564);
			IOP->PhysicalMMU->mapObject(0x1F801568, IOP->REGISTER_1568);
			IOP->PhysicalMMU->mapObject(0x1F8015F0, IOP->REGISTER_15F0);
			IOP->PhysicalMMU->mapObject(0x1F802070, IOP->REGISTER_2070);

			// DMAC Registers.
			IOP->PhysicalMMU->mapObject(0x1F801080, IOP->DMAC->CHANNEL_fromMDEC->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801084, IOP->DMAC->CHANNEL_fromMDEC->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801088, IOP->DMAC->CHANNEL_fromMDEC->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801090, IOP->DMAC->CHANNEL_toMDEC->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801094, IOP->DMAC->CHANNEL_toMDEC->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801098, IOP->DMAC->CHANNEL_toMDEC->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010A0, IOP->DMAC->CHANNEL_SIF2->MADR);
			IOP->PhysicalMMU->mapObject(0x1F8010A4, IOP->DMAC->CHANNEL_SIF2->BCR);
			IOP->PhysicalMMU->mapObject(0x1F8010A8, IOP->DMAC->CHANNEL_SIF2->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010B0, IOP->DMAC->CHANNEL_CDROM->MADR);
			IOP->PhysicalMMU->mapObject(0x1F8010B4, IOP->DMAC->CHANNEL_CDROM->BCR);
			IOP->PhysicalMMU->mapObject(0x1F8010B8, IOP->DMAC->CHANNEL_CDROM->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010C0, IOP->DMAC->CHANNEL_SPU2c1->MADR);
			IOP->PhysicalMMU->mapObject(0x1F8010C4, IOP->DMAC->CHANNEL_SPU2c1->BCR);
			IOP->PhysicalMMU->mapObject(0x1F8010C8, IOP->DMAC->CHANNEL_SPU2c1->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010CC, IOP->DMAC->CHANNEL_SPU2c1->TADR);
			IOP->PhysicalMMU->mapObject(0x1F8010D0, IOP->DMAC->CHANNEL_PIO->MADR);
			IOP->PhysicalMMU->mapObject(0x1F8010D4, IOP->DMAC->CHANNEL_PIO->BCR);
			IOP->PhysicalMMU->mapObject(0x1F8010D8, IOP->DMAC->CHANNEL_PIO->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010E0, IOP->DMAC->CHANNEL_OTClear->MADR);
			IOP->PhysicalMMU->mapObject(0x1F8010E4, IOP->DMAC->CHANNEL_OTClear->BCR);
			IOP->PhysicalMMU->mapObject(0x1F8010E8, IOP->DMAC->CHANNEL_OTClear->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801500, IOP->DMAC->CHANNEL_SPU2c2->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801504, IOP->DMAC->CHANNEL_SPU2c2->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801508, IOP->DMAC->CHANNEL_SPU2c2->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801510, IOP->DMAC->CHANNEL_DEV9->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801514, IOP->DMAC->CHANNEL_DEV9->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801518, IOP->DMAC->CHANNEL_DEV9->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801520, IOP->DMAC->CHANNEL_SIF0->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801524, IOP->DMAC->CHANNEL_SIF0->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801528, IOP->DMAC->CHANNEL_SIF0->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F80152C, IOP->DMAC->CHANNEL_SIF0->TADR);
			IOP->PhysicalMMU->mapObject(0x1F801530, IOP->DMAC->CHANNEL_SIF1->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801534, IOP->DMAC->CHANNEL_SIF1->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801538, IOP->DMAC->CHANNEL_SIF1->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801540, IOP->DMAC->CHANNEL_fromSIO2->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801544, IOP->DMAC->CHANNEL_fromSIO2->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801548, IOP->DMAC->CHANNEL_fromSIO2->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F801550, IOP->DMAC->CHANNEL_toSIO2->MADR);
			IOP->PhysicalMMU->mapObject(0x1F801554, IOP->DMAC->CHANNEL_toSIO2->BCR);
			IOP->PhysicalMMU->mapObject(0x1F801558, IOP->DMAC->CHANNEL_toSIO2->CHCR);
			IOP->PhysicalMMU->mapObject(0x1F8010F0, IOP->DMAC->PCR0);
			IOP->PhysicalMMU->mapObject(0x1F8010F4, IOP->DMAC->ICR0);
			IOP->PhysicalMMU->mapObject(0x1F801570, IOP->DMAC->PCR1);
			IOP->PhysicalMMU->mapObject(0x1F801574, IOP->DMAC->ICR1);
			IOP->PhysicalMMU->mapObject(0x1F801578, IOP->DMAC->GCTRL);

			// INTC Registers.
			IOP->PhysicalMMU->mapObject(0x1F801070, IOP->INTC->STAT);
			IOP->PhysicalMMU->mapObject(0x1F801074, IOP->INTC->MASK);
			IOP->PhysicalMMU->mapObject(0x1F801078, IOP->INTC->CTRL);

			// CDVD Registers.
			IOP->PhysicalMMU->mapObject(0x1F402004, IOP->CDVD->N_COMMAND);
			IOP->PhysicalMMU->mapObject(0x1F402005, IOP->CDVD->N_READY);
			IOP->PhysicalMMU->mapObject(0x1F402006, IOP->CDVD->ERROR);
			IOP->PhysicalMMU->mapObject(0x1F402007, IOP->CDVD->BREAK);
			IOP->PhysicalMMU->mapObject(0x1F402008, IOP->CDVD->STATUS);
			IOP->PhysicalMMU->mapObject(0x1F40200A, IOP->CDVD->STATUS); // Mirrored?
			IOP->PhysicalMMU->mapObject(0x1F40200B, IOP->CDVD->TRAY_STATE);
			IOP->PhysicalMMU->mapObject(0x1F40200C, IOP->CDVD->CRT_MINUTE);
			IOP->PhysicalMMU->mapObject(0x1F40200D, IOP->CDVD->CRT_SECOND);
			IOP->PhysicalMMU->mapObject(0x1F40200E, IOP->CDVD->CRT_FRAME);
			IOP->PhysicalMMU->mapObject(0x1F40200F, IOP->CDVD->TYPE);
			IOP->PhysicalMMU->mapObject(0x1F402013, IOP->CDVD->REGISTER_2013);
			IOP->PhysicalMMU->mapObject(0x1F402015, IOP->CDVD->RSV);
			IOP->PhysicalMMU->mapObject(0x1F402016, IOP->CDVD->S_COMMAND);
			IOP->PhysicalMMU->mapObject(0x1F402017, IOP->CDVD->S_READY);
			IOP->PhysicalMMU->mapObject(0x1F402018, IOP->CDVD->S_DATA_OUT);
			IOP->PhysicalMMU->mapObject(0x1F402020, IOP->CDVD->KEY_20);
			IOP->PhysicalMMU->mapObject(0x1F402021, IOP->CDVD->KEY_21);
			IOP->PhysicalMMU->mapObject(0x1F402022, IOP->CDVD->KEY_22);
			IOP->PhysicalMMU->mapObject(0x1F402023, IOP->CDVD->KEY_23);
			IOP->PhysicalMMU->mapObject(0x1F402024, IOP->CDVD->KEY_24);
			IOP->PhysicalMMU->mapObject(0x1F402028, IOP->CDVD->KEY_28);
			IOP->PhysicalMMU->mapObject(0x1F402029, IOP->CDVD->KEY_29);
			IOP->PhysicalMMU->mapObject(0x1F40202A, IOP->CDVD->KEY_2A);
			IOP->PhysicalMMU->mapObject(0x1F40202B, IOP->CDVD->KEY_2B);
			IOP->PhysicalMMU->mapObject(0x1F40202C, IOP->CDVD->KEY_2C);
			IOP->PhysicalMMU->mapObject(0x1F402030, IOP->CDVD->KEY_30);
			IOP->PhysicalMMU->mapObject(0x1F402031, IOP->CDVD->KEY_31);
			IOP->PhysicalMMU->mapObject(0x1F402032, IOP->CDVD->KEY_32);
			IOP->PhysicalMMU->mapObject(0x1F402033, IOP->CDVD->KEY_33);
			IOP->PhysicalMMU->mapObject(0x1F402034, IOP->CDVD->KEY_34);
			IOP->PhysicalMMU->mapObject(0x1F402038, IOP->CDVD->KEY_38);
			IOP->PhysicalMMU->mapObject(0x1F402039, IOP->CDVD->KEY_XOR);
			IOP->PhysicalMMU->mapObject(0x1F40203A, IOP->CDVD->DEC_SET);

			// SPU2 Registers.
			IOP->PhysicalMMU->mapObject(0x1F900000, IOP->SPU2->SPU2_REGISTERS);
			IOP->PhysicalMMU->mapObject(0x1F900800, IOP->SPU2->SPU2_REGISTERS); // Mirrored? See "spu2sys.cpp" in PCSX2.

			// Timers Registers.
			IOP->PhysicalMMU->mapObject(0x1F801100, IOP->Timers->TIMER_0->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F801104, IOP->Timers->TIMER_0->MODE);
			IOP->PhysicalMMU->mapObject(0x1F801108, IOP->Timers->TIMER_0->COMP);
			IOP->PhysicalMMU->mapObject(0x1F801110, IOP->Timers->TIMER_1->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F801114, IOP->Timers->TIMER_1->MODE);
			IOP->PhysicalMMU->mapObject(0x1F801118, IOP->Timers->TIMER_1->COMP);
			IOP->PhysicalMMU->mapObject(0x1F801120, IOP->Timers->TIMER_2->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F801124, IOP->Timers->TIMER_2->MODE);
			IOP->PhysicalMMU->mapObject(0x1F801128, IOP->Timers->TIMER_2->COMP);
			IOP->PhysicalMMU->mapObject(0x1F801480, IOP->Timers->TIMER_3->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F801484, IOP->Timers->TIMER_3->MODE);
			IOP->PhysicalMMU->mapObject(0x1F801488, IOP->Timers->TIMER_3->COMP);
			IOP->PhysicalMMU->mapObject(0x1F801490, IOP->Timers->TIMER_4->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F801494, IOP->Timers->TIMER_4->MODE);
			IOP->PhysicalMMU->mapObject(0x1F801498, IOP->Timers->TIMER_4->COMP);
			IOP->PhysicalMMU->mapObject(0x1F8014A0, IOP->Timers->TIMER_5->COUNT);
			IOP->PhysicalMMU->mapObject(0x1F8014A4, IOP->Timers->TIMER_5->MODE);
			IOP->PhysicalMMU->mapObject(0x1F8014A8, IOP->Timers->TIMER_5->COMP);

			// Parallel Port.
			IOP->PhysicalMMU->mapObject(Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT, IOP->ParallelPort);
		}

		// SIF Registers
		{
			IOP->PhysicalMMU->mapObject(0x1D000000, Common->SBUS_MSCOM);
			IOP->PhysicalMMU->mapObject(0x1D000010, Common->SBUS_SMCOM);
			IOP->PhysicalMMU->mapObject(0x1D000020, Common->SBUS_MSFLG);
			IOP->PhysicalMMU->mapObject(0x1D000030, Common->SBUS_SMFLG);
			IOP->PhysicalMMU->mapObject(0x1D000040, Common->SBUS_F240);
			IOP->PhysicalMMU->mapObject(0x1D000060, Common->SBUS_F260);
		}
	}
}
