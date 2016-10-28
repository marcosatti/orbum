#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/Clock/Clock_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"

#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ImageMappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BusErrorMMemory_t.h"

#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/Timers/Timers_t.h"
#include "Common/PS2Resources/EE/Timers/Types/Timers_Registers_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/DMAC/Types/DMAC_Registers_t.h"
#include "Common/PS2Resources/EE/INTC/INTC_t.h"
#include "Common/PS2Resources/EE/INTC/Types/INTC_Registers_t.h"
#include "Common/PS2Resources/EE/IPU/IPU_t.h"
#include "Common/PS2Resources/EE/GIF/GIF_t.h"
#include "Common/PS2Resources/EE/VPU/VPU_t.h"
#include "Common/PS2Resources/EE/VPU/VU/VU_t.h"
#include "Common/PS2Resources/EE/VPU/VIF/VIF_t.h"

#include "Common/PS2Resources/IOP/IOPCore/IOPCore_t.h"

PS2Resources_t::PS2Resources_t() :
	Clock(std::make_shared<Clock_t>()),
	GS(std::make_shared<GS_t>(this)),
	EE(std::make_shared<EE_t>(this)),
	IOP(std::make_shared<IOP_t>(this))
{
	mapPhysicalMemory_EE();
	mapPhysicalMemory_IOP();
}

