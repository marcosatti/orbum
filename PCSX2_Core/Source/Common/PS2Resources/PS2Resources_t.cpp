#include "stdafx.h"

#include <memory>

#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/Clock/Clock_t.h"
#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/GS/GS_t.h"
#include "Common/PS2Resources/IOP/IOP_t.h"

#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/Types/PhysicalMMU/MappedRegister32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
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
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T0_COUNT", 0x10000000, EE->Timers->TIMERS_REGISTER_T0_COUNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T0_MODE", 0x10000010, EE->Timers->TIMERS_REGISTER_T0_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T0_COMP", 0x10000020, EE->Timers->TIMERS_REGISTER_T0_COMP));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T0_HOLD", 0x10000030, EE->Timers->TIMERS_REGISTER_T0_HOLD));
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_MEMORY_TIMER_0040);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T1_COUNT", 0x10000800, EE->Timers->TIMERS_REGISTER_T1_COUNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T1_MODE", 0x10000810, EE->Timers->TIMERS_REGISTER_T1_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T1_COMP", 0x10000820, EE->Timers->TIMERS_REGISTER_T1_COMP));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T1_HOLD", 0x10000830, EE->Timers->TIMERS_REGISTER_T1_HOLD));
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_MEMORY_TIMER_0840);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T2_COUNT", 0x10001000, EE->Timers->TIMERS_REGISTER_T2_COUNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T2_MODE", 0x10001010, EE->Timers->TIMERS_REGISTER_T2_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T2_COMP", 0x10001020, EE->Timers->TIMERS_REGISTER_T2_COMP));
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_MEMORY_TIMER_1030);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T3_COUNT", 0x10001800, EE->Timers->TIMERS_REGISTER_T3_COUNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T3_MODE", 0x10001810, EE->Timers->TIMERS_REGISTER_T3_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("TIMER: T3_COMP", 0x10001820, EE->Timers->TIMERS_REGISTER_T3_COMP));
		EE->PhysicalMMU->mapMemory(EE->Timers->TIMERS_MEMORY_TIMER_1830);

		// IPU Registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("IPU: IPU_CMD", 0x10002000, EE->IPU->IPU_REGISTER_CMD));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("IPU: IPU_CTRL", 0x10002010, EE->IPU->IPU_REGISTER_CTRL));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("IPU: IPU_BP", 0x10002020, EE->IPU->IPU_REGISTER_BP));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("IPU: IPU_TOP", 0x10002030, EE->IPU->IPU_REGISTER_TOP));
		EE->PhysicalMMU->mapMemory(EE->IPU->IPU_MEMORY_2040);

		// GIF Registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_CTRL", 0x10003000, EE->GIF->GIF_REGISTER_CTRL));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_MODE", 0x10003010, EE->GIF->GIF_REGISTER_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_STAT", 0x10003020, EE->GIF->GIF_REGISTER_STAT));
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_MEMORY_3030);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_TAG0", 0x10003040, EE->GIF->GIF_REGISTER_TAG0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_TAG1", 0x10003050, EE->GIF->GIF_REGISTER_TAG1));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_TAG2", 0x10003060, EE->GIF->GIF_REGISTER_TAG2));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_TAG3", 0x10003070, EE->GIF->GIF_REGISTER_TAG3));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_CNT", 0x10003080, EE->GIF->GIF_REGISTER_CNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_P3CNT", 0x10003090, EE->GIF->GIF_REGISTER_P3CNT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("GIF: GIF_P3TAG", 0x100030a0, EE->GIF->GIF_REGISTER_P3TAG));
		EE->PhysicalMMU->mapMemory(EE->GIF->GIF_MEMORY_30b0);

		// VIF0 Registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_STAT", 0x10003800, EE->VPU->VIF->VIF0_REGISTER_STAT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_FBRST", 0x10003810, EE->VPU->VIF->VIF0_REGISTER_FBRST));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_ERR", 0x10003820, EE->VPU->VIF->VIF0_REGISTER_ERR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_MARK", 0x10003830, EE->VPU->VIF->VIF0_REGISTER_MARK));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_CYCLE", 0x10003840, EE->VPU->VIF->VIF0_REGISTER_CYCLE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_MODE", 0x10003850, EE->VPU->VIF->VIF0_REGISTER_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_NUM", 0x10003860, EE->VPU->VIF->VIF0_REGISTER_NUM));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_MASK", 0x10003870, EE->VPU->VIF->VIF0_REGISTER_MASK));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_CODE", 0x10003880, EE->VPU->VIF->VIF0_REGISTER_CODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_ITOPS", 0x10003890, EE->VPU->VIF->VIF0_REGISTER_ITOPS));
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_38a0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_38b0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_38c0);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_ITOP", 0x100038d0, EE->VPU->VIF->VIF0_REGISTER_ITOP));
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_38e0);
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_38f0);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_R0", 0x10003900, EE->VPU->VIF->VIF0_REGISTER_R0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_R1", 0x10003910, EE->VPU->VIF->VIF0_REGISTER_R1));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_R2", 0x10003920, EE->VPU->VIF->VIF0_REGISTER_R2));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_R3", 0x10003930, EE->VPU->VIF->VIF0_REGISTER_R3));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_C0", 0x10003940, EE->VPU->VIF->VIF0_REGISTER_C0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_C1", 0x10003950, EE->VPU->VIF->VIF0_REGISTER_C1));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_C2", 0x10003960, EE->VPU->VIF->VIF0_REGISTER_C2));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF0: VIF0_C3", 0x10003970, EE->VPU->VIF->VIF0_REGISTER_C3));
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF0_MEMORY_3980);

		// VIF1 Registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_STAT", 0x10003c00, EE->VPU->VIF->VIF1_REGISTER_STAT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_FBRST", 0x10003c10, EE->VPU->VIF->VIF1_REGISTER_FBRST));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_ERR", 0x10003c20, EE->VPU->VIF->VIF1_REGISTER_ERR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_MARK", 0x10003c30, EE->VPU->VIF->VIF1_REGISTER_MARK));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_CYCLE", 0x10003c40, EE->VPU->VIF->VIF1_REGISTER_CYCLE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_MODE", 0x10003c50, EE->VPU->VIF->VIF1_REGISTER_MODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_NUM", 0x10003c60, EE->VPU->VIF->VIF1_REGISTER_NUM));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_MASK", 0x10003c70, EE->VPU->VIF->VIF1_REGISTER_MASK));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_CODE", 0x10003c80, EE->VPU->VIF->VIF1_REGISTER_CODE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_ITOPS", 0x10003c90, EE->VPU->VIF->VIF1_REGISTER_ITOPS));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_BASE", 0x10003ca0, EE->VPU->VIF->VIF1_REGISTER_BASE));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_OFST", 0x10003cb0, EE->VPU->VIF->VIF1_REGISTER_OFST));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_TOPS", 0x10003cc0, EE->VPU->VIF->VIF1_REGISTER_TOPS));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_ITOP", 0x10003cd0, EE->VPU->VIF->VIF1_REGISTER_ITOP));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_TOP", 0x10003ce0, EE->VPU->VIF->VIF1_REGISTER_TOP));
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_MEMORY_3cf0);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_R0", 0x10003d00, EE->VPU->VIF->VIF1_REGISTER_R0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_R1", 0x10003d10, EE->VPU->VIF->VIF1_REGISTER_R1));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_R2", 0x10003d20, EE->VPU->VIF->VIF1_REGISTER_R2));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_R3", 0x10003d30, EE->VPU->VIF->VIF1_REGISTER_R3));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_C0", 0x10003d40, EE->VPU->VIF->VIF1_REGISTER_C0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_C1", 0x10003d50, EE->VPU->VIF->VIF1_REGISTER_C1));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_C2", 0x10003d60, EE->VPU->VIF->VIF1_REGISTER_C2));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("VIF1: VIF1_C3", 0x10003d70, EE->VPU->VIF->VIF1_REGISTER_C3));
		EE->PhysicalMMU->mapMemory(EE->VPU->VIF->VIF1_MEMORY_3d80);

		// FIFO Registers.
		EE->PhysicalMMU->mapMemory(EE->EE_FIFO_VIF0);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x10004000", 0x10004010, 0x10, 0xFF0, 0x10004000, EE->PhysicalMMU)); // Image of 0x10004000.
		
		EE->PhysicalMMU->mapMemory(EE->EE_FIFO_VIF1);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x10005000", 0x10005010, 0x10, 0xFF0, 0x10005000, EE->PhysicalMMU)); // Image of 0x10005000.
		
		EE->PhysicalMMU->mapMemory(EE->EE_FIFO_GIF);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x10006000", 0x10006010, 0x10, 0xFF0, 0x10006000, EE->PhysicalMMU)); // Image of 0x10006000.
		
		EE->PhysicalMMU->mapMemory(EE->EE_FIFO_IPU_out);
		EE->PhysicalMMU->mapMemory(EE->EE_FIFO_IPU_in);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x10007000", 0x10007020, 0x20, 0xFE0, 0x10007000, EE->PhysicalMMU)); // Image of 0x10007000.
		

		// DMAC registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_CHCR", 0x10008000, EE->DMAC->DMAC_REGISTER_D0_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_MADR", 0x10008010, EE->DMAC->DMAC_REGISTER_D0_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_QWC", 0x10008020, EE->DMAC->DMAC_REGISTER_D0_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_TADR", 0x10008030, EE->DMAC->DMAC_REGISTER_D0_TADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_ASR0", 0x10008040, EE->DMAC->DMAC_REGISTER_D0_ASR0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D0_ASR1", 0x10008050, EE->DMAC->DMAC_REGISTER_D0_ASR1));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_8060);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_CHCR", 0x10009000, EE->DMAC->DMAC_REGISTER_D1_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_MADR", 0x10009010, EE->DMAC->DMAC_REGISTER_D1_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_QWC", 0x10009020, EE->DMAC->DMAC_REGISTER_D1_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_TADR", 0x10009030, EE->DMAC->DMAC_REGISTER_D1_TADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_ASR0", 0x10009040, EE->DMAC->DMAC_REGISTER_D1_ASR0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D1_ASR1", 0x10009050, EE->DMAC->DMAC_REGISTER_D1_ASR1));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_9060);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_CHCR", 0x1000a000, EE->DMAC->DMAC_REGISTER_D2_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_MADR", 0x1000a010, EE->DMAC->DMAC_REGISTER_D2_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_QWC", 0x1000a020, EE->DMAC->DMAC_REGISTER_D2_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_TADR", 0x1000a030, EE->DMAC->DMAC_REGISTER_D2_TADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_ASR0", 0x1000a040, EE->DMAC->DMAC_REGISTER_D2_ASR0));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D2_ASR1", 0x1000a050, EE->DMAC->DMAC_REGISTER_D2_ASR1));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_a060);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D3_CHCR", 0x1000b000, EE->DMAC->DMAC_REGISTER_D3_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D3_MADR", 0x1000b010, EE->DMAC->DMAC_REGISTER_D3_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D3_QWC", 0x1000b020, EE->DMAC->DMAC_REGISTER_D3_QWC));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_b030);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D4_CHCR", 0x1000b400, EE->DMAC->DMAC_REGISTER_D4_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D4_MADR", 0x1000b410, EE->DMAC->DMAC_REGISTER_D4_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D4_QWC", 0x1000b420, EE->DMAC->DMAC_REGISTER_D4_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D4_TADR", 0x1000b430, EE->DMAC->DMAC_REGISTER_D4_TADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_b440);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D5_CHCR", 0x1000c000, EE->DMAC->DMAC_REGISTER_D5_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D5_MADR", 0x1000c010, EE->DMAC->DMAC_REGISTER_D5_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D5_QWC", 0x1000c020, EE->DMAC->DMAC_REGISTER_D5_QWC));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_c030);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D6_CHCR", 0x1000c400, EE->DMAC->DMAC_REGISTER_D6_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D6_MADR", 0x1000c410, EE->DMAC->DMAC_REGISTER_D6_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D6_QWC", 0x1000c420, EE->DMAC->DMAC_REGISTER_D6_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D6_TADR", 0x1000c430, EE->DMAC->DMAC_REGISTER_D6_TADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_c440);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D7_CHCR", 0x1000c800, EE->DMAC->DMAC_REGISTER_D7_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D7_MADR", 0x1000c810, EE->DMAC->DMAC_REGISTER_D7_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D7_QWC", 0x1000c820, EE->DMAC->DMAC_REGISTER_D7_QWC));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_c830);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D8_CHCR", 0x1000d000, EE->DMAC->DMAC_REGISTER_D8_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D8_MADR", 0x1000d010, EE->DMAC->DMAC_REGISTER_D8_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D8_QWC", 0x1000d020, EE->DMAC->DMAC_REGISTER_D8_QWC));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_d030);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D8_SADR", 0x1000d080, EE->DMAC->DMAC_REGISTER_D8_SADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_d090);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D9_CHCR", 0x1000d400, EE->DMAC->DMAC_REGISTER_D9_CHCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D9_MADR", 0x1000d410, EE->DMAC->DMAC_REGISTER_D9_MADR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D9_QWC", 0x1000d420, EE->DMAC->DMAC_REGISTER_D9_QWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D9_TADR", 0x1000d430, EE->DMAC->DMAC_REGISTER_D9_TADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_d440);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D9_SADR", 0x1000d480, EE->DMAC->DMAC_REGISTER_D9_SADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_d490);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_CTRL", 0x1000e000, EE->DMAC->DMAC_REGISTER_D_CTRL));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_STAT", 0x1000e010, EE->DMAC->DMAC_REGISTER_D_STAT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_PCR", 0x1000e020, EE->DMAC->DMAC_REGISTER_D_PCR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_SQWC", 0x1000e030, EE->DMAC->DMAC_REGISTER_D_SQWC));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_RBSR", 0x1000e040, EE->DMAC->DMAC_REGISTER_D_RBSR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_RBOR", 0x1000e050, EE->DMAC->DMAC_REGISTER_D_RBOR));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_STADR", 0x1000e060, EE->DMAC->DMAC_REGISTER_D_STADR));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_e070);

		// INTC registers.
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("INTC: I_STAT", 0x1000f000, EE->INTC->INTC_REGISTER_I_STAT));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("INTC: I_MASK", 0x1000f010, EE->INTC->INTC_REGISTER_I_MASK));
		EE->PhysicalMMU->mapMemory(EE->INTC->INTC_MEMORY_f020);

		// MISC registers.
		EE->PhysicalMMU->mapMemory(EE->EE_MEMORY_SIO);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("SIF: SB_SMFLG", 0x1000f230, EE->EE_REGISTER_SB_SMFLG));
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("Undocumented: F400", 0x1000f400, EE->EE_REGISTER_F400));
		EE->PhysicalMMU->mapMemory(EE->EE_MEMORY_F410);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("Undocumented: F420", 0x1000f420, EE->EE_REGISTER_F420));
		EE->PhysicalMMU->mapMemory(EE->EE_MEMORY_MCH);
		EE->PhysicalMMU->mapMemory(EE->EE_MEMORY_F450);

		// DMAC registers (extended).
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_F500);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_ENABLER", 0x1000f520, EE->DMAC->DMAC_REGISTER_D_ENABLER));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_F530);
		EE->PhysicalMMU->mapMemory(std::make_shared<MappedRegister32_t>("DMAC: D_ENABLEW", 0x1000f590, EE->DMAC->DMAC_REGISTER_D_ENABLEW));
		EE->PhysicalMMU->mapMemory(EE->DMAC->DMAC_MEMORY_F5A0);
	}

	// VU0/1 Memory
	{
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU0_MEMORY_Micro0);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x11000000", 0x11001000, 0x1000, 0x3000, 0x11000000, EE->PhysicalMMU)); // Image of 0x11000000.
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU0_MEMORY_Mem0);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x11004000", 0x11005000, 0x1000, 0x3000, 0x11004000, EE->PhysicalMMU)); // Image of 0x11004000.
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEMORY_Micro1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEMORY_Mem1);
		EE->PhysicalMMU->mapMemory(EE->VPU->VU->VU1_MEMORY_BusErr);
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
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000400, 0x400, 0x400, 0x12000000, EE->PhysicalMMU)); // Image of 0x12000000.
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x12000000", 0x12000800, 0x800, 0x800, 0x12000000, EE->PhysicalMMU)); // Image of 0x12000000.
		

		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_CSR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_IMR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1020);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_BUSDIR);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1050);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SIGLBLID);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1090);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_1100);
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001400, 0x400, 0x400, 0x12001000, EE->PhysicalMMU)); // Image of 0x12001000.
		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x12001000", 0x12001800, 0x800, 0x800, 0x12001000, EE->PhysicalMMU)); // Image of 0x12001000.

		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPE_2000);
		EE->PhysicalMMU->mapMemory(EE->getRootResources()->GS->GS_P_REGISTER_SPEBusErr);
	}

	// IOP Mirrors
	{
		EE->PhysicalMMU->mapMemory(IOP->IOP_HW_REGISTERS);

		EE->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x00000000", 0x1C000000, PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, PS2Constants::IOP::IOPMemory::SIZE_IOP_MEMORY, 0x00000000, IOP->PhysicalMMU)); // Image of IOP 0x00000000.
		
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
		IOP->PhysicalMMU->mapMemory(std::make_shared<ImageMappedMemory_t>("Image: 0x1FC00000", 0xFFC00000, PS2Constants::EE::BootROM::SIZE_BOOT_ROM, PS2Constants::EE::BootROM::SIZE_BOOT_ROM, PS2Constants::EE::BootROM::PADDRESS_BOOT_ROM, IOP->PhysicalMMU)); // Image of 0x1FC00000.
	}
}
