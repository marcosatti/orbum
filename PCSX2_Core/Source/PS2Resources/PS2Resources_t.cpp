#include "stdafx.h"

#include <memory>

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Clock/Clock_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/GS/GS_t.h"
#include "PS2Resources/IOP/IOP_t.h"
#include "PS2Resources/SIF/SIF_t.h"

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/PCRegister16_t.h"
#include "Common/Types/Registers/ConstantRegister8_t.h"
#include "Common/Types/Registers/ConstantRegister32_t.h"
#include "Common/Types/Registers/DebugRegister32_t.h"
#include "Common/Types/Registers/WrapperR16Register32_t.h"
#include "Common/Types/Registers/WrapperF32Register32_t.h"

#include "PS2Resources/EE/Types/EERegisters_t.h"
#include "PS2Resources/EE/Types/BootROM_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimer_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimerRegisters_t.h"
#include "PS2Resources/EE/DMAC/EEDmac_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannelRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacRegisters_t.h"
#include "PS2Resources/EE/DMAC/Types/EEDmacChannels_t.h"
#include "PS2Resources/EE/INTC/EEIntc_t.h"
#include "PS2Resources/EE/INTC/Types/EEIntcRegisters_t.h"
#include "PS2Resources/EE/IPU/IPU_t.h"
#include "PS2Resources/EE/GIF/GIF_t.h"
#include "PS2Resources/EE/VPU/VPU_t.h"
#include "PS2Resources/EE/VPU/Types/VPURegisters_t.h"
#include "PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VIFUnits_t.h"
#include "PS2Resources/EE/VPU/VIF/Types/VIFUnitRegisters_t.h"
#include "PS2Resources/EE/VPU/VU/VU_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnits_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VuUnitRegisters_t.h"
#include "PS2Resources/EE/VPU/VU/Types/VURegisters_t.h"

#include "PS2Resources/IOP/IOPCore/IOPCore_t.h"
#include "PS2Resources/IOP/DMAC/IOPDmac_t.h"
#include "PS2Resources/IOP/DMAC/Types/IOPDmacChannels_t.h"
#include "PS2Resources/IOP/INTC/IOPIntc_t.h"
#include "PS2Resources/IOP/CDVD/CDVD_t.h"
#include "PS2Resources/IOP/Timers/IOPTimers_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimer_t.h"
#include "PS2Resources/IOP/Timers/Types/IOPTimersTimerRegisters_t.h"

PS2Resources_t::PS2Resources_t() :
	Clock(std::make_shared<Clock_t>()),
	GS(std::make_shared<GS_t>(this)),
	EE(std::make_shared<EE_t>(this)),
	IOP(std::make_shared<IOP_t>(this)),
	SIF(std::make_shared<SIF_t>(this))
{
	initPhysicalMemoryMap_EE();
	initPhysicalMemoryMap_IOP();
	initPhysicalMemoryMap_VU0();
	initPhysicalMemoryMap_VU1();
	initControlRegistersMap_VU0();
}

void PS2Resources_t::initPhysicalMemoryMap_EE() const
{
	// EE Memory.
	{
		// Main Memory.
		EE->PhysicalMMU->mapObject(PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY, EE->MainMemory);

		// Scratchpad Memory.
		EE->PhysicalMMU->mapObject(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, EE->EECore->ScratchpadMemory);

		// Various ROMs.
		EE->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
		EE->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);
		EE->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_EROM, EE->EROM);
		EE->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM2, EE->ROM2);

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
		EE->PhysicalMMU->mapObject(0x10004000, EE->FIFO_VIF0);
		EE->PhysicalMMU->mapObject(0x10005000, EE->FIFO_VIF1);
		EE->PhysicalMMU->mapObject(0x10006000, EE->FIFO_GIF);
		EE->PhysicalMMU->mapObject(0x10007000, EE->FIFO_IPU_out);
		EE->PhysicalMMU->mapObject(0x10007010, EE->FIFO_IPU_in);

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

		// Main Memory.
		EE->PhysicalMMU->mapObject(0x1C000000, IOP->MainMemory);
	}

	// SIF Registers.
	{
		EE->PhysicalMMU->mapObject(0x1000F200, SIF->MSCOM);
		EE->PhysicalMMU->mapObject(0x1000F210, SIF->SMCOM);
		EE->PhysicalMMU->mapObject(0x1000F220, SIF->MSFLG);
		EE->PhysicalMMU->mapObject(0x1000F230, SIF->SMFLG);
	}
}

