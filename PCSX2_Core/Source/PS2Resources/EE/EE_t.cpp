#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "PS2Resources/EE/EE_t.h"
#include "Common/Types/Memory/Memory_t.h"
#include "Common/Types/Memory/ROMemory_t.h"
#include "Common/Types/Memory/ConstantMemory_t.h"
#include "Common/Types/Registers/Register32_t.h"
#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/EE/Types/EERegisters_t.h"
#include "PS2Resources/EE/Types/BootROM_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/IPU/IPU_t.h"
#include "PS2Resources/EE/GIF/GIF_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"

#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VifUnits_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VifUnitRegisters_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/Common/Common_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/GS/GS_t.h"
#include "PS2Resources/IOP/IOP_t.h"

EE_t::EE_t(const PS2Resources_t* PS2Resources) :
	PS2ResourcesSubcategory(PS2Resources),
	EECore(std::make_shared<EECore_t>(getRoot())),
	DMAC(std::make_shared<EEDmac_t>(getRoot())),
	INTC(std::make_shared<EEIntc_t>(getRoot())),
	Timers(std::make_shared<EETimers_t>(getRoot())),
	IPU(std::make_shared<IPU_t>(getRoot())),
	GIF(std::make_shared<GIF_t>(getRoot())),
	VPU(std::make_shared<VPU_t>(getRoot())),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_4GB, Constants::SIZE_4MB, Constants::SIZE_4B)),
	MainMemory(std::make_shared<Memory_t>(PS2Constants::EE::MainMemory::SIZE_MAIN_MEMORY, "Main Memory")),
	BootROM(std::make_shared<BootROM_t>()),
	ROM1(std::make_shared<ROMemory_t>(PS2Constants::EE::ROM::SIZE_ROM1, "ROM1")),
	EROM(std::make_shared<ROMemory_t>(PS2Constants::EE::ROM::SIZE_EROM, "EROM")),
	ROM2(std::make_shared<ROMemory_t>(PS2Constants::EE::ROM::SIZE_ROM2, "ROM2")),
	UNKNOWN_1A000000(std::make_shared<ConstantMemory_t>(0x10000, "Unknown: 1A00")),

	// Registers.
	MEMORY_SIO(std::make_shared<EERegister_SIO_t>()),
	REGISTER_F400(std::make_shared<Register32_t>()),
	MEMORY_F410(std::make_shared<ConstantMemory_t>(0x04, "Undocumented: F410")),
	REGISTER_F420(std::make_shared<Register32_t>()),
	MEMORY_MCH(std::make_shared<EERegister_MCH_t>()),
	MEMORY_F450(std::make_shared<Memory_t>(0xB0, "Undocumented: F450"))
{
}

void EE_t::postResourcesInit()
{
	EECore->postResourcesInit();
	DMAC->postResourcesInit();
	INTC->postResourcesInit();
	Timers->postResourcesInit();
	IPU->postResourcesInit();
	GIF->postResourcesInit();
	VPU->postResourcesInit();

	initEEPhysicalMemoryMap();
}

