#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish writing documentation.
EE_t delares the EE structure of the PS2.
It encompasses everything seen on the diagram on page 22 of the EE Overview Manual, and the items within the EE Users Manual.
*/

class EECore_t;
class Timers_t;
class EERegisterSIO_t;
class EERegisterMCH_t;
class StorageObject_t;
class StorageObject32_t;
class DeadStorageObject_t;
class XORStorageObject32_t;
class BusErrorStorageObject_t;
class EERegisterTimerMode_t;
class EERegisterTimerCount_t;
class EERegisterINTCIStat_t;

class EE_t : public PS2ResourcesSubobject
{
public:
	explicit EE_t(const PS2Resources_t *const PS2Resources);

	/*
	The EE Core structure.
	*/
	std::shared_ptr<EECore_t> EECore;

	/*
	The Timers resources (TIMER0, TIMER1, etc).
	*/
	std::shared_ptr<Timers_t> Timers;

	/*
	EE registers, defined on page 21 onwards of the EE Users Manual. All are prefixed with EE_REGISTER, and start from PS2 physical address 0x10000000 to 0x11000000.
	If special functionality is needed, they are subclassed off StorageObject_t (or similar) and defined in Types/EERegisters_t.
	They are ordered by ascending, meaning the lowest physical address, to the highest.

	Also see the intitaliser list of EE_t(.cpp), where you can see the object parameter definitions.
	*/
	// 0x10000000 (Timers)
	std::shared_ptr<EERegisterTimerCount_t>  EE_REGISTER_T0_COUNT;
	std::shared_ptr<EERegisterTimerMode_t>   EE_REGISTER_T0_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T0_COMP;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T0_HOLD;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_TIMER_0040;
	std::shared_ptr<EERegisterTimerCount_t>  EE_REGISTER_T1_COUNT;
	std::shared_ptr<EERegisterTimerMode_t>   EE_REGISTER_T1_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T1_COMP;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T1_HOLD;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_TIMER_0840;
	std::shared_ptr<EERegisterTimerCount_t>  EE_REGISTER_T2_COUNT;
	std::shared_ptr<EERegisterTimerMode_t>   EE_REGISTER_T2_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T2_COMP;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_TIMER_1030;
	std::shared_ptr<EERegisterTimerCount_t>  EE_REGISTER_T3_COUNT;
	std::shared_ptr<EERegisterTimerMode_t>   EE_REGISTER_T3_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_T3_COMP;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_TIMER_1830;
	// Array of timer objects, needed to perform iterations.
	struct TimerRegisters_t
	{
		std::shared_ptr<EERegisterTimerCount_t> mCount;
		std::shared_ptr<EERegisterTimerMode_t>  mMode;
		std::shared_ptr<StorageObject32_t>      mCompare;
		std::shared_ptr<StorageObject32_t>      mHold;
	} TimerRegisters[4];

	// 0x10002000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_IPU_CMD;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_IPU_CTRL;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_IPU_BP;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_IPU_TOP;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_IPU_2040;

	// 0x10003000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_CTRL;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_STAT;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_GIF_3030;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_TAG0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_TAG1;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_TAG2;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_TAG3;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_CNT;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_P3CNT;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_GIF_P3TAG;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_GIF_30b0;

	// 0x10003800
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_STAT;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_FBRST;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_ERR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_MARK;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_CYCLE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_NUM;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_MASK;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_CODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_ITOPS;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_38a0;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_38b0;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_38c0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_ITOP;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_38e0;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_38f0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_R0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_R1;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_R2;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_R3;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_C0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_C1;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_C2;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF0_C3;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF0_3980;

	// 0x10003E00
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_STAT;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_FBRST;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_ERR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_MARK;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_CYCLE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_MODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_NUM;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_MASK;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_CODE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_ITOPS;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_BASE;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_OFST;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_TOPS;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_ITOP;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_TOP;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF1_3cf0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_R0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_R1;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_R2;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_R3;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_C0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_C1;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_C2;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_VIF1_C3;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_VIF1_3d80;

