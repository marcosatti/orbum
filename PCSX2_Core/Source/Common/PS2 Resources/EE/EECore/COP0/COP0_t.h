#pragma once

#include "Common/PS2 Resources/EE/EECore/COP0/Bitfield Registers/COP0_BitfieldRegisters_t.h"


class COP0_t {
public:
	/*
	COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor).
	See EE Core Users Manual.
	*/

	// Bitfield Register implementations.
	/*
	The registers listed below are used by COP0 for various functions relating to (mostly) memory management and exception handling.
	Comments are provided for each register. See EE Core Users Manual, pg 62 for more information.
	The registers can only be accessed by name, due to the changed order (see note below on why).

	Note: Registers r24 and r25 have been split up into 7 and 3 registers respectively as per the docs, as it is not feasible to implement them as sub-registers.
		  The new registers have been assigned register numbers from 32 -> 39 (for PCSX2 reference).

	All bitfield registers are subclassed off the BitfieldRegister32_t class.
	*/

	// General registers.
	std::shared_ptr<RegisterIndex_t>	Index		= std::make_shared<RegisterIndex_t>();		// r0:  Index that specifies TLB entry for reading for writing.
	std::shared_ptr<RegisterRandom_t>	Random		= std::make_shared<RegisterRandom_t>();     // r1:  Pseudo-random index for TLB replacement.
	std::shared_ptr<RegisterEntryLo0_t> EntryLo0	= std::make_shared<RegisterEntryLo0_t>();   // r2:  Low half of TLB entry (for even PFN).
	std::shared_ptr<RegisterEntryLo1_t> EntryLo1	= std::make_shared<RegisterEntryLo1_t>();   // r3:  Low half of TLB entry (for odd PFN).
	std::shared_ptr<RegisterContext_t>	Context		= std::make_shared<RegisterContext_t>();    // r4:  Pointer to PTE table.
	std::shared_ptr<RegisterPageMask_t> PageMask	= std::make_shared<RegisterPageMask_t>();   // r5:  Most significant part of the TLB entry (page size mark).
	std::shared_ptr<RegisterWired_t>	Wired		= std::make_shared<RegisterWired_t>();      // r6:  Number of wired TLB entries.
	std::shared_ptr<RegisterReserved_t> reserved0	= std::make_shared<RegisterReserved_t>();  	// r7:  Reserved.
	std::shared_ptr<RegisterBadVAddr_t> BadVAddr	= std::make_shared<RegisterBadVAddr_t>();   // r8:  Bad virtual address value (for exceptions).
	std::shared_ptr<RegisterCount_t>	Count		= std::make_shared<RegisterCount_t>();      // r9:  Timer Compare.
	std::shared_ptr<RegisterEntryHi_t>	EntryHi		= std::make_shared<RegisterEntryHi_t>();    // r10: High half (Virtual page number and ASID) of TLB entry.
	std::shared_ptr<RegisterCompare_t>	Compare		= std::make_shared<RegisterCompare_t>();    // r11: Timer reference value.
	std::shared_ptr<RegisterStatus_t>	Status		= std::make_shared<RegisterStatus_t>();     // r12: Processor Status Register.
	std::shared_ptr<RegisterCause_t>	Cause		= std::make_shared<RegisterCause_t>();      // r13: Result of last exception taken.
	std::shared_ptr<RegisterEPC_t>		EPC			= std::make_shared<RegisterEPC_t>();        // r14: Exception Program Counter.
	std::shared_ptr<RegisterPRId_t>		PRId		= std::make_shared<RegisterPRId_t>();       // r15: Processor Revision Identifier.
	std::shared_ptr<RegisterConfig_t>	Config		= std::make_shared<RegisterConfig_t>();     // r16: Configuration Register.
	std::shared_ptr<RegisterReserved_t> reserved1	= std::make_shared<RegisterReserved_t>(); 	// r17: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved2	= std::make_shared<RegisterReserved_t>();  	// r18: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved3	= std::make_shared<RegisterReserved_t>(); 	// r19: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved4	= std::make_shared<RegisterReserved_t>();  	// r20: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved5	= std::make_shared<RegisterReserved_t>(); 	// r21: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved6	= std::make_shared<RegisterReserved_t>();  	// r22: Reserved.
	std::shared_ptr<RegisterBadPAddr_t> BadPAddr	= std::make_shared<RegisterBadPAddr_t>();   // r23: Bad Physical Address value (for exceptions).
																								// r24: See below for r24.
																								// r25: See below for r25.
	std::shared_ptr<RegisterReserved_t> reserved7	= std::make_shared<RegisterReserved_t>();  	// r26: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved8	= std::make_shared<RegisterReserved_t>();  	// r27: Reserved.
	std::shared_ptr<RegisterTagLo_t>	TagLo		= std::make_shared<RegisterTagLo_t>();      // r28: Low bits of the Cache Tag.
	std::shared_ptr<RegisterTagHi_t>	TagHi		= std::make_shared<RegisterTagHi_t>();    	// r29: High bits of the Cache Tag.
	std::shared_ptr<RegisterErrorEPC_t> ErrorEPC	= std::make_shared<RegisterErrorEPC_t>();   // r30: Error Exception Program Counter.
	std::shared_ptr<RegisterReserved_t> reserved9	= std::make_shared<RegisterReserved_t>();  	// r31: Reserved.

	// Debug registers.
	std::shared_ptr<RegisterBPC_t>		BPC			= std::make_shared<RegisterBPC_t>();        // r24: Registers related to debug function.
	std::shared_ptr<RegisterIAB_t>		IAB			= std::make_shared<RegisterIAB_t>();		// r32: Instruction address breakpoint settings.
	std::shared_ptr<RegisterIABM_t>		IABM		= std::make_shared<RegisterIABM_t>();		// r33: Instruction address breakpoint settings.
	std::shared_ptr<RegisterDAB_t>		DAB			= std::make_shared<RegisterDAB_t>();		// r34: Data address breakpoint settings.
	std::shared_ptr<RegisterDABM_t>		DABM		= std::make_shared<RegisterDABM_t>();		// r35: Data address breakpoint settings.
	std::shared_ptr<RegisterDVB_t>		DVB			= std::make_shared<RegisterDVB_t>();		// r36: Data value breakpoint settings.
	std::shared_ptr<RegisterDVBM_t>		DVBM		= std::make_shared<RegisterDVBM_t>();		// r37: Data value breakpoint settings.

	// Performance registers.
	std::shared_ptr<RegisterPCCR_t>		PCCR		= std::make_shared<RegisterPCCR_t>();       // r25: Performance counter and control register.
	std::shared_ptr<RegisterPCR0_t>		PCR0		= std::make_shared<RegisterPCR0_t>();       // r38: Performance counter.
	std::shared_ptr<RegisterPCR1_t>		PCR1		= std::make_shared<RegisterPCR1_t>();       // r39: Performance counter.

};
