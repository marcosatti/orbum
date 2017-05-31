#include <memory>

#include "Common/Types/ByteMMU/ByteMMU_t.h"
#include "Common/Types/Register/MapperRegister16Register32_t.h"
#include "Common/Types/Register/PCRegister16_t.h"
#include "Common/Types/Register/ConstantRegister8_t.h"
#include "Common/Types/Register/ConstantRegister32_t.h"
#include "Common/Types/Register/PairRegister16_t.h"
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
#include "Resources/IOP/INTC/IOPIntc_t.h"
#include "Resources/IOP/INTC/Types/IOPIntcRegisters_t.h"
#include "Resources/IOP/Timers/IOPTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimers_t.h"
#include "Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

#include "Resources/CDVD/CDVD_t.h"
#include "Resources/CDVD/Types/CDVDRegisters_t.h"
#include "Resources/CDVD/Types/CDVDFIFOQueues_t.h"

#include "Resources/SPU2/SPU2_t.h"
#include "Resources/SPU2/Types/SPU2Registers_t.h"
#include "Resources/SPU2/Types/SPU2Cores_t.h"
#include "Resources/SPU2/Types/SPU2CoreRegisters_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoices_t.h"
#include "Resources/SPU2/Types/SPU2CoreVoiceRegisters_t.h"

#include "Resources/SIO2/SIO2_t.h"

Resources_t::Resources_t() :
	Clock(std::make_shared<Clock_t>()),
	Common(std::make_shared<Common_t>()),
	GS(std::make_shared<GS_t>()),
	EE(std::make_shared<EE_t>()),
	IOP(std::make_shared<IOP_t>()),
	CDVD(std::make_shared<CDVD_t>()),
	SPU2(std::make_shared<SPU2_t>()),
	SIO2(std::make_shared<SIO2_t>())
{
	postInit_EE_DMAC();
	postInit_EE_VPU_VU();
	postInit_SPU2();
	postInit_IOP_DMAC();

	// Put these last - they are dependant on the resources initialised from the other init functions (due to memory mappings).
	postInit_EE();
	postInit_IOP();
}