void EE_t::initEEPhysicalMemoryMap() const
{
	// EE Memory.
	{
		// Main Memory.
		PhysicalMMU->mapObject(PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY, MainMemory);

		// Scratchpad Memory.
		PhysicalMMU->mapObject(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, EECore->ScratchpadMemory);

		// Various ROMs.
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_BOOT_ROM, BootROM);
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM1, ROM1);
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_EROM, EROM);
		PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM2, ROM2);

		// Unknown memory.
		PhysicalMMU->mapObject(0x1A000000, UNKNOWN_1A000000);
	}

	// EE Registers.
	{
		// MISC EE registers.
		PhysicalMMU->mapObject(0x1000F100, MEMORY_SIO);
		PhysicalMMU->mapObject(0x1000f400, REGISTER_F400);
		PhysicalMMU->mapObject(0x1000f410, MEMORY_F410);
		PhysicalMMU->mapObject(0x1000f420, REGISTER_F420);
		PhysicalMMU->mapObject(0x1000F430, MEMORY_MCH);
		PhysicalMMU->mapObject(0x1000f450, MEMORY_F450);

		// Timers Registers.
		PhysicalMMU->mapObject(0x10000000, Timers->TIMER_0->COUNT);
		PhysicalMMU->mapObject(0x10000010, Timers->TIMER_0->MODE);
		PhysicalMMU->mapObject(0x10000020, Timers->TIMER_0->COMP);
		PhysicalMMU->mapObject(0x10000030, Timers->TIMER_0->HOLD);
		PhysicalMMU->mapObject(0x10000800, Timers->TIMER_1->COUNT);
		PhysicalMMU->mapObject(0x10000810, Timers->TIMER_1->MODE);
		PhysicalMMU->mapObject(0x10000820, Timers->TIMER_1->COMP);
		PhysicalMMU->mapObject(0x10000830, Timers->TIMER_1->HOLD);
		PhysicalMMU->mapObject(0x10001000, Timers->TIMER_2->COUNT);
		PhysicalMMU->mapObject(0x10001010, Timers->TIMER_2->MODE);
		PhysicalMMU->mapObject(0x10001020, Timers->TIMER_2->COMP);
		PhysicalMMU->mapObject(0x10001800, Timers->TIMER_3->COUNT);
		PhysicalMMU->mapObject(0x10001810, Timers->TIMER_3->MODE);
		PhysicalMMU->mapObject(0x10001820, Timers->TIMER_3->COMP);

		// IPU Registers.
		PhysicalMMU->mapObject(0x10002000, IPU->CMD);
		PhysicalMMU->mapObject(0x10002010, IPU->CTRL);
		PhysicalMMU->mapObject(0x10002020, IPU->BP);
		PhysicalMMU->mapObject(0x10002030, IPU->TOP);

		// GIF Registers.
		PhysicalMMU->mapObject(0x10003000, GIF->CTRL);
		PhysicalMMU->mapObject(0x10003010, GIF->MODE);
		PhysicalMMU->mapObject(0x10003020, GIF->STAT);
		PhysicalMMU->mapObject(0x10003040, GIF->TAG0);
		PhysicalMMU->mapObject(0x10003050, GIF->TAG1);
		PhysicalMMU->mapObject(0x10003060, GIF->TAG2);
		PhysicalMMU->mapObject(0x10003070, GIF->TAG3);
		PhysicalMMU->mapObject(0x10003080, GIF->CNT);
		PhysicalMMU->mapObject(0x10003090, GIF->P3CNT);
		PhysicalMMU->mapObject(0x100030a0, GIF->P3TAG);

		// VIF0 Registers.
		PhysicalMMU->mapObject(0x10003800, VPU->VIF->VIF0->STAT);
		PhysicalMMU->mapObject(0x10003810, VPU->VIF->VIF0->FBRST);
		PhysicalMMU->mapObject(0x10003820, VPU->VIF->VIF0->ERR);
		PhysicalMMU->mapObject(0x10003830, VPU->VIF->VIF0->MARK);
		PhysicalMMU->mapObject(0x10003840, VPU->VIF->VIF0->CYCLE);
		PhysicalMMU->mapObject(0x10003850, VPU->VIF->VIF0->MODE);
		PhysicalMMU->mapObject(0x10003860, VPU->VIF->VIF0->NUM);
		PhysicalMMU->mapObject(0x10003870, VPU->VIF->VIF0->MASK);
		PhysicalMMU->mapObject(0x10003880, VPU->VIF->VIF0->CODE);
		PhysicalMMU->mapObject(0x10003890, VPU->VIF->VIF0->ITOPS);
		PhysicalMMU->mapObject(0x100038d0, VPU->VIF->VIF0->ITOP);
		PhysicalMMU->mapObject(0x10003900, VPU->VIF->VIF0->R0);
		PhysicalMMU->mapObject(0x10003910, VPU->VIF->VIF0->R1);
		PhysicalMMU->mapObject(0x10003920, VPU->VIF->VIF0->R2);
		PhysicalMMU->mapObject(0x10003930, VPU->VIF->VIF0->R3);
		PhysicalMMU->mapObject(0x10003940, VPU->VIF->VIF0->C0);
		PhysicalMMU->mapObject(0x10003950, VPU->VIF->VIF0->C1);
		PhysicalMMU->mapObject(0x10003960, VPU->VIF->VIF0->C2);
		PhysicalMMU->mapObject(0x10003970, VPU->VIF->VIF0->C3);

		// VIF1 Registers.
		PhysicalMMU->mapObject(0x10003c00, VPU->VIF->VIF1->STAT);
		PhysicalMMU->mapObject(0x10003c10, VPU->VIF->VIF1->FBRST);
		PhysicalMMU->mapObject(0x10003c20, VPU->VIF->VIF1->ERR);
		PhysicalMMU->mapObject(0x10003c30, VPU->VIF->VIF1->MARK);
		PhysicalMMU->mapObject(0x10003c40, VPU->VIF->VIF1->CYCLE);
		PhysicalMMU->mapObject(0x10003c50, VPU->VIF->VIF1->MODE);
		PhysicalMMU->mapObject(0x10003c60, VPU->VIF->VIF1->NUM);
		PhysicalMMU->mapObject(0x10003c70, VPU->VIF->VIF1->MASK);
		PhysicalMMU->mapObject(0x10003c80, VPU->VIF->VIF1->CODE);
		PhysicalMMU->mapObject(0x10003c90, VPU->VIF->VIF1->ITOPS);
		PhysicalMMU->mapObject(0x10003ca0, VPU->VIF->VIF1->BASE);
		PhysicalMMU->mapObject(0x10003cb0, VPU->VIF->VIF1->OFST);
		PhysicalMMU->mapObject(0x10003cc0, VPU->VIF->VIF1->TOPS);
		PhysicalMMU->mapObject(0x10003cd0, VPU->VIF->VIF1->ITOP);
		PhysicalMMU->mapObject(0x10003ce0, VPU->VIF->VIF1->TOP);
		PhysicalMMU->mapObject(0x10003d00, VPU->VIF->VIF1->R0);
		PhysicalMMU->mapObject(0x10003d10, VPU->VIF->VIF1->R1);
		PhysicalMMU->mapObject(0x10003d20, VPU->VIF->VIF1->R2);
		PhysicalMMU->mapObject(0x10003d30, VPU->VIF->VIF1->R3);
		PhysicalMMU->mapObject(0x10003d40, VPU->VIF->VIF1->C0);
		PhysicalMMU->mapObject(0x10003d50, VPU->VIF->VIF1->C1);
		PhysicalMMU->mapObject(0x10003d60, VPU->VIF->VIF1->C2);
		PhysicalMMU->mapObject(0x10003d70, VPU->VIF->VIF1->C3);

		// FIFO Registers.
		PhysicalMMU->mapObject(0x10004000, getRoot()->Common->FIFO_VIF0);
		PhysicalMMU->mapObject(0x10005000, getRoot()->Common->FIFO_VIF1);
		PhysicalMMU->mapObject(0x10006000, getRoot()->Common->FIFO_GIF);
		PhysicalMMU->mapObject(0x10007000, getRoot()->Common->FIFO_IPU); // Meant to be read only...
		PhysicalMMU->mapObject(0x10007010, getRoot()->Common->FIFO_IPU); // Meant to be write only...

		// DMAC registers.
		PhysicalMMU->mapObject(0x10008000, DMAC->CHANNEL_VIF0->CHCR);
		PhysicalMMU->mapObject(0x10008010, DMAC->CHANNEL_VIF0->MADR);
		PhysicalMMU->mapObject(0x10008020, DMAC->CHANNEL_VIF0->QWC);
		PhysicalMMU->mapObject(0x10008030, DMAC->CHANNEL_VIF0->TADR);
		PhysicalMMU->mapObject(0x10008040, DMAC->CHANNEL_VIF0->ASR0);
		PhysicalMMU->mapObject(0x10008050, DMAC->CHANNEL_VIF0->ASR1);
		PhysicalMMU->mapObject(0x10008060, DMAC->CHANNEL_VIF0->MEMORY_8060);
		PhysicalMMU->mapObject(0x10009000, DMAC->CHANNEL_VIF1->CHCR);
		PhysicalMMU->mapObject(0x10009010, DMAC->CHANNEL_VIF1->MADR);
		PhysicalMMU->mapObject(0x10009020, DMAC->CHANNEL_VIF1->QWC);
		PhysicalMMU->mapObject(0x10009030, DMAC->CHANNEL_VIF1->TADR);
		PhysicalMMU->mapObject(0x10009040, DMAC->CHANNEL_VIF1->ASR0);
		PhysicalMMU->mapObject(0x10009050, DMAC->CHANNEL_VIF1->ASR1);
		PhysicalMMU->mapObject(0x10009060, DMAC->CHANNEL_VIF1->MEMORY_9060);
		PhysicalMMU->mapObject(0x1000a000, DMAC->CHANNEL_GIF->CHCR);
		PhysicalMMU->mapObject(0x1000a010, DMAC->CHANNEL_GIF->MADR);
		PhysicalMMU->mapObject(0x1000a020, DMAC->CHANNEL_GIF->QWC);
		PhysicalMMU->mapObject(0x1000a030, DMAC->CHANNEL_GIF->TADR);
		PhysicalMMU->mapObject(0x1000a040, DMAC->CHANNEL_GIF->ASR0);
		PhysicalMMU->mapObject(0x1000a050, DMAC->CHANNEL_GIF->ASR1);
		PhysicalMMU->mapObject(0x1000a060, DMAC->CHANNEL_GIF->MEMORY_A060);
		PhysicalMMU->mapObject(0x1000b000, DMAC->CHANNEL_fromIPU->CHCR);
		PhysicalMMU->mapObject(0x1000b010, DMAC->CHANNEL_fromIPU->MADR);
		PhysicalMMU->mapObject(0x1000b020, DMAC->CHANNEL_fromIPU->QWC);
		PhysicalMMU->mapObject(0x1000b030, DMAC->CHANNEL_fromIPU->MEMORY_B030);
		PhysicalMMU->mapObject(0x1000b400, DMAC->CHANNEL_toIPU->CHCR);
		PhysicalMMU->mapObject(0x1000b410, DMAC->CHANNEL_toIPU->MADR);
		PhysicalMMU->mapObject(0x1000b420, DMAC->CHANNEL_toIPU->QWC);
		PhysicalMMU->mapObject(0x1000b430, DMAC->CHANNEL_toIPU->TADR);
		PhysicalMMU->mapObject(0x1000b440, DMAC->CHANNEL_toIPU->MEMORY_B440);
		PhysicalMMU->mapObject(0x1000c000, DMAC->CHANNEL_SIF0->CHCR);
		PhysicalMMU->mapObject(0x1000c010, DMAC->CHANNEL_SIF0->MADR);
		PhysicalMMU->mapObject(0x1000c020, DMAC->CHANNEL_SIF0->QWC);
		PhysicalMMU->mapObject(0x1000c030, DMAC->CHANNEL_SIF0->MEMORY_C030);
		PhysicalMMU->mapObject(0x1000c400, DMAC->CHANNEL_SIF1->CHCR);
		PhysicalMMU->mapObject(0x1000c410, DMAC->CHANNEL_SIF1->MADR);
		PhysicalMMU->mapObject(0x1000c420, DMAC->CHANNEL_SIF1->QWC);
		PhysicalMMU->mapObject(0x1000c430, DMAC->CHANNEL_SIF1->TADR);
		PhysicalMMU->mapObject(0x1000c440, DMAC->CHANNEL_SIF1->MEMORY_C440);
		PhysicalMMU->mapObject(0x1000c800, DMAC->CHANNEL_SIF2->CHCR);
		PhysicalMMU->mapObject(0x1000c810, DMAC->CHANNEL_SIF2->MADR);
		PhysicalMMU->mapObject(0x1000c820, DMAC->CHANNEL_SIF2->QWC);
		PhysicalMMU->mapObject(0x1000c830, DMAC->CHANNEL_SIF2->MEMORY_C830);
		PhysicalMMU->mapObject(0x1000d000, DMAC->CHANNEL_fromSPR->CHCR);
		PhysicalMMU->mapObject(0x1000d010, DMAC->CHANNEL_fromSPR->MADR);
		PhysicalMMU->mapObject(0x1000d020, DMAC->CHANNEL_fromSPR->QWC);
		PhysicalMMU->mapObject(0x1000d030, DMAC->CHANNEL_fromSPR->MEMORY_D030);
		PhysicalMMU->mapObject(0x1000d080, DMAC->CHANNEL_fromSPR->SADR);
		PhysicalMMU->mapObject(0x1000d090, DMAC->CHANNEL_fromSPR->MEMORY_D090);
		PhysicalMMU->mapObject(0x1000d400, DMAC->CHANNEL_toSPR->CHCR);
		PhysicalMMU->mapObject(0x1000d410, DMAC->CHANNEL_toSPR->MADR);
		PhysicalMMU->mapObject(0x1000d420, DMAC->CHANNEL_toSPR->QWC);
		PhysicalMMU->mapObject(0x1000d430, DMAC->CHANNEL_toSPR->TADR);
		PhysicalMMU->mapObject(0x1000d440, DMAC->CHANNEL_toSPR->MEMORY_D440);
		PhysicalMMU->mapObject(0x1000d480, DMAC->CHANNEL_toSPR->SADR);
		PhysicalMMU->mapObject(0x1000d490, DMAC->CHANNEL_toSPR->MEMORY_D490);
		PhysicalMMU->mapObject(0x1000e000, DMAC->CTRL);
		PhysicalMMU->mapObject(0x1000e010, DMAC->STAT);
		PhysicalMMU->mapObject(0x1000e020, DMAC->PCR);
		PhysicalMMU->mapObject(0x1000e030, DMAC->SQWC);
		PhysicalMMU->mapObject(0x1000e040, DMAC->RBSR);
		PhysicalMMU->mapObject(0x1000e050, DMAC->RBOR);
		PhysicalMMU->mapObject(0x1000e060, DMAC->STADR);

		// INTC registers.
		PhysicalMMU->mapObject(0x1000f000, INTC->STAT);
		PhysicalMMU->mapObject(0x1000f010, INTC->MASK);

		// DMAC registers (extended).
		PhysicalMMU->mapObject(0x1000f500, DMAC->MEMORY_F500);
		PhysicalMMU->mapObject(0x1000f520, DMAC->ENABLER);
		PhysicalMMU->mapObject(0x1000f590, DMAC->ENABLEW);
	}

	// VU0/1 Memory.
	{
		PhysicalMMU->mapObject(0x11000000, VPU->VU->VU0->MEMORY_Micro);
		PhysicalMMU->mapObject(0x11004000, VPU->VU->VU0->MEMORY_Mem);
		PhysicalMMU->mapObject(0x11008000, VPU->VU->VU1->MEMORY_Micro);
		PhysicalMMU->mapObject(0x1100c000, VPU->VU->VU1->MEMORY_Mem);
	}

	// GS Privileged Registers.
	{
		PhysicalMMU->mapObject(0x12000000, getRoot()->GS->PMODE);
		PhysicalMMU->mapObject(0x12000010, getRoot()->GS->SMODE1);
		PhysicalMMU->mapObject(0x12000020, getRoot()->GS->SMODE2);
		PhysicalMMU->mapObject(0x12000030, getRoot()->GS->SRFSH);
		PhysicalMMU->mapObject(0x12000040, getRoot()->GS->SYNCH1);
		PhysicalMMU->mapObject(0x12000050, getRoot()->GS->SYNCH2);
		PhysicalMMU->mapObject(0x12000060, getRoot()->GS->SYNCV);
		PhysicalMMU->mapObject(0x12000070, getRoot()->GS->DISPFB1);
		PhysicalMMU->mapObject(0x12000080, getRoot()->GS->DISPLAY1);
		PhysicalMMU->mapObject(0x12000090, getRoot()->GS->DISPFB2);
		PhysicalMMU->mapObject(0x120000a0, getRoot()->GS->DISPLAY2);
		PhysicalMMU->mapObject(0x120000b0, getRoot()->GS->EXTBUF);
		PhysicalMMU->mapObject(0x120000c0, getRoot()->GS->EXTDATA);
		PhysicalMMU->mapObject(0x120000d0, getRoot()->GS->EXTWRITE);
		PhysicalMMU->mapObject(0x120000e0, getRoot()->GS->BGCOLOR);

		PhysicalMMU->mapObject(0x12001000, getRoot()->GS->CSR);
		PhysicalMMU->mapObject(0x12001010, getRoot()->GS->IMR);
		PhysicalMMU->mapObject(0x12001040, getRoot()->GS->BUSDIR);
		PhysicalMMU->mapObject(0x12001080, getRoot()->GS->SIGLBLID);
	}

	// IOP Mirrors.
	{
		// Misc IOP Registers.
		PhysicalMMU->mapObject(0x1F80141C, getRoot()->IOP->HW_SSBUS_DEV9_DELAY3);
		PhysicalMMU->mapObject(0x1F801470, getRoot()->IOP->REGISTER_1470);
		PhysicalMMU->mapObject(0x1F803800, getRoot()->IOP->REGISTER_3800);

		// Main Memory.
		PhysicalMMU->mapObject(0x1C000000, getRoot()->IOP->MainMemory);
	}

	// SIF Registers.
	{
		PhysicalMMU->mapObject(0x1000F200, getRoot()->Common->MSCOM);
		PhysicalMMU->mapObject(0x1000F210, getRoot()->Common->SMCOM);
		PhysicalMMU->mapObject(0x1000F220, getRoot()->Common->MSFLG);
		PhysicalMMU->mapObject(0x1000F230, getRoot()->Common->SMFLG);
		PhysicalMMU->mapObject(0x1000F240, getRoot()->Common->SBUS_REGISTER_F240);
		PhysicalMMU->mapObject(0x1000F250, getRoot()->Common->SBUS_REGISTER_F250);
		PhysicalMMU->mapObject(0x1000F260, getRoot()->Common->SBUS_REGISTER_F260);
		PhysicalMMU->mapObject(0x1000F300, getRoot()->Common->SBUS_REGISTER_F300);
		PhysicalMMU->mapObject(0x1000F380, getRoot()->Common->SBUS_REGISTER_F380);
	}
}