void PS2Resources_t::initPhysicalMemoryMap_IOP() const
{
	// IOP Memory.
	{
		// Main Memory.
		IOP->PhysicalMMU->mapObject(PS2Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY, IOP->MainMemory);

		// Various ROMs.
		IOP->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_BOOT_ROM, EE->BootROM);
		IOP->PhysicalMMU->mapObject(PS2Constants::EE::ROM::PADDRESS_ROM1, EE->ROM1);

		// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation.
		IOP->PhysicalMMU->mapObject(0xFFC00000, EE->BootROM);

		// Scratchpad Memory.
		IOP->PhysicalMMU->mapObject(PS2Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, IOP->IOPCore->ScratchpadMemory);
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
		IOP->PhysicalMMU->mapObject(0x1F801578, IOP->REGISTER_1578);
		IOP->PhysicalMMU->mapObject(0x1F8015F0, IOP->REGISTER_15F0);
		IOP->PhysicalMMU->mapObject(0x1F802070, IOP->REGISTER_2070);

		// DMAC Registers.
		IOP->PhysicalMMU->mapObject(0x1F801080, IOP->DMAC->CHANNEL_0->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801084, IOP->DMAC->CHANNEL_0->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801088, IOP->DMAC->CHANNEL_0->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80108C, IOP->DMAC->CHANNEL_0->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801090, IOP->DMAC->CHANNEL_1->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801094, IOP->DMAC->CHANNEL_1->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801098, IOP->DMAC->CHANNEL_1->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80109C, IOP->DMAC->CHANNEL_1->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010A0, IOP->DMAC->CHANNEL_2->MADR);
		IOP->PhysicalMMU->mapObject(0x1F8010A4, IOP->DMAC->CHANNEL_2->BCR);
		IOP->PhysicalMMU->mapObject(0x1F8010A8, IOP->DMAC->CHANNEL_2->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F8010AC, IOP->DMAC->CHANNEL_2->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010B0, IOP->DMAC->CHANNEL_3->MADR);
		IOP->PhysicalMMU->mapObject(0x1F8010B4, IOP->DMAC->CHANNEL_3->BCR);
		IOP->PhysicalMMU->mapObject(0x1F8010B8, IOP->DMAC->CHANNEL_3->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F8010BC, IOP->DMAC->CHANNEL_3->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010C0, IOP->DMAC->CHANNEL_4->MADR);
		IOP->PhysicalMMU->mapObject(0x1F8010C4, IOP->DMAC->CHANNEL_4->BCR);
		IOP->PhysicalMMU->mapObject(0x1F8010C8, IOP->DMAC->CHANNEL_4->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F8010CC, IOP->DMAC->CHANNEL_4->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010D0, IOP->DMAC->CHANNEL_5->MADR);
		IOP->PhysicalMMU->mapObject(0x1F8010D4, IOP->DMAC->CHANNEL_5->BCR);
		IOP->PhysicalMMU->mapObject(0x1F8010D8, IOP->DMAC->CHANNEL_5->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F8010DC, IOP->DMAC->CHANNEL_5->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010E0, IOP->DMAC->CHANNEL_6->MADR);
		IOP->PhysicalMMU->mapObject(0x1F8010E4, IOP->DMAC->CHANNEL_6->BCR);
		IOP->PhysicalMMU->mapObject(0x1F8010E8, IOP->DMAC->CHANNEL_6->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F8010EC, IOP->DMAC->CHANNEL_6->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801500, IOP->DMAC->CHANNEL_7->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801504, IOP->DMAC->CHANNEL_7->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801508, IOP->DMAC->CHANNEL_7->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80150C, IOP->DMAC->CHANNEL_7->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801510, IOP->DMAC->CHANNEL_8->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801514, IOP->DMAC->CHANNEL_8->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801518, IOP->DMAC->CHANNEL_8->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80151C, IOP->DMAC->CHANNEL_8->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801520, IOP->DMAC->CHANNEL_9->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801524, IOP->DMAC->CHANNEL_9->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801528, IOP->DMAC->CHANNEL_9->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80152C, IOP->DMAC->CHANNEL_9->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801530, IOP->DMAC->CHANNEL_10->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801534, IOP->DMAC->CHANNEL_10->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801538, IOP->DMAC->CHANNEL_10->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80153C, IOP->DMAC->CHANNEL_10->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801540, IOP->DMAC->CHANNEL_11->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801544, IOP->DMAC->CHANNEL_11->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801548, IOP->DMAC->CHANNEL_11->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80154C, IOP->DMAC->CHANNEL_11->TADR);
		IOP->PhysicalMMU->mapObject(0x1F801550, IOP->DMAC->CHANNEL_12->MADR);
		IOP->PhysicalMMU->mapObject(0x1F801554, IOP->DMAC->CHANNEL_12->BCR);
		IOP->PhysicalMMU->mapObject(0x1F801558, IOP->DMAC->CHANNEL_12->CHCR);
		IOP->PhysicalMMU->mapObject(0x1F80155C, IOP->DMAC->CHANNEL_12->TADR);
		IOP->PhysicalMMU->mapObject(0x1F8010F0, IOP->DMAC->PCR);
		IOP->PhysicalMMU->mapObject(0x1F8010F4, IOP->DMAC->ICR);
		IOP->PhysicalMMU->mapObject(0x1F801570, IOP->DMAC->PCR2);
		IOP->PhysicalMMU->mapObject(0x1F801574, IOP->DMAC->ICR2);

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
		IOP->PhysicalMMU->mapObject(PS2Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT, IOP->ParallelPort);

	}

	// SIF Registers
	{
		IOP->PhysicalMMU->mapObject(0x1D000000, SIF->MSCOM);
		IOP->PhysicalMMU->mapObject(0x1D000010, SIF->SMCOM);
		IOP->PhysicalMMU->mapObject(0x1D000020, SIF->MSFLG);
		IOP->PhysicalMMU->mapObject(0x1D000030, SIF->SMFLG);
		IOP->PhysicalMMU->mapObject(0x1D000060, SIF->REGISTER_0060);
	}
}