void PS2Resources_t::mapPhysicalMemory_EE() const
{
	// EE Memory.
	{
		// Main memory 32MB
		EE->PhysicalMMU->mapMemory(EE->MainMemory);

		// Scratchpad memory 16KB
		EE->PhysicalMMU->mapMemory(EE->EECore->ScratchpadMemory);

		// Boot ROM 4MB
		EE->PhysicalMMU->mapMemory(EE->BootROM);

		// Unknown memory.
		EE->PhysicalMMU->mapMemory(EE->UNKNOWN_1A000000);
	}

	// EE Registers.
	{
		// Timers Registers.
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T0_COUNT);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T0_MODE);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T0_COMP);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T0_HOLD);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_TIMER_0040);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T1_COUNT);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T1_MODE);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T1_COMP);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T1_HOLD);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_TIMER_0840);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T2_COUNT);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T2_MODE);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T2_COMP);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_TIMER_1030);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T3_COUNT);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T3_MODE);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_T3_COMP);
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_REGISTER_TIMER_1830);

		// IPU Registers.
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_REGISTER_CMD);
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_REGISTER_CTRL);
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_REGISTER_BP);
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_REGISTER_TOP);
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_REGISTER_2040);

		// GIF Registers.
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_CTRL);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_MODE);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_3030);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_TAG0);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_TAG1);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_TAG2);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_TAG3);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_CNT);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_P3CNT);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_P3TAG);
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_REGISTER_30b0);

		// VIF0 Registers.
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_FBRST);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_ERR);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_MARK);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_CYCLE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_MODE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_NUM);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_MASK);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_CODE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_ITOPS);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_38a0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_38b0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_38c0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_ITOP);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_38e0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_38f0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_R0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_R1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_R2);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_R3);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_C0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_C1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_C2);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_C3);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_REGISTER_3980);

		// VIF1 Registers.
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_FBRST);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_ERR);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_MARK);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_CYCLE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_MODE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_NUM);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_MASK);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_CODE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_ITOPS);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_BASE);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_OFST);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_TOPS);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_ITOP);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_TOP);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_3cf0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_R0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_R1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_R2);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_R3);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_C0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_C1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_C2);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_C3);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_REGISTER_3d80);

		// FIFO Registers.
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_VIF0_FIFO);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10004000", 0x10004010, 0x10, 0xFF0, 0x10004000, EE->PhysicalMMU) // Image of 0x10004000.
		);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_VIF1_FIFO);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10005000", 0x10005010, 0x10, 0xFF0, 0x10005000, EE->PhysicalMMU) // Image of 0x10005000.
		);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_GIF_FIFO);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10006000", 0x10006010, 0x10, 0xFF0, 0x10006000, EE->PhysicalMMU) // Image of 0x10006000.
		);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_IPU_out_FIFO);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_IPU_in_FIFO);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10007000", 0x10007020, 0x20, 0xFE0, 0x10007000, EE->PhysicalMMU) // Image of 0x10007000.
		);

		// DMAC registers.
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_ASR0);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D0_ASR1);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_8060);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_ASR0);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D1_ASR1);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_9060);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_ASR0);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D2_ASR1);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_a060);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D3_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D3_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D3_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_b030);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D4_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D4_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D4_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D4_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_b440);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D5_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D5_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D5_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_c030);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D6_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D6_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D6_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D6_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_c440);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D7_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D7_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D7_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_c830);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D8_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D8_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D8_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_d030);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D8_SADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_d090);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D9_CHCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D9_MADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D9_QWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D9_TADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_d440);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D9_SADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_d490);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_CTRL);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_STAT);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_PCR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_SQWC);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_RBSR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_RBOR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_STADR);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_e070);

		// INTC registers.
		EE->PhysicalMMU->mapMemory(EE->INTC->INTC_REGISTER_I_STAT);
		EE->PhysicalMMU->mapMemory(EE->INTC->INTC_REGISTER_I_MASK);
		EE->PhysicalMMU->mapMemory(EE->INTC->INTC_REGISTER_f020);

		// MISC registers.
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_SIO);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_SB_SMFLG);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_F400);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_F410);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_F420);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_MCH);
		EE->PhysicalMMU->mapMemory(EE->EE_REGISTER_F450);

		// DMAC registers (extended).
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_F500);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_ENABLER);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_F530);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_D_ENABLEW);
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_REGISTER_F5A0);
	}

	// VU0/1 Memory
	{
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU0_MEM_Micro0);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x11000000", 0x11001000, 0x1000, 0x3000, 0x11000000, EE->PhysicalMMU) // Image of 0x11000000.
		);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU0_MEM_Mem0);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x11004000", 0x11005000, 0x1000, 0x3000, 0x11004000, EE->PhysicalMMU) // Image of 0x11004000.
		);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEM_Micro1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEM_Mem1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEM_BusErr);
	}

	// GS Privileged Registers.
	{
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_PMODE);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SMODE1);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SMODE2);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SRFSH);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SYNCH1);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SYNCH2);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SYNCV);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_DISPFB1);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_DISPLAY1);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_DISPFB2);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_DISPLAY2);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_EXTBUF);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_EXTDATA);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_EXTWRITE);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_BGCOLOR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_00f0);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000400, 0x400, 0x400, 0x12000000, EE->PhysicalMMU) // Image of 0x12000000.
		);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000800, 0x800, 0x800, 0x12000000, EE->PhysicalMMU) // Image of 0x12000000.
		);

		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_CSR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_IMR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1020);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_BUSDIR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1050);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SIGLBLID);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1090);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1100);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001400, 0x400, 0x400, 0x12001000, EE->PhysicalMMU) // Image of 0x12001000.
		);
		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001800, 0x800, 0x800, 0x12001000, EE->PhysicalMMU) // Image of 0x12001000.
		);

		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_2000);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPEBusErr);
	}

	// IOP Mirrors
	{
		EE->PhysicalMMU->mapMemory(IOP->IOP_HW_REGISTERS);

		EE->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x00000000", 0x1C000000, PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, 0x00000000, IOP->PhysicalMMU) // Image of IOP 0x00000000.
		);
	}
}

void PS2Resources_t::mapPhysicalMemory_IOP() const
{
	// IOP Memory.
	{
		// Main Memory
		IOP->PhysicalMMU->mapMemory(IOP->MainMemory);

		// Boot ROM
		IOP->PhysicalMMU->mapMemory(EE->BootROM);

		// Scratchpad Memory
		IOP->PhysicalMMU->mapMemory(IOP->IOPCore->ScratchpadMemory);

		// HW Registers
		IOP->PhysicalMMU->mapMemory(IOP->IOP_HW_REGISTERS);

		// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation.
		IOP->PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x1FC00000", 0xFFC00000, 0x400000, 0x400000, 0x1FC00000, IOP->PhysicalMMU) // Image of 0x1FC00000.
		);
	}
}
