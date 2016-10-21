#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ImageMappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BusErrorMMemory_t.h"
#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
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
#include "Common/PS2Resources/GS/GS_t.h"


EE_t::EE_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	EECore(std::make_shared<EECore_t>(getRootResources())),
	DMAC(std::make_shared<DMAC_t>(getRootResources())),
	INTC(std::make_shared<INTC_t>(getRootResources())),
	Timers(std::make_shared<Timers_t>(getRootResources())),
	IPU(std::make_shared<IPU_t>(getRootResources())),
	GIF(std::make_shared<GIF_t>(getRootResources())),
	VPU(std::make_shared<VPU_t>(getRootResources())),
	MainMemory(std::make_shared<MappedMemory_t>(PS2Constants::EE::MainMemory::SIZE_MAIN_MEMORY, "Main Memory", PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY)),
	BootROM(std::make_shared<BootROM_t>()),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_512MB, Constants::SIZE_4MB, Constants::SIZE_16B)),

	// Registers.
	EE_REGISTER_VIF0_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF0_FIFO", 0x10004000)),
	EE_REGISTER_VIF1_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF1_FIFO", 0x10005000)),
	EE_REGISTER_GIF_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: GIF_FIFO", 0x10006000)),
	EE_REGISTER_IPU_out_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_out_FIFO", 0x10007000)),
	EE_REGISTER_IPU_in_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_in_FIFO", 0x10007010)),
	EE_REGISTER_SIO(std::make_shared<EERegisterSIO_t>()),
	EE_REGISTER_SB_SMFLG(std::make_shared<MappedMemory32_t>("SIF: SB_SMFLG", 0x1000f230)),
	EE_REGISTER_F400(std::make_shared<MappedMemory32_t>("Undocumented: F400", 0x1000f400)),
	EE_REGISTER_F410(std::make_shared<DeadMMemory_t>(0x04, "Undocumented: F410", 0x1000f410)),
	EE_REGISTER_F420(std::make_shared<MappedMemory32_t>("Undocumented: F420", 0x1000f420)),
	EE_REGISTER_MCH(std::make_shared<EERegisterMCH_t>()),
	EE_REGISTER_F450(std::make_shared<MappedMemory_t>(0xB0, "Undocumented: F450", 0x1000f450))
{
	// Map the EE physical space.

	// EE Memory.
	{
		// Main memory 32MB
		PhysicalMMU->mapMemory(MainMemory);

		// Scratchpad memory 16KB
		PhysicalMMU->mapMemory(EECore->ScratchpadMemory);

		// Boot ROM 4MB
		PhysicalMMU->mapMemory(BootROM);
	}

	// EE Registers.
	{
		// Timers Registers.
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T0_COUNT);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T0_MODE);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T0_COMP);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T0_HOLD);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_TIMER_0040);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T1_COUNT);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T1_MODE);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T1_COMP);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T1_HOLD);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_TIMER_0840);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T2_COUNT);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T2_MODE);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T2_COMP);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_TIMER_1030);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T3_COUNT);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T3_MODE);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_T3_COMP);
		PhysicalMMU->mapMemory(Timers->TIMERS_REGISTER_TIMER_1830);

		// IPU Registers.
		PhysicalMMU->mapMemory(IPU->IPU_REGISTER_CMD);
		PhysicalMMU->mapMemory(IPU->IPU_REGISTER_CTRL);
		PhysicalMMU->mapMemory(IPU->IPU_REGISTER_BP);
		PhysicalMMU->mapMemory(IPU->IPU_REGISTER_TOP);
		PhysicalMMU->mapMemory(IPU->IPU_REGISTER_2040);

		// GIF Registers.
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_CTRL);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_MODE);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_STAT);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_3030);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_TAG0);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_TAG1);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_TAG2);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_TAG3);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_CNT);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_P3CNT);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_P3TAG);
		PhysicalMMU->mapMemory(GIF->GIF_REGISTER_30b0);

		// VIF0 Registers.
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_STAT);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_FBRST);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_ERR);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_MARK);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_CYCLE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_MODE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_NUM);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_MASK);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_CODE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_ITOPS);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_38a0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_38b0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_38c0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_ITOP);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_38e0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_38f0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_R0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_R1);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_R2);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_R3);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_C0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_C1);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_C2);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_C3);
		PhysicalMMU->mapMemory(VPU->VIF->VIF0_REGISTER_3980);

		// VIF1 Registers.
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_STAT);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_FBRST);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_ERR);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_MARK);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_CYCLE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_MODE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_NUM);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_MASK);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_CODE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_ITOPS);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_BASE);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_OFST);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_TOPS);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_ITOP);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_TOP);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_3cf0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_R0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_R1);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_R2);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_R3);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_C0);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_C1);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_C2);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_C3);
		PhysicalMMU->mapMemory(VPU->VIF->VIF1_REGISTER_3d80);

		// FIFO Registers.
		PhysicalMMU->mapMemory(EE_REGISTER_VIF0_FIFO);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10004000", 0x10004010, 0x10, 0xFF0, 0x10004000, PhysicalMMU) // Image of 0x10004000.
		);
		PhysicalMMU->mapMemory(EE_REGISTER_VIF1_FIFO);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10005000", 0x10005010, 0x10, 0xFF0, 0x10005000, PhysicalMMU) // Image of 0x10005000.
		);
		PhysicalMMU->mapMemory(EE_REGISTER_GIF_FIFO);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10006000", 0x10006010, 0x10, 0xFF0, 0x10006000, PhysicalMMU) // Image of 0x10006000.
		);
		PhysicalMMU->mapMemory(EE_REGISTER_IPU_out_FIFO);
		PhysicalMMU->mapMemory(EE_REGISTER_IPU_in_FIFO);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x10007000", 0x10007020, 0x20, 0xFE0, 0x10007000, PhysicalMMU) // Image of 0x10007000.
		);

		// DMAC registers.
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_ASR0);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D0_ASR1);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_8060);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_ASR0);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D1_ASR1);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_9060);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_ASR0);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D2_ASR1);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_a060);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D3_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D3_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D3_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_b030);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D4_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D4_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D4_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D4_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_b440);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D5_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D5_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D5_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_c030);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D6_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D6_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D6_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D6_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_c440);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D7_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D7_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D7_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_c830);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D8_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D8_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D8_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_d030);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D8_SADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_d090);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D9_CHCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D9_MADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D9_QWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D9_TADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_d440);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D9_SADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_d490);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_CTRL);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_STAT);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_PCR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_SQWC);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_RBSR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_RBOR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_STADR);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_e070);

		// INTC registers.
		PhysicalMMU->mapMemory(INTC->INTC_REGISTER_I_STAT);
		PhysicalMMU->mapMemory(INTC->INTC_REGISTER_I_MASK);
		PhysicalMMU->mapMemory(INTC->INTC_REGISTER_f020);

		// MISC registers.
		PhysicalMMU->mapMemory(EE_REGISTER_SIO);
		PhysicalMMU->mapMemory(EE_REGISTER_SB_SMFLG);
		PhysicalMMU->mapMemory(EE_REGISTER_F400);
		PhysicalMMU->mapMemory(EE_REGISTER_F410);
		PhysicalMMU->mapMemory(EE_REGISTER_F420);
		PhysicalMMU->mapMemory(EE_REGISTER_MCH);
		PhysicalMMU->mapMemory(EE_REGISTER_F450);

		// DMAC registers (extended).
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_F500);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_ENABLER);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_F530);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_D_ENABLEW);
		PhysicalMMU->mapMemory(DMAC->DMAC_REGISTER_F5A0);
	}

	// VU0/1 Memory
	{
		PhysicalMMU->mapMemory(VPU->VU->VU0_MEM_Micro0);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x11000000", 0x11001000, 0x1000, 0x3000, 0x11000000, PhysicalMMU) // Image of 0x11000000.
		);
		PhysicalMMU->mapMemory(VPU->VU->VU0_MEM_Mem0);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x11004000", 0x11005000, 0x1000, 0x3000, 0x11004000, PhysicalMMU) // Image of 0x11004000.
		);
		PhysicalMMU->mapMemory(VPU->VU->VU1_MEM_Micro1);
		PhysicalMMU->mapMemory(VPU->VU->VU1_MEM_Mem1);
		PhysicalMMU->mapMemory(VPU->VU->VU1_MEM_BusErr);
	}

	// GS Privileged Registers.
	{
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_PMODE);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SMODE1);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SMODE2);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SRFSH);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SYNCH1);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SYNCH2);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SYNCV);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_DISPFB1);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_DISPLAY1);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_DISPFB2);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_DISPLAY2);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_EXTBUF);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_EXTDATA);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_EXTWRITE);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_BGCOLOR);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_00f0);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000400, 0x400, 0x400, 0x12000000, PhysicalMMU) // Image of 0x12000000.
		);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000800, 0x800, 0x800, 0x12000000, PhysicalMMU) // Image of 0x12000000.
		);

		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_CSR);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_IMR);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_1020);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_BUSDIR);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_1050);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SIGLBLID);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_1090);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_1100);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001400, 0x400, 0x400, 0x12001000, PhysicalMMU) // Image of 0x12001000.
		);
		PhysicalMMU->mapMemory(
			std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001800, 0x800, 0x800, 0x12001000, PhysicalMMU) // Image of 0x12001000.
		);

		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPE_2000);
		PhysicalMMU->mapMemory(getRootResources()->GS->GS_P_REGISTER_SPEBusErr);
	}
}