	// 0x10004000
	std::shared_ptr<StorageObject_t>         EE_REGISTER_VIF0_FIFO;
	std::shared_ptr<StorageObject_t>         EE_REGISTER_VIF1_FIFO;
	std::shared_ptr<StorageObject_t>         EE_REGISTER_GIF_FIFO;
	std::shared_ptr<StorageObject_t>         EE_REGISTER_IPU_out_FIFO;
	std::shared_ptr<StorageObject_t>         EE_REGISTER_IPU_in_FIFO;

	// 0x10008000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_TADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_ASR0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D0_ASR1;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_8060;

	// 0x10009000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_TADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_ASR0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D1_ASR1;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_9060;

	// 0x1000A000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_TADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_ASR0;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D2_ASR1;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_a060;
	
	// 0x1000B000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D3_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D3_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D3_QWC;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_b030;
	
	// 0x1000B400
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D4_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D4_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D4_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D4_TADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_b440;

	// 0x1000C000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D5_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D5_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D5_QWC;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_c030;

	// 0x1000C400
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D6_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D6_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D6_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D6_TADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_c440;
	
	// 0x1000C800
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D7_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D7_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D7_QWC;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_c830;

	// 0x1000D000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D8_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D8_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D8_QWC;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_d030;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D8_SADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_d090;

	// 0x1000D400
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D9_CHCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D9_MADR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D9_QWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D9_TADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_d440;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D9_SADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_d490;

	// 0x1000E000
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_CTRL;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_STAT;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_PCR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_SQWC;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_RBSR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_RBOR;
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_STADR;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_DMAC_e070;

	// 0x1000F000
	std::shared_ptr<EERegisterINTCIStat_t>   EE_REGISTER_I_STAT;
	std::shared_ptr<XORStorageObject32_t>    EE_REGISTER_I_MASK;
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_INTC_f020;

	// 0x1000F100
	std::shared_ptr<EERegisterSIO_t>		 EE_REGISTER_SIO;       // Register "SIO"					@ 0x1000F100 -> 0x1000F200. Some information can be found in the Toshiba Tx79 architecture manual (similar to the EE).
	
	// 0x1000F200
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_SB_SMFLG;

	// 0x1000F400
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_F400;      // Register "Undocumented: F400"    @ 0x1000F400 -> 0x1000F410.
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_F410;      // Register "Undocumented: F410"    @ 0x1000F410 -> 0x1000F420. Needs to be a dead storage (by BIOS).
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_F420;      // Register "Undocumented: F420"    @ 0x1000F420 -> 0x1000F430.
	std::shared_ptr<EERegisterMCH_t>		 EE_REGISTER_MCH;		// Register "MCH"                   @ 0x1000F430 -> 0x1000F450. No documentation (except for name)! From old PCSX2. Needed by the BIOS for RDRAM initalisation?
	std::shared_ptr<StorageObject_t>         EE_REGISTER_F450;      // Register "Undocumented: F450"    @ 0x1000F450 -> 0x1000F500.

	// 0x1000F500
	std::shared_ptr<StorageObject_t>         EE_REGISTER_F500;      // Register "Undocumented: F500"    @ 0x1000F500 -> 0x1000F520.
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_ENABLER; 
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_F530;      
	std::shared_ptr<StorageObject32_t>       EE_REGISTER_D_ENABLEW; 
	std::shared_ptr<DeadStorageObject_t>     EE_REGISTER_F5A0;      

	/*
	VU memory, defined on page 25 of the EE Users Manual. All are prefixed with VU_MEM, and start at PS2 physical address 0x11000000 to 0x12000000.
	If special functionality is needed, they are subclassed off StorageObject_t (or similar) and defined in Types/EERegisters_t.
	They are ordered by ascending, meaning the lowest physical address, to the highest.

	Also see the intitaliser list of EE_t(.cpp), where you can see the object parameter definitions.
	*/
	// 0x110000000
	std::shared_ptr<StorageObject_t>         VU_MEM_VU0Micro0;
	std::shared_ptr<StorageObject_t>         VU_MEM_VU0Mem0;

	// 0x11008000
	std::shared_ptr<StorageObject_t>         VU_MEM_VU1Micro1;
	std::shared_ptr<StorageObject_t>         VU_MEM_VU1Mem1;
	std::shared_ptr<BusErrorStorageObject_t> VU_MEM_VU1BusErr;
};