void PS2Resources_t::initPhysicalMemoryMap_VU0() const
{
	// VU0 Memory.
	{
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x0000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x1000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x2000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x3000, EE->VPU->VU->VU0->MEMORY_Mem);
	}

	// VU1 Registers, see VU Users Manual page 222. 
	{
		// VF Registers.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
			EE->VPU->VU->VU0->MemPhysicalMMU->mapObject(0x4000 + i * Constants::NUMBER_BYTES_IN_QWORD, EE->VPU->VU->VU1->VF[i]);

		// VI Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded! 
		// NOT mapped as the true register size of 16-bit (need to do a Register32_t wrapping)! 
		// See EE Users Manual page 84.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
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
	}
}

void PS2Resources_t::initPhysicalMemoryMap_VU1() const
{
	// VU1 Memory.
	EE->VPU->VU->VU1->MemPhysicalMMU->mapObject(0x0000, EE->VPU->VU->VU1->MEMORY_Mem);
}

void PS2Resources_t::initControlRegistersMap_VU0() const
{
	auto& VU0 = EE->VPU->VU->VU0;
	auto& VU1 = EE->VPU->VU->VU1;
	auto& VU = EE->VPU->VU;
	auto& VPU = EE->VPU;

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
	VU0->CCR[28] = VU->FBRST;
	VU0->CCR[29] = VPU->STAT;
	VU0->CCR[30] = nullptr; 
	VU0->CCR[31] = VU1->CMSAR;
}
