#include "stdafx.h"

#include <memory>

#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/Register/MapperRegister16Register32_t.h"
#include "Common/Types/Register/PCRegister16_t.h"
#include "Common/Types/Register/ConstantRegister8_t.h"
#include "Common/Types/Register/ConstantRegister32_t.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/ROByteMemory_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"

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
#include "Resources/EE/VPU/VIF/Types/VIFCores_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFCoreRegisters_t.h"
#include "Resources/EE/VPU/VU/VU_t.h"
#include "Resources/EE/VPU/VU/Types/VUCores_t.h"
#include "Resources/EE/VPU/VU/Types/VURegisters_t.h"
#include "Resources/EE/VPU/VU/Types/VUCoreRegisters_t.h"

#include "Resources/IOP/IOPCore/IOPCore_t.h"
#include "Resources/IOP/DMAC/IOPDmac_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacRegisters_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "Resources/IOP/DMAC/Types/IOPDmacChannelRegisters_t.h"
#include "Resources/IOP/CDVD/CDVD_t.h"
#include "Resources/IOP/SPU2/SPU2_t.h"
#include "Resources/IOP/SPU2/Types/SPU2Cores_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/IOP/SPU2/Types/SPU2CoreVoiceRegisters_t.h"
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
		EE->VPU->VU->VU0 = std::make_shared<VUCore_VU0_t>(EE->EECore->COP0);
		EE->VPU->VU->VU0->CCR[0] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[0]);
		EE->VPU->VU->VU0->CCR[1] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[1]);
		EE->VPU->VU->VU0->CCR[2] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[2]);
		EE->VPU->VU->VU0->CCR[3] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[3]);
		EE->VPU->VU->VU0->CCR[4] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[4]);
		EE->VPU->VU->VU0->CCR[5] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[5]);
		EE->VPU->VU->VU0->CCR[6] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[6]);
		EE->VPU->VU->VU0->CCR[7] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[7]);
		EE->VPU->VU->VU0->CCR[8] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[8]);
		EE->VPU->VU->VU0->CCR[9] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[9]);
		EE->VPU->VU->VU0->CCR[10] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[10]);
		EE->VPU->VU->VU0->CCR[11] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[11]);
		EE->VPU->VU->VU0->CCR[12] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[12]);
		EE->VPU->VU->VU0->CCR[13] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[13]);
		EE->VPU->VU->VU0->CCR[14] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[14]);
		EE->VPU->VU->VU0->CCR[15] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->VI[15]);
		EE->VPU->VU->VU0->CCR[16] = EE->VPU->VU->VU0->Status;
		EE->VPU->VU->VU0->CCR[17] = EE->VPU->VU->VU0->MAC;
		EE->VPU->VU->VU0->CCR[18] = EE->VPU->VU->VU0->Clipping;
		EE->VPU->VU->VU0->CCR[19] = nullptr;
		EE->VPU->VU->VU0->CCR[20] = EE->VPU->VU->VU0->R;
		EE->VPU->VU->VU0->CCR[21] = EE->VPU->VU->VU0->I;
		EE->VPU->VU->VU0->CCR[22] = EE->VPU->VU->VU0->Q;
		EE->VPU->VU->VU0->CCR[23] = nullptr;
		EE->VPU->VU->VU0->CCR[24] = nullptr;
		EE->VPU->VU->VU0->CCR[25] = nullptr;
		EE->VPU->VU->VU0->CCR[26] = std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU0->PC); // TPC.
		EE->VPU->VU->VU0->CCR[27] = EE->VPU->VU->VU0->CMSAR;
		EE->VPU->VU->VU0->CCR[28] = EE->VPU->VU->FBRST;
		EE->VPU->VU->VU0->CCR[29] = EE->VPU->STAT;
		EE->VPU->VU->VU0->CCR[30] = nullptr;
		EE->VPU->VU->VU0->CCR[31] = EE->VPU->VU->VU1->CMSAR;
	}

	// Initalise VU units array.
	{
		EE->VPU->VU->VU_CORES[0] = EE->VPU->VU->VU0;
		EE->VPU->VU->VU_CORES[1] = EE->VPU->VU->VU1;
	}

	// Initalise VU0 and VU1 physical memory map.
	{
		// VU0 Memory.
		EE->VPU->VU->VU0->MMU->mapObject(0x0000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MMU->mapObject(0x1000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MMU->mapObject(0x2000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MMU->mapObject(0x3000, EE->VPU->VU->VU0->MEMORY_Mem);

		// VU1.VF Registers, see VU Users Manual page 222. 
		for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
			EE->VPU->VU->VU0->MMU->mapObject(0x4000 + i * Constants::NUMBER_BYTES_IN_QWORD, EE->VPU->VU->VU1->VF[i]);

		// VU1.VI Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded! 
		// NOT mapped as the true register size of 16-bit (need to do a Register32_t wrapping)! 
		// See EE Users Manual page 84.
		for (auto i = 0; i < Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
			EE->VPU->VU->VU0->MMU->mapObject(0x4200 + i * Constants::NUMBER_BYTES_IN_QWORD, std::make_shared<MapperRegister16Register32_t>("N/A", false, false, EE->VPU->VU->VU1->VI[i]));

		// Misc Registers.
		EE->VPU->VU->VU0->MMU->mapObject(0x4300, EE->VPU->VU->VU1->Status);
		EE->VPU->VU->VU0->MMU->mapObject(0x4310, EE->VPU->VU->VU1->MAC);
		EE->VPU->VU->VU0->MMU->mapObject(0x4320, EE->VPU->VU->VU1->Clipping);
		EE->VPU->VU->VU0->MMU->mapObject(0x4340, EE->VPU->VU->VU1->R);
		EE->VPU->VU->VU0->MMU->mapObject(0x4350, EE->VPU->VU->VU1->I);
		EE->VPU->VU->VU0->MMU->mapObject(0x4360, EE->VPU->VU->VU1->Q);
		EE->VPU->VU->VU0->MMU->mapObject(0x4370, EE->VPU->VU->VU1->P);
		EE->VPU->VU->VU0->MMU->mapObject(0x43A0, EE->VPU->VU->VU1->PC); // TPC.

		// VU1 Memory.
		EE->VPU->VU->VU1->MMU->mapObject(0x0000, EE->VPU->VU->VU1->MEMORY_Mem);
	}
}

void Resources_t::postInit_EE() const
{
	// Initalise physical memory map of EE.
	{
		// EE Memory.
		{
			// Main Memory.
			EE->MMU->mapObject(Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY, EE->MainMemory);

			// Scratchpad Memory.
			EE->MMU->mapObject(Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, EE->EECore->ScratchpadMemory);

			// Various ROMs.
			EE->MMU->mapObject(Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
			EE->MMU->mapObject(Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);
			EE->MMU->mapObject(Constants::EE::ROM::PADDRESS_EROM, EE->EROM);
			EE->MMU->mapObject(Constants::EE::ROM::PADDRESS_ROM2, EE->ROM2);

			// Unknown memory.
			EE->MMU->mapObject(0x1A000000, EE->UNKNOWN_1A000000);
		}

		// EE Registers.
		{
			// MISC EE registers.
			EE->MMU->mapObject(0x1000F100, EE->MEMORY_SIO);
			EE->MMU->mapObject(0x1000f400, EE->REGISTER_F400);
			EE->MMU->mapObject(0x1000f410, EE->MEMORY_F410);
			EE->MMU->mapObject(0x1000f420, EE->REGISTER_F420);
			EE->MMU->mapObject(0x1000F430, EE->MEMORY_MCH);
			EE->MMU->mapObject(0x1000f450, EE->MEMORY_F450);

			// Timers Registers.
			EE->MMU->mapObject(0x10000000, EE->Timers->TIMER_0->COUNT);
			EE->MMU->mapObject(0x10000010, EE->Timers->TIMER_0->MODE);
			EE->MMU->mapObject(0x10000020, EE->Timers->TIMER_0->COMP);
			EE->MMU->mapObject(0x10000030, EE->Timers->TIMER_0->HOLD);
			EE->MMU->mapObject(0x10000800, EE->Timers->TIMER_1->COUNT);
			EE->MMU->mapObject(0x10000810, EE->Timers->TIMER_1->MODE);
			EE->MMU->mapObject(0x10000820, EE->Timers->TIMER_1->COMP);
			EE->MMU->mapObject(0x10000830, EE->Timers->TIMER_1->HOLD);
			EE->MMU->mapObject(0x10001000, EE->Timers->TIMER_2->COUNT);
			EE->MMU->mapObject(0x10001010, EE->Timers->TIMER_2->MODE);
			EE->MMU->mapObject(0x10001020, EE->Timers->TIMER_2->COMP);
			EE->MMU->mapObject(0x10001800, EE->Timers->TIMER_3->COUNT);
			EE->MMU->mapObject(0x10001810, EE->Timers->TIMER_3->MODE);
			EE->MMU->mapObject(0x10001820, EE->Timers->TIMER_3->COMP);

			// IPU Registers.
			EE->MMU->mapObject(0x10002000, EE->IPU->CMD);
			EE->MMU->mapObject(0x10002010, EE->IPU->CTRL);
			EE->MMU->mapObject(0x10002020, EE->IPU->BP);
			EE->MMU->mapObject(0x10002030, EE->IPU->TOP);

			// GIF Registers.
			EE->MMU->mapObject(0x10003000, EE->GIF->CTRL);
			EE->MMU->mapObject(0x10003010, EE->GIF->MODE);
			EE->MMU->mapObject(0x10003020, EE->GIF->STAT);
			EE->MMU->mapObject(0x10003040, EE->GIF->TAG0);
			EE->MMU->mapObject(0x10003050, EE->GIF->TAG1);
			EE->MMU->mapObject(0x10003060, EE->GIF->TAG2);
			EE->MMU->mapObject(0x10003070, EE->GIF->TAG3);
			EE->MMU->mapObject(0x10003080, EE->GIF->CNT);
			EE->MMU->mapObject(0x10003090, EE->GIF->P3CNT);
			EE->MMU->mapObject(0x100030a0, EE->GIF->P3TAG);

			// VIF0 Registers.
			EE->MMU->mapObject(0x10003800, EE->VPU->VIF->VIF0->STAT);
			EE->MMU->mapObject(0x10003810, EE->VPU->VIF->VIF0->FBRST);
			EE->MMU->mapObject(0x10003820, EE->VPU->VIF->VIF0->ERR);
			EE->MMU->mapObject(0x10003830, EE->VPU->VIF->VIF0->MARK);
			EE->MMU->mapObject(0x10003840, EE->VPU->VIF->VIF0->CYCLE);
			EE->MMU->mapObject(0x10003850, EE->VPU->VIF->VIF0->MODE);
			EE->MMU->mapObject(0x10003860, EE->VPU->VIF->VIF0->NUM);
			EE->MMU->mapObject(0x10003870, EE->VPU->VIF->VIF0->MASK);
			EE->MMU->mapObject(0x10003880, EE->VPU->VIF->VIF0->CODE);
			EE->MMU->mapObject(0x10003890, EE->VPU->VIF->VIF0->ITOPS);
			EE->MMU->mapObject(0x100038d0, EE->VPU->VIF->VIF0->ITOP);
			EE->MMU->mapObject(0x10003900, EE->VPU->VIF->VIF0->R0);
			EE->MMU->mapObject(0x10003910, EE->VPU->VIF->VIF0->R1);
			EE->MMU->mapObject(0x10003920, EE->VPU->VIF->VIF0->R2);
			EE->MMU->mapObject(0x10003930, EE->VPU->VIF->VIF0->R3);
			EE->MMU->mapObject(0x10003940, EE->VPU->VIF->VIF0->C0);
			EE->MMU->mapObject(0x10003950, EE->VPU->VIF->VIF0->C1);
			EE->MMU->mapObject(0x10003960, EE->VPU->VIF->VIF0->C2);
			EE->MMU->mapObject(0x10003970, EE->VPU->VIF->VIF0->C3);

			// VIF1 Registers.
			EE->MMU->mapObject(0x10003c00, EE->VPU->VIF->VIF1->STAT);
			EE->MMU->mapObject(0x10003c10, EE->VPU->VIF->VIF1->FBRST);
			EE->MMU->mapObject(0x10003c20, EE->VPU->VIF->VIF1->ERR);
			EE->MMU->mapObject(0x10003c30, EE->VPU->VIF->VIF1->MARK);
			EE->MMU->mapObject(0x10003c40, EE->VPU->VIF->VIF1->CYCLE);
			EE->MMU->mapObject(0x10003c50, EE->VPU->VIF->VIF1->MODE);
			EE->MMU->mapObject(0x10003c60, EE->VPU->VIF->VIF1->NUM);
			EE->MMU->mapObject(0x10003c70, EE->VPU->VIF->VIF1->MASK);
			EE->MMU->mapObject(0x10003c80, EE->VPU->VIF->VIF1->CODE);
			EE->MMU->mapObject(0x10003c90, EE->VPU->VIF->VIF1->ITOPS);
			EE->MMU->mapObject(0x10003ca0, EE->VPU->VIF->VIF1->BASE);
			EE->MMU->mapObject(0x10003cb0, EE->VPU->VIF->VIF1->OFST);
			EE->MMU->mapObject(0x10003cc0, EE->VPU->VIF->VIF1->TOPS);
			EE->MMU->mapObject(0x10003cd0, EE->VPU->VIF->VIF1->ITOP);
			EE->MMU->mapObject(0x10003ce0, EE->VPU->VIF->VIF1->TOP);
			EE->MMU->mapObject(0x10003d00, EE->VPU->VIF->VIF1->R0);
			EE->MMU->mapObject(0x10003d10, EE->VPU->VIF->VIF1->R1);
			EE->MMU->mapObject(0x10003d20, EE->VPU->VIF->VIF1->R2);
			EE->MMU->mapObject(0x10003d30, EE->VPU->VIF->VIF1->R3);
			EE->MMU->mapObject(0x10003d40, EE->VPU->VIF->VIF1->C0);
			EE->MMU->mapObject(0x10003d50, EE->VPU->VIF->VIF1->C1);
			EE->MMU->mapObject(0x10003d60, EE->VPU->VIF->VIF1->C2);
			EE->MMU->mapObject(0x10003d70, EE->VPU->VIF->VIF1->C3);

			// FIFO Registers.
			EE->MMU->mapObject(0x10004000, Common->FIFO_VIF0);
			EE->MMU->mapObject(0x10005000, Common->FIFO_VIF1);
			EE->MMU->mapObject(0x10006000, Common->FIFO_GIF);
			EE->MMU->mapObject(0x10007000, Common->FIFO_fromIPU);
			EE->MMU->mapObject(0x10007010, Common->FIFO_toIPU);

			// DMAC registers.
			EE->MMU->mapObject(0x10008000, EE->DMAC->CHANNEL_VIF0->CHCR);
			EE->MMU->mapObject(0x10008010, EE->DMAC->CHANNEL_VIF0->MADR);
			EE->MMU->mapObject(0x10008020, EE->DMAC->CHANNEL_VIF0->QWC);
			EE->MMU->mapObject(0x10008030, EE->DMAC->CHANNEL_VIF0->TADR);
			EE->MMU->mapObject(0x10008040, EE->DMAC->CHANNEL_VIF0->ASR0);
			EE->MMU->mapObject(0x10008050, EE->DMAC->CHANNEL_VIF0->ASR1);
			EE->MMU->mapObject(0x10008060, EE->DMAC->CHANNEL_VIF0->MEMORY_8060);
			EE->MMU->mapObject(0x10009000, EE->DMAC->CHANNEL_VIF1->CHCR);
			EE->MMU->mapObject(0x10009010, EE->DMAC->CHANNEL_VIF1->MADR);
			EE->MMU->mapObject(0x10009020, EE->DMAC->CHANNEL_VIF1->QWC);
			EE->MMU->mapObject(0x10009030, EE->DMAC->CHANNEL_VIF1->TADR);
			EE->MMU->mapObject(0x10009040, EE->DMAC->CHANNEL_VIF1->ASR0);
			EE->MMU->mapObject(0x10009050, EE->DMAC->CHANNEL_VIF1->ASR1);
			EE->MMU->mapObject(0x10009060, EE->DMAC->CHANNEL_VIF1->MEMORY_9060);
			EE->MMU->mapObject(0x1000a000, EE->DMAC->CHANNEL_GIF->CHCR);
			EE->MMU->mapObject(0x1000a010, EE->DMAC->CHANNEL_GIF->MADR);
			EE->MMU->mapObject(0x1000a020, EE->DMAC->CHANNEL_GIF->QWC);
			EE->MMU->mapObject(0x1000a030, EE->DMAC->CHANNEL_GIF->TADR);
			EE->MMU->mapObject(0x1000a040, EE->DMAC->CHANNEL_GIF->ASR0);
			EE->MMU->mapObject(0x1000a050, EE->DMAC->CHANNEL_GIF->ASR1);
			EE->MMU->mapObject(0x1000a060, EE->DMAC->CHANNEL_GIF->MEMORY_A060);
			EE->MMU->mapObject(0x1000b000, EE->DMAC->CHANNEL_fromIPU->CHCR);
			EE->MMU->mapObject(0x1000b010, EE->DMAC->CHANNEL_fromIPU->MADR);
			EE->MMU->mapObject(0x1000b020, EE->DMAC->CHANNEL_fromIPU->QWC);
			EE->MMU->mapObject(0x1000b030, EE->DMAC->CHANNEL_fromIPU->MEMORY_B030);
			EE->MMU->mapObject(0x1000b400, EE->DMAC->CHANNEL_toIPU->CHCR);
			EE->MMU->mapObject(0x1000b410, EE->DMAC->CHANNEL_toIPU->MADR);
			EE->MMU->mapObject(0x1000b420, EE->DMAC->CHANNEL_toIPU->QWC);
			EE->MMU->mapObject(0x1000b430, EE->DMAC->CHANNEL_toIPU->TADR);
			EE->MMU->mapObject(0x1000b440, EE->DMAC->CHANNEL_toIPU->MEMORY_B440);
			EE->MMU->mapObject(0x1000c000, EE->DMAC->CHANNEL_SIF0->CHCR);
			EE->MMU->mapObject(0x1000c010, EE->DMAC->CHANNEL_SIF0->MADR);
			EE->MMU->mapObject(0x1000c020, EE->DMAC->CHANNEL_SIF0->QWC);
			EE->MMU->mapObject(0x1000c030, EE->DMAC->CHANNEL_SIF0->MEMORY_C030);
			EE->MMU->mapObject(0x1000c400, EE->DMAC->CHANNEL_SIF1->CHCR);
			EE->MMU->mapObject(0x1000c410, EE->DMAC->CHANNEL_SIF1->MADR);
			EE->MMU->mapObject(0x1000c420, EE->DMAC->CHANNEL_SIF1->QWC);
			EE->MMU->mapObject(0x1000c430, EE->DMAC->CHANNEL_SIF1->TADR);
			EE->MMU->mapObject(0x1000c440, EE->DMAC->CHANNEL_SIF1->MEMORY_C440);
			EE->MMU->mapObject(0x1000c800, EE->DMAC->CHANNEL_SIF2->CHCR);
			EE->MMU->mapObject(0x1000c810, EE->DMAC->CHANNEL_SIF2->MADR);
			EE->MMU->mapObject(0x1000c820, EE->DMAC->CHANNEL_SIF2->QWC);
			EE->MMU->mapObject(0x1000c830, EE->DMAC->CHANNEL_SIF2->MEMORY_C830);
			EE->MMU->mapObject(0x1000d000, EE->DMAC->CHANNEL_fromSPR->CHCR);
			EE->MMU->mapObject(0x1000d010, EE->DMAC->CHANNEL_fromSPR->MADR);
			EE->MMU->mapObject(0x1000d020, EE->DMAC->CHANNEL_fromSPR->QWC);
			EE->MMU->mapObject(0x1000d030, EE->DMAC->CHANNEL_fromSPR->MEMORY_D030);
			EE->MMU->mapObject(0x1000d080, EE->DMAC->CHANNEL_fromSPR->SADR);
			EE->MMU->mapObject(0x1000d090, EE->DMAC->CHANNEL_fromSPR->MEMORY_D090);
			EE->MMU->mapObject(0x1000d400, EE->DMAC->CHANNEL_toSPR->CHCR);
			EE->MMU->mapObject(0x1000d410, EE->DMAC->CHANNEL_toSPR->MADR);
			EE->MMU->mapObject(0x1000d420, EE->DMAC->CHANNEL_toSPR->QWC);
			EE->MMU->mapObject(0x1000d430, EE->DMAC->CHANNEL_toSPR->TADR);
			EE->MMU->mapObject(0x1000d440, EE->DMAC->CHANNEL_toSPR->MEMORY_D440);
			EE->MMU->mapObject(0x1000d480, EE->DMAC->CHANNEL_toSPR->SADR);
			EE->MMU->mapObject(0x1000d490, EE->DMAC->CHANNEL_toSPR->MEMORY_D490);
			EE->MMU->mapObject(0x1000e000, EE->DMAC->CTRL);
			EE->MMU->mapObject(0x1000e010, EE->DMAC->STAT);
			EE->MMU->mapObject(0x1000e020, EE->DMAC->PCR);
			EE->MMU->mapObject(0x1000e030, EE->DMAC->SQWC);
			EE->MMU->mapObject(0x1000e040, EE->DMAC->RBSR);
			EE->MMU->mapObject(0x1000e050, EE->DMAC->RBOR);
			EE->MMU->mapObject(0x1000e060, EE->DMAC->STADR);

			// INTC registers.
			EE->MMU->mapObject(0x1000f000, EE->INTC->STAT);
			EE->MMU->mapObject(0x1000f010, EE->INTC->MASK);

			// DMAC registers (extended).
			EE->MMU->mapObject(0x1000f500, EE->DMAC->MEMORY_F500);
			EE->MMU->mapObject(0x1000f520, EE->DMAC->ENABLER);
			EE->MMU->mapObject(0x1000f590, EE->DMAC->ENABLEW);
		}

		// VU0/1 Memory.
		{
			EE->MMU->mapObject(0x11000000, EE->VPU->VU->VU0->MEMORY_Micro);
			EE->MMU->mapObject(0x11004000, EE->VPU->VU->VU0->MEMORY_Mem);
			EE->MMU->mapObject(0x11008000, EE->VPU->VU->VU1->MEMORY_Micro);
			EE->MMU->mapObject(0x1100c000, EE->VPU->VU->VU1->MEMORY_Mem);
		}

		// GS Privileged Registers.
		{
			EE->MMU->mapObject(0x12000000, GS->PMODE);
			EE->MMU->mapObject(0x12000010, GS->SMODE1);
			EE->MMU->mapObject(0x12000020, GS->SMODE2);
			EE->MMU->mapObject(0x12000030, GS->SRFSH);
			EE->MMU->mapObject(0x12000040, GS->SYNCH1);
			EE->MMU->mapObject(0x12000050, GS->SYNCH2);
			EE->MMU->mapObject(0x12000060, GS->SYNCV);
			EE->MMU->mapObject(0x12000070, GS->DISPFB1);
			EE->MMU->mapObject(0x12000080, GS->DISPLAY1);
			EE->MMU->mapObject(0x12000090, GS->DISPFB2);
			EE->MMU->mapObject(0x120000a0, GS->DISPLAY2);
			EE->MMU->mapObject(0x120000b0, GS->EXTBUF);
			EE->MMU->mapObject(0x120000c0, GS->EXTDATA);
			EE->MMU->mapObject(0x120000d0, GS->EXTWRITE);
			EE->MMU->mapObject(0x120000e0, GS->BGCOLOR);

			EE->MMU->mapObject(0x12001000, GS->CSR);
			EE->MMU->mapObject(0x12001010, GS->IMR);
			EE->MMU->mapObject(0x12001040, GS->BUSDIR);
			EE->MMU->mapObject(0x12001080, GS->SIGLBLID);
		}

		// IOP Mirrors.
		{
			// Misc IOP Registers.
			EE->MMU->mapObject(0x1F80141C, IOP->HW_SSBUS_DEV9_DELAY3);
			EE->MMU->mapObject(0x1F801470, IOP->REGISTER_1470);
			EE->MMU->mapObject(0x1F803800, IOP->REGISTER_3800);

			// Main Memory.
			EE->MMU->mapObject(0x1C000000, IOP->MainMemory);
		}

		// SIF Registers.
		{
			EE->MMU->mapObject(0x1000F200, Common->SBUS_MSCOM);
			EE->MMU->mapObject(0x1000F210, Common->SBUS_SMCOM);
			EE->MMU->mapObject(0x1000F220, Common->SBUS_MSFLG);
			EE->MMU->mapObject(0x1000F230, Common->SBUS_SMFLG);
			EE->MMU->mapObject(0x1000F240, Common->SBUS_F240);
			EE->MMU->mapObject(0x1000F250, Common->SBUS_F250);
			EE->MMU->mapObject(0x1000F260, Common->SBUS_F260);
			EE->MMU->mapObject(0x1000F300, Common->SBUS_F300);
			EE->MMU->mapObject(0x1000F380, Common->SBUS_F380);
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
			IOP->MMU->mapObject(Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY, IOP->MainMemory);

			// Various ROMs.
			IOP->MMU->mapObject(Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
			IOP->MMU->mapObject(Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);

			// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation. TODO: related to cache control (this is probably very wrong), investigate.
			IOP->MMU->mapObject(0xFFC00000, EE->BootROM);

			// Scratchpad Memory.
			IOP->MMU->mapObject(Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, IOP->IOPCore->ScratchpadMemory);
		}

		// IOP Registers.
		{
			// Misc IOP Registers.
			IOP->MMU->mapObject(0x1F801000, IOP->HW_SSBUS_SPD_ADDR);
			IOP->MMU->mapObject(0x1F801004, IOP->HW_SSBUS_PIO_ADDR);
			IOP->MMU->mapObject(0x1F801008, IOP->HW_SSBUS_SPD_DELAY);
			IOP->MMU->mapObject(0x1F80100C, IOP->HW_SSBUS_DEV1_DELAY);
			IOP->MMU->mapObject(0x1F801010, IOP->HW_SSBUS_ROM_DELAY);
			IOP->MMU->mapObject(0x1F801014, IOP->HW_SSBUS_SPU_DELAY);
			IOP->MMU->mapObject(0x1F801018, IOP->HW_SSBUS_DEV5_DELAY);
			IOP->MMU->mapObject(0x1F80101C, IOP->HW_SSBUS_PIO_DELAY);
			IOP->MMU->mapObject(0x1F801020, IOP->HW_SSBUS_COM_DELAY);
			IOP->MMU->mapObject(0x1F801060, IOP->HW_RAM_SIZE);
			IOP->MMU->mapObject(0x1F801400, IOP->HW_SSBUS_DEV1_ADDR);
			IOP->MMU->mapObject(0x1F801404, IOP->HW_SSBUS_SPU_ADDR);
			IOP->MMU->mapObject(0x1F801408, IOP->HW_SSBUS_DEV5_ADDR);
			IOP->MMU->mapObject(0x1F80140C, IOP->HW_SSBUS_SPU1_ADDR);
			IOP->MMU->mapObject(0x1F801410, IOP->HW_SSBUS_DEV9_ADDR3);
			IOP->MMU->mapObject(0x1F801414, IOP->HW_SSBUS_SPU1_DELAY);
			IOP->MMU->mapObject(0x1F801418, IOP->HW_SSBUS_DEV9_DELAY2);
			IOP->MMU->mapObject(0x1F80141C, IOP->HW_SSBUS_DEV9_DELAY3);
			IOP->MMU->mapObject(0x1F801420, IOP->HW_SSBUS_DEV9_DELAY1);
			IOP->MMU->mapObject(0x1F801450, IOP->HW_ICFG);
			IOP->MMU->mapObject(0x1F801560, IOP->REGISTER_1560);
			IOP->MMU->mapObject(0x1F801564, IOP->REGISTER_1564);
			IOP->MMU->mapObject(0x1F801568, IOP->REGISTER_1568);
			IOP->MMU->mapObject(0x1F8015F0, IOP->REGISTER_15F0);
			IOP->MMU->mapObject(0x1F802070, IOP->REGISTER_2070);

			// DMAC Registers.
			IOP->MMU->mapObject(0x1F801080, IOP->DMAC->CHANNEL_fromMDEC->MADR);
			IOP->MMU->mapObject(0x1F801084, IOP->DMAC->CHANNEL_fromMDEC->BCR);
			IOP->MMU->mapObject(0x1F801088, IOP->DMAC->CHANNEL_fromMDEC->CHCR);
			IOP->MMU->mapObject(0x1F801090, IOP->DMAC->CHANNEL_toMDEC->MADR);
			IOP->MMU->mapObject(0x1F801094, IOP->DMAC->CHANNEL_toMDEC->BCR);
			IOP->MMU->mapObject(0x1F801098, IOP->DMAC->CHANNEL_toMDEC->CHCR);
			IOP->MMU->mapObject(0x1F8010A0, IOP->DMAC->CHANNEL_SIF2->MADR);
			IOP->MMU->mapObject(0x1F8010A4, IOP->DMAC->CHANNEL_SIF2->BCR);
			IOP->MMU->mapObject(0x1F8010A8, IOP->DMAC->CHANNEL_SIF2->CHCR);
			IOP->MMU->mapObject(0x1F8010B0, IOP->DMAC->CHANNEL_CDROM->MADR);
			IOP->MMU->mapObject(0x1F8010B4, IOP->DMAC->CHANNEL_CDROM->BCR);
			IOP->MMU->mapObject(0x1F8010B8, IOP->DMAC->CHANNEL_CDROM->CHCR);
			IOP->MMU->mapObject(0x1F8010C0, IOP->DMAC->CHANNEL_SPU2c1->MADR);
			IOP->MMU->mapObject(0x1F8010C4, IOP->DMAC->CHANNEL_SPU2c1->BCR);
			IOP->MMU->mapObject(0x1F8010C8, IOP->DMAC->CHANNEL_SPU2c1->CHCR);
			IOP->MMU->mapObject(0x1F8010CC, IOP->DMAC->CHANNEL_SPU2c1->TADR);
			IOP->MMU->mapObject(0x1F8010D0, IOP->DMAC->CHANNEL_PIO->MADR);
			IOP->MMU->mapObject(0x1F8010D4, IOP->DMAC->CHANNEL_PIO->BCR);
			IOP->MMU->mapObject(0x1F8010D8, IOP->DMAC->CHANNEL_PIO->CHCR);
			IOP->MMU->mapObject(0x1F8010E0, IOP->DMAC->CHANNEL_OTClear->MADR);
			IOP->MMU->mapObject(0x1F8010E4, IOP->DMAC->CHANNEL_OTClear->BCR);
			IOP->MMU->mapObject(0x1F8010E8, IOP->DMAC->CHANNEL_OTClear->CHCR);
			IOP->MMU->mapObject(0x1F801500, IOP->DMAC->CHANNEL_SPU2c2->MADR);
			IOP->MMU->mapObject(0x1F801504, IOP->DMAC->CHANNEL_SPU2c2->BCR);
			IOP->MMU->mapObject(0x1F801508, IOP->DMAC->CHANNEL_SPU2c2->CHCR);
			IOP->MMU->mapObject(0x1F801510, IOP->DMAC->CHANNEL_DEV9->MADR);
			IOP->MMU->mapObject(0x1F801514, IOP->DMAC->CHANNEL_DEV9->BCR);
			IOP->MMU->mapObject(0x1F801518, IOP->DMAC->CHANNEL_DEV9->CHCR);
			IOP->MMU->mapObject(0x1F801520, IOP->DMAC->CHANNEL_SIF0->MADR);
			IOP->MMU->mapObject(0x1F801524, IOP->DMAC->CHANNEL_SIF0->BCR);
			IOP->MMU->mapObject(0x1F801528, IOP->DMAC->CHANNEL_SIF0->CHCR);
			IOP->MMU->mapObject(0x1F80152C, IOP->DMAC->CHANNEL_SIF0->TADR);
			IOP->MMU->mapObject(0x1F801530, IOP->DMAC->CHANNEL_SIF1->MADR);
			IOP->MMU->mapObject(0x1F801534, IOP->DMAC->CHANNEL_SIF1->BCR);
			IOP->MMU->mapObject(0x1F801538, IOP->DMAC->CHANNEL_SIF1->CHCR);
			IOP->MMU->mapObject(0x1F801540, IOP->DMAC->CHANNEL_fromSIO2->MADR);
			IOP->MMU->mapObject(0x1F801544, IOP->DMAC->CHANNEL_fromSIO2->BCR);
			IOP->MMU->mapObject(0x1F801548, IOP->DMAC->CHANNEL_fromSIO2->CHCR);
			IOP->MMU->mapObject(0x1F801550, IOP->DMAC->CHANNEL_toSIO2->MADR);
			IOP->MMU->mapObject(0x1F801554, IOP->DMAC->CHANNEL_toSIO2->BCR);
			IOP->MMU->mapObject(0x1F801558, IOP->DMAC->CHANNEL_toSIO2->CHCR);
			IOP->MMU->mapObject(0x1F8010F0, IOP->DMAC->PCR0);
			IOP->MMU->mapObject(0x1F8010F4, IOP->DMAC->ICR0);
			IOP->MMU->mapObject(0x1F801570, IOP->DMAC->PCR1);
			IOP->MMU->mapObject(0x1F801574, IOP->DMAC->ICR1);
			IOP->MMU->mapObject(0x1F801578, IOP->DMAC->GCTRL);

			// INTC Registers.
			IOP->MMU->mapObject(0x1F801070, IOP->INTC->STAT);
			IOP->MMU->mapObject(0x1F801074, IOP->INTC->MASK);
			IOP->MMU->mapObject(0x1F801078, IOP->INTC->CTRL);

			// CDVD Registers.
			IOP->MMU->mapObject(0x1F402004, IOP->CDVD->N_COMMAND);
			IOP->MMU->mapObject(0x1F402005, IOP->CDVD->N_READY);
			IOP->MMU->mapObject(0x1F402006, IOP->CDVD->ERROR);
			IOP->MMU->mapObject(0x1F402007, IOP->CDVD->BREAK);
			IOP->MMU->mapObject(0x1F402008, IOP->CDVD->STATUS);
			IOP->MMU->mapObject(0x1F40200A, IOP->CDVD->STATUS); // Mirrored?
			IOP->MMU->mapObject(0x1F40200B, IOP->CDVD->TRAY_STATE);
			IOP->MMU->mapObject(0x1F40200C, IOP->CDVD->CRT_MINUTE);
			IOP->MMU->mapObject(0x1F40200D, IOP->CDVD->CRT_SECOND);
			IOP->MMU->mapObject(0x1F40200E, IOP->CDVD->CRT_FRAME);
			IOP->MMU->mapObject(0x1F40200F, IOP->CDVD->TYPE);
			IOP->MMU->mapObject(0x1F402013, IOP->CDVD->REGISTER_2013);
			IOP->MMU->mapObject(0x1F402015, IOP->CDVD->RSV);
			IOP->MMU->mapObject(0x1F402016, IOP->CDVD->S_COMMAND);
			IOP->MMU->mapObject(0x1F402017, IOP->CDVD->S_READY);
			IOP->MMU->mapObject(0x1F402018, IOP->CDVD->S_DATA_OUT);
			IOP->MMU->mapObject(0x1F402020, IOP->CDVD->KEY_20);
			IOP->MMU->mapObject(0x1F402021, IOP->CDVD->KEY_21);
			IOP->MMU->mapObject(0x1F402022, IOP->CDVD->KEY_22);
			IOP->MMU->mapObject(0x1F402023, IOP->CDVD->KEY_23);
			IOP->MMU->mapObject(0x1F402024, IOP->CDVD->KEY_24);
			IOP->MMU->mapObject(0x1F402028, IOP->CDVD->KEY_28);
			IOP->MMU->mapObject(0x1F402029, IOP->CDVD->KEY_29);
			IOP->MMU->mapObject(0x1F40202A, IOP->CDVD->KEY_2A);
			IOP->MMU->mapObject(0x1F40202B, IOP->CDVD->KEY_2B);
			IOP->MMU->mapObject(0x1F40202C, IOP->CDVD->KEY_2C);
			IOP->MMU->mapObject(0x1F402030, IOP->CDVD->KEY_30);
			IOP->MMU->mapObject(0x1F402031, IOP->CDVD->KEY_31);
			IOP->MMU->mapObject(0x1F402032, IOP->CDVD->KEY_32);
			IOP->MMU->mapObject(0x1F402033, IOP->CDVD->KEY_33);
			IOP->MMU->mapObject(0x1F402034, IOP->CDVD->KEY_34);
			IOP->MMU->mapObject(0x1F402038, IOP->CDVD->KEY_38);
			IOP->MMU->mapObject(0x1F402039, IOP->CDVD->KEY_XOR);
			IOP->MMU->mapObject(0x1F40203A, IOP->CDVD->DEC_SET);

			// SPU2 Registers.
			IOP->MMU->mapObject(0x1F900000, IOP->SPU2->CORES[0]->VOICES[0]->VOLL);
			IOP->MMU->mapObject(0x1F900002, IOP->SPU2->CORES[0]->VOICES[0]->VOLR);
			IOP->MMU->mapObject(0x1F900004, IOP->SPU2->CORES[0]->VOICES[0]->PITCH);
			IOP->MMU->mapObject(0x1F900006, IOP->SPU2->CORES[0]->VOICES[0]->ADSR1);
			IOP->MMU->mapObject(0x1F900008, IOP->SPU2->CORES[0]->VOICES[0]->ADSR2);
			IOP->MMU->mapObject(0x1F90000A, IOP->SPU2->CORES[0]->VOICES[0]->ENVX);
			IOP->MMU->mapObject(0x1F90000C, IOP->SPU2->CORES[0]->VOICES[0]->VOLXL);
			IOP->MMU->mapObject(0x1F90000E, IOP->SPU2->CORES[0]->VOICES[0]->VOLXR);
			IOP->MMU->mapObject(0x1F900010, IOP->SPU2->CORES[0]->VOICES[1]->VOLL);
			IOP->MMU->mapObject(0x1F900012, IOP->SPU2->CORES[0]->VOICES[1]->VOLR);
			IOP->MMU->mapObject(0x1F900014, IOP->SPU2->CORES[0]->VOICES[1]->PITCH);
			IOP->MMU->mapObject(0x1F900016, IOP->SPU2->CORES[0]->VOICES[1]->ADSR1);
			IOP->MMU->mapObject(0x1F900018, IOP->SPU2->CORES[0]->VOICES[1]->ADSR2);
			IOP->MMU->mapObject(0x1F90001A, IOP->SPU2->CORES[0]->VOICES[1]->ENVX);
			IOP->MMU->mapObject(0x1F90001C, IOP->SPU2->CORES[0]->VOICES[1]->VOLXL);
			IOP->MMU->mapObject(0x1F90001E, IOP->SPU2->CORES[0]->VOICES[1]->VOLXR);
			IOP->MMU->mapObject(0x1F900020, IOP->SPU2->CORES[0]->VOICES[2]->VOLL);
			IOP->MMU->mapObject(0x1F900022, IOP->SPU2->CORES[0]->VOICES[2]->VOLR);
			IOP->MMU->mapObject(0x1F900024, IOP->SPU2->CORES[0]->VOICES[2]->PITCH);
			IOP->MMU->mapObject(0x1F900026, IOP->SPU2->CORES[0]->VOICES[2]->ADSR1);
			IOP->MMU->mapObject(0x1F900028, IOP->SPU2->CORES[0]->VOICES[2]->ADSR2);
			IOP->MMU->mapObject(0x1F90002A, IOP->SPU2->CORES[0]->VOICES[2]->ENVX);
			IOP->MMU->mapObject(0x1F90002C, IOP->SPU2->CORES[0]->VOICES[2]->VOLXL);
			IOP->MMU->mapObject(0x1F90002E, IOP->SPU2->CORES[0]->VOICES[2]->VOLXR);
			IOP->MMU->mapObject(0x1F900030, IOP->SPU2->CORES[0]->VOICES[3]->VOLL);
			IOP->MMU->mapObject(0x1F900032, IOP->SPU2->CORES[0]->VOICES[3]->VOLR);
			IOP->MMU->mapObject(0x1F900034, IOP->SPU2->CORES[0]->VOICES[3]->PITCH);
			IOP->MMU->mapObject(0x1F900036, IOP->SPU2->CORES[0]->VOICES[3]->ADSR1);
			IOP->MMU->mapObject(0x1F900038, IOP->SPU2->CORES[0]->VOICES[3]->ADSR2);
			IOP->MMU->mapObject(0x1F90003A, IOP->SPU2->CORES[0]->VOICES[3]->ENVX);
			IOP->MMU->mapObject(0x1F90003C, IOP->SPU2->CORES[0]->VOICES[3]->VOLXL);
			IOP->MMU->mapObject(0x1F90003E, IOP->SPU2->CORES[0]->VOICES[3]->VOLXR);
			IOP->MMU->mapObject(0x1F900040, IOP->SPU2->CORES[0]->VOICES[4]->VOLL);
			IOP->MMU->mapObject(0x1F900042, IOP->SPU2->CORES[0]->VOICES[4]->VOLR);
			IOP->MMU->mapObject(0x1F900044, IOP->SPU2->CORES[0]->VOICES[4]->PITCH);
			IOP->MMU->mapObject(0x1F900046, IOP->SPU2->CORES[0]->VOICES[4]->ADSR1);
			IOP->MMU->mapObject(0x1F900048, IOP->SPU2->CORES[0]->VOICES[4]->ADSR2);
			IOP->MMU->mapObject(0x1F90004A, IOP->SPU2->CORES[0]->VOICES[4]->ENVX);
			IOP->MMU->mapObject(0x1F90004C, IOP->SPU2->CORES[0]->VOICES[4]->VOLXL);
			IOP->MMU->mapObject(0x1F90004E, IOP->SPU2->CORES[0]->VOICES[4]->VOLXR);
			IOP->MMU->mapObject(0x1F900050, IOP->SPU2->CORES[0]->VOICES[5]->VOLL);
			IOP->MMU->mapObject(0x1F900052, IOP->SPU2->CORES[0]->VOICES[5]->VOLR);
			IOP->MMU->mapObject(0x1F900054, IOP->SPU2->CORES[0]->VOICES[5]->PITCH);
			IOP->MMU->mapObject(0x1F900056, IOP->SPU2->CORES[0]->VOICES[5]->ADSR1);
			IOP->MMU->mapObject(0x1F900058, IOP->SPU2->CORES[0]->VOICES[5]->ADSR2);
			IOP->MMU->mapObject(0x1F90005A, IOP->SPU2->CORES[0]->VOICES[5]->ENVX);
			IOP->MMU->mapObject(0x1F90005C, IOP->SPU2->CORES[0]->VOICES[5]->VOLXL);
			IOP->MMU->mapObject(0x1F90005E, IOP->SPU2->CORES[0]->VOICES[5]->VOLXR);
			IOP->MMU->mapObject(0x1F900060, IOP->SPU2->CORES[0]->VOICES[6]->VOLL);
			IOP->MMU->mapObject(0x1F900062, IOP->SPU2->CORES[0]->VOICES[6]->VOLR);
			IOP->MMU->mapObject(0x1F900064, IOP->SPU2->CORES[0]->VOICES[6]->PITCH);
			IOP->MMU->mapObject(0x1F900066, IOP->SPU2->CORES[0]->VOICES[6]->ADSR1);
			IOP->MMU->mapObject(0x1F900068, IOP->SPU2->CORES[0]->VOICES[6]->ADSR2);
			IOP->MMU->mapObject(0x1F90006A, IOP->SPU2->CORES[0]->VOICES[6]->ENVX);
			IOP->MMU->mapObject(0x1F90006C, IOP->SPU2->CORES[0]->VOICES[6]->VOLXL);
			IOP->MMU->mapObject(0x1F90006E, IOP->SPU2->CORES[0]->VOICES[6]->VOLXR);
			IOP->MMU->mapObject(0x1F900070, IOP->SPU2->CORES[0]->VOICES[7]->VOLL);
			IOP->MMU->mapObject(0x1F900072, IOP->SPU2->CORES[0]->VOICES[7]->VOLR);
			IOP->MMU->mapObject(0x1F900074, IOP->SPU2->CORES[0]->VOICES[7]->PITCH);
			IOP->MMU->mapObject(0x1F900076, IOP->SPU2->CORES[0]->VOICES[7]->ADSR1);
			IOP->MMU->mapObject(0x1F900078, IOP->SPU2->CORES[0]->VOICES[7]->ADSR2);
			IOP->MMU->mapObject(0x1F90007A, IOP->SPU2->CORES[0]->VOICES[7]->ENVX);
			IOP->MMU->mapObject(0x1F90007C, IOP->SPU2->CORES[0]->VOICES[7]->VOLXL);
			IOP->MMU->mapObject(0x1F90007E, IOP->SPU2->CORES[0]->VOICES[7]->VOLXR);
			IOP->MMU->mapObject(0x1F900080, IOP->SPU2->CORES[0]->VOICES[8]->VOLL);
			IOP->MMU->mapObject(0x1F900082, IOP->SPU2->CORES[0]->VOICES[8]->VOLR);
			IOP->MMU->mapObject(0x1F900084, IOP->SPU2->CORES[0]->VOICES[8]->PITCH);
			IOP->MMU->mapObject(0x1F900086, IOP->SPU2->CORES[0]->VOICES[8]->ADSR1);
			IOP->MMU->mapObject(0x1F900088, IOP->SPU2->CORES[0]->VOICES[8]->ADSR2);
			IOP->MMU->mapObject(0x1F90008A, IOP->SPU2->CORES[0]->VOICES[8]->ENVX);
			IOP->MMU->mapObject(0x1F90008C, IOP->SPU2->CORES[0]->VOICES[8]->VOLXL);
			IOP->MMU->mapObject(0x1F90008E, IOP->SPU2->CORES[0]->VOICES[8]->VOLXR);
			IOP->MMU->mapObject(0x1F900090, IOP->SPU2->CORES[0]->VOICES[9]->VOLL);
			IOP->MMU->mapObject(0x1F900092, IOP->SPU2->CORES[0]->VOICES[9]->VOLR);
			IOP->MMU->mapObject(0x1F900094, IOP->SPU2->CORES[0]->VOICES[9]->PITCH);
			IOP->MMU->mapObject(0x1F900096, IOP->SPU2->CORES[0]->VOICES[9]->ADSR1);
			IOP->MMU->mapObject(0x1F900098, IOP->SPU2->CORES[0]->VOICES[9]->ADSR2);
			IOP->MMU->mapObject(0x1F90009A, IOP->SPU2->CORES[0]->VOICES[9]->ENVX);
			IOP->MMU->mapObject(0x1F90009C, IOP->SPU2->CORES[0]->VOICES[9]->VOLXL);
			IOP->MMU->mapObject(0x1F90009E, IOP->SPU2->CORES[0]->VOICES[9]->VOLXR);
			IOP->MMU->mapObject(0x1F9000A0, IOP->SPU2->CORES[0]->VOICES[10]->VOLL);
			IOP->MMU->mapObject(0x1F9000A2, IOP->SPU2->CORES[0]->VOICES[10]->VOLR);
			IOP->MMU->mapObject(0x1F9000A4, IOP->SPU2->CORES[0]->VOICES[10]->PITCH);
			IOP->MMU->mapObject(0x1F9000A6, IOP->SPU2->CORES[0]->VOICES[10]->ADSR1);
			IOP->MMU->mapObject(0x1F9000A8, IOP->SPU2->CORES[0]->VOICES[10]->ADSR2);
			IOP->MMU->mapObject(0x1F9000AA, IOP->SPU2->CORES[0]->VOICES[10]->ENVX);
			IOP->MMU->mapObject(0x1F9000AC, IOP->SPU2->CORES[0]->VOICES[10]->VOLXL);
			IOP->MMU->mapObject(0x1F9000AE, IOP->SPU2->CORES[0]->VOICES[10]->VOLXR);
			IOP->MMU->mapObject(0x1F9000B0, IOP->SPU2->CORES[0]->VOICES[11]->VOLL);
			IOP->MMU->mapObject(0x1F9000B2, IOP->SPU2->CORES[0]->VOICES[11]->VOLR);
			IOP->MMU->mapObject(0x1F9000B4, IOP->SPU2->CORES[0]->VOICES[11]->PITCH);
			IOP->MMU->mapObject(0x1F9000B6, IOP->SPU2->CORES[0]->VOICES[11]->ADSR1);
			IOP->MMU->mapObject(0x1F9000B8, IOP->SPU2->CORES[0]->VOICES[11]->ADSR2);
			IOP->MMU->mapObject(0x1F9000BA, IOP->SPU2->CORES[0]->VOICES[11]->ENVX);
			IOP->MMU->mapObject(0x1F9000BC, IOP->SPU2->CORES[0]->VOICES[11]->VOLXL);
			IOP->MMU->mapObject(0x1F9000BE, IOP->SPU2->CORES[0]->VOICES[11]->VOLXR);
			IOP->MMU->mapObject(0x1F9000C0, IOP->SPU2->CORES[0]->VOICES[12]->VOLL);
			IOP->MMU->mapObject(0x1F9000C2, IOP->SPU2->CORES[0]->VOICES[12]->VOLR);
			IOP->MMU->mapObject(0x1F9000C4, IOP->SPU2->CORES[0]->VOICES[12]->PITCH);
			IOP->MMU->mapObject(0x1F9000C6, IOP->SPU2->CORES[0]->VOICES[12]->ADSR1);
			IOP->MMU->mapObject(0x1F9000C8, IOP->SPU2->CORES[0]->VOICES[12]->ADSR2);
			IOP->MMU->mapObject(0x1F9000CA, IOP->SPU2->CORES[0]->VOICES[12]->ENVX);
			IOP->MMU->mapObject(0x1F9000CC, IOP->SPU2->CORES[0]->VOICES[12]->VOLXL);
			IOP->MMU->mapObject(0x1F9000CE, IOP->SPU2->CORES[0]->VOICES[12]->VOLXR);
			IOP->MMU->mapObject(0x1F9000D0, IOP->SPU2->CORES[0]->VOICES[13]->VOLL);
			IOP->MMU->mapObject(0x1F9000D2, IOP->SPU2->CORES[0]->VOICES[13]->VOLR);
			IOP->MMU->mapObject(0x1F9000D4, IOP->SPU2->CORES[0]->VOICES[13]->PITCH);
			IOP->MMU->mapObject(0x1F9000D6, IOP->SPU2->CORES[0]->VOICES[13]->ADSR1);
			IOP->MMU->mapObject(0x1F9000D8, IOP->SPU2->CORES[0]->VOICES[13]->ADSR2);
			IOP->MMU->mapObject(0x1F9000DA, IOP->SPU2->CORES[0]->VOICES[13]->ENVX);
			IOP->MMU->mapObject(0x1F9000DC, IOP->SPU2->CORES[0]->VOICES[13]->VOLXL);
			IOP->MMU->mapObject(0x1F9000DE, IOP->SPU2->CORES[0]->VOICES[13]->VOLXR);
			IOP->MMU->mapObject(0x1F9000E0, IOP->SPU2->CORES[0]->VOICES[14]->VOLL);
			IOP->MMU->mapObject(0x1F9000E2, IOP->SPU2->CORES[0]->VOICES[14]->VOLR);
			IOP->MMU->mapObject(0x1F9000E4, IOP->SPU2->CORES[0]->VOICES[14]->PITCH);
			IOP->MMU->mapObject(0x1F9000E6, IOP->SPU2->CORES[0]->VOICES[14]->ADSR1);
			IOP->MMU->mapObject(0x1F9000E8, IOP->SPU2->CORES[0]->VOICES[14]->ADSR2);
			IOP->MMU->mapObject(0x1F9000EA, IOP->SPU2->CORES[0]->VOICES[14]->ENVX);
			IOP->MMU->mapObject(0x1F9000EC, IOP->SPU2->CORES[0]->VOICES[14]->VOLXL);
			IOP->MMU->mapObject(0x1F9000EE, IOP->SPU2->CORES[0]->VOICES[14]->VOLXR);
			IOP->MMU->mapObject(0x1F9000F0, IOP->SPU2->CORES[0]->VOICES[15]->VOLL);
			IOP->MMU->mapObject(0x1F9000F2, IOP->SPU2->CORES[0]->VOICES[15]->VOLR);
			IOP->MMU->mapObject(0x1F9000F4, IOP->SPU2->CORES[0]->VOICES[15]->PITCH);
			IOP->MMU->mapObject(0x1F9000F6, IOP->SPU2->CORES[0]->VOICES[15]->ADSR1);
			IOP->MMU->mapObject(0x1F9000F8, IOP->SPU2->CORES[0]->VOICES[15]->ADSR2);
			IOP->MMU->mapObject(0x1F9000FA, IOP->SPU2->CORES[0]->VOICES[15]->ENVX);
			IOP->MMU->mapObject(0x1F9000FC, IOP->SPU2->CORES[0]->VOICES[15]->VOLXL);
			IOP->MMU->mapObject(0x1F9000FE, IOP->SPU2->CORES[0]->VOICES[15]->VOLXR);
			IOP->MMU->mapObject(0x1F900100, IOP->SPU2->CORES[0]->VOICES[16]->VOLL);
			IOP->MMU->mapObject(0x1F900102, IOP->SPU2->CORES[0]->VOICES[16]->VOLR);
			IOP->MMU->mapObject(0x1F900104, IOP->SPU2->CORES[0]->VOICES[16]->PITCH);
			IOP->MMU->mapObject(0x1F900106, IOP->SPU2->CORES[0]->VOICES[16]->ADSR1);
			IOP->MMU->mapObject(0x1F900108, IOP->SPU2->CORES[0]->VOICES[16]->ADSR2);
			IOP->MMU->mapObject(0x1F90010A, IOP->SPU2->CORES[0]->VOICES[16]->ENVX);
			IOP->MMU->mapObject(0x1F90010C, IOP->SPU2->CORES[0]->VOICES[16]->VOLXL);
			IOP->MMU->mapObject(0x1F90010E, IOP->SPU2->CORES[0]->VOICES[16]->VOLXR);
			IOP->MMU->mapObject(0x1F900110, IOP->SPU2->CORES[0]->VOICES[17]->VOLL);
			IOP->MMU->mapObject(0x1F900112, IOP->SPU2->CORES[0]->VOICES[17]->VOLR);
			IOP->MMU->mapObject(0x1F900114, IOP->SPU2->CORES[0]->VOICES[17]->PITCH);
			IOP->MMU->mapObject(0x1F900116, IOP->SPU2->CORES[0]->VOICES[17]->ADSR1);
			IOP->MMU->mapObject(0x1F900118, IOP->SPU2->CORES[0]->VOICES[17]->ADSR2);
			IOP->MMU->mapObject(0x1F90011A, IOP->SPU2->CORES[0]->VOICES[17]->ENVX);
			IOP->MMU->mapObject(0x1F90011C, IOP->SPU2->CORES[0]->VOICES[17]->VOLXL);
			IOP->MMU->mapObject(0x1F90011E, IOP->SPU2->CORES[0]->VOICES[17]->VOLXR);
			IOP->MMU->mapObject(0x1F900120, IOP->SPU2->CORES[0]->VOICES[18]->VOLL);
			IOP->MMU->mapObject(0x1F900122, IOP->SPU2->CORES[0]->VOICES[18]->VOLR);
			IOP->MMU->mapObject(0x1F900124, IOP->SPU2->CORES[0]->VOICES[18]->PITCH);
			IOP->MMU->mapObject(0x1F900126, IOP->SPU2->CORES[0]->VOICES[18]->ADSR1);
			IOP->MMU->mapObject(0x1F900128, IOP->SPU2->CORES[0]->VOICES[18]->ADSR2);
			IOP->MMU->mapObject(0x1F90012A, IOP->SPU2->CORES[0]->VOICES[18]->ENVX);
			IOP->MMU->mapObject(0x1F90012C, IOP->SPU2->CORES[0]->VOICES[18]->VOLXL);
			IOP->MMU->mapObject(0x1F90012E, IOP->SPU2->CORES[0]->VOICES[18]->VOLXR);
			IOP->MMU->mapObject(0x1F900130, IOP->SPU2->CORES[0]->VOICES[19]->VOLL);
			IOP->MMU->mapObject(0x1F900132, IOP->SPU2->CORES[0]->VOICES[19]->VOLR);
			IOP->MMU->mapObject(0x1F900134, IOP->SPU2->CORES[0]->VOICES[19]->PITCH);
			IOP->MMU->mapObject(0x1F900136, IOP->SPU2->CORES[0]->VOICES[19]->ADSR1);
			IOP->MMU->mapObject(0x1F900138, IOP->SPU2->CORES[0]->VOICES[19]->ADSR2);
			IOP->MMU->mapObject(0x1F90013A, IOP->SPU2->CORES[0]->VOICES[19]->ENVX);
			IOP->MMU->mapObject(0x1F90013C, IOP->SPU2->CORES[0]->VOICES[19]->VOLXL);
			IOP->MMU->mapObject(0x1F90013E, IOP->SPU2->CORES[0]->VOICES[19]->VOLXR);
			IOP->MMU->mapObject(0x1F900140, IOP->SPU2->CORES[0]->VOICES[20]->VOLL);
			IOP->MMU->mapObject(0x1F900142, IOP->SPU2->CORES[0]->VOICES[20]->VOLR);
			IOP->MMU->mapObject(0x1F900144, IOP->SPU2->CORES[0]->VOICES[20]->PITCH);
			IOP->MMU->mapObject(0x1F900146, IOP->SPU2->CORES[0]->VOICES[20]->ADSR1);
			IOP->MMU->mapObject(0x1F900148, IOP->SPU2->CORES[0]->VOICES[20]->ADSR2);
			IOP->MMU->mapObject(0x1F90014A, IOP->SPU2->CORES[0]->VOICES[20]->ENVX);
			IOP->MMU->mapObject(0x1F90014C, IOP->SPU2->CORES[0]->VOICES[20]->VOLXL);
			IOP->MMU->mapObject(0x1F90014E, IOP->SPU2->CORES[0]->VOICES[20]->VOLXR);
			IOP->MMU->mapObject(0x1F900150, IOP->SPU2->CORES[0]->VOICES[21]->VOLL);
			IOP->MMU->mapObject(0x1F900152, IOP->SPU2->CORES[0]->VOICES[21]->VOLR);
			IOP->MMU->mapObject(0x1F900154, IOP->SPU2->CORES[0]->VOICES[21]->PITCH);
			IOP->MMU->mapObject(0x1F900156, IOP->SPU2->CORES[0]->VOICES[21]->ADSR1);
			IOP->MMU->mapObject(0x1F900158, IOP->SPU2->CORES[0]->VOICES[21]->ADSR2);
			IOP->MMU->mapObject(0x1F90015A, IOP->SPU2->CORES[0]->VOICES[21]->ENVX);
			IOP->MMU->mapObject(0x1F90015C, IOP->SPU2->CORES[0]->VOICES[21]->VOLXL);
			IOP->MMU->mapObject(0x1F90015E, IOP->SPU2->CORES[0]->VOICES[21]->VOLXR);
			IOP->MMU->mapObject(0x1F900160, IOP->SPU2->CORES[0]->VOICES[22]->VOLL);
			IOP->MMU->mapObject(0x1F900162, IOP->SPU2->CORES[0]->VOICES[22]->VOLR);
			IOP->MMU->mapObject(0x1F900164, IOP->SPU2->CORES[0]->VOICES[22]->PITCH);
			IOP->MMU->mapObject(0x1F900166, IOP->SPU2->CORES[0]->VOICES[22]->ADSR1);
			IOP->MMU->mapObject(0x1F900168, IOP->SPU2->CORES[0]->VOICES[22]->ADSR2);
			IOP->MMU->mapObject(0x1F90016A, IOP->SPU2->CORES[0]->VOICES[22]->ENVX);
			IOP->MMU->mapObject(0x1F90016C, IOP->SPU2->CORES[0]->VOICES[22]->VOLXL);
			IOP->MMU->mapObject(0x1F90016E, IOP->SPU2->CORES[0]->VOICES[22]->VOLXR);
			IOP->MMU->mapObject(0x1F900170, IOP->SPU2->CORES[0]->VOICES[23]->VOLL);
			IOP->MMU->mapObject(0x1F900172, IOP->SPU2->CORES[0]->VOICES[23]->VOLR);
			IOP->MMU->mapObject(0x1F900174, IOP->SPU2->CORES[0]->VOICES[23]->PITCH);
			IOP->MMU->mapObject(0x1F900176, IOP->SPU2->CORES[0]->VOICES[23]->ADSR1);
			IOP->MMU->mapObject(0x1F900178, IOP->SPU2->CORES[0]->VOICES[23]->ADSR2);
			IOP->MMU->mapObject(0x1F90017A, IOP->SPU2->CORES[0]->VOICES[23]->ENVX);
			IOP->MMU->mapObject(0x1F90017C, IOP->SPU2->CORES[0]->VOICES[23]->VOLXL);
			IOP->MMU->mapObject(0x1F90017E, IOP->SPU2->CORES[0]->VOICES[23]->VOLXR);
			IOP->MMU->mapObject(0x1F900180, IOP->SPU2->CORES[0]->PMON0);
			IOP->MMU->mapObject(0x1F900182, IOP->SPU2->CORES[0]->PMON1);
			IOP->MMU->mapObject(0x1F900184, IOP->SPU2->CORES[0]->NON0);
			IOP->MMU->mapObject(0x1F900186, IOP->SPU2->CORES[0]->NON1);
			IOP->MMU->mapObject(0x1F900188, IOP->SPU2->CORES[0]->VMIXL0);
			IOP->MMU->mapObject(0x1F90018A, IOP->SPU2->CORES[0]->VMIXL1);
			IOP->MMU->mapObject(0x1F90018C, IOP->SPU2->CORES[0]->VMIXEL0);
			IOP->MMU->mapObject(0x1F90018E, IOP->SPU2->CORES[0]->VMIXEL1);
			IOP->MMU->mapObject(0x1F900190, IOP->SPU2->CORES[0]->VMIXR0);
			IOP->MMU->mapObject(0x1F900192, IOP->SPU2->CORES[0]->VMIXR1);
			IOP->MMU->mapObject(0x1F900194, IOP->SPU2->CORES[0]->VMIXER0);
			IOP->MMU->mapObject(0x1F900196, IOP->SPU2->CORES[0]->VMIXER1);
			IOP->MMU->mapObject(0x1F900198, IOP->SPU2->CORES[0]->MMIX);
			IOP->MMU->mapObject(0x1F90019A, IOP->SPU2->CORES[0]->ATTR);
			IOP->MMU->mapObject(0x1F90019C, IOP->SPU2->CORES[0]->IRQAL);
			IOP->MMU->mapObject(0x1F90019E, IOP->SPU2->CORES[0]->IRQAH);
			IOP->MMU->mapObject(0x1F9001A0, IOP->SPU2->CORES[0]->KON0);
			IOP->MMU->mapObject(0x1F9001A2, IOP->SPU2->CORES[0]->KON1);
			IOP->MMU->mapObject(0x1F9001A4, IOP->SPU2->CORES[0]->KOF0);
			IOP->MMU->mapObject(0x1F9001A6, IOP->SPU2->CORES[0]->KOF1);
			IOP->MMU->mapObject(0x1F9001A8, IOP->SPU2->CORES[0]->TSAL);
			IOP->MMU->mapObject(0x1F9001AA, IOP->SPU2->CORES[0]->TSAH);
			IOP->MMU->mapObject(0x1F9001AC, IOP->SPU2->CORES[0]->DATA0);
			IOP->MMU->mapObject(0x1F9001AE, IOP->SPU2->CORES[0]->DATA1);
			IOP->MMU->mapObject(0x1F9001B0, IOP->SPU2->CORES[0]->DATA2);
			IOP->MMU->mapObject(0x1F9001C0, IOP->SPU2->CORES[0]->VOICES[0]->SSAL);
			IOP->MMU->mapObject(0x1F9001C2, IOP->SPU2->CORES[0]->VOICES[0]->SSAH);
			IOP->MMU->mapObject(0x1F9001C4, IOP->SPU2->CORES[0]->VOICES[0]->LSAXL);
			IOP->MMU->mapObject(0x1F9001C6, IOP->SPU2->CORES[0]->VOICES[0]->LSAXH);
			IOP->MMU->mapObject(0x1F9001C8, IOP->SPU2->CORES[0]->VOICES[0]->NAXL);
			IOP->MMU->mapObject(0x1F9001CA, IOP->SPU2->CORES[0]->VOICES[0]->NAXH);
			IOP->MMU->mapObject(0x1F9001CC, IOP->SPU2->CORES[0]->VOICES[1]->SSAL);
			IOP->MMU->mapObject(0x1F9001CE, IOP->SPU2->CORES[0]->VOICES[1]->SSAH);
			IOP->MMU->mapObject(0x1F9001D0, IOP->SPU2->CORES[0]->VOICES[1]->LSAXL);
			IOP->MMU->mapObject(0x1F9001D2, IOP->SPU2->CORES[0]->VOICES[1]->LSAXH);
			IOP->MMU->mapObject(0x1F9001D4, IOP->SPU2->CORES[0]->VOICES[1]->NAXL);
			IOP->MMU->mapObject(0x1F9001D6, IOP->SPU2->CORES[0]->VOICES[1]->NAXH);
			IOP->MMU->mapObject(0x1F9001D8, IOP->SPU2->CORES[0]->VOICES[2]->SSAL);
			IOP->MMU->mapObject(0x1F9001DA, IOP->SPU2->CORES[0]->VOICES[2]->SSAH);
			IOP->MMU->mapObject(0x1F9001DC, IOP->SPU2->CORES[0]->VOICES[2]->LSAXL);
			IOP->MMU->mapObject(0x1F9001DE, IOP->SPU2->CORES[0]->VOICES[2]->LSAXH);
			IOP->MMU->mapObject(0x1F9001E0, IOP->SPU2->CORES[0]->VOICES[2]->NAXL);
			IOP->MMU->mapObject(0x1F9001E2, IOP->SPU2->CORES[0]->VOICES[2]->NAXH);
			IOP->MMU->mapObject(0x1F9001E4, IOP->SPU2->CORES[0]->VOICES[3]->SSAL);
			IOP->MMU->mapObject(0x1F9001E6, IOP->SPU2->CORES[0]->VOICES[3]->SSAH);
			IOP->MMU->mapObject(0x1F9001E8, IOP->SPU2->CORES[0]->VOICES[3]->LSAXL);
			IOP->MMU->mapObject(0x1F9001EA, IOP->SPU2->CORES[0]->VOICES[3]->LSAXH);
			IOP->MMU->mapObject(0x1F9001EC, IOP->SPU2->CORES[0]->VOICES[3]->NAXL);
			IOP->MMU->mapObject(0x1F9001EE, IOP->SPU2->CORES[0]->VOICES[3]->NAXH);
			IOP->MMU->mapObject(0x1F9001F0, IOP->SPU2->CORES[0]->VOICES[4]->SSAL);
			IOP->MMU->mapObject(0x1F9001F2, IOP->SPU2->CORES[0]->VOICES[4]->SSAH);
			IOP->MMU->mapObject(0x1F9001F4, IOP->SPU2->CORES[0]->VOICES[4]->LSAXL);
			IOP->MMU->mapObject(0x1F9001F6, IOP->SPU2->CORES[0]->VOICES[4]->LSAXH);
			IOP->MMU->mapObject(0x1F9001F8, IOP->SPU2->CORES[0]->VOICES[4]->NAXL);
			IOP->MMU->mapObject(0x1F9001FA, IOP->SPU2->CORES[0]->VOICES[4]->NAXH);
			IOP->MMU->mapObject(0x1F9001FC, IOP->SPU2->CORES[0]->VOICES[5]->SSAL);
			IOP->MMU->mapObject(0x1F9001FE, IOP->SPU2->CORES[0]->VOICES[5]->SSAH);
			IOP->MMU->mapObject(0x1F900200, IOP->SPU2->CORES[0]->VOICES[5]->LSAXL);
			IOP->MMU->mapObject(0x1F900202, IOP->SPU2->CORES[0]->VOICES[5]->LSAXH);
			IOP->MMU->mapObject(0x1F900204, IOP->SPU2->CORES[0]->VOICES[5]->NAXL);
			IOP->MMU->mapObject(0x1F900206, IOP->SPU2->CORES[0]->VOICES[5]->NAXH);
			IOP->MMU->mapObject(0x1F900208, IOP->SPU2->CORES[0]->VOICES[6]->SSAL);
			IOP->MMU->mapObject(0x1F90020A, IOP->SPU2->CORES[0]->VOICES[6]->SSAH);
			IOP->MMU->mapObject(0x1F90020C, IOP->SPU2->CORES[0]->VOICES[6]->LSAXL);
			IOP->MMU->mapObject(0x1F90020E, IOP->SPU2->CORES[0]->VOICES[6]->LSAXH);
			IOP->MMU->mapObject(0x1F900210, IOP->SPU2->CORES[0]->VOICES[6]->NAXL);
			IOP->MMU->mapObject(0x1F900212, IOP->SPU2->CORES[0]->VOICES[6]->NAXH);
			IOP->MMU->mapObject(0x1F900214, IOP->SPU2->CORES[0]->VOICES[7]->SSAL);
			IOP->MMU->mapObject(0x1F900216, IOP->SPU2->CORES[0]->VOICES[7]->SSAH);
			IOP->MMU->mapObject(0x1F900218, IOP->SPU2->CORES[0]->VOICES[7]->LSAXL);
			IOP->MMU->mapObject(0x1F90021A, IOP->SPU2->CORES[0]->VOICES[7]->LSAXH);
			IOP->MMU->mapObject(0x1F90021C, IOP->SPU2->CORES[0]->VOICES[7]->NAXL);
			IOP->MMU->mapObject(0x1F90021E, IOP->SPU2->CORES[0]->VOICES[7]->NAXH);
			IOP->MMU->mapObject(0x1F900220, IOP->SPU2->CORES[0]->VOICES[8]->SSAL);
			IOP->MMU->mapObject(0x1F900222, IOP->SPU2->CORES[0]->VOICES[8]->SSAH);
			IOP->MMU->mapObject(0x1F900224, IOP->SPU2->CORES[0]->VOICES[8]->LSAXL);
			IOP->MMU->mapObject(0x1F900226, IOP->SPU2->CORES[0]->VOICES[8]->LSAXH);
			IOP->MMU->mapObject(0x1F900228, IOP->SPU2->CORES[0]->VOICES[8]->NAXL);
			IOP->MMU->mapObject(0x1F90022A, IOP->SPU2->CORES[0]->VOICES[8]->NAXH);
			IOP->MMU->mapObject(0x1F90022C, IOP->SPU2->CORES[0]->VOICES[9]->SSAL);
			IOP->MMU->mapObject(0x1F90022E, IOP->SPU2->CORES[0]->VOICES[9]->SSAH);
			IOP->MMU->mapObject(0x1F900230, IOP->SPU2->CORES[0]->VOICES[9]->LSAXL);
			IOP->MMU->mapObject(0x1F900232, IOP->SPU2->CORES[0]->VOICES[9]->LSAXH);
			IOP->MMU->mapObject(0x1F900234, IOP->SPU2->CORES[0]->VOICES[9]->NAXL);
			IOP->MMU->mapObject(0x1F900236, IOP->SPU2->CORES[0]->VOICES[9]->NAXH);
			IOP->MMU->mapObject(0x1F900238, IOP->SPU2->CORES[0]->VOICES[10]->SSAL);
			IOP->MMU->mapObject(0x1F90023A, IOP->SPU2->CORES[0]->VOICES[10]->SSAH);
			IOP->MMU->mapObject(0x1F90023C, IOP->SPU2->CORES[0]->VOICES[10]->LSAXL);
			IOP->MMU->mapObject(0x1F90023E, IOP->SPU2->CORES[0]->VOICES[10]->LSAXH);
			IOP->MMU->mapObject(0x1F900240, IOP->SPU2->CORES[0]->VOICES[10]->NAXL);
			IOP->MMU->mapObject(0x1F900242, IOP->SPU2->CORES[0]->VOICES[10]->NAXH);
			IOP->MMU->mapObject(0x1F900244, IOP->SPU2->CORES[0]->VOICES[11]->SSAL);
			IOP->MMU->mapObject(0x1F900246, IOP->SPU2->CORES[0]->VOICES[11]->SSAH);
			IOP->MMU->mapObject(0x1F900248, IOP->SPU2->CORES[0]->VOICES[11]->LSAXL);
			IOP->MMU->mapObject(0x1F90024A, IOP->SPU2->CORES[0]->VOICES[11]->LSAXH);
			IOP->MMU->mapObject(0x1F90024C, IOP->SPU2->CORES[0]->VOICES[11]->NAXL);
			IOP->MMU->mapObject(0x1F90024E, IOP->SPU2->CORES[0]->VOICES[11]->NAXH);
			IOP->MMU->mapObject(0x1F900250, IOP->SPU2->CORES[0]->VOICES[12]->SSAL);
			IOP->MMU->mapObject(0x1F900252, IOP->SPU2->CORES[0]->VOICES[12]->SSAH);
			IOP->MMU->mapObject(0x1F900254, IOP->SPU2->CORES[0]->VOICES[12]->LSAXL);
			IOP->MMU->mapObject(0x1F900256, IOP->SPU2->CORES[0]->VOICES[12]->LSAXH);
			IOP->MMU->mapObject(0x1F900258, IOP->SPU2->CORES[0]->VOICES[12]->NAXL);
			IOP->MMU->mapObject(0x1F90025A, IOP->SPU2->CORES[0]->VOICES[12]->NAXH);
			IOP->MMU->mapObject(0x1F90025C, IOP->SPU2->CORES[0]->VOICES[13]->SSAL);
			IOP->MMU->mapObject(0x1F90025E, IOP->SPU2->CORES[0]->VOICES[13]->SSAH);
			IOP->MMU->mapObject(0x1F900260, IOP->SPU2->CORES[0]->VOICES[13]->LSAXL);
			IOP->MMU->mapObject(0x1F900262, IOP->SPU2->CORES[0]->VOICES[13]->LSAXH);
			IOP->MMU->mapObject(0x1F900264, IOP->SPU2->CORES[0]->VOICES[13]->NAXL);
			IOP->MMU->mapObject(0x1F900266, IOP->SPU2->CORES[0]->VOICES[13]->NAXH);
			IOP->MMU->mapObject(0x1F900268, IOP->SPU2->CORES[0]->VOICES[14]->SSAL);
			IOP->MMU->mapObject(0x1F90026A, IOP->SPU2->CORES[0]->VOICES[14]->SSAH);
			IOP->MMU->mapObject(0x1F90026C, IOP->SPU2->CORES[0]->VOICES[14]->LSAXL);
			IOP->MMU->mapObject(0x1F90026E, IOP->SPU2->CORES[0]->VOICES[14]->LSAXH);
			IOP->MMU->mapObject(0x1F900270, IOP->SPU2->CORES[0]->VOICES[14]->NAXL);
			IOP->MMU->mapObject(0x1F900272, IOP->SPU2->CORES[0]->VOICES[14]->NAXH);
			IOP->MMU->mapObject(0x1F900274, IOP->SPU2->CORES[0]->VOICES[15]->SSAL);
			IOP->MMU->mapObject(0x1F900276, IOP->SPU2->CORES[0]->VOICES[15]->SSAH);
			IOP->MMU->mapObject(0x1F900278, IOP->SPU2->CORES[0]->VOICES[15]->LSAXL);
			IOP->MMU->mapObject(0x1F90027A, IOP->SPU2->CORES[0]->VOICES[15]->LSAXH);
			IOP->MMU->mapObject(0x1F90027C, IOP->SPU2->CORES[0]->VOICES[15]->NAXL);
			IOP->MMU->mapObject(0x1F90027E, IOP->SPU2->CORES[0]->VOICES[15]->NAXH);
			IOP->MMU->mapObject(0x1F900280, IOP->SPU2->CORES[0]->VOICES[16]->SSAL);
			IOP->MMU->mapObject(0x1F900282, IOP->SPU2->CORES[0]->VOICES[16]->SSAH);
			IOP->MMU->mapObject(0x1F900284, IOP->SPU2->CORES[0]->VOICES[16]->LSAXL);
			IOP->MMU->mapObject(0x1F900286, IOP->SPU2->CORES[0]->VOICES[16]->LSAXH);
			IOP->MMU->mapObject(0x1F900288, IOP->SPU2->CORES[0]->VOICES[16]->NAXL);
			IOP->MMU->mapObject(0x1F90028A, IOP->SPU2->CORES[0]->VOICES[16]->NAXH);
			IOP->MMU->mapObject(0x1F90028C, IOP->SPU2->CORES[0]->VOICES[17]->SSAL);
			IOP->MMU->mapObject(0x1F90028E, IOP->SPU2->CORES[0]->VOICES[17]->SSAH);
			IOP->MMU->mapObject(0x1F900290, IOP->SPU2->CORES[0]->VOICES[17]->LSAXL);
			IOP->MMU->mapObject(0x1F900292, IOP->SPU2->CORES[0]->VOICES[17]->LSAXH);
			IOP->MMU->mapObject(0x1F900294, IOP->SPU2->CORES[0]->VOICES[17]->NAXL);
			IOP->MMU->mapObject(0x1F900296, IOP->SPU2->CORES[0]->VOICES[17]->NAXH);
			IOP->MMU->mapObject(0x1F900298, IOP->SPU2->CORES[0]->VOICES[18]->SSAL);
			IOP->MMU->mapObject(0x1F90029A, IOP->SPU2->CORES[0]->VOICES[18]->SSAH);
			IOP->MMU->mapObject(0x1F90029C, IOP->SPU2->CORES[0]->VOICES[18]->LSAXL);
			IOP->MMU->mapObject(0x1F90029E, IOP->SPU2->CORES[0]->VOICES[18]->LSAXH);
			IOP->MMU->mapObject(0x1F9002A0, IOP->SPU2->CORES[0]->VOICES[18]->NAXL);
			IOP->MMU->mapObject(0x1F9002A2, IOP->SPU2->CORES[0]->VOICES[18]->NAXH);
			IOP->MMU->mapObject(0x1F9002A4, IOP->SPU2->CORES[0]->VOICES[19]->SSAL);
			IOP->MMU->mapObject(0x1F9002A6, IOP->SPU2->CORES[0]->VOICES[19]->SSAH);
			IOP->MMU->mapObject(0x1F9002A8, IOP->SPU2->CORES[0]->VOICES[19]->LSAXL);
			IOP->MMU->mapObject(0x1F9002AA, IOP->SPU2->CORES[0]->VOICES[19]->LSAXH);
			IOP->MMU->mapObject(0x1F9002AC, IOP->SPU2->CORES[0]->VOICES[19]->NAXL);
			IOP->MMU->mapObject(0x1F9002AE, IOP->SPU2->CORES[0]->VOICES[19]->NAXH);
			IOP->MMU->mapObject(0x1F9002B0, IOP->SPU2->CORES[0]->VOICES[20]->SSAL);
			IOP->MMU->mapObject(0x1F9002B2, IOP->SPU2->CORES[0]->VOICES[20]->SSAH);
			IOP->MMU->mapObject(0x1F9002B4, IOP->SPU2->CORES[0]->VOICES[20]->LSAXL);
			IOP->MMU->mapObject(0x1F9002B6, IOP->SPU2->CORES[0]->VOICES[20]->LSAXH);
			IOP->MMU->mapObject(0x1F9002B8, IOP->SPU2->CORES[0]->VOICES[20]->NAXL);
			IOP->MMU->mapObject(0x1F9002BA, IOP->SPU2->CORES[0]->VOICES[20]->NAXH);
			IOP->MMU->mapObject(0x1F9002BC, IOP->SPU2->CORES[0]->VOICES[21]->SSAL);
			IOP->MMU->mapObject(0x1F9002BE, IOP->SPU2->CORES[0]->VOICES[21]->SSAH);
			IOP->MMU->mapObject(0x1F9002C0, IOP->SPU2->CORES[0]->VOICES[21]->LSAXL);
			IOP->MMU->mapObject(0x1F9002C2, IOP->SPU2->CORES[0]->VOICES[21]->LSAXH);
			IOP->MMU->mapObject(0x1F9002C4, IOP->SPU2->CORES[0]->VOICES[21]->NAXL);
			IOP->MMU->mapObject(0x1F9002C6, IOP->SPU2->CORES[0]->VOICES[21]->NAXH);
			IOP->MMU->mapObject(0x1F9002C8, IOP->SPU2->CORES[0]->VOICES[22]->SSAL);
			IOP->MMU->mapObject(0x1F9002CA, IOP->SPU2->CORES[0]->VOICES[22]->SSAH);
			IOP->MMU->mapObject(0x1F9002CC, IOP->SPU2->CORES[0]->VOICES[22]->LSAXL);
			IOP->MMU->mapObject(0x1F9002CE, IOP->SPU2->CORES[0]->VOICES[22]->LSAXH);
			IOP->MMU->mapObject(0x1F9002D0, IOP->SPU2->CORES[0]->VOICES[22]->NAXL);
			IOP->MMU->mapObject(0x1F9002D2, IOP->SPU2->CORES[0]->VOICES[22]->NAXH);
			IOP->MMU->mapObject(0x1F9002D4, IOP->SPU2->CORES[0]->VOICES[23]->SSAL);
			IOP->MMU->mapObject(0x1F9002D6, IOP->SPU2->CORES[0]->VOICES[23]->SSAH);
			IOP->MMU->mapObject(0x1F9002D8, IOP->SPU2->CORES[0]->VOICES[23]->LSAXL);
			IOP->MMU->mapObject(0x1F9002DA, IOP->SPU2->CORES[0]->VOICES[23]->LSAXH);
			IOP->MMU->mapObject(0x1F9002DC, IOP->SPU2->CORES[0]->VOICES[23]->NAXL);
			IOP->MMU->mapObject(0x1F9002DE, IOP->SPU2->CORES[0]->VOICES[23]->NAXH);
			IOP->MMU->mapObject(0x1F9002E0, IOP->SPU2->CORES[0]->ESAL);
			IOP->MMU->mapObject(0x1F9002E2, IOP->SPU2->CORES[0]->ESAH);
			IOP->MMU->mapObject(0x1F9002E4, IOP->SPU2->CORES[0]->APF1_SIZEL);
			IOP->MMU->mapObject(0x1F9002E6, IOP->SPU2->CORES[0]->APF1_SIZEH);
			IOP->MMU->mapObject(0x1F9002E8, IOP->SPU2->CORES[0]->APF2_SIZEL);
			IOP->MMU->mapObject(0x1F9002EA, IOP->SPU2->CORES[0]->APF2_SIZEH);
			IOP->MMU->mapObject(0x1F9002EC, IOP->SPU2->CORES[0]->SAME_L_DSTL);
			IOP->MMU->mapObject(0x1F9002EE, IOP->SPU2->CORES[0]->SAME_L_DSTH);
			IOP->MMU->mapObject(0x1F9002F0, IOP->SPU2->CORES[0]->SAME_R_DSTL);
			IOP->MMU->mapObject(0x1F9002F2, IOP->SPU2->CORES[0]->SAME_R_DSTH);
			IOP->MMU->mapObject(0x1F9002F4, IOP->SPU2->CORES[0]->COMB1_L_SRCL);
			IOP->MMU->mapObject(0x1F9002F6, IOP->SPU2->CORES[0]->COMB1_L_SRCH);
			IOP->MMU->mapObject(0x1F9002F8, IOP->SPU2->CORES[0]->COMB1_R_SRCL);
			IOP->MMU->mapObject(0x1F9002FA, IOP->SPU2->CORES[0]->COMB1_R_SRCH);
			IOP->MMU->mapObject(0x1F9002FC, IOP->SPU2->CORES[0]->COMB2_L_SRCL);
			IOP->MMU->mapObject(0x1F9002FE, IOP->SPU2->CORES[0]->COMB2_L_SRCH);
			IOP->MMU->mapObject(0x1F900300, IOP->SPU2->CORES[0]->COMB2_R_SRCL);
			IOP->MMU->mapObject(0x1F900302, IOP->SPU2->CORES[0]->COMB2_R_SRCH);
			IOP->MMU->mapObject(0x1F900304, IOP->SPU2->CORES[0]->SAME_L_SRCL);
			IOP->MMU->mapObject(0x1F900306, IOP->SPU2->CORES[0]->SAME_L_SRCH);
			IOP->MMU->mapObject(0x1F900308, IOP->SPU2->CORES[0]->SAME_R_SRCL);
			IOP->MMU->mapObject(0x1F90030A, IOP->SPU2->CORES[0]->SAME_R_SRCH);
			IOP->MMU->mapObject(0x1F90030C, IOP->SPU2->CORES[0]->DIFF_L_DSTL);
			IOP->MMU->mapObject(0x1F90030E, IOP->SPU2->CORES[0]->DIFF_L_DSTH);
			IOP->MMU->mapObject(0x1F900310, IOP->SPU2->CORES[0]->DIFF_R_DSTL);
			IOP->MMU->mapObject(0x1F900312, IOP->SPU2->CORES[0]->DIFF_R_DSTH);
			IOP->MMU->mapObject(0x1F900314, IOP->SPU2->CORES[0]->COMB3_L_SRCL);
			IOP->MMU->mapObject(0x1F900316, IOP->SPU2->CORES[0]->COMB3_L_SRCH);
			IOP->MMU->mapObject(0x1F900318, IOP->SPU2->CORES[0]->COMB3_R_SRCL);
			IOP->MMU->mapObject(0x1F90031A, IOP->SPU2->CORES[0]->COMB3_R_SRCH);
			IOP->MMU->mapObject(0x1F90031C, IOP->SPU2->CORES[0]->COMB4_L_SRCL);
			IOP->MMU->mapObject(0x1F90031E, IOP->SPU2->CORES[0]->COMB4_L_SRCH);
			IOP->MMU->mapObject(0x1F900320, IOP->SPU2->CORES[0]->COMB4_R_SRCL);
			IOP->MMU->mapObject(0x1F900322, IOP->SPU2->CORES[0]->COMB4_R_SRCH);
			IOP->MMU->mapObject(0x1F900324, IOP->SPU2->CORES[0]->DIFF_L_SRCL);
			IOP->MMU->mapObject(0x1F900326, IOP->SPU2->CORES[0]->DIFF_L_SRCH);
			IOP->MMU->mapObject(0x1F900328, IOP->SPU2->CORES[0]->DIFF_R_SRCL);
			IOP->MMU->mapObject(0x1F90032A, IOP->SPU2->CORES[0]->DIFF_R_SRCH);
			IOP->MMU->mapObject(0x1F90032C, IOP->SPU2->CORES[0]->APF1_L_DSTL);
			IOP->MMU->mapObject(0x1F90032E, IOP->SPU2->CORES[0]->APF1_L_DSTH);
			IOP->MMU->mapObject(0x1F900330, IOP->SPU2->CORES[0]->APF1_R_DSTL);
			IOP->MMU->mapObject(0x1F900332, IOP->SPU2->CORES[0]->APF1_R_DSTH);
			IOP->MMU->mapObject(0x1F900334, IOP->SPU2->CORES[0]->APF2_L_DSTL);
			IOP->MMU->mapObject(0x1F900336, IOP->SPU2->CORES[0]->APF2_L_DSTH);
			IOP->MMU->mapObject(0x1F900338, IOP->SPU2->CORES[0]->APF2_R_DSTL);
			IOP->MMU->mapObject(0x1F90033A, IOP->SPU2->CORES[0]->APF2_R_DSTH);
			IOP->MMU->mapObject(0x1F90033C, IOP->SPU2->CORES[0]->EEAL);
			IOP->MMU->mapObject(0x1F90033E, IOP->SPU2->CORES[0]->EEAH);
			IOP->MMU->mapObject(0x1F900340, IOP->SPU2->CORES[0]->ENDX0);
			IOP->MMU->mapObject(0x1F900342, IOP->SPU2->CORES[0]->ENDX1);
			IOP->MMU->mapObject(0x1F900344, IOP->SPU2->CORES[0]->STATX);
			IOP->MMU->mapObject(0x1F900346, IOP->SPU2->CORES[0]->MEMORY_0X46);

			// Timers Registers.
			IOP->MMU->mapObject(0x1F801100, IOP->Timers->TIMER_0->COUNT);
			IOP->MMU->mapObject(0x1F801104, IOP->Timers->TIMER_0->MODE);
			IOP->MMU->mapObject(0x1F801108, IOP->Timers->TIMER_0->COMP);
			IOP->MMU->mapObject(0x1F801110, IOP->Timers->TIMER_1->COUNT);
			IOP->MMU->mapObject(0x1F801114, IOP->Timers->TIMER_1->MODE);
			IOP->MMU->mapObject(0x1F801118, IOP->Timers->TIMER_1->COMP);
			IOP->MMU->mapObject(0x1F801120, IOP->Timers->TIMER_2->COUNT);
			IOP->MMU->mapObject(0x1F801124, IOP->Timers->TIMER_2->MODE);
			IOP->MMU->mapObject(0x1F801128, IOP->Timers->TIMER_2->COMP);
			IOP->MMU->mapObject(0x1F801480, IOP->Timers->TIMER_3->COUNT);
			IOP->MMU->mapObject(0x1F801484, IOP->Timers->TIMER_3->MODE);
			IOP->MMU->mapObject(0x1F801488, IOP->Timers->TIMER_3->COMP);
			IOP->MMU->mapObject(0x1F801490, IOP->Timers->TIMER_4->COUNT);
			IOP->MMU->mapObject(0x1F801494, IOP->Timers->TIMER_4->MODE);
			IOP->MMU->mapObject(0x1F801498, IOP->Timers->TIMER_4->COMP);
			IOP->MMU->mapObject(0x1F8014A0, IOP->Timers->TIMER_5->COUNT);
			IOP->MMU->mapObject(0x1F8014A4, IOP->Timers->TIMER_5->MODE);
			IOP->MMU->mapObject(0x1F8014A8, IOP->Timers->TIMER_5->COMP);

			// Parallel Port.
			IOP->MMU->mapObject(Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT, IOP->ParallelPort);
		}

		// SIF Registers
		{
			IOP->MMU->mapObject(0x1D000000, Common->SBUS_MSCOM);
			IOP->MMU->mapObject(0x1D000010, Common->SBUS_SMCOM);
			IOP->MMU->mapObject(0x1D000020, Common->SBUS_MSFLG);
			IOP->MMU->mapObject(0x1D000030, Common->SBUS_SMFLG);
			IOP->MMU->mapObject(0x1D000040, Common->SBUS_F240);
			IOP->MMU->mapObject(0x1D000060, Common->SBUS_F260);
		}
	}
}
