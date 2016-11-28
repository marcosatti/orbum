#include "stdafx.h"

#include <memory>

#include "PS2Resources/PS2Resources_t.h"
#include "PS2Resources/Clock/Clock_t.h"
#include "PS2Resources/EE/EE_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/GS/GS_t.h"
#include "PS2Resources/IOP/IOP_t.h"

#include "Common/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/Types/Registers/PCRegister16_t.h"
#include "Common/Types/Registers/WrapperR16Register32_t.h"
#include "Common/Types/Registers/WrapperF32Register32_t.h"

#include "PS2Resources/EE/Types/EERegisters_t.h"
#include "PS2Resources/EE/Types/BootROM_t.h"
#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/Timers/EETimers_t.h"
#include "PS2Resources/EE/Timers/Types/EETimersTimers_t.h"
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

PS2Resources_t::PS2Resources_t() :
	Clock(std::make_shared<Clock_t>()),
	GS(std::make_shared<GS_t>(this)),
	EE(std::make_shared<EE_t>(this)),
	IOP(std::make_shared<IOP_t>(this))
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
		// Main memory 32MB
		EE->PhysicalMMU->mapMemory(PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY, EE->MainMemory);

		// Scratchpad memory 16KB
		EE->PhysicalMMU->mapMemory(PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, EE->EECore->ScratchpadMemory);

		// Boot ROM 4MB
		EE->PhysicalMMU->mapMemory(PS2Constants::EE::BootROM::PADDRESS_BOOT_ROM, EE->BootROM);

		// Unknown memory.
		EE->PhysicalMMU->mapMemory(0x1A000000, EE->UNKNOWN_1A000000);
	}

	// EE Registers.
	{
		// MISC EE registers.
		EE->PhysicalMMU->mapMemory(0x1000F100, EE->MEMORY_SIO);
		EE->PhysicalMMU->mapMemory(0x1000f230, EE->REGISTER_SB_SMFLG);
		EE->PhysicalMMU->mapMemory(0x1000f400, EE->REGISTER_F400);
		EE->PhysicalMMU->mapMemory(0x1000f410, EE->MEMORY_F410);
		EE->PhysicalMMU->mapMemory(0x1000f420, EE->REGISTER_F420);
		EE->PhysicalMMU->mapMemory(0x1000F430, EE->MEMORY_MCH);
		EE->PhysicalMMU->mapMemory(0x1000f450, EE->MEMORY_F450);

		// Timers Registers.
		EE->PhysicalMMU->mapMemory(0x10000000, EE->Timers->TIMER0->mCOUNT);
		EE->PhysicalMMU->mapMemory(0x10000010, EE->Timers->TIMER0->mMODE);
		EE->PhysicalMMU->mapMemory(0x10000020, EE->Timers->TIMER0->mCOMP);
		EE->PhysicalMMU->mapMemory(0x10000030, EE->Timers->TIMER0->mHOLD);
		EE->PhysicalMMU->mapMemory(0x10000800, EE->Timers->TIMER1->mCOUNT);
		EE->PhysicalMMU->mapMemory(0x10000810, EE->Timers->TIMER1->mMODE);
		EE->PhysicalMMU->mapMemory(0x10000820, EE->Timers->TIMER1->mCOMP);
		EE->PhysicalMMU->mapMemory(0x10000830, EE->Timers->TIMER1->mHOLD);
		EE->PhysicalMMU->mapMemory(0x10001000, EE->Timers->TIMER2->mCOUNT);
		EE->PhysicalMMU->mapMemory(0x10001010, EE->Timers->TIMER2->mMODE);
		EE->PhysicalMMU->mapMemory(0x10001020, EE->Timers->TIMER2->mCOMP);
		EE->PhysicalMMU->mapMemory(0x10001800, EE->Timers->TIMER3->mCOUNT);
		EE->PhysicalMMU->mapMemory(0x10001810, EE->Timers->TIMER3->mMODE);
		EE->PhysicalMMU->mapMemory(0x10001820, EE->Timers->TIMER3->mCOMP);

		// IPU Registers.
		EE->PhysicalMMU->mapMemory(0x10002000, EE->IPU->REGISTER_CMD);
		EE->PhysicalMMU->mapMemory(0x10002010, EE->IPU->REGISTER_CTRL);
		EE->PhysicalMMU->mapMemory(0x10002020, EE->IPU->REGISTER_BP);
		EE->PhysicalMMU->mapMemory(0x10002030, EE->IPU->REGISTER_TOP);

		// GIF Registers.
		EE->PhysicalMMU->mapMemory(0x10003000, EE->GIF->REGISTER_CTRL);
		EE->PhysicalMMU->mapMemory(0x10003010, EE->GIF->REGISTER_MODE);
		EE->PhysicalMMU->mapMemory(0x10003020, EE->GIF->REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(0x10003040, EE->GIF->REGISTER_TAG0);
		EE->PhysicalMMU->mapMemory(0x10003050, EE->GIF->REGISTER_TAG1);
		EE->PhysicalMMU->mapMemory(0x10003060, EE->GIF->REGISTER_TAG2);
		EE->PhysicalMMU->mapMemory(0x10003070, EE->GIF->REGISTER_TAG3);
		EE->PhysicalMMU->mapMemory(0x10003080, EE->GIF->REGISTER_CNT);
		EE->PhysicalMMU->mapMemory(0x10003090, EE->GIF->REGISTER_P3CNT);
		EE->PhysicalMMU->mapMemory(0x100030a0, EE->GIF->REGISTER_P3TAG);

		// VIF0 Registers.
		EE->PhysicalMMU->mapMemory(0x10003800, EE->VPU->VIF->VIF0->mSTAT);
		EE->PhysicalMMU->mapMemory(0x10003810, EE->VPU->VIF->VIF0->mFBRST);
		EE->PhysicalMMU->mapMemory(0x10003820, EE->VPU->VIF->VIF0->mERR);
		EE->PhysicalMMU->mapMemory(0x10003830, EE->VPU->VIF->VIF0->mMARK);
		EE->PhysicalMMU->mapMemory(0x10003840, EE->VPU->VIF->VIF0->mCYCLE);
		EE->PhysicalMMU->mapMemory(0x10003850, EE->VPU->VIF->VIF0->mMODE);
		EE->PhysicalMMU->mapMemory(0x10003860, EE->VPU->VIF->VIF0->mNUM);
		EE->PhysicalMMU->mapMemory(0x10003870, EE->VPU->VIF->VIF0->mMASK);
		EE->PhysicalMMU->mapMemory(0x10003880, EE->VPU->VIF->VIF0->mCODE);
		EE->PhysicalMMU->mapMemory(0x10003890, EE->VPU->VIF->VIF0->mITOPS);
		EE->PhysicalMMU->mapMemory(0x100038d0, EE->VPU->VIF->VIF0->mITOP);
		EE->PhysicalMMU->mapMemory(0x10003900, EE->VPU->VIF->VIF0->mR0);
		EE->PhysicalMMU->mapMemory(0x10003910, EE->VPU->VIF->VIF0->mR1);
		EE->PhysicalMMU->mapMemory(0x10003920, EE->VPU->VIF->VIF0->mR2);
		EE->PhysicalMMU->mapMemory(0x10003930, EE->VPU->VIF->VIF0->mR3);
		EE->PhysicalMMU->mapMemory(0x10003940, EE->VPU->VIF->VIF0->mC0);
		EE->PhysicalMMU->mapMemory(0x10003950, EE->VPU->VIF->VIF0->mC1);
		EE->PhysicalMMU->mapMemory(0x10003960, EE->VPU->VIF->VIF0->mC2);
		EE->PhysicalMMU->mapMemory(0x10003970, EE->VPU->VIF->VIF0->mC3);

		// VIF1 Registers.
		EE->PhysicalMMU->mapMemory(0x10003c00, EE->VPU->VIF->VIF1->mSTAT);
		EE->PhysicalMMU->mapMemory(0x10003c10, EE->VPU->VIF->VIF1->mFBRST);
		EE->PhysicalMMU->mapMemory(0x10003c20, EE->VPU->VIF->VIF1->mERR);
		EE->PhysicalMMU->mapMemory(0x10003c30, EE->VPU->VIF->VIF1->mMARK);
		EE->PhysicalMMU->mapMemory(0x10003c40, EE->VPU->VIF->VIF1->mCYCLE);
		EE->PhysicalMMU->mapMemory(0x10003c50, EE->VPU->VIF->VIF1->mMODE);
		EE->PhysicalMMU->mapMemory(0x10003c60, EE->VPU->VIF->VIF1->mNUM);
		EE->PhysicalMMU->mapMemory(0x10003c70, EE->VPU->VIF->VIF1->mMASK);
		EE->PhysicalMMU->mapMemory(0x10003c80, EE->VPU->VIF->VIF1->mCODE);
		EE->PhysicalMMU->mapMemory(0x10003c90, EE->VPU->VIF->VIF1->mITOPS);
		EE->PhysicalMMU->mapMemory(0x10003ca0, EE->VPU->VIF->VIF1->mBASE);
		EE->PhysicalMMU->mapMemory(0x10003cb0, EE->VPU->VIF->VIF1->mOFST);
		EE->PhysicalMMU->mapMemory(0x10003cc0, EE->VPU->VIF->VIF1->mTOPS);
		EE->PhysicalMMU->mapMemory(0x10003cd0, EE->VPU->VIF->VIF1->mITOP);
		EE->PhysicalMMU->mapMemory(0x10003ce0, EE->VPU->VIF->VIF1->mTOP);
		EE->PhysicalMMU->mapMemory(0x10003d00, EE->VPU->VIF->VIF1->mR0);
		EE->PhysicalMMU->mapMemory(0x10003d10, EE->VPU->VIF->VIF1->mR1);
		EE->PhysicalMMU->mapMemory(0x10003d20, EE->VPU->VIF->VIF1->mR2);
		EE->PhysicalMMU->mapMemory(0x10003d30, EE->VPU->VIF->VIF1->mR3);
		EE->PhysicalMMU->mapMemory(0x10003d40, EE->VPU->VIF->VIF1->mC0);
		EE->PhysicalMMU->mapMemory(0x10003d50, EE->VPU->VIF->VIF1->mC1);
		EE->PhysicalMMU->mapMemory(0x10003d60, EE->VPU->VIF->VIF1->mC2);
		EE->PhysicalMMU->mapMemory(0x10003d70, EE->VPU->VIF->VIF1->mC3);

		// FIFO Registers.
		EE->PhysicalMMU->mapMemory(0x10004000, EE->FIFO_VIF0);
		EE->PhysicalMMU->mapMemory(0x10005000, EE->FIFO_VIF1);
		EE->PhysicalMMU->mapMemory(0x10006000, EE->FIFO_GIF);
		EE->PhysicalMMU->mapMemory(0x10007000, EE->FIFO_IPU_out);
		EE->PhysicalMMU->mapMemory(0x10007010, EE->FIFO_IPU_in);

		// DMAC registers.
		EE->PhysicalMMU->mapMemory(0x10008000, EE->DMAC->CHANNEL_VIF0->mCHCR);
		EE->PhysicalMMU->mapMemory(0x10008010, EE->DMAC->CHANNEL_VIF0->mMADR);
		EE->PhysicalMMU->mapMemory(0x10008020, EE->DMAC->CHANNEL_VIF0->mQWC);
		EE->PhysicalMMU->mapMemory(0x10008030, EE->DMAC->CHANNEL_VIF0->mTADR);
		EE->PhysicalMMU->mapMemory(0x10008040, EE->DMAC->CHANNEL_VIF0->mASR0);
		EE->PhysicalMMU->mapMemory(0x10008050, EE->DMAC->CHANNEL_VIF0->mASR1);
		EE->PhysicalMMU->mapMemory(0x10008060, EE->DMAC->CHANNEL_VIF0->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x10009000, EE->DMAC->CHANNEL_VIF1->mCHCR);
		EE->PhysicalMMU->mapMemory(0x10009010, EE->DMAC->CHANNEL_VIF1->mMADR);
		EE->PhysicalMMU->mapMemory(0x10009020, EE->DMAC->CHANNEL_VIF1->mQWC);
		EE->PhysicalMMU->mapMemory(0x10009030, EE->DMAC->CHANNEL_VIF1->mTADR);
		EE->PhysicalMMU->mapMemory(0x10009040, EE->DMAC->CHANNEL_VIF1->mASR0);
		EE->PhysicalMMU->mapMemory(0x10009050, EE->DMAC->CHANNEL_VIF1->mASR1);
		EE->PhysicalMMU->mapMemory(0x10009060, EE->DMAC->CHANNEL_VIF1->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000a000, EE->DMAC->CHANNEL_GIF->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000a010, EE->DMAC->CHANNEL_GIF->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000a020, EE->DMAC->CHANNEL_GIF->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000a030, EE->DMAC->CHANNEL_GIF->mTADR);
		EE->PhysicalMMU->mapMemory(0x1000a040, EE->DMAC->CHANNEL_GIF->mASR0);
		EE->PhysicalMMU->mapMemory(0x1000a050, EE->DMAC->CHANNEL_GIF->mASR1);
		EE->PhysicalMMU->mapMemory(0x1000a060, EE->DMAC->CHANNEL_GIF->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000b000, EE->DMAC->CHANNEL_fromIPU->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000b010, EE->DMAC->CHANNEL_fromIPU->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000b020, EE->DMAC->CHANNEL_fromIPU->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000b030, EE->DMAC->CHANNEL_fromIPU->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000b400, EE->DMAC->CHANNEL_toIPU->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000b410, EE->DMAC->CHANNEL_toIPU->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000b420, EE->DMAC->CHANNEL_toIPU->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000b430, EE->DMAC->CHANNEL_toIPU->mTADR);
		EE->PhysicalMMU->mapMemory(0x1000b440, EE->DMAC->CHANNEL_toIPU->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000c000, EE->DMAC->CHANNEL_SIF0->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000c010, EE->DMAC->CHANNEL_SIF0->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000c020, EE->DMAC->CHANNEL_SIF0->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000c030, EE->DMAC->CHANNEL_SIF0->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000c400, EE->DMAC->CHANNEL_SIF1->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000c410, EE->DMAC->CHANNEL_SIF1->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000c420, EE->DMAC->CHANNEL_SIF1->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000c430, EE->DMAC->CHANNEL_SIF1->mTADR);
		EE->PhysicalMMU->mapMemory(0x1000c440, EE->DMAC->CHANNEL_SIF1->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000c800, EE->DMAC->CHANNEL_SIF2->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000c810, EE->DMAC->CHANNEL_SIF2->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000c820, EE->DMAC->CHANNEL_SIF2->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000c830, EE->DMAC->CHANNEL_SIF2->mRESERVED);
		EE->PhysicalMMU->mapMemory(0x1000d000, EE->DMAC->CHANNEL_fromSPR->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000d010, EE->DMAC->CHANNEL_fromSPR->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000d020, EE->DMAC->CHANNEL_fromSPR->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000d030, EE->DMAC->CHANNEL_fromSPR->mRESERVED0);
		EE->PhysicalMMU->mapMemory(0x1000d080, EE->DMAC->CHANNEL_fromSPR->mSADR);
		EE->PhysicalMMU->mapMemory(0x1000d090, EE->DMAC->CHANNEL_fromSPR->mRESERVED1);
		EE->PhysicalMMU->mapMemory(0x1000d400, EE->DMAC->CHANNEL_toSPR->mCHCR);
		EE->PhysicalMMU->mapMemory(0x1000d410, EE->DMAC->CHANNEL_toSPR->mMADR);
		EE->PhysicalMMU->mapMemory(0x1000d420, EE->DMAC->CHANNEL_toSPR->mQWC);
		EE->PhysicalMMU->mapMemory(0x1000d430, EE->DMAC->CHANNEL_toSPR->mTADR);
		EE->PhysicalMMU->mapMemory(0x1000d440, EE->DMAC->CHANNEL_toSPR->mRESERVED0);
		EE->PhysicalMMU->mapMemory(0x1000d480, EE->DMAC->CHANNEL_toSPR->mSADR);
		EE->PhysicalMMU->mapMemory(0x1000d490, EE->DMAC->CHANNEL_toSPR->mRESERVED1);
		EE->PhysicalMMU->mapMemory(0x1000e000, EE->DMAC->REGISTER_CTRL);
		EE->PhysicalMMU->mapMemory(0x1000e010, EE->DMAC->REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(0x1000e020, EE->DMAC->REGISTER_PCR);
		EE->PhysicalMMU->mapMemory(0x1000e030, EE->DMAC->REGISTER_SQWC);
		EE->PhysicalMMU->mapMemory(0x1000e040, EE->DMAC->REGISTER_RBSR);
		EE->PhysicalMMU->mapMemory(0x1000e050, EE->DMAC->REGISTER_RBOR);
		EE->PhysicalMMU->mapMemory(0x1000e060, EE->DMAC->REGISTER_STADR);

		// INTC registers.
		EE->PhysicalMMU->mapMemory(0x1000f000, EE->INTC->REGISTER_STAT);
		EE->PhysicalMMU->mapMemory(0x1000f010, EE->INTC->REGISTER_MASK);

		// DMAC registers (extended).
		EE->PhysicalMMU->mapMemory(0x1000f500, EE->DMAC->MEMORY_F500);
		EE->PhysicalMMU->mapMemory(0x1000f520, EE->DMAC->REGISTER_ENABLER);
		EE->PhysicalMMU->mapMemory(0x1000f590, EE->DMAC->REGISTER_ENABLEW);
	}

	// VU0/1 Memory
	{
		EE->PhysicalMMU->mapMemory(0x11000000, EE->VPU->VU->VU0->MEMORY_Micro);
		EE->PhysicalMMU->mapMemory(0x11004000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->PhysicalMMU->mapMemory(0x11008000, EE->VPU->VU->VU1->MEMORY_Micro);
		EE->PhysicalMMU->mapMemory(0x1100c000, EE->VPU->VU->VU1->MEMORY_Mem);
	}

	// GS Privileged Registers.
	{
		EE->PhysicalMMU->mapMemory(0x12000000, GS->GS_P_REGISTER_PMODE);
		EE->PhysicalMMU->mapMemory(0x12000010, GS->GS_P_REGISTER_SMODE1);
		EE->PhysicalMMU->mapMemory(0x12000020, GS->GS_P_REGISTER_SMODE2);
		EE->PhysicalMMU->mapMemory(0x12000030, GS->GS_P_REGISTER_SRFSH);
		EE->PhysicalMMU->mapMemory(0x12000040, GS->GS_P_REGISTER_SYNCH1);
		EE->PhysicalMMU->mapMemory(0x12000050, GS->GS_P_REGISTER_SYNCH2);
		EE->PhysicalMMU->mapMemory(0x12000060, GS->GS_P_REGISTER_SYNCV);
		EE->PhysicalMMU->mapMemory(0x12000070, GS->GS_P_REGISTER_DISPFB1);
		EE->PhysicalMMU->mapMemory(0x12000080, GS->GS_P_REGISTER_DISPLAY1);
		EE->PhysicalMMU->mapMemory(0x12000090, GS->GS_P_REGISTER_DISPFB2);
		EE->PhysicalMMU->mapMemory(0x120000a0, GS->GS_P_REGISTER_DISPLAY2);
		EE->PhysicalMMU->mapMemory(0x120000b0, GS->GS_P_REGISTER_EXTBUF);
		EE->PhysicalMMU->mapMemory(0x120000c0, GS->GS_P_REGISTER_EXTDATA);
		EE->PhysicalMMU->mapMemory(0x120000d0, GS->GS_P_REGISTER_EXTWRITE);
		EE->PhysicalMMU->mapMemory(0x120000e0, GS->GS_P_REGISTER_BGCOLOR);
		
		EE->PhysicalMMU->mapMemory(0x12001000, GS->GS_P_REGISTER_CSR);
		EE->PhysicalMMU->mapMemory(0x12001010, GS->GS_P_REGISTER_IMR);
		EE->PhysicalMMU->mapMemory(0x12001040, GS->GS_P_REGISTER_BUSDIR);
		EE->PhysicalMMU->mapMemory(0x12001080, GS->GS_P_REGISTER_SIGLBLID);
	}

	// IOP Mirrors
	{
		EE->PhysicalMMU->mapMemory(0x1F801000, IOP->IOP_HW_REGISTERS);
		EE->PhysicalMMU->mapMemory(0x1C000000, IOP->MainMemory);
	}
}

void PS2Resources_t::initPhysicalMemoryMap_IOP() const
{
	// Main Memory
	IOP->PhysicalMMU->mapMemory(PS2Constants::IOP::IOPMemory::PADDRESS_IOP_MEMORY, IOP->MainMemory);

	// Boot ROM
	IOP->PhysicalMMU->mapMemory(PS2Constants::EE::BootROM::PADDRESS_BOOT_ROM, EE->BootROM);

	// Scratchpad Memory
	IOP->PhysicalMMU->mapMemory(PS2Constants::IOP::IOPCore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY, IOP->IOPCore->ScratchpadMemory);

	// Parallel Port
	IOP->PhysicalMMU->mapMemory(PS2Constants::IOP::ParallelPort::PADDRESS_PARALLEL_PORT, IOP->ParallelPort);

	// HW Registers
	IOP->PhysicalMMU->mapMemory(0x1F801000, IOP->IOP_HW_REGISTERS);

	// Mirror of the Boot ROM at 0xFFC00000. Needed by IOP bios initalisation.
	IOP->PhysicalMMU->mapMemory(0xFFC00000, EE->BootROM);
}

void PS2Resources_t::initPhysicalMemoryMap_VU0() const
{
	// VU0 Memory.
	{
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x0000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x1000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x2000, EE->VPU->VU->VU0->MEMORY_Mem);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x3000, EE->VPU->VU->VU0->MEMORY_Mem);
	}

	// VU1 Registers, see VU Users Manual page 222. 
	{
		// VF Registers.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VF_REGISTERS; i++)
			EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4000 + i * Constants::NUMBER_BYTES_IN_QWORD, EE->VPU->VU->VU1->VF[i]);

		// VI Registers. Aligned on 128-bit boundaries, accessed by 32-bit r/w, but upper 16-bits discarded! 
		// NOT mapped as the true register size of 16-bit (need to do a Register32_t wrapping)! 
		// See EE Users Manual page 84.
		// The upper 112-bits are left unmapped.
		for (auto i = 0; i < PS2Constants::EE::VPU::VU::NUMBER_VI_REGISTERS; i++)
			EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4200 + i * Constants::NUMBER_BYTES_IN_QWORD, std::make_shared<WrapperR16Register32_t>(EE->VPU->VU->VU1->VI[i]));

		// Misc Registers.
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4300, EE->VPU->VU->VU1->Status);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4310, EE->VPU->VU->VU1->MAC);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4320, EE->VPU->VU->VU1->Clipping);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4340, EE->VPU->VU->VU1->R);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4350, EE->VPU->VU->VU1->I);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4360, EE->VPU->VU->VU1->Q);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x4370, EE->VPU->VU->VU1->P);
		EE->VPU->VU->VU0->MemPhysicalMMU->mapMemory(0x43A0, EE->VPU->VU->VU1->PC); // TPC.
	}
}

void PS2Resources_t::initPhysicalMemoryMap_VU1() const
{
	// VU1 Memory.
	EE->VPU->VU->VU1->MemPhysicalMMU->mapMemory(0x0000, EE->VPU->VU->VU1->MEMORY_Mem);
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