void Resources_t::postInit_EE_DMAC() const
{
	// Initialise DMAC channels.
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
	// Initialise VU0 & the CCR registers.
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

	// Initialise VU units array.
	{
		EE->VPU->VU->VU_CORES[0] = EE->VPU->VU->VU0;
		EE->VPU->VU->VU_CORES[1] = EE->VPU->VU->VU1;
	}

	// Initialise VU0 and VU1 physical memory map.
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
	// Initialise physical memory map of EE.
	{
		// EE Memory.
		{
			// Main Memory.
			EE->MMU->mapObject(0x00000000, EE->MainMemory);

			// Scratchpad Memory.
			EE->MMU->mapObject(0x70000000, EE->EECore->ScratchpadMemory);

			// Various ROMs.
			EE->MMU->mapObject(0x1FC00000, EE->BootROM);
			EE->MMU->mapObject(0x1E000000, EE->ROM1);
			EE->MMU->mapObject(0x1E040000, EE->EROM);
			EE->MMU->mapObject(0x1E400000, EE->ROM2);

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
	IOP->DMAC->CHANNEL_fromMDEC = std::make_shared<IOPDmacChannel_fromMDEC_t>(Common->FIFO_fromMDEC);
	IOP->DMAC->CHANNEL_toMDEC = std::make_shared<IOPDmacChannel_toMDEC_t>(Common->FIFO_toMDEC);
	IOP->DMAC->CHANNEL_SIF2 = std::make_shared<IOPDmacChannel_SIF2_t>(Common->FIFO_SIF2, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_CDROM = std::make_shared<IOPDmacChannel_CDROM_t>(Common->FIFO_CDROM);
	IOP->DMAC->CHANNEL_SPU2C0 = std::make_shared<IOPDmacChannel_SPU2C0_t>(Common->FIFO_SPU2C0);
	IOP->DMAC->CHANNEL_PIO = std::make_shared<IOPDmacChannel_PIO_t>(Common->FIFO_PIO);
	IOP->DMAC->CHANNEL_OTClear = std::make_shared<IOPDmacChannel_OTClear_t>(Common->FIFO_OTClear);
	IOP->DMAC->CHANNEL_SPU2C1 = std::make_shared<IOPDmacChannel_SPU2C1_t>(Common->FIFO_SPU2C1);
	IOP->DMAC->CHANNEL_DEV9 = std::make_shared<IOPDmacChannel_DEV9_t>(Common->FIFO_DEV9);
	IOP->DMAC->CHANNEL_SIF0 = std::make_shared<IOPDmacChannel_SIF0_t>(Common->FIFO_SIF0, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_SIF1 = std::make_shared<IOPDmacChannel_SIF1_t>(Common->FIFO_SIF1, Common->SBUS_F240);
	IOP->DMAC->CHANNEL_fromSIO2 = std::make_shared<IOPDmacChannel_fromSIO2_t>(Common->FIFO_fromSIO2);
	IOP->DMAC->CHANNEL_toSIO2 = std::make_shared<IOPDmacChannel_toSIO2_t>(Common->FIFO_toSIO2);
	IOP->DMAC->CHANNEL_13 = std::make_shared<IOPDmacChannel_CH13_t>();

	IOP->DMAC->CHANNELS[0] = IOP->DMAC->CHANNEL_fromMDEC;
	IOP->DMAC->CHANNELS[1] = IOP->DMAC->CHANNEL_toMDEC;
	IOP->DMAC->CHANNELS[2] = IOP->DMAC->CHANNEL_SIF2;
	IOP->DMAC->CHANNELS[3] = IOP->DMAC->CHANNEL_CDROM;
	IOP->DMAC->CHANNELS[4] = IOP->DMAC->CHANNEL_SPU2C0;
	IOP->DMAC->CHANNELS[5] = IOP->DMAC->CHANNEL_PIO;
	IOP->DMAC->CHANNELS[6] = IOP->DMAC->CHANNEL_OTClear;
	IOP->DMAC->CHANNELS[7] = IOP->DMAC->CHANNEL_SPU2C1;
	IOP->DMAC->CHANNELS[8] = IOP->DMAC->CHANNEL_DEV9;
	IOP->DMAC->CHANNELS[9] = IOP->DMAC->CHANNEL_SIF0;
	IOP->DMAC->CHANNELS[10] = IOP->DMAC->CHANNEL_SIF1;
	IOP->DMAC->CHANNELS[11] = IOP->DMAC->CHANNEL_fromSIO2;
	IOP->DMAC->CHANNELS[12] = IOP->DMAC->CHANNEL_toSIO2;
	IOP->DMAC->CHANNELS[13] = IOP->DMAC->CHANNEL_13;
}

void Resources_t::postInit_IOP() const
{
	// Initialise physical memory map of IOP.
	{
		// IOP Memory.
		{
			// Main Memory.
			IOP->MMU->mapObject(0x00000000, IOP->MainMemory);

			// Various ROMs.
			IOP->MMU->mapObject(0x1FC00000, EE->BootROM);
			IOP->MMU->mapObject(0x1E000000, EE->ROM1);

			// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initialisation. TODO: related to cache control (this is probably very wrong), investigate.
			IOP->MMU->mapObject(0xFFC00000, EE->BootROM);

			// Scratchpad Memory.
			IOP->MMU->mapObject(0x1F800000, IOP->IOPCore->ScratchpadMemory);
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
			IOP->MMU->mapObject(0x1F8010C0, IOP->DMAC->CHANNEL_SPU2C0->MADR);
			IOP->MMU->mapObject(0x1F8010C4, IOP->DMAC->CHANNEL_SPU2C0->BCR);
			IOP->MMU->mapObject(0x1F8010C8, IOP->DMAC->CHANNEL_SPU2C0->CHCR);
			IOP->MMU->mapObject(0x1F8010CC, IOP->DMAC->CHANNEL_SPU2C0->TADR);
			IOP->MMU->mapObject(0x1F8010D0, IOP->DMAC->CHANNEL_PIO->MADR);
			IOP->MMU->mapObject(0x1F8010D4, IOP->DMAC->CHANNEL_PIO->BCR);
			IOP->MMU->mapObject(0x1F8010D8, IOP->DMAC->CHANNEL_PIO->CHCR);
			IOP->MMU->mapObject(0x1F8010E0, IOP->DMAC->CHANNEL_OTClear->MADR);
			IOP->MMU->mapObject(0x1F8010E4, IOP->DMAC->CHANNEL_OTClear->BCR);
			IOP->MMU->mapObject(0x1F8010E8, IOP->DMAC->CHANNEL_OTClear->CHCR);
			IOP->MMU->mapObject(0x1F801500, IOP->DMAC->CHANNEL_SPU2C1->MADR);
			IOP->MMU->mapObject(0x1F801504, IOP->DMAC->CHANNEL_SPU2C1->BCR);
			IOP->MMU->mapObject(0x1F801508, IOP->DMAC->CHANNEL_SPU2C1->CHCR);
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
			IOP->MMU->mapObject(0x1F402004, CDVD->N_COMMAND);
			IOP->MMU->mapObject(0x1F402005, CDVD->N_RDY_DIN);
			IOP->MMU->mapObject(0x1F402006, CDVD->N_DATA_OUT);
			IOP->MMU->mapObject(0x1F402007, CDVD->BREAK);
			IOP->MMU->mapObject(0x1F402008, CDVD->INTR_STAT);
			IOP->MMU->mapObject(0x1F40200A, CDVD->STATUS);
			IOP->MMU->mapObject(0x1F40200B, CDVD->TRAY_STATE);
			IOP->MMU->mapObject(0x1F40200C, CDVD->CRT_MINUTE);
			IOP->MMU->mapObject(0x1F40200D, CDVD->CRT_SECOND);
			IOP->MMU->mapObject(0x1F40200E, CDVD->CRT_FRAME);
			IOP->MMU->mapObject(0x1F40200F, CDVD->TYPE);
			IOP->MMU->mapObject(0x1F402013, CDVD->REGISTER_2013);
			IOP->MMU->mapObject(0x1F402015, CDVD->RSV);
			IOP->MMU->mapObject(0x1F402016, CDVD->S_COMMAND);
			IOP->MMU->mapObject(0x1F402017, CDVD->S_RDY_DIN);
			IOP->MMU->mapObject(0x1F402018, CDVD->S_DATA_OUT);
			IOP->MMU->mapObject(0x1F402020, CDVD->KEY_20);
			IOP->MMU->mapObject(0x1F402021, CDVD->KEY_21);
			IOP->MMU->mapObject(0x1F402022, CDVD->KEY_22);
			IOP->MMU->mapObject(0x1F402023, CDVD->KEY_23);
			IOP->MMU->mapObject(0x1F402024, CDVD->KEY_24);
			IOP->MMU->mapObject(0x1F402028, CDVD->KEY_28);
			IOP->MMU->mapObject(0x1F402029, CDVD->KEY_29);
			IOP->MMU->mapObject(0x1F40202A, CDVD->KEY_2A);
			IOP->MMU->mapObject(0x1F40202B, CDVD->KEY_2B);
			IOP->MMU->mapObject(0x1F40202C, CDVD->KEY_2C);
			IOP->MMU->mapObject(0x1F402030, CDVD->KEY_30);
			IOP->MMU->mapObject(0x1F402031, CDVD->KEY_31);
			IOP->MMU->mapObject(0x1F402032, CDVD->KEY_32);
			IOP->MMU->mapObject(0x1F402033, CDVD->KEY_33);
			IOP->MMU->mapObject(0x1F402034, CDVD->KEY_34);
			IOP->MMU->mapObject(0x1F402038, CDVD->KEY_38);
			IOP->MMU->mapObject(0x1F402039, CDVD->KEY_XOR);
			IOP->MMU->mapObject(0x1F40203A, CDVD->DEC_SET);

			// SPU2 Registers.
			IOP->MMU->mapObject(0x1F900000, SPU2->CORE_0->VOICE_0->VOLL);
			IOP->MMU->mapObject(0x1F900002, SPU2->CORE_0->VOICE_0->VOLR);
			IOP->MMU->mapObject(0x1F900004, SPU2->CORE_0->VOICE_0->PITCH);
			IOP->MMU->mapObject(0x1F900006, SPU2->CORE_0->VOICE_0->ADSR1);
			IOP->MMU->mapObject(0x1F900008, SPU2->CORE_0->VOICE_0->ADSR2);
			IOP->MMU->mapObject(0x1F90000A, SPU2->CORE_0->VOICE_0->ENVX);
			IOP->MMU->mapObject(0x1F90000C, SPU2->CORE_0->VOICE_0->VOLXL);
			IOP->MMU->mapObject(0x1F90000E, SPU2->CORE_0->VOICE_0->VOLXR);
			IOP->MMU->mapObject(0x1F900010, SPU2->CORE_0->VOICE_1->VOLL);
			IOP->MMU->mapObject(0x1F900012, SPU2->CORE_0->VOICE_1->VOLR);
			IOP->MMU->mapObject(0x1F900014, SPU2->CORE_0->VOICE_1->PITCH);
			IOP->MMU->mapObject(0x1F900016, SPU2->CORE_0->VOICE_1->ADSR1);
			IOP->MMU->mapObject(0x1F900018, SPU2->CORE_0->VOICE_1->ADSR2);
			IOP->MMU->mapObject(0x1F90001A, SPU2->CORE_0->VOICE_1->ENVX);
			IOP->MMU->mapObject(0x1F90001C, SPU2->CORE_0->VOICE_1->VOLXL);
			IOP->MMU->mapObject(0x1F90001E, SPU2->CORE_0->VOICE_1->VOLXR);
			IOP->MMU->mapObject(0x1F900020, SPU2->CORE_0->VOICE_2->VOLL);
			IOP->MMU->mapObject(0x1F900022, SPU2->CORE_0->VOICE_2->VOLR);
			IOP->MMU->mapObject(0x1F900024, SPU2->CORE_0->VOICE_2->PITCH);
			IOP->MMU->mapObject(0x1F900026, SPU2->CORE_0->VOICE_2->ADSR1);
			IOP->MMU->mapObject(0x1F900028, SPU2->CORE_0->VOICE_2->ADSR2);
			IOP->MMU->mapObject(0x1F90002A, SPU2->CORE_0->VOICE_2->ENVX);
			IOP->MMU->mapObject(0x1F90002C, SPU2->CORE_0->VOICE_2->VOLXL);
			IOP->MMU->mapObject(0x1F90002E, SPU2->CORE_0->VOICE_2->VOLXR);
			IOP->MMU->mapObject(0x1F900030, SPU2->CORE_0->VOICE_3->VOLL);
			IOP->MMU->mapObject(0x1F900032, SPU2->CORE_0->VOICE_3->VOLR);
			IOP->MMU->mapObject(0x1F900034, SPU2->CORE_0->VOICE_3->PITCH);
			IOP->MMU->mapObject(0x1F900036, SPU2->CORE_0->VOICE_3->ADSR1);
			IOP->MMU->mapObject(0x1F900038, SPU2->CORE_0->VOICE_3->ADSR2);
			IOP->MMU->mapObject(0x1F90003A, SPU2->CORE_0->VOICE_3->ENVX);
			IOP->MMU->mapObject(0x1F90003C, SPU2->CORE_0->VOICE_3->VOLXL);
			IOP->MMU->mapObject(0x1F90003E, SPU2->CORE_0->VOICE_3->VOLXR);
			IOP->MMU->mapObject(0x1F900040, SPU2->CORE_0->VOICE_4->VOLL);
			IOP->MMU->mapObject(0x1F900042, SPU2->CORE_0->VOICE_4->VOLR);
			IOP->MMU->mapObject(0x1F900044, SPU2->CORE_0->VOICE_4->PITCH);
			IOP->MMU->mapObject(0x1F900046, SPU2->CORE_0->VOICE_4->ADSR1);
			IOP->MMU->mapObject(0x1F900048, SPU2->CORE_0->VOICE_4->ADSR2);
			IOP->MMU->mapObject(0x1F90004A, SPU2->CORE_0->VOICE_4->ENVX);
			IOP->MMU->mapObject(0x1F90004C, SPU2->CORE_0->VOICE_4->VOLXL);
			IOP->MMU->mapObject(0x1F90004E, SPU2->CORE_0->VOICE_4->VOLXR);
			IOP->MMU->mapObject(0x1F900050, SPU2->CORE_0->VOICE_5->VOLL);
			IOP->MMU->mapObject(0x1F900052, SPU2->CORE_0->VOICE_5->VOLR);
			IOP->MMU->mapObject(0x1F900054, SPU2->CORE_0->VOICE_5->PITCH);
			IOP->MMU->mapObject(0x1F900056, SPU2->CORE_0->VOICE_5->ADSR1);
			IOP->MMU->mapObject(0x1F900058, SPU2->CORE_0->VOICE_5->ADSR2);
			IOP->MMU->mapObject(0x1F90005A, SPU2->CORE_0->VOICE_5->ENVX);
			IOP->MMU->mapObject(0x1F90005C, SPU2->CORE_0->VOICE_5->VOLXL);
			IOP->MMU->mapObject(0x1F90005E, SPU2->CORE_0->VOICE_5->VOLXR);
			IOP->MMU->mapObject(0x1F900060, SPU2->CORE_0->VOICE_6->VOLL);
			IOP->MMU->mapObject(0x1F900062, SPU2->CORE_0->VOICE_6->VOLR);
			IOP->MMU->mapObject(0x1F900064, SPU2->CORE_0->VOICE_6->PITCH);
			IOP->MMU->mapObject(0x1F900066, SPU2->CORE_0->VOICE_6->ADSR1);
			IOP->MMU->mapObject(0x1F900068, SPU2->CORE_0->VOICE_6->ADSR2);
			IOP->MMU->mapObject(0x1F90006A, SPU2->CORE_0->VOICE_6->ENVX);
			IOP->MMU->mapObject(0x1F90006C, SPU2->CORE_0->VOICE_6->VOLXL);
			IOP->MMU->mapObject(0x1F90006E, SPU2->CORE_0->VOICE_6->VOLXR);
			IOP->MMU->mapObject(0x1F900070, SPU2->CORE_0->VOICE_7->VOLL);
			IOP->MMU->mapObject(0x1F900072, SPU2->CORE_0->VOICE_7->VOLR);
			IOP->MMU->mapObject(0x1F900074, SPU2->CORE_0->VOICE_7->PITCH);
			IOP->MMU->mapObject(0x1F900076, SPU2->CORE_0->VOICE_7->ADSR1);
			IOP->MMU->mapObject(0x1F900078, SPU2->CORE_0->VOICE_7->ADSR2);
			IOP->MMU->mapObject(0x1F90007A, SPU2->CORE_0->VOICE_7->ENVX);
			IOP->MMU->mapObject(0x1F90007C, SPU2->CORE_0->VOICE_7->VOLXL);
			IOP->MMU->mapObject(0x1F90007E, SPU2->CORE_0->VOICE_7->VOLXR);
			IOP->MMU->mapObject(0x1F900080, SPU2->CORE_0->VOICE_8->VOLL);
			IOP->MMU->mapObject(0x1F900082, SPU2->CORE_0->VOICE_8->VOLR);
			IOP->MMU->mapObject(0x1F900084, SPU2->CORE_0->VOICE_8->PITCH);
			IOP->MMU->mapObject(0x1F900086, SPU2->CORE_0->VOICE_8->ADSR1);
			IOP->MMU->mapObject(0x1F900088, SPU2->CORE_0->VOICE_8->ADSR2);
			IOP->MMU->mapObject(0x1F90008A, SPU2->CORE_0->VOICE_8->ENVX);
			IOP->MMU->mapObject(0x1F90008C, SPU2->CORE_0->VOICE_8->VOLXL);
			IOP->MMU->mapObject(0x1F90008E, SPU2->CORE_0->VOICE_8->VOLXR);
			IOP->MMU->mapObject(0x1F900090, SPU2->CORE_0->VOICE_9->VOLL);
			IOP->MMU->mapObject(0x1F900092, SPU2->CORE_0->VOICE_9->VOLR);
			IOP->MMU->mapObject(0x1F900094, SPU2->CORE_0->VOICE_9->PITCH);
			IOP->MMU->mapObject(0x1F900096, SPU2->CORE_0->VOICE_9->ADSR1);
			IOP->MMU->mapObject(0x1F900098, SPU2->CORE_0->VOICE_9->ADSR2);
			IOP->MMU->mapObject(0x1F90009A, SPU2->CORE_0->VOICE_9->ENVX);
			IOP->MMU->mapObject(0x1F90009C, SPU2->CORE_0->VOICE_9->VOLXL);
			IOP->MMU->mapObject(0x1F90009E, SPU2->CORE_0->VOICE_9->VOLXR);
			IOP->MMU->mapObject(0x1F9000A0, SPU2->CORE_0->VOICE_10->VOLL);
			IOP->MMU->mapObject(0x1F9000A2, SPU2->CORE_0->VOICE_10->VOLR);
			IOP->MMU->mapObject(0x1F9000A4, SPU2->CORE_0->VOICE_10->PITCH);
			IOP->MMU->mapObject(0x1F9000A6, SPU2->CORE_0->VOICE_10->ADSR1);
			IOP->MMU->mapObject(0x1F9000A8, SPU2->CORE_0->VOICE_10->ADSR2);
			IOP->MMU->mapObject(0x1F9000AA, SPU2->CORE_0->VOICE_10->ENVX);
			IOP->MMU->mapObject(0x1F9000AC, SPU2->CORE_0->VOICE_10->VOLXL);
			IOP->MMU->mapObject(0x1F9000AE, SPU2->CORE_0->VOICE_10->VOLXR);
			IOP->MMU->mapObject(0x1F9000B0, SPU2->CORE_0->VOICE_11->VOLL);
			IOP->MMU->mapObject(0x1F9000B2, SPU2->CORE_0->VOICE_11->VOLR);
			IOP->MMU->mapObject(0x1F9000B4, SPU2->CORE_0->VOICE_11->PITCH);
			IOP->MMU->mapObject(0x1F9000B6, SPU2->CORE_0->VOICE_11->ADSR1);
			IOP->MMU->mapObject(0x1F9000B8, SPU2->CORE_0->VOICE_11->ADSR2);
			IOP->MMU->mapObject(0x1F9000BA, SPU2->CORE_0->VOICE_11->ENVX);
			IOP->MMU->mapObject(0x1F9000BC, SPU2->CORE_0->VOICE_11->VOLXL);
			IOP->MMU->mapObject(0x1F9000BE, SPU2->CORE_0->VOICE_11->VOLXR);
			IOP->MMU->mapObject(0x1F9000C0, SPU2->CORE_0->VOICE_12->VOLL);
			IOP->MMU->mapObject(0x1F9000C2, SPU2->CORE_0->VOICE_12->VOLR);
			IOP->MMU->mapObject(0x1F9000C4, SPU2->CORE_0->VOICE_12->PITCH);
			IOP->MMU->mapObject(0x1F9000C6, SPU2->CORE_0->VOICE_12->ADSR1);
			IOP->MMU->mapObject(0x1F9000C8, SPU2->CORE_0->VOICE_12->ADSR2);
			IOP->MMU->mapObject(0x1F9000CA, SPU2->CORE_0->VOICE_12->ENVX);
			IOP->MMU->mapObject(0x1F9000CC, SPU2->CORE_0->VOICE_12->VOLXL);
			IOP->MMU->mapObject(0x1F9000CE, SPU2->CORE_0->VOICE_12->VOLXR);
			IOP->MMU->mapObject(0x1F9000D0, SPU2->CORE_0->VOICE_13->VOLL);
			IOP->MMU->mapObject(0x1F9000D2, SPU2->CORE_0->VOICE_13->VOLR);
			IOP->MMU->mapObject(0x1F9000D4, SPU2->CORE_0->VOICE_13->PITCH);
			IOP->MMU->mapObject(0x1F9000D6, SPU2->CORE_0->VOICE_13->ADSR1);
			IOP->MMU->mapObject(0x1F9000D8, SPU2->CORE_0->VOICE_13->ADSR2);
			IOP->MMU->mapObject(0x1F9000DA, SPU2->CORE_0->VOICE_13->ENVX);
			IOP->MMU->mapObject(0x1F9000DC, SPU2->CORE_0->VOICE_13->VOLXL);
			IOP->MMU->mapObject(0x1F9000DE, SPU2->CORE_0->VOICE_13->VOLXR);
			IOP->MMU->mapObject(0x1F9000E0, SPU2->CORE_0->VOICE_14->VOLL);
			IOP->MMU->mapObject(0x1F9000E2, SPU2->CORE_0->VOICE_14->VOLR);
			IOP->MMU->mapObject(0x1F9000E4, SPU2->CORE_0->VOICE_14->PITCH);
			IOP->MMU->mapObject(0x1F9000E6, SPU2->CORE_0->VOICE_14->ADSR1);
			IOP->MMU->mapObject(0x1F9000E8, SPU2->CORE_0->VOICE_14->ADSR2);
			IOP->MMU->mapObject(0x1F9000EA, SPU2->CORE_0->VOICE_14->ENVX);
			IOP->MMU->mapObject(0x1F9000EC, SPU2->CORE_0->VOICE_14->VOLXL);
			IOP->MMU->mapObject(0x1F9000EE, SPU2->CORE_0->VOICE_14->VOLXR);
			IOP->MMU->mapObject(0x1F9000F0, SPU2->CORE_0->VOICE_15->VOLL);
			IOP->MMU->mapObject(0x1F9000F2, SPU2->CORE_0->VOICE_15->VOLR);
			IOP->MMU->mapObject(0x1F9000F4, SPU2->CORE_0->VOICE_15->PITCH);
			IOP->MMU->mapObject(0x1F9000F6, SPU2->CORE_0->VOICE_15->ADSR1);
			IOP->MMU->mapObject(0x1F9000F8, SPU2->CORE_0->VOICE_15->ADSR2);
			IOP->MMU->mapObject(0x1F9000FA, SPU2->CORE_0->VOICE_15->ENVX);
			IOP->MMU->mapObject(0x1F9000FC, SPU2->CORE_0->VOICE_15->VOLXL);
			IOP->MMU->mapObject(0x1F9000FE, SPU2->CORE_0->VOICE_15->VOLXR);
			IOP->MMU->mapObject(0x1F900100, SPU2->CORE_0->VOICE_16->VOLL);
			IOP->MMU->mapObject(0x1F900102, SPU2->CORE_0->VOICE_16->VOLR);
			IOP->MMU->mapObject(0x1F900104, SPU2->CORE_0->VOICE_16->PITCH);
			IOP->MMU->mapObject(0x1F900106, SPU2->CORE_0->VOICE_16->ADSR1);
			IOP->MMU->mapObject(0x1F900108, SPU2->CORE_0->VOICE_16->ADSR2);
			IOP->MMU->mapObject(0x1F90010A, SPU2->CORE_0->VOICE_16->ENVX);
			IOP->MMU->mapObject(0x1F90010C, SPU2->CORE_0->VOICE_16->VOLXL);
			IOP->MMU->mapObject(0x1F90010E, SPU2->CORE_0->VOICE_16->VOLXR);
			IOP->MMU->mapObject(0x1F900110, SPU2->CORE_0->VOICE_17->VOLL);
			IOP->MMU->mapObject(0x1F900112, SPU2->CORE_0->VOICE_17->VOLR);
			IOP->MMU->mapObject(0x1F900114, SPU2->CORE_0->VOICE_17->PITCH);
			IOP->MMU->mapObject(0x1F900116, SPU2->CORE_0->VOICE_17->ADSR1);
			IOP->MMU->mapObject(0x1F900118, SPU2->CORE_0->VOICE_17->ADSR2);
			IOP->MMU->mapObject(0x1F90011A, SPU2->CORE_0->VOICE_17->ENVX);
			IOP->MMU->mapObject(0x1F90011C, SPU2->CORE_0->VOICE_17->VOLXL);
			IOP->MMU->mapObject(0x1F90011E, SPU2->CORE_0->VOICE_17->VOLXR);
			IOP->MMU->mapObject(0x1F900120, SPU2->CORE_0->VOICE_18->VOLL);
			IOP->MMU->mapObject(0x1F900122, SPU2->CORE_0->VOICE_18->VOLR);
			IOP->MMU->mapObject(0x1F900124, SPU2->CORE_0->VOICE_18->PITCH);
			IOP->MMU->mapObject(0x1F900126, SPU2->CORE_0->VOICE_18->ADSR1);
			IOP->MMU->mapObject(0x1F900128, SPU2->CORE_0->VOICE_18->ADSR2);
			IOP->MMU->mapObject(0x1F90012A, SPU2->CORE_0->VOICE_18->ENVX);
			IOP->MMU->mapObject(0x1F90012C, SPU2->CORE_0->VOICE_18->VOLXL);
			IOP->MMU->mapObject(0x1F90012E, SPU2->CORE_0->VOICE_18->VOLXR);
			IOP->MMU->mapObject(0x1F900130, SPU2->CORE_0->VOICE_19->VOLL);
			IOP->MMU->mapObject(0x1F900132, SPU2->CORE_0->VOICE_19->VOLR);
			IOP->MMU->mapObject(0x1F900134, SPU2->CORE_0->VOICE_19->PITCH);
			IOP->MMU->mapObject(0x1F900136, SPU2->CORE_0->VOICE_19->ADSR1);
			IOP->MMU->mapObject(0x1F900138, SPU2->CORE_0->VOICE_19->ADSR2);
			IOP->MMU->mapObject(0x1F90013A, SPU2->CORE_0->VOICE_19->ENVX);
			IOP->MMU->mapObject(0x1F90013C, SPU2->CORE_0->VOICE_19->VOLXL);
			IOP->MMU->mapObject(0x1F90013E, SPU2->CORE_0->VOICE_19->VOLXR);
			IOP->MMU->mapObject(0x1F900140, SPU2->CORE_0->VOICE_20->VOLL);
			IOP->MMU->mapObject(0x1F900142, SPU2->CORE_0->VOICE_20->VOLR);
			IOP->MMU->mapObject(0x1F900144, SPU2->CORE_0->VOICE_20->PITCH);
			IOP->MMU->mapObject(0x1F900146, SPU2->CORE_0->VOICE_20->ADSR1);
			IOP->MMU->mapObject(0x1F900148, SPU2->CORE_0->VOICE_20->ADSR2);
			IOP->MMU->mapObject(0x1F90014A, SPU2->CORE_0->VOICE_20->ENVX);
			IOP->MMU->mapObject(0x1F90014C, SPU2->CORE_0->VOICE_20->VOLXL);
			IOP->MMU->mapObject(0x1F90014E, SPU2->CORE_0->VOICE_20->VOLXR);
			IOP->MMU->mapObject(0x1F900150, SPU2->CORE_0->VOICE_21->VOLL);
			IOP->MMU->mapObject(0x1F900152, SPU2->CORE_0->VOICE_21->VOLR);
			IOP->MMU->mapObject(0x1F900154, SPU2->CORE_0->VOICE_21->PITCH);
			IOP->MMU->mapObject(0x1F900156, SPU2->CORE_0->VOICE_21->ADSR1);
			IOP->MMU->mapObject(0x1F900158, SPU2->CORE_0->VOICE_21->ADSR2);
			IOP->MMU->mapObject(0x1F90015A, SPU2->CORE_0->VOICE_21->ENVX);
			IOP->MMU->mapObject(0x1F90015C, SPU2->CORE_0->VOICE_21->VOLXL);
			IOP->MMU->mapObject(0x1F90015E, SPU2->CORE_0->VOICE_21->VOLXR);
			IOP->MMU->mapObject(0x1F900160, SPU2->CORE_0->VOICE_22->VOLL);
			IOP->MMU->mapObject(0x1F900162, SPU2->CORE_0->VOICE_22->VOLR);
			IOP->MMU->mapObject(0x1F900164, SPU2->CORE_0->VOICE_22->PITCH);
			IOP->MMU->mapObject(0x1F900166, SPU2->CORE_0->VOICE_22->ADSR1);
			IOP->MMU->mapObject(0x1F900168, SPU2->CORE_0->VOICE_22->ADSR2);
			IOP->MMU->mapObject(0x1F90016A, SPU2->CORE_0->VOICE_22->ENVX);
			IOP->MMU->mapObject(0x1F90016C, SPU2->CORE_0->VOICE_22->VOLXL);
			IOP->MMU->mapObject(0x1F90016E, SPU2->CORE_0->VOICE_22->VOLXR);
			IOP->MMU->mapObject(0x1F900170, SPU2->CORE_0->VOICE_23->VOLL);
			IOP->MMU->mapObject(0x1F900172, SPU2->CORE_0->VOICE_23->VOLR);
			IOP->MMU->mapObject(0x1F900174, SPU2->CORE_0->VOICE_23->PITCH);
			IOP->MMU->mapObject(0x1F900176, SPU2->CORE_0->VOICE_23->ADSR1);
			IOP->MMU->mapObject(0x1F900178, SPU2->CORE_0->VOICE_23->ADSR2);
			IOP->MMU->mapObject(0x1F90017A, SPU2->CORE_0->VOICE_23->ENVX);
			IOP->MMU->mapObject(0x1F90017C, SPU2->CORE_0->VOICE_23->VOLXL);
			IOP->MMU->mapObject(0x1F90017E, SPU2->CORE_0->VOICE_23->VOLXR);
			IOP->MMU->mapObject(0x1F900180, SPU2->CORE_0->PMON0);
			IOP->MMU->mapObject(0x1F900182, SPU2->CORE_0->PMON1);
			IOP->MMU->mapObject(0x1F900184, SPU2->CORE_0->NON0);
			IOP->MMU->mapObject(0x1F900186, SPU2->CORE_0->NON1);
			IOP->MMU->mapObject(0x1F900188, SPU2->CORE_0->VMIXL0);
			IOP->MMU->mapObject(0x1F90018A, SPU2->CORE_0->VMIXL1);
			IOP->MMU->mapObject(0x1F90018C, SPU2->CORE_0->VMIXEL0);
			IOP->MMU->mapObject(0x1F90018E, SPU2->CORE_0->VMIXEL1);
			IOP->MMU->mapObject(0x1F900190, SPU2->CORE_0->VMIXR0);
			IOP->MMU->mapObject(0x1F900192, SPU2->CORE_0->VMIXR1);
			IOP->MMU->mapObject(0x1F900194, SPU2->CORE_0->VMIXER0);
			IOP->MMU->mapObject(0x1F900196, SPU2->CORE_0->VMIXER1);
			IOP->MMU->mapObject(0x1F900198, SPU2->CORE_0->MMIX);
			IOP->MMU->mapObject(0x1F90019A, SPU2->CORE_0->ATTR);
			IOP->MMU->mapObject(0x1F90019C, SPU2->CORE_0->IRQAH);
			IOP->MMU->mapObject(0x1F90019E, SPU2->CORE_0->IRQAL);
			IOP->MMU->mapObject(0x1F9001A0, SPU2->CORE_0->KON0);
			IOP->MMU->mapObject(0x1F9001A2, SPU2->CORE_0->KON1);
			IOP->MMU->mapObject(0x1F9001A4, SPU2->CORE_0->KOF0);
			IOP->MMU->mapObject(0x1F9001A6, SPU2->CORE_0->KOF1);
			IOP->MMU->mapObject(0x1F9001A8, SPU2->CORE_0->TSAH);
			IOP->MMU->mapObject(0x1F9001AA, SPU2->CORE_0->TSAL);
			IOP->MMU->mapObject(0x1F9001AC, SPU2->CORE_0->DATA0);
			IOP->MMU->mapObject(0x1F9001AE, SPU2->CORE_0->DATA1);
			IOP->MMU->mapObject(0x1F9001B0, SPU2->CORE_0->ADMAS);
			IOP->MMU->mapObject(0x1F9001C0, SPU2->CORE_0->VOICE_0->SSAH);
			IOP->MMU->mapObject(0x1F9001C2, SPU2->CORE_0->VOICE_0->SSAL);
			IOP->MMU->mapObject(0x1F9001C4, SPU2->CORE_0->VOICE_0->LSAXH);
			IOP->MMU->mapObject(0x1F9001C6, SPU2->CORE_0->VOICE_0->LSAXL);
			IOP->MMU->mapObject(0x1F9001C8, SPU2->CORE_0->VOICE_0->NAXH);
			IOP->MMU->mapObject(0x1F9001CA, SPU2->CORE_0->VOICE_0->NAXL);
			IOP->MMU->mapObject(0x1F9001CC, SPU2->CORE_0->VOICE_1->SSAH);
			IOP->MMU->mapObject(0x1F9001CE, SPU2->CORE_0->VOICE_1->SSAL);
			IOP->MMU->mapObject(0x1F9001D0, SPU2->CORE_0->VOICE_1->LSAXH);
			IOP->MMU->mapObject(0x1F9001D2, SPU2->CORE_0->VOICE_1->LSAXL);
			IOP->MMU->mapObject(0x1F9001D4, SPU2->CORE_0->VOICE_1->NAXH);
			IOP->MMU->mapObject(0x1F9001D6, SPU2->CORE_0->VOICE_1->NAXL);
			IOP->MMU->mapObject(0x1F9001D8, SPU2->CORE_0->VOICE_2->SSAH);
			IOP->MMU->mapObject(0x1F9001DA, SPU2->CORE_0->VOICE_2->SSAL);
			IOP->MMU->mapObject(0x1F9001DC, SPU2->CORE_0->VOICE_2->LSAXH);
			IOP->MMU->mapObject(0x1F9001DE, SPU2->CORE_0->VOICE_2->LSAXL);
			IOP->MMU->mapObject(0x1F9001E0, SPU2->CORE_0->VOICE_2->NAXH);
			IOP->MMU->mapObject(0x1F9001E2, SPU2->CORE_0->VOICE_2->NAXL);
			IOP->MMU->mapObject(0x1F9001E4, SPU2->CORE_0->VOICE_3->SSAH);
			IOP->MMU->mapObject(0x1F9001E6, SPU2->CORE_0->VOICE_3->SSAL);
			IOP->MMU->mapObject(0x1F9001E8, SPU2->CORE_0->VOICE_3->LSAXH);
			IOP->MMU->mapObject(0x1F9001EA, SPU2->CORE_0->VOICE_3->LSAXL);
			IOP->MMU->mapObject(0x1F9001EC, SPU2->CORE_0->VOICE_3->NAXH);
			IOP->MMU->mapObject(0x1F9001EE, SPU2->CORE_0->VOICE_3->NAXL);
			IOP->MMU->mapObject(0x1F9001F0, SPU2->CORE_0->VOICE_4->SSAH);
			IOP->MMU->mapObject(0x1F9001F2, SPU2->CORE_0->VOICE_4->SSAL);
			IOP->MMU->mapObject(0x1F9001F4, SPU2->CORE_0->VOICE_4->LSAXH);
			IOP->MMU->mapObject(0x1F9001F6, SPU2->CORE_0->VOICE_4->LSAXL);
			IOP->MMU->mapObject(0x1F9001F8, SPU2->CORE_0->VOICE_4->NAXH);
			IOP->MMU->mapObject(0x1F9001FA, SPU2->CORE_0->VOICE_4->NAXL);
			IOP->MMU->mapObject(0x1F9001FC, SPU2->CORE_0->VOICE_5->SSAH);
			IOP->MMU->mapObject(0x1F9001FE, SPU2->CORE_0->VOICE_5->SSAL);
			IOP->MMU->mapObject(0x1F900200, SPU2->CORE_0->VOICE_5->LSAXH);
			IOP->MMU->mapObject(0x1F900202, SPU2->CORE_0->VOICE_5->LSAXL);
			IOP->MMU->mapObject(0x1F900204, SPU2->CORE_0->VOICE_5->NAXH);
			IOP->MMU->mapObject(0x1F900206, SPU2->CORE_0->VOICE_5->NAXL);
			IOP->MMU->mapObject(0x1F900208, SPU2->CORE_0->VOICE_6->SSAH);
			IOP->MMU->mapObject(0x1F90020A, SPU2->CORE_0->VOICE_6->SSAL);
			IOP->MMU->mapObject(0x1F90020C, SPU2->CORE_0->VOICE_6->LSAXH);
			IOP->MMU->mapObject(0x1F90020E, SPU2->CORE_0->VOICE_6->LSAXL);
			IOP->MMU->mapObject(0x1F900210, SPU2->CORE_0->VOICE_6->NAXH);
			IOP->MMU->mapObject(0x1F900212, SPU2->CORE_0->VOICE_6->NAXL);
			IOP->MMU->mapObject(0x1F900214, SPU2->CORE_0->VOICE_7->SSAH);
			IOP->MMU->mapObject(0x1F900216, SPU2->CORE_0->VOICE_7->SSAL);
			IOP->MMU->mapObject(0x1F900218, SPU2->CORE_0->VOICE_7->LSAXH);
			IOP->MMU->mapObject(0x1F90021A, SPU2->CORE_0->VOICE_7->LSAXL);
			IOP->MMU->mapObject(0x1F90021C, SPU2->CORE_0->VOICE_7->NAXH);
			IOP->MMU->mapObject(0x1F90021E, SPU2->CORE_0->VOICE_7->NAXL);
			IOP->MMU->mapObject(0x1F900220, SPU2->CORE_0->VOICE_8->SSAH);
			IOP->MMU->mapObject(0x1F900222, SPU2->CORE_0->VOICE_8->SSAL);
			IOP->MMU->mapObject(0x1F900224, SPU2->CORE_0->VOICE_8->LSAXH);
			IOP->MMU->mapObject(0x1F900226, SPU2->CORE_0->VOICE_8->LSAXL);
			IOP->MMU->mapObject(0x1F900228, SPU2->CORE_0->VOICE_8->NAXH);
			IOP->MMU->mapObject(0x1F90022A, SPU2->CORE_0->VOICE_8->NAXL);
			IOP->MMU->mapObject(0x1F90022C, SPU2->CORE_0->VOICE_9->SSAH);
			IOP->MMU->mapObject(0x1F90022E, SPU2->CORE_0->VOICE_9->SSAL);
			IOP->MMU->mapObject(0x1F900230, SPU2->CORE_0->VOICE_9->LSAXH);
			IOP->MMU->mapObject(0x1F900232, SPU2->CORE_0->VOICE_9->LSAXL);
			IOP->MMU->mapObject(0x1F900234, SPU2->CORE_0->VOICE_9->NAXH);
			IOP->MMU->mapObject(0x1F900236, SPU2->CORE_0->VOICE_9->NAXL);
			IOP->MMU->mapObject(0x1F900238, SPU2->CORE_0->VOICE_10->SSAH);
			IOP->MMU->mapObject(0x1F90023A, SPU2->CORE_0->VOICE_10->SSAL);
			IOP->MMU->mapObject(0x1F90023C, SPU2->CORE_0->VOICE_10->LSAXH);
			IOP->MMU->mapObject(0x1F90023E, SPU2->CORE_0->VOICE_10->LSAXL);
			IOP->MMU->mapObject(0x1F900240, SPU2->CORE_0->VOICE_10->NAXH);
			IOP->MMU->mapObject(0x1F900242, SPU2->CORE_0->VOICE_10->NAXL);
			IOP->MMU->mapObject(0x1F900244, SPU2->CORE_0->VOICE_11->SSAH);
			IOP->MMU->mapObject(0x1F900246, SPU2->CORE_0->VOICE_11->SSAL);
			IOP->MMU->mapObject(0x1F900248, SPU2->CORE_0->VOICE_11->LSAXH);
			IOP->MMU->mapObject(0x1F90024A, SPU2->CORE_0->VOICE_11->LSAXL);
			IOP->MMU->mapObject(0x1F90024C, SPU2->CORE_0->VOICE_11->NAXH);
			IOP->MMU->mapObject(0x1F90024E, SPU2->CORE_0->VOICE_11->NAXL);
			IOP->MMU->mapObject(0x1F900250, SPU2->CORE_0->VOICE_12->SSAH);
			IOP->MMU->mapObject(0x1F900252, SPU2->CORE_0->VOICE_12->SSAL);
			IOP->MMU->mapObject(0x1F900254, SPU2->CORE_0->VOICE_12->LSAXH);
			IOP->MMU->mapObject(0x1F900256, SPU2->CORE_0->VOICE_12->LSAXL);
			IOP->MMU->mapObject(0x1F900258, SPU2->CORE_0->VOICE_12->NAXH);
			IOP->MMU->mapObject(0x1F90025A, SPU2->CORE_0->VOICE_12->NAXL);
			IOP->MMU->mapObject(0x1F90025C, SPU2->CORE_0->VOICE_13->SSAH);
			IOP->MMU->mapObject(0x1F90025E, SPU2->CORE_0->VOICE_13->SSAL);
			IOP->MMU->mapObject(0x1F900260, SPU2->CORE_0->VOICE_13->LSAXH);
			IOP->MMU->mapObject(0x1F900262, SPU2->CORE_0->VOICE_13->LSAXL);
			IOP->MMU->mapObject(0x1F900264, SPU2->CORE_0->VOICE_13->NAXH);
			IOP->MMU->mapObject(0x1F900266, SPU2->CORE_0->VOICE_13->NAXL);
			IOP->MMU->mapObject(0x1F900268, SPU2->CORE_0->VOICE_14->SSAH);
			IOP->MMU->mapObject(0x1F90026A, SPU2->CORE_0->VOICE_14->SSAL);
			IOP->MMU->mapObject(0x1F90026C, SPU2->CORE_0->VOICE_14->LSAXH);
			IOP->MMU->mapObject(0x1F90026E, SPU2->CORE_0->VOICE_14->LSAXL);
			IOP->MMU->mapObject(0x1F900270, SPU2->CORE_0->VOICE_14->NAXH);
			IOP->MMU->mapObject(0x1F900272, SPU2->CORE_0->VOICE_14->NAXL);
			IOP->MMU->mapObject(0x1F900274, SPU2->CORE_0->VOICE_15->SSAH);
			IOP->MMU->mapObject(0x1F900276, SPU2->CORE_0->VOICE_15->SSAL);
			IOP->MMU->mapObject(0x1F900278, SPU2->CORE_0->VOICE_15->LSAXH);
			IOP->MMU->mapObject(0x1F90027A, SPU2->CORE_0->VOICE_15->LSAXL);
			IOP->MMU->mapObject(0x1F90027C, SPU2->CORE_0->VOICE_15->NAXH);
			IOP->MMU->mapObject(0x1F90027E, SPU2->CORE_0->VOICE_15->NAXL);
			IOP->MMU->mapObject(0x1F900280, SPU2->CORE_0->VOICE_16->SSAH);
			IOP->MMU->mapObject(0x1F900282, SPU2->CORE_0->VOICE_16->SSAL);
			IOP->MMU->mapObject(0x1F900284, SPU2->CORE_0->VOICE_16->LSAXH);
			IOP->MMU->mapObject(0x1F900286, SPU2->CORE_0->VOICE_16->LSAXL);
			IOP->MMU->mapObject(0x1F900288, SPU2->CORE_0->VOICE_16->NAXH);
			IOP->MMU->mapObject(0x1F90028A, SPU2->CORE_0->VOICE_16->NAXL);
			IOP->MMU->mapObject(0x1F90028C, SPU2->CORE_0->VOICE_17->SSAH);
			IOP->MMU->mapObject(0x1F90028E, SPU2->CORE_0->VOICE_17->SSAL);
			IOP->MMU->mapObject(0x1F900290, SPU2->CORE_0->VOICE_17->LSAXH);
			IOP->MMU->mapObject(0x1F900292, SPU2->CORE_0->VOICE_17->LSAXL);
			IOP->MMU->mapObject(0x1F900294, SPU2->CORE_0->VOICE_17->NAXH);
			IOP->MMU->mapObject(0x1F900296, SPU2->CORE_0->VOICE_17->NAXL);
			IOP->MMU->mapObject(0x1F900298, SPU2->CORE_0->VOICE_18->SSAH);
			IOP->MMU->mapObject(0x1F90029A, SPU2->CORE_0->VOICE_18->SSAL);
			IOP->MMU->mapObject(0x1F90029C, SPU2->CORE_0->VOICE_18->LSAXH);
			IOP->MMU->mapObject(0x1F90029E, SPU2->CORE_0->VOICE_18->LSAXL);
			IOP->MMU->mapObject(0x1F9002A0, SPU2->CORE_0->VOICE_18->NAXH);
			IOP->MMU->mapObject(0x1F9002A2, SPU2->CORE_0->VOICE_18->NAXL);
			IOP->MMU->mapObject(0x1F9002A4, SPU2->CORE_0->VOICE_19->SSAH);
			IOP->MMU->mapObject(0x1F9002A6, SPU2->CORE_0->VOICE_19->SSAL);
			IOP->MMU->mapObject(0x1F9002A8, SPU2->CORE_0->VOICE_19->LSAXH);
			IOP->MMU->mapObject(0x1F9002AA, SPU2->CORE_0->VOICE_19->LSAXL);
			IOP->MMU->mapObject(0x1F9002AC, SPU2->CORE_0->VOICE_19->NAXH);
			IOP->MMU->mapObject(0x1F9002AE, SPU2->CORE_0->VOICE_19->NAXL);
			IOP->MMU->mapObject(0x1F9002B0, SPU2->CORE_0->VOICE_20->SSAH);
			IOP->MMU->mapObject(0x1F9002B2, SPU2->CORE_0->VOICE_20->SSAL);
			IOP->MMU->mapObject(0x1F9002B4, SPU2->CORE_0->VOICE_20->LSAXH);
			IOP->MMU->mapObject(0x1F9002B6, SPU2->CORE_0->VOICE_20->LSAXL);
			IOP->MMU->mapObject(0x1F9002B8, SPU2->CORE_0->VOICE_20->NAXH);
			IOP->MMU->mapObject(0x1F9002BA, SPU2->CORE_0->VOICE_20->NAXL);
			IOP->MMU->mapObject(0x1F9002BC, SPU2->CORE_0->VOICE_21->SSAH);
			IOP->MMU->mapObject(0x1F9002BE, SPU2->CORE_0->VOICE_21->SSAL);
			IOP->MMU->mapObject(0x1F9002C0, SPU2->CORE_0->VOICE_21->LSAXH);
			IOP->MMU->mapObject(0x1F9002C2, SPU2->CORE_0->VOICE_21->LSAXL);
			IOP->MMU->mapObject(0x1F9002C4, SPU2->CORE_0->VOICE_21->NAXH);
			IOP->MMU->mapObject(0x1F9002C6, SPU2->CORE_0->VOICE_21->NAXL);
			IOP->MMU->mapObject(0x1F9002C8, SPU2->CORE_0->VOICE_22->SSAH);
			IOP->MMU->mapObject(0x1F9002CA, SPU2->CORE_0->VOICE_22->SSAL);
			IOP->MMU->mapObject(0x1F9002CC, SPU2->CORE_0->VOICE_22->LSAXH);
			IOP->MMU->mapObject(0x1F9002CE, SPU2->CORE_0->VOICE_22->LSAXL);
			IOP->MMU->mapObject(0x1F9002D0, SPU2->CORE_0->VOICE_22->NAXH);
			IOP->MMU->mapObject(0x1F9002D2, SPU2->CORE_0->VOICE_22->NAXL);
			IOP->MMU->mapObject(0x1F9002D4, SPU2->CORE_0->VOICE_23->SSAH);
			IOP->MMU->mapObject(0x1F9002D6, SPU2->CORE_0->VOICE_23->SSAL);
			IOP->MMU->mapObject(0x1F9002D8, SPU2->CORE_0->VOICE_23->LSAXH);
			IOP->MMU->mapObject(0x1F9002DA, SPU2->CORE_0->VOICE_23->LSAXL);
			IOP->MMU->mapObject(0x1F9002DC, SPU2->CORE_0->VOICE_23->NAXH);
			IOP->MMU->mapObject(0x1F9002DE, SPU2->CORE_0->VOICE_23->NAXL);
			IOP->MMU->mapObject(0x1F9002E0, SPU2->CORE_0->ESAH);
			IOP->MMU->mapObject(0x1F9002E2, SPU2->CORE_0->ESAL);
			IOP->MMU->mapObject(0x1F9002E4, SPU2->CORE_0->APF1_SIZEH);
			IOP->MMU->mapObject(0x1F9002E6, SPU2->CORE_0->APF1_SIZEL);
			IOP->MMU->mapObject(0x1F9002E8, SPU2->CORE_0->APF2_SIZEH);
			IOP->MMU->mapObject(0x1F9002EA, SPU2->CORE_0->APF2_SIZEL);
			IOP->MMU->mapObject(0x1F9002EC, SPU2->CORE_0->SAME_L_DSTH);
			IOP->MMU->mapObject(0x1F9002EE, SPU2->CORE_0->SAME_L_DSTL);
			IOP->MMU->mapObject(0x1F9002F0, SPU2->CORE_0->SAME_R_DSTH);
			IOP->MMU->mapObject(0x1F9002F2, SPU2->CORE_0->SAME_R_DSTL);
			IOP->MMU->mapObject(0x1F9002F4, SPU2->CORE_0->COMB1_L_SRCH);
			IOP->MMU->mapObject(0x1F9002F6, SPU2->CORE_0->COMB1_L_SRCL);
			IOP->MMU->mapObject(0x1F9002F8, SPU2->CORE_0->COMB1_R_SRCH);
			IOP->MMU->mapObject(0x1F9002FA, SPU2->CORE_0->COMB1_R_SRCL);
			IOP->MMU->mapObject(0x1F9002FC, SPU2->CORE_0->COMB2_L_SRCH);
			IOP->MMU->mapObject(0x1F9002FE, SPU2->CORE_0->COMB2_L_SRCL);
			IOP->MMU->mapObject(0x1F900300, SPU2->CORE_0->COMB2_R_SRCH);
			IOP->MMU->mapObject(0x1F900302, SPU2->CORE_0->COMB2_R_SRCL);
			IOP->MMU->mapObject(0x1F900304, SPU2->CORE_0->SAME_L_SRCH);
			IOP->MMU->mapObject(0x1F900306, SPU2->CORE_0->SAME_L_SRCL);
			IOP->MMU->mapObject(0x1F900308, SPU2->CORE_0->SAME_R_SRCH);
			IOP->MMU->mapObject(0x1F90030A, SPU2->CORE_0->SAME_R_SRCL);
			IOP->MMU->mapObject(0x1F90030C, SPU2->CORE_0->DIFF_L_DSTH);
			IOP->MMU->mapObject(0x1F90030E, SPU2->CORE_0->DIFF_L_DSTL);
			IOP->MMU->mapObject(0x1F900310, SPU2->CORE_0->DIFF_R_DSTH);
			IOP->MMU->mapObject(0x1F900312, SPU2->CORE_0->DIFF_R_DSTL);
			IOP->MMU->mapObject(0x1F900314, SPU2->CORE_0->COMB3_L_SRCH);
			IOP->MMU->mapObject(0x1F900316, SPU2->CORE_0->COMB3_L_SRCL);
			IOP->MMU->mapObject(0x1F900318, SPU2->CORE_0->COMB3_R_SRCH);
			IOP->MMU->mapObject(0x1F90031A, SPU2->CORE_0->COMB3_R_SRCL);
			IOP->MMU->mapObject(0x1F90031C, SPU2->CORE_0->COMB4_L_SRCH);
			IOP->MMU->mapObject(0x1F90031E, SPU2->CORE_0->COMB4_L_SRCL);
			IOP->MMU->mapObject(0x1F900320, SPU2->CORE_0->COMB4_R_SRCH);
			IOP->MMU->mapObject(0x1F900322, SPU2->CORE_0->COMB4_R_SRCL);
			IOP->MMU->mapObject(0x1F900324, SPU2->CORE_0->DIFF_L_SRCH);
			IOP->MMU->mapObject(0x1F900326, SPU2->CORE_0->DIFF_L_SRCL);
			IOP->MMU->mapObject(0x1F900328, SPU2->CORE_0->DIFF_R_SRCH);
			IOP->MMU->mapObject(0x1F90032A, SPU2->CORE_0->DIFF_R_SRCL);
			IOP->MMU->mapObject(0x1F90032C, SPU2->CORE_0->APF1_L_DSTH);
			IOP->MMU->mapObject(0x1F90032E, SPU2->CORE_0->APF1_L_DSTL);
			IOP->MMU->mapObject(0x1F900330, SPU2->CORE_0->APF1_R_DSTH);
			IOP->MMU->mapObject(0x1F900332, SPU2->CORE_0->APF1_R_DSTL);
			IOP->MMU->mapObject(0x1F900334, SPU2->CORE_0->APF2_L_DSTH);
			IOP->MMU->mapObject(0x1F900336, SPU2->CORE_0->APF2_L_DSTL);
			IOP->MMU->mapObject(0x1F900338, SPU2->CORE_0->APF2_R_DSTH);
			IOP->MMU->mapObject(0x1F90033A, SPU2->CORE_0->APF2_R_DSTL);
			IOP->MMU->mapObject(0x1F90033C, SPU2->CORE_0->EEAH);
			IOP->MMU->mapObject(0x1F90033E, SPU2->CORE_0->EEAL);
			IOP->MMU->mapObject(0x1F900340, SPU2->CORE_0->ENDX0);
			IOP->MMU->mapObject(0x1F900342, SPU2->CORE_0->ENDX1);
			IOP->MMU->mapObject(0x1F900344, SPU2->CORE_0->STATX);
			IOP->MMU->mapObject(0x1F900346, SPU2->CORE_0->MEMORY_0346);
			IOP->MMU->mapObject(0x1F900400, SPU2->CORE_1->VOICE_0->VOLL);
			IOP->MMU->mapObject(0x1F900402, SPU2->CORE_1->VOICE_0->VOLR);
			IOP->MMU->mapObject(0x1F900404, SPU2->CORE_1->VOICE_0->PITCH);
			IOP->MMU->mapObject(0x1F900406, SPU2->CORE_1->VOICE_0->ADSR1);
			IOP->MMU->mapObject(0x1F900408, SPU2->CORE_1->VOICE_0->ADSR2);
			IOP->MMU->mapObject(0x1F90040A, SPU2->CORE_1->VOICE_0->ENVX);
			IOP->MMU->mapObject(0x1F90040C, SPU2->CORE_1->VOICE_0->VOLXL);
			IOP->MMU->mapObject(0x1F90040E, SPU2->CORE_1->VOICE_0->VOLXR);
			IOP->MMU->mapObject(0x1F900410, SPU2->CORE_1->VOICE_1->VOLL);
			IOP->MMU->mapObject(0x1F900412, SPU2->CORE_1->VOICE_1->VOLR);
			IOP->MMU->mapObject(0x1F900414, SPU2->CORE_1->VOICE_1->PITCH);
			IOP->MMU->mapObject(0x1F900416, SPU2->CORE_1->VOICE_1->ADSR1);
			IOP->MMU->mapObject(0x1F900418, SPU2->CORE_1->VOICE_1->ADSR2);
			IOP->MMU->mapObject(0x1F90041A, SPU2->CORE_1->VOICE_1->ENVX);
			IOP->MMU->mapObject(0x1F90041C, SPU2->CORE_1->VOICE_1->VOLXL);
			IOP->MMU->mapObject(0x1F90041E, SPU2->CORE_1->VOICE_1->VOLXR);
			IOP->MMU->mapObject(0x1F900420, SPU2->CORE_1->VOICE_2->VOLL);
			IOP->MMU->mapObject(0x1F900422, SPU2->CORE_1->VOICE_2->VOLR);
			IOP->MMU->mapObject(0x1F900424, SPU2->CORE_1->VOICE_2->PITCH);
			IOP->MMU->mapObject(0x1F900426, SPU2->CORE_1->VOICE_2->ADSR1);
			IOP->MMU->mapObject(0x1F900428, SPU2->CORE_1->VOICE_2->ADSR2);
			IOP->MMU->mapObject(0x1F90042A, SPU2->CORE_1->VOICE_2->ENVX);
			IOP->MMU->mapObject(0x1F90042C, SPU2->CORE_1->VOICE_2->VOLXL);
			IOP->MMU->mapObject(0x1F90042E, SPU2->CORE_1->VOICE_2->VOLXR);
			IOP->MMU->mapObject(0x1F900430, SPU2->CORE_1->VOICE_3->VOLL);
			IOP->MMU->mapObject(0x1F900432, SPU2->CORE_1->VOICE_3->VOLR);
			IOP->MMU->mapObject(0x1F900434, SPU2->CORE_1->VOICE_3->PITCH);
			IOP->MMU->mapObject(0x1F900436, SPU2->CORE_1->VOICE_3->ADSR1);
			IOP->MMU->mapObject(0x1F900438, SPU2->CORE_1->VOICE_3->ADSR2);
			IOP->MMU->mapObject(0x1F90043A, SPU2->CORE_1->VOICE_3->ENVX);
			IOP->MMU->mapObject(0x1F90043C, SPU2->CORE_1->VOICE_3->VOLXL);
			IOP->MMU->mapObject(0x1F90043E, SPU2->CORE_1->VOICE_3->VOLXR);
			IOP->MMU->mapObject(0x1F900440, SPU2->CORE_1->VOICE_4->VOLL);
			IOP->MMU->mapObject(0x1F900442, SPU2->CORE_1->VOICE_4->VOLR);
			IOP->MMU->mapObject(0x1F900444, SPU2->CORE_1->VOICE_4->PITCH);
			IOP->MMU->mapObject(0x1F900446, SPU2->CORE_1->VOICE_4->ADSR1);
			IOP->MMU->mapObject(0x1F900448, SPU2->CORE_1->VOICE_4->ADSR2);
			IOP->MMU->mapObject(0x1F90044A, SPU2->CORE_1->VOICE_4->ENVX);
			IOP->MMU->mapObject(0x1F90044C, SPU2->CORE_1->VOICE_4->VOLXL);
			IOP->MMU->mapObject(0x1F90044E, SPU2->CORE_1->VOICE_4->VOLXR);
			IOP->MMU->mapObject(0x1F900450, SPU2->CORE_1->VOICE_5->VOLL);
			IOP->MMU->mapObject(0x1F900452, SPU2->CORE_1->VOICE_5->VOLR);
			IOP->MMU->mapObject(0x1F900454, SPU2->CORE_1->VOICE_5->PITCH);
			IOP->MMU->mapObject(0x1F900456, SPU2->CORE_1->VOICE_5->ADSR1);
			IOP->MMU->mapObject(0x1F900458, SPU2->CORE_1->VOICE_5->ADSR2);
			IOP->MMU->mapObject(0x1F90045A, SPU2->CORE_1->VOICE_5->ENVX);
			IOP->MMU->mapObject(0x1F90045C, SPU2->CORE_1->VOICE_5->VOLXL);
			IOP->MMU->mapObject(0x1F90045E, SPU2->CORE_1->VOICE_5->VOLXR);
			IOP->MMU->mapObject(0x1F900460, SPU2->CORE_1->VOICE_6->VOLL);
			IOP->MMU->mapObject(0x1F900462, SPU2->CORE_1->VOICE_6->VOLR);
			IOP->MMU->mapObject(0x1F900464, SPU2->CORE_1->VOICE_6->PITCH);
			IOP->MMU->mapObject(0x1F900466, SPU2->CORE_1->VOICE_6->ADSR1);
			IOP->MMU->mapObject(0x1F900468, SPU2->CORE_1->VOICE_6->ADSR2);
			IOP->MMU->mapObject(0x1F90046A, SPU2->CORE_1->VOICE_6->ENVX);
			IOP->MMU->mapObject(0x1F90046C, SPU2->CORE_1->VOICE_6->VOLXL);
			IOP->MMU->mapObject(0x1F90046E, SPU2->CORE_1->VOICE_6->VOLXR);
			IOP->MMU->mapObject(0x1F900470, SPU2->CORE_1->VOICE_7->VOLL);
			IOP->MMU->mapObject(0x1F900472, SPU2->CORE_1->VOICE_7->VOLR);
			IOP->MMU->mapObject(0x1F900474, SPU2->CORE_1->VOICE_7->PITCH);
			IOP->MMU->mapObject(0x1F900476, SPU2->CORE_1->VOICE_7->ADSR1);
			IOP->MMU->mapObject(0x1F900478, SPU2->CORE_1->VOICE_7->ADSR2);
			IOP->MMU->mapObject(0x1F90047A, SPU2->CORE_1->VOICE_7->ENVX);
			IOP->MMU->mapObject(0x1F90047C, SPU2->CORE_1->VOICE_7->VOLXL);
			IOP->MMU->mapObject(0x1F90047E, SPU2->CORE_1->VOICE_7->VOLXR);
			IOP->MMU->mapObject(0x1F900480, SPU2->CORE_1->VOICE_8->VOLL);
			IOP->MMU->mapObject(0x1F900482, SPU2->CORE_1->VOICE_8->VOLR);
			IOP->MMU->mapObject(0x1F900484, SPU2->CORE_1->VOICE_8->PITCH);
			IOP->MMU->mapObject(0x1F900486, SPU2->CORE_1->VOICE_8->ADSR1);
			IOP->MMU->mapObject(0x1F900488, SPU2->CORE_1->VOICE_8->ADSR2);
			IOP->MMU->mapObject(0x1F90048A, SPU2->CORE_1->VOICE_8->ENVX);
			IOP->MMU->mapObject(0x1F90048C, SPU2->CORE_1->VOICE_8->VOLXL);
			IOP->MMU->mapObject(0x1F90048E, SPU2->CORE_1->VOICE_8->VOLXR);
			IOP->MMU->mapObject(0x1F900490, SPU2->CORE_1->VOICE_9->VOLL);
			IOP->MMU->mapObject(0x1F900492, SPU2->CORE_1->VOICE_9->VOLR);
			IOP->MMU->mapObject(0x1F900494, SPU2->CORE_1->VOICE_9->PITCH);
			IOP->MMU->mapObject(0x1F900496, SPU2->CORE_1->VOICE_9->ADSR1);
			IOP->MMU->mapObject(0x1F900498, SPU2->CORE_1->VOICE_9->ADSR2);
			IOP->MMU->mapObject(0x1F90049A, SPU2->CORE_1->VOICE_9->ENVX);
			IOP->MMU->mapObject(0x1F90049C, SPU2->CORE_1->VOICE_9->VOLXL);
			IOP->MMU->mapObject(0x1F90049E, SPU2->CORE_1->VOICE_9->VOLXR);
			IOP->MMU->mapObject(0x1F9004A0, SPU2->CORE_1->VOICE_10->VOLL);
			IOP->MMU->mapObject(0x1F9004A2, SPU2->CORE_1->VOICE_10->VOLR);
			IOP->MMU->mapObject(0x1F9004A4, SPU2->CORE_1->VOICE_10->PITCH);
			IOP->MMU->mapObject(0x1F9004A6, SPU2->CORE_1->VOICE_10->ADSR1);
			IOP->MMU->mapObject(0x1F9004A8, SPU2->CORE_1->VOICE_10->ADSR2);
			IOP->MMU->mapObject(0x1F9004AA, SPU2->CORE_1->VOICE_10->ENVX);
			IOP->MMU->mapObject(0x1F9004AC, SPU2->CORE_1->VOICE_10->VOLXL);
			IOP->MMU->mapObject(0x1F9004AE, SPU2->CORE_1->VOICE_10->VOLXR);
			IOP->MMU->mapObject(0x1F9004B0, SPU2->CORE_1->VOICE_11->VOLL);
			IOP->MMU->mapObject(0x1F9004B2, SPU2->CORE_1->VOICE_11->VOLR);
			IOP->MMU->mapObject(0x1F9004B4, SPU2->CORE_1->VOICE_11->PITCH);
			IOP->MMU->mapObject(0x1F9004B6, SPU2->CORE_1->VOICE_11->ADSR1);
			IOP->MMU->mapObject(0x1F9004B8, SPU2->CORE_1->VOICE_11->ADSR2);
			IOP->MMU->mapObject(0x1F9004BA, SPU2->CORE_1->VOICE_11->ENVX);
			IOP->MMU->mapObject(0x1F9004BC, SPU2->CORE_1->VOICE_11->VOLXL);
			IOP->MMU->mapObject(0x1F9004BE, SPU2->CORE_1->VOICE_11->VOLXR);
			IOP->MMU->mapObject(0x1F9004C0, SPU2->CORE_1->VOICE_12->VOLL);
			IOP->MMU->mapObject(0x1F9004C2, SPU2->CORE_1->VOICE_12->VOLR);
			IOP->MMU->mapObject(0x1F9004C4, SPU2->CORE_1->VOICE_12->PITCH);
			IOP->MMU->mapObject(0x1F9004C6, SPU2->CORE_1->VOICE_12->ADSR1);
			IOP->MMU->mapObject(0x1F9004C8, SPU2->CORE_1->VOICE_12->ADSR2);
			IOP->MMU->mapObject(0x1F9004CA, SPU2->CORE_1->VOICE_12->ENVX);
			IOP->MMU->mapObject(0x1F9004CC, SPU2->CORE_1->VOICE_12->VOLXL);
			IOP->MMU->mapObject(0x1F9004CE, SPU2->CORE_1->VOICE_12->VOLXR);
			IOP->MMU->mapObject(0x1F9004D0, SPU2->CORE_1->VOICE_13->VOLL);
			IOP->MMU->mapObject(0x1F9004D2, SPU2->CORE_1->VOICE_13->VOLR);
			IOP->MMU->mapObject(0x1F9004D4, SPU2->CORE_1->VOICE_13->PITCH);
			IOP->MMU->mapObject(0x1F9004D6, SPU2->CORE_1->VOICE_13->ADSR1);
			IOP->MMU->mapObject(0x1F9004D8, SPU2->CORE_1->VOICE_13->ADSR2);
			IOP->MMU->mapObject(0x1F9004DA, SPU2->CORE_1->VOICE_13->ENVX);
			IOP->MMU->mapObject(0x1F9004DC, SPU2->CORE_1->VOICE_13->VOLXL);
			IOP->MMU->mapObject(0x1F9004DE, SPU2->CORE_1->VOICE_13->VOLXR);
			IOP->MMU->mapObject(0x1F9004E0, SPU2->CORE_1->VOICE_14->VOLL);
			IOP->MMU->mapObject(0x1F9004E2, SPU2->CORE_1->VOICE_14->VOLR);
			IOP->MMU->mapObject(0x1F9004E4, SPU2->CORE_1->VOICE_14->PITCH);
			IOP->MMU->mapObject(0x1F9004E6, SPU2->CORE_1->VOICE_14->ADSR1);
			IOP->MMU->mapObject(0x1F9004E8, SPU2->CORE_1->VOICE_14->ADSR2);
			IOP->MMU->mapObject(0x1F9004EA, SPU2->CORE_1->VOICE_14->ENVX);
			IOP->MMU->mapObject(0x1F9004EC, SPU2->CORE_1->VOICE_14->VOLXL);
			IOP->MMU->mapObject(0x1F9004EE, SPU2->CORE_1->VOICE_14->VOLXR);
			IOP->MMU->mapObject(0x1F9004F0, SPU2->CORE_1->VOICE_15->VOLL);
			IOP->MMU->mapObject(0x1F9004F2, SPU2->CORE_1->VOICE_15->VOLR);
			IOP->MMU->mapObject(0x1F9004F4, SPU2->CORE_1->VOICE_15->PITCH);
			IOP->MMU->mapObject(0x1F9004F6, SPU2->CORE_1->VOICE_15->ADSR1);
			IOP->MMU->mapObject(0x1F9004F8, SPU2->CORE_1->VOICE_15->ADSR2);
			IOP->MMU->mapObject(0x1F9004FA, SPU2->CORE_1->VOICE_15->ENVX);
			IOP->MMU->mapObject(0x1F9004FC, SPU2->CORE_1->VOICE_15->VOLXL);
			IOP->MMU->mapObject(0x1F9004FE, SPU2->CORE_1->VOICE_15->VOLXR);
			IOP->MMU->mapObject(0x1F900500, SPU2->CORE_1->VOICE_16->VOLL);
			IOP->MMU->mapObject(0x1F900502, SPU2->CORE_1->VOICE_16->VOLR);
			IOP->MMU->mapObject(0x1F900504, SPU2->CORE_1->VOICE_16->PITCH);
			IOP->MMU->mapObject(0x1F900506, SPU2->CORE_1->VOICE_16->ADSR1);
			IOP->MMU->mapObject(0x1F900508, SPU2->CORE_1->VOICE_16->ADSR2);
			IOP->MMU->mapObject(0x1F90050A, SPU2->CORE_1->VOICE_16->ENVX);
			IOP->MMU->mapObject(0x1F90050C, SPU2->CORE_1->VOICE_16->VOLXL);
			IOP->MMU->mapObject(0x1F90050E, SPU2->CORE_1->VOICE_16->VOLXR);
			IOP->MMU->mapObject(0x1F900510, SPU2->CORE_1->VOICE_17->VOLL);
			IOP->MMU->mapObject(0x1F900512, SPU2->CORE_1->VOICE_17->VOLR);
			IOP->MMU->mapObject(0x1F900514, SPU2->CORE_1->VOICE_17->PITCH);
			IOP->MMU->mapObject(0x1F900516, SPU2->CORE_1->VOICE_17->ADSR1);
			IOP->MMU->mapObject(0x1F900518, SPU2->CORE_1->VOICE_17->ADSR2);
			IOP->MMU->mapObject(0x1F90051A, SPU2->CORE_1->VOICE_17->ENVX);
			IOP->MMU->mapObject(0x1F90051C, SPU2->CORE_1->VOICE_17->VOLXL);
			IOP->MMU->mapObject(0x1F90051E, SPU2->CORE_1->VOICE_17->VOLXR);
			IOP->MMU->mapObject(0x1F900520, SPU2->CORE_1->VOICE_18->VOLL);
			IOP->MMU->mapObject(0x1F900522, SPU2->CORE_1->VOICE_18->VOLR);
			IOP->MMU->mapObject(0x1F900524, SPU2->CORE_1->VOICE_18->PITCH);
			IOP->MMU->mapObject(0x1F900526, SPU2->CORE_1->VOICE_18->ADSR1);
			IOP->MMU->mapObject(0x1F900528, SPU2->CORE_1->VOICE_18->ADSR2);
			IOP->MMU->mapObject(0x1F90052A, SPU2->CORE_1->VOICE_18->ENVX);
			IOP->MMU->mapObject(0x1F90052C, SPU2->CORE_1->VOICE_18->VOLXL);
			IOP->MMU->mapObject(0x1F90052E, SPU2->CORE_1->VOICE_18->VOLXR);
			IOP->MMU->mapObject(0x1F900530, SPU2->CORE_1->VOICE_19->VOLL);
			IOP->MMU->mapObject(0x1F900532, SPU2->CORE_1->VOICE_19->VOLR);
			IOP->MMU->mapObject(0x1F900534, SPU2->CORE_1->VOICE_19->PITCH);
			IOP->MMU->mapObject(0x1F900536, SPU2->CORE_1->VOICE_19->ADSR1);
			IOP->MMU->mapObject(0x1F900538, SPU2->CORE_1->VOICE_19->ADSR2);
			IOP->MMU->mapObject(0x1F90053A, SPU2->CORE_1->VOICE_19->ENVX);
			IOP->MMU->mapObject(0x1F90053C, SPU2->CORE_1->VOICE_19->VOLXL);
			IOP->MMU->mapObject(0x1F90053E, SPU2->CORE_1->VOICE_19->VOLXR);
			IOP->MMU->mapObject(0x1F900540, SPU2->CORE_1->VOICE_20->VOLL);
			IOP->MMU->mapObject(0x1F900542, SPU2->CORE_1->VOICE_20->VOLR);
			IOP->MMU->mapObject(0x1F900544, SPU2->CORE_1->VOICE_20->PITCH);
			IOP->MMU->mapObject(0x1F900546, SPU2->CORE_1->VOICE_20->ADSR1);
			IOP->MMU->mapObject(0x1F900548, SPU2->CORE_1->VOICE_20->ADSR2);
			IOP->MMU->mapObject(0x1F90054A, SPU2->CORE_1->VOICE_20->ENVX);
			IOP->MMU->mapObject(0x1F90054C, SPU2->CORE_1->VOICE_20->VOLXL);
			IOP->MMU->mapObject(0x1F90054E, SPU2->CORE_1->VOICE_20->VOLXR);
			IOP->MMU->mapObject(0x1F900550, SPU2->CORE_1->VOICE_21->VOLL);
			IOP->MMU->mapObject(0x1F900552, SPU2->CORE_1->VOICE_21->VOLR);
			IOP->MMU->mapObject(0x1F900554, SPU2->CORE_1->VOICE_21->PITCH);
			IOP->MMU->mapObject(0x1F900556, SPU2->CORE_1->VOICE_21->ADSR1);
			IOP->MMU->mapObject(0x1F900558, SPU2->CORE_1->VOICE_21->ADSR2);
			IOP->MMU->mapObject(0x1F90055A, SPU2->CORE_1->VOICE_21->ENVX);
			IOP->MMU->mapObject(0x1F90055C, SPU2->CORE_1->VOICE_21->VOLXL);
			IOP->MMU->mapObject(0x1F90055E, SPU2->CORE_1->VOICE_21->VOLXR);
			IOP->MMU->mapObject(0x1F900560, SPU2->CORE_1->VOICE_22->VOLL);
			IOP->MMU->mapObject(0x1F900562, SPU2->CORE_1->VOICE_22->VOLR);
			IOP->MMU->mapObject(0x1F900564, SPU2->CORE_1->VOICE_22->PITCH);
			IOP->MMU->mapObject(0x1F900566, SPU2->CORE_1->VOICE_22->ADSR1);
			IOP->MMU->mapObject(0x1F900568, SPU2->CORE_1->VOICE_22->ADSR2);
			IOP->MMU->mapObject(0x1F90056A, SPU2->CORE_1->VOICE_22->ENVX);
			IOP->MMU->mapObject(0x1F90056C, SPU2->CORE_1->VOICE_22->VOLXL);
			IOP->MMU->mapObject(0x1F90056E, SPU2->CORE_1->VOICE_22->VOLXR);
			IOP->MMU->mapObject(0x1F900570, SPU2->CORE_1->VOICE_23->VOLL);
			IOP->MMU->mapObject(0x1F900572, SPU2->CORE_1->VOICE_23->VOLR);
			IOP->MMU->mapObject(0x1F900574, SPU2->CORE_1->VOICE_23->PITCH);
			IOP->MMU->mapObject(0x1F900576, SPU2->CORE_1->VOICE_23->ADSR1);
			IOP->MMU->mapObject(0x1F900578, SPU2->CORE_1->VOICE_23->ADSR2);
			IOP->MMU->mapObject(0x1F90057A, SPU2->CORE_1->VOICE_23->ENVX);
			IOP->MMU->mapObject(0x1F90057C, SPU2->CORE_1->VOICE_23->VOLXL);
			IOP->MMU->mapObject(0x1F90057E, SPU2->CORE_1->VOICE_23->VOLXR);
			IOP->MMU->mapObject(0x1F900580, SPU2->CORE_1->PMON0);
			IOP->MMU->mapObject(0x1F900582, SPU2->CORE_1->PMON1);
			IOP->MMU->mapObject(0x1F900584, SPU2->CORE_1->NON0);
			IOP->MMU->mapObject(0x1F900586, SPU2->CORE_1->NON1);
			IOP->MMU->mapObject(0x1F900588, SPU2->CORE_1->VMIXL0);
			IOP->MMU->mapObject(0x1F90058A, SPU2->CORE_1->VMIXL1);
			IOP->MMU->mapObject(0x1F90058C, SPU2->CORE_1->VMIXEL0);
			IOP->MMU->mapObject(0x1F90058E, SPU2->CORE_1->VMIXEL1);
			IOP->MMU->mapObject(0x1F900590, SPU2->CORE_1->VMIXR0);
			IOP->MMU->mapObject(0x1F900592, SPU2->CORE_1->VMIXR1);
			IOP->MMU->mapObject(0x1F900594, SPU2->CORE_1->VMIXER0);
			IOP->MMU->mapObject(0x1F900596, SPU2->CORE_1->VMIXER1);
			IOP->MMU->mapObject(0x1F900598, SPU2->CORE_1->MMIX);
			IOP->MMU->mapObject(0x1F90059A, SPU2->CORE_1->ATTR);
			IOP->MMU->mapObject(0x1F90059C, SPU2->CORE_1->IRQAH);
			IOP->MMU->mapObject(0x1F90059E, SPU2->CORE_1->IRQAL);
			IOP->MMU->mapObject(0x1F9005A0, SPU2->CORE_1->KON0);
			IOP->MMU->mapObject(0x1F9005A2, SPU2->CORE_1->KON1);
			IOP->MMU->mapObject(0x1F9005A4, SPU2->CORE_1->KOF0);
			IOP->MMU->mapObject(0x1F9005A6, SPU2->CORE_1->KOF1);
			IOP->MMU->mapObject(0x1F9005A8, SPU2->CORE_1->TSAH);
			IOP->MMU->mapObject(0x1F9005AA, SPU2->CORE_1->TSAL);
			IOP->MMU->mapObject(0x1F9005AC, SPU2->CORE_1->DATA0);
			IOP->MMU->mapObject(0x1F9005AE, SPU2->CORE_1->DATA1);
			IOP->MMU->mapObject(0x1F9005B0, SPU2->CORE_1->ADMAS);
			IOP->MMU->mapObject(0x1F9005C0, SPU2->CORE_1->VOICE_0->SSAH);
			IOP->MMU->mapObject(0x1F9005C2, SPU2->CORE_1->VOICE_0->SSAL);
			IOP->MMU->mapObject(0x1F9005C4, SPU2->CORE_1->VOICE_0->LSAXH);
			IOP->MMU->mapObject(0x1F9005C6, SPU2->CORE_1->VOICE_0->LSAXL);
			IOP->MMU->mapObject(0x1F9005C8, SPU2->CORE_1->VOICE_0->NAXH);
			IOP->MMU->mapObject(0x1F9005CA, SPU2->CORE_1->VOICE_0->NAXL);
			IOP->MMU->mapObject(0x1F9005CC, SPU2->CORE_1->VOICE_1->SSAH);
			IOP->MMU->mapObject(0x1F9005CE, SPU2->CORE_1->VOICE_1->SSAL);
			IOP->MMU->mapObject(0x1F9005D0, SPU2->CORE_1->VOICE_1->LSAXH);
			IOP->MMU->mapObject(0x1F9005D2, SPU2->CORE_1->VOICE_1->LSAXL);
			IOP->MMU->mapObject(0x1F9005D4, SPU2->CORE_1->VOICE_1->NAXH);
			IOP->MMU->mapObject(0x1F9005D6, SPU2->CORE_1->VOICE_1->NAXL);
			IOP->MMU->mapObject(0x1F9005D8, SPU2->CORE_1->VOICE_2->SSAH);
			IOP->MMU->mapObject(0x1F9005DA, SPU2->CORE_1->VOICE_2->SSAL);
			IOP->MMU->mapObject(0x1F9005DC, SPU2->CORE_1->VOICE_2->LSAXH);
			IOP->MMU->mapObject(0x1F9005DE, SPU2->CORE_1->VOICE_2->LSAXL);
			IOP->MMU->mapObject(0x1F9005E0, SPU2->CORE_1->VOICE_2->NAXH);
			IOP->MMU->mapObject(0x1F9005E2, SPU2->CORE_1->VOICE_2->NAXL);
			IOP->MMU->mapObject(0x1F9005E4, SPU2->CORE_1->VOICE_3->SSAH);
			IOP->MMU->mapObject(0x1F9005E6, SPU2->CORE_1->VOICE_3->SSAL);
			IOP->MMU->mapObject(0x1F9005E8, SPU2->CORE_1->VOICE_3->LSAXH);
			IOP->MMU->mapObject(0x1F9005EA, SPU2->CORE_1->VOICE_3->LSAXL);
			IOP->MMU->mapObject(0x1F9005EC, SPU2->CORE_1->VOICE_3->NAXH);
			IOP->MMU->mapObject(0x1F9005EE, SPU2->CORE_1->VOICE_3->NAXL);
			IOP->MMU->mapObject(0x1F9005F0, SPU2->CORE_1->VOICE_4->SSAH);
			IOP->MMU->mapObject(0x1F9005F2, SPU2->CORE_1->VOICE_4->SSAL);
			IOP->MMU->mapObject(0x1F9005F4, SPU2->CORE_1->VOICE_4->LSAXH);
			IOP->MMU->mapObject(0x1F9005F6, SPU2->CORE_1->VOICE_4->LSAXL);
			IOP->MMU->mapObject(0x1F9005F8, SPU2->CORE_1->VOICE_4->NAXH);
			IOP->MMU->mapObject(0x1F9005FA, SPU2->CORE_1->VOICE_4->NAXL);
			IOP->MMU->mapObject(0x1F9005FC, SPU2->CORE_1->VOICE_5->SSAH);
			IOP->MMU->mapObject(0x1F9005FE, SPU2->CORE_1->VOICE_5->SSAL);
			IOP->MMU->mapObject(0x1F900600, SPU2->CORE_1->VOICE_5->LSAXH);
			IOP->MMU->mapObject(0x1F900602, SPU2->CORE_1->VOICE_5->LSAXL);
			IOP->MMU->mapObject(0x1F900604, SPU2->CORE_1->VOICE_5->NAXH);
			IOP->MMU->mapObject(0x1F900606, SPU2->CORE_1->VOICE_5->NAXL);
			IOP->MMU->mapObject(0x1F900608, SPU2->CORE_1->VOICE_6->SSAH);
			IOP->MMU->mapObject(0x1F90060A, SPU2->CORE_1->VOICE_6->SSAL);
			IOP->MMU->mapObject(0x1F90060C, SPU2->CORE_1->VOICE_6->LSAXH);
			IOP->MMU->mapObject(0x1F90060E, SPU2->CORE_1->VOICE_6->LSAXL);
			IOP->MMU->mapObject(0x1F900610, SPU2->CORE_1->VOICE_6->NAXH);
			IOP->MMU->mapObject(0x1F900612, SPU2->CORE_1->VOICE_6->NAXL);
			IOP->MMU->mapObject(0x1F900614, SPU2->CORE_1->VOICE_7->SSAH);
			IOP->MMU->mapObject(0x1F900616, SPU2->CORE_1->VOICE_7->SSAL);
			IOP->MMU->mapObject(0x1F900618, SPU2->CORE_1->VOICE_7->LSAXH);
			IOP->MMU->mapObject(0x1F90061A, SPU2->CORE_1->VOICE_7->LSAXL);
			IOP->MMU->mapObject(0x1F90061C, SPU2->CORE_1->VOICE_7->NAXH);
			IOP->MMU->mapObject(0x1F90061E, SPU2->CORE_1->VOICE_7->NAXL);
			IOP->MMU->mapObject(0x1F900620, SPU2->CORE_1->VOICE_8->SSAH);
			IOP->MMU->mapObject(0x1F900622, SPU2->CORE_1->VOICE_8->SSAL);
			IOP->MMU->mapObject(0x1F900624, SPU2->CORE_1->VOICE_8->LSAXH);
			IOP->MMU->mapObject(0x1F900626, SPU2->CORE_1->VOICE_8->LSAXL);
			IOP->MMU->mapObject(0x1F900628, SPU2->CORE_1->VOICE_8->NAXH);
			IOP->MMU->mapObject(0x1F90062A, SPU2->CORE_1->VOICE_8->NAXL);
			IOP->MMU->mapObject(0x1F90062C, SPU2->CORE_1->VOICE_9->SSAH);
			IOP->MMU->mapObject(0x1F90062E, SPU2->CORE_1->VOICE_9->SSAL);
			IOP->MMU->mapObject(0x1F900630, SPU2->CORE_1->VOICE_9->LSAXH);
			IOP->MMU->mapObject(0x1F900632, SPU2->CORE_1->VOICE_9->LSAXL);
			IOP->MMU->mapObject(0x1F900634, SPU2->CORE_1->VOICE_9->NAXH);
			IOP->MMU->mapObject(0x1F900636, SPU2->CORE_1->VOICE_9->NAXL);
			IOP->MMU->mapObject(0x1F900638, SPU2->CORE_1->VOICE_10->SSAH);
			IOP->MMU->mapObject(0x1F90063A, SPU2->CORE_1->VOICE_10->SSAL);
			IOP->MMU->mapObject(0x1F90063C, SPU2->CORE_1->VOICE_10->LSAXH);
			IOP->MMU->mapObject(0x1F90063E, SPU2->CORE_1->VOICE_10->LSAXL);
			IOP->MMU->mapObject(0x1F900640, SPU2->CORE_1->VOICE_10->NAXH);
			IOP->MMU->mapObject(0x1F900642, SPU2->CORE_1->VOICE_10->NAXL);
			IOP->MMU->mapObject(0x1F900644, SPU2->CORE_1->VOICE_11->SSAH);
			IOP->MMU->mapObject(0x1F900646, SPU2->CORE_1->VOICE_11->SSAL);
			IOP->MMU->mapObject(0x1F900648, SPU2->CORE_1->VOICE_11->LSAXH);
			IOP->MMU->mapObject(0x1F90064A, SPU2->CORE_1->VOICE_11->LSAXL);
			IOP->MMU->mapObject(0x1F90064C, SPU2->CORE_1->VOICE_11->NAXH);
			IOP->MMU->mapObject(0x1F90064E, SPU2->CORE_1->VOICE_11->NAXL);
			IOP->MMU->mapObject(0x1F900650, SPU2->CORE_1->VOICE_12->SSAH);
			IOP->MMU->mapObject(0x1F900652, SPU2->CORE_1->VOICE_12->SSAL);
			IOP->MMU->mapObject(0x1F900654, SPU2->CORE_1->VOICE_12->LSAXH);
			IOP->MMU->mapObject(0x1F900656, SPU2->CORE_1->VOICE_12->LSAXL);
			IOP->MMU->mapObject(0x1F900658, SPU2->CORE_1->VOICE_12->NAXH);
			IOP->MMU->mapObject(0x1F90065A, SPU2->CORE_1->VOICE_12->NAXL);
			IOP->MMU->mapObject(0x1F90065C, SPU2->CORE_1->VOICE_13->SSAH);
			IOP->MMU->mapObject(0x1F90065E, SPU2->CORE_1->VOICE_13->SSAL);
			IOP->MMU->mapObject(0x1F900660, SPU2->CORE_1->VOICE_13->LSAXH);
			IOP->MMU->mapObject(0x1F900662, SPU2->CORE_1->VOICE_13->LSAXL);
			IOP->MMU->mapObject(0x1F900664, SPU2->CORE_1->VOICE_13->NAXH);
			IOP->MMU->mapObject(0x1F900666, SPU2->CORE_1->VOICE_13->NAXL);
			IOP->MMU->mapObject(0x1F900668, SPU2->CORE_1->VOICE_14->SSAH);
			IOP->MMU->mapObject(0x1F90066A, SPU2->CORE_1->VOICE_14->SSAL);
			IOP->MMU->mapObject(0x1F90066C, SPU2->CORE_1->VOICE_14->LSAXH);
			IOP->MMU->mapObject(0x1F90066E, SPU2->CORE_1->VOICE_14->LSAXL);
			IOP->MMU->mapObject(0x1F900670, SPU2->CORE_1->VOICE_14->NAXH);
			IOP->MMU->mapObject(0x1F900672, SPU2->CORE_1->VOICE_14->NAXL);
			IOP->MMU->mapObject(0x1F900674, SPU2->CORE_1->VOICE_15->SSAH);
			IOP->MMU->mapObject(0x1F900676, SPU2->CORE_1->VOICE_15->SSAL);
			IOP->MMU->mapObject(0x1F900678, SPU2->CORE_1->VOICE_15->LSAXH);
			IOP->MMU->mapObject(0x1F90067A, SPU2->CORE_1->VOICE_15->LSAXL);
			IOP->MMU->mapObject(0x1F90067C, SPU2->CORE_1->VOICE_15->NAXH);
			IOP->MMU->mapObject(0x1F90067E, SPU2->CORE_1->VOICE_15->NAXL);
			IOP->MMU->mapObject(0x1F900680, SPU2->CORE_1->VOICE_16->SSAH);
			IOP->MMU->mapObject(0x1F900682, SPU2->CORE_1->VOICE_16->SSAL);
			IOP->MMU->mapObject(0x1F900684, SPU2->CORE_1->VOICE_16->LSAXH);
			IOP->MMU->mapObject(0x1F900686, SPU2->CORE_1->VOICE_16->LSAXL);
			IOP->MMU->mapObject(0x1F900688, SPU2->CORE_1->VOICE_16->NAXH);
			IOP->MMU->mapObject(0x1F90068A, SPU2->CORE_1->VOICE_16->NAXL);
			IOP->MMU->mapObject(0x1F90068C, SPU2->CORE_1->VOICE_17->SSAH);
			IOP->MMU->mapObject(0x1F90068E, SPU2->CORE_1->VOICE_17->SSAL);
			IOP->MMU->mapObject(0x1F900690, SPU2->CORE_1->VOICE_17->LSAXH);
			IOP->MMU->mapObject(0x1F900692, SPU2->CORE_1->VOICE_17->LSAXL);
			IOP->MMU->mapObject(0x1F900694, SPU2->CORE_1->VOICE_17->NAXH);
			IOP->MMU->mapObject(0x1F900696, SPU2->CORE_1->VOICE_17->NAXL);
			IOP->MMU->mapObject(0x1F900698, SPU2->CORE_1->VOICE_18->SSAH);
			IOP->MMU->mapObject(0x1F90069A, SPU2->CORE_1->VOICE_18->SSAL);
			IOP->MMU->mapObject(0x1F90069C, SPU2->CORE_1->VOICE_18->LSAXH);
			IOP->MMU->mapObject(0x1F90069E, SPU2->CORE_1->VOICE_18->LSAXL);
			IOP->MMU->mapObject(0x1F9006A0, SPU2->CORE_1->VOICE_18->NAXH);
			IOP->MMU->mapObject(0x1F9006A2, SPU2->CORE_1->VOICE_18->NAXL);
			IOP->MMU->mapObject(0x1F9006A4, SPU2->CORE_1->VOICE_19->SSAH);
			IOP->MMU->mapObject(0x1F9006A6, SPU2->CORE_1->VOICE_19->SSAL);
			IOP->MMU->mapObject(0x1F9006A8, SPU2->CORE_1->VOICE_19->LSAXH);
			IOP->MMU->mapObject(0x1F9006AA, SPU2->CORE_1->VOICE_19->LSAXL);
			IOP->MMU->mapObject(0x1F9006AC, SPU2->CORE_1->VOICE_19->NAXH);
			IOP->MMU->mapObject(0x1F9006AE, SPU2->CORE_1->VOICE_19->NAXL);
			IOP->MMU->mapObject(0x1F9006B0, SPU2->CORE_1->VOICE_20->SSAH);
			IOP->MMU->mapObject(0x1F9006B2, SPU2->CORE_1->VOICE_20->SSAL);
			IOP->MMU->mapObject(0x1F9006B4, SPU2->CORE_1->VOICE_20->LSAXH);
			IOP->MMU->mapObject(0x1F9006B6, SPU2->CORE_1->VOICE_20->LSAXL);
			IOP->MMU->mapObject(0x1F9006B8, SPU2->CORE_1->VOICE_20->NAXH);
			IOP->MMU->mapObject(0x1F9006BA, SPU2->CORE_1->VOICE_20->NAXL);
			IOP->MMU->mapObject(0x1F9006BC, SPU2->CORE_1->VOICE_21->SSAH);
			IOP->MMU->mapObject(0x1F9006BE, SPU2->CORE_1->VOICE_21->SSAL);
			IOP->MMU->mapObject(0x1F9006C0, SPU2->CORE_1->VOICE_21->LSAXH);
			IOP->MMU->mapObject(0x1F9006C2, SPU2->CORE_1->VOICE_21->LSAXL);
			IOP->MMU->mapObject(0x1F9006C4, SPU2->CORE_1->VOICE_21->NAXH);
			IOP->MMU->mapObject(0x1F9006C6, SPU2->CORE_1->VOICE_21->NAXL);
			IOP->MMU->mapObject(0x1F9006C8, SPU2->CORE_1->VOICE_22->SSAH);
			IOP->MMU->mapObject(0x1F9006CA, SPU2->CORE_1->VOICE_22->SSAL);
			IOP->MMU->mapObject(0x1F9006CC, SPU2->CORE_1->VOICE_22->LSAXH);
			IOP->MMU->mapObject(0x1F9006CE, SPU2->CORE_1->VOICE_22->LSAXL);
			IOP->MMU->mapObject(0x1F9006D0, SPU2->CORE_1->VOICE_22->NAXH);
			IOP->MMU->mapObject(0x1F9006D2, SPU2->CORE_1->VOICE_22->NAXL);
			IOP->MMU->mapObject(0x1F9006D4, SPU2->CORE_1->VOICE_23->SSAH);
			IOP->MMU->mapObject(0x1F9006D6, SPU2->CORE_1->VOICE_23->SSAL);
			IOP->MMU->mapObject(0x1F9006D8, SPU2->CORE_1->VOICE_23->LSAXH);
			IOP->MMU->mapObject(0x1F9006DA, SPU2->CORE_1->VOICE_23->LSAXL);
			IOP->MMU->mapObject(0x1F9006DC, SPU2->CORE_1->VOICE_23->NAXH);
			IOP->MMU->mapObject(0x1F9006DE, SPU2->CORE_1->VOICE_23->NAXL);
			IOP->MMU->mapObject(0x1F9006E0, SPU2->CORE_1->ESAH);
			IOP->MMU->mapObject(0x1F9006E2, SPU2->CORE_1->ESAL);
			IOP->MMU->mapObject(0x1F9006E4, SPU2->CORE_1->APF1_SIZEH);
			IOP->MMU->mapObject(0x1F9006E6, SPU2->CORE_1->APF1_SIZEL);
			IOP->MMU->mapObject(0x1F9006E8, SPU2->CORE_1->APF2_SIZEH);
			IOP->MMU->mapObject(0x1F9006EA, SPU2->CORE_1->APF2_SIZEL);
			IOP->MMU->mapObject(0x1F9006EC, SPU2->CORE_1->SAME_L_DSTH);
			IOP->MMU->mapObject(0x1F9006EE, SPU2->CORE_1->SAME_L_DSTL);
			IOP->MMU->mapObject(0x1F9006F0, SPU2->CORE_1->SAME_R_DSTH);
			IOP->MMU->mapObject(0x1F9006F2, SPU2->CORE_1->SAME_R_DSTL);
			IOP->MMU->mapObject(0x1F9006F4, SPU2->CORE_1->COMB1_L_SRCH);
			IOP->MMU->mapObject(0x1F9006F6, SPU2->CORE_1->COMB1_L_SRCL);
			IOP->MMU->mapObject(0x1F9006F8, SPU2->CORE_1->COMB1_R_SRCH);
			IOP->MMU->mapObject(0x1F9006FA, SPU2->CORE_1->COMB1_R_SRCL);
			IOP->MMU->mapObject(0x1F9006FC, SPU2->CORE_1->COMB2_L_SRCH);
			IOP->MMU->mapObject(0x1F9006FE, SPU2->CORE_1->COMB2_L_SRCL);
			IOP->MMU->mapObject(0x1F900700, SPU2->CORE_1->COMB2_R_SRCH);
			IOP->MMU->mapObject(0x1F900702, SPU2->CORE_1->COMB2_R_SRCL);
			IOP->MMU->mapObject(0x1F900704, SPU2->CORE_1->SAME_L_SRCH);
			IOP->MMU->mapObject(0x1F900706, SPU2->CORE_1->SAME_L_SRCL);
			IOP->MMU->mapObject(0x1F900708, SPU2->CORE_1->SAME_R_SRCH);
			IOP->MMU->mapObject(0x1F90070A, SPU2->CORE_1->SAME_R_SRCL);
			IOP->MMU->mapObject(0x1F90070C, SPU2->CORE_1->DIFF_L_DSTH);
			IOP->MMU->mapObject(0x1F90070E, SPU2->CORE_1->DIFF_L_DSTL);
			IOP->MMU->mapObject(0x1F900710, SPU2->CORE_1->DIFF_R_DSTH);
			IOP->MMU->mapObject(0x1F900712, SPU2->CORE_1->DIFF_R_DSTL);
			IOP->MMU->mapObject(0x1F900714, SPU2->CORE_1->COMB3_L_SRCH);
			IOP->MMU->mapObject(0x1F900716, SPU2->CORE_1->COMB3_L_SRCL);
			IOP->MMU->mapObject(0x1F900718, SPU2->CORE_1->COMB3_R_SRCH);
			IOP->MMU->mapObject(0x1F90071A, SPU2->CORE_1->COMB3_R_SRCL);
			IOP->MMU->mapObject(0x1F90071C, SPU2->CORE_1->COMB4_L_SRCH);
			IOP->MMU->mapObject(0x1F90071E, SPU2->CORE_1->COMB4_L_SRCL);
			IOP->MMU->mapObject(0x1F900720, SPU2->CORE_1->COMB4_R_SRCH);
			IOP->MMU->mapObject(0x1F900722, SPU2->CORE_1->COMB4_R_SRCL);
			IOP->MMU->mapObject(0x1F900724, SPU2->CORE_1->DIFF_L_SRCH);
			IOP->MMU->mapObject(0x1F900726, SPU2->CORE_1->DIFF_L_SRCL);
			IOP->MMU->mapObject(0x1F900728, SPU2->CORE_1->DIFF_R_SRCH);
			IOP->MMU->mapObject(0x1F90072A, SPU2->CORE_1->DIFF_R_SRCL);
			IOP->MMU->mapObject(0x1F90072C, SPU2->CORE_1->APF1_L_DSTH);
			IOP->MMU->mapObject(0x1F90072E, SPU2->CORE_1->APF1_L_DSTL);
			IOP->MMU->mapObject(0x1F900730, SPU2->CORE_1->APF1_R_DSTH);
			IOP->MMU->mapObject(0x1F900732, SPU2->CORE_1->APF1_R_DSTL);
			IOP->MMU->mapObject(0x1F900734, SPU2->CORE_1->APF2_L_DSTH);
			IOP->MMU->mapObject(0x1F900736, SPU2->CORE_1->APF2_L_DSTL);
			IOP->MMU->mapObject(0x1F900738, SPU2->CORE_1->APF2_R_DSTH);
			IOP->MMU->mapObject(0x1F90073A, SPU2->CORE_1->APF2_R_DSTL);
			IOP->MMU->mapObject(0x1F90073C, SPU2->CORE_1->EEAH);
			IOP->MMU->mapObject(0x1F90073E, SPU2->CORE_1->EEAL);
			IOP->MMU->mapObject(0x1F900740, SPU2->CORE_1->ENDX0);
			IOP->MMU->mapObject(0x1F900742, SPU2->CORE_1->ENDX1);
			IOP->MMU->mapObject(0x1F900744, SPU2->CORE_1->STATX);
			IOP->MMU->mapObject(0x1F900760, SPU2->CORE_0->MVOLL);
			IOP->MMU->mapObject(0x1F900762, SPU2->CORE_0->MVOLR);
			IOP->MMU->mapObject(0x1F900764, SPU2->CORE_0->EVOLL);
			IOP->MMU->mapObject(0x1F900766, SPU2->CORE_0->EVOLR);
			IOP->MMU->mapObject(0x1F900768, SPU2->CORE_0->AVOLL);
			IOP->MMU->mapObject(0x1F90076A, SPU2->CORE_0->AVOLR);
			IOP->MMU->mapObject(0x1F90076C, SPU2->CORE_0->BVOLL);
			IOP->MMU->mapObject(0x1F90076E, SPU2->CORE_0->BVOLR);
			IOP->MMU->mapObject(0x1F900770, SPU2->CORE_0->MVOLXL);
			IOP->MMU->mapObject(0x1F900772, SPU2->CORE_0->MVOLXR);
			IOP->MMU->mapObject(0x1F900774, SPU2->CORE_0->IIR_VOL);
			IOP->MMU->mapObject(0x1F900776, SPU2->CORE_0->COMB1_VOL);
			IOP->MMU->mapObject(0x1F900778, SPU2->CORE_0->COMB2_VOL);
			IOP->MMU->mapObject(0x1F90077A, SPU2->CORE_0->COMB3_VOL);
			IOP->MMU->mapObject(0x1F90077C, SPU2->CORE_0->COMB4_VOL);
			IOP->MMU->mapObject(0x1F90077E, SPU2->CORE_0->WALL_VOL);
			IOP->MMU->mapObject(0x1F900780, SPU2->CORE_0->APF1_VOL);
			IOP->MMU->mapObject(0x1F900782, SPU2->CORE_0->APF2_VOL);
			IOP->MMU->mapObject(0x1F900784, SPU2->CORE_0->IN_COEF_L);
			IOP->MMU->mapObject(0x1F900786, SPU2->CORE_0->IN_COEF_R);
			IOP->MMU->mapObject(0x1F900788, SPU2->CORE_1->MVOLL);
			IOP->MMU->mapObject(0x1F90078A, SPU2->CORE_1->MVOLR);
			IOP->MMU->mapObject(0x1F90078C, SPU2->CORE_1->EVOLL);
			IOP->MMU->mapObject(0x1F90078E, SPU2->CORE_1->EVOLR);
			IOP->MMU->mapObject(0x1F900790, SPU2->CORE_1->AVOLL);
			IOP->MMU->mapObject(0x1F900792, SPU2->CORE_1->AVOLR);
			IOP->MMU->mapObject(0x1F900794, SPU2->CORE_1->BVOLL);
			IOP->MMU->mapObject(0x1F900796, SPU2->CORE_1->BVOLR);
			IOP->MMU->mapObject(0x1F900798, SPU2->CORE_1->MVOLXL);
			IOP->MMU->mapObject(0x1F90079A, SPU2->CORE_1->MVOLXR);
			IOP->MMU->mapObject(0x1F90079C, SPU2->CORE_1->IIR_VOL);
			IOP->MMU->mapObject(0x1F90079E, SPU2->CORE_1->COMB1_VOL);
			IOP->MMU->mapObject(0x1F9007A0, SPU2->CORE_1->COMB2_VOL);
			IOP->MMU->mapObject(0x1F9007A2, SPU2->CORE_1->COMB3_VOL);
			IOP->MMU->mapObject(0x1F9007A4, SPU2->CORE_1->COMB4_VOL);
			IOP->MMU->mapObject(0x1F9007A6, SPU2->CORE_1->WALL_VOL);
			IOP->MMU->mapObject(0x1F9007A8, SPU2->CORE_1->APF1_VOL);
			IOP->MMU->mapObject(0x1F9007AA, SPU2->CORE_1->APF2_VOL);
			IOP->MMU->mapObject(0x1F9007AC, SPU2->CORE_1->IN_COEF_L);
			IOP->MMU->mapObject(0x1F9007AE, SPU2->CORE_1->IN_COEF_R);
			IOP->MMU->mapObject(0x1F9007C0, SPU2->SPDIF_OUT);
			IOP->MMU->mapObject(0x1F9007C2, SPU2->SPDIF_IRQINFO);
			IOP->MMU->mapObject(0x1F9007C4, SPU2->SPDIF_07C4);
			IOP->MMU->mapObject(0x1F9007C6, SPU2->SPDIF_MODE);
			IOP->MMU->mapObject(0x1F9007C8, SPU2->SPDIF_MEDIA);
			IOP->MMU->mapObject(0x1F9007CA, SPU2->SPDIF_07CA);
			IOP->MMU->mapObject(0x1F9007CC, SPU2->SPDIF_PROTECT);
			IOP->MMU->mapObject(0x1F900B46, SPU2->CORE_0->MEMORY_0346);

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
			IOP->MMU->mapObject(0x1F000000, IOP->ParallelPort);

			// SIO2 Registers.
			IOP->MMU->mapObject(0x1F808268, SIO2->CTRL);
			IOP->MMU->mapObject(0x1F808278, SIO2->REGISTER_8278);
			IOP->MMU->mapObject(0x1F80827C, SIO2->REGISTER_827C);
			IOP->MMU->mapObject(0x1F808280, SIO2->INTR);
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

void Resources_t::postInit_SPU2() const
{
	SPU2->CORE_0 = std::make_shared<SPU2Core_C0_t>(Common->FIFO_SPU2C0);
	SPU2->CORE_1 = std::make_shared<SPU2Core_C1_t>(Common->FIFO_SPU2C1);
	SPU2->CORES[0] = SPU2->CORE_0;
	SPU2->CORES[1] = SPU2->CORE_1;
}
