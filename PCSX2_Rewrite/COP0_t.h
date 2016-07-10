#pragma once

#include "Globals.h"
#include "COP0_Registers_t.h"

namespace PS2 {
	namespace EE {

		class COP0_t {
		public:
			/*
			COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor).
			See EE Core Users Manual.
			*/

			// Register implementations.
			/*
			The registers listed below are used by COP0 for various functions relating to (mostly) memory management and exception handling.
			Comments are provided for each register. See EE Core Users Manual, pg 62 for more information.
			The registers can only be accessed by name, due to the changed order (see note below on why).

			Note: Registers r24 and r25 have been split up into 7 and 3 registers respectively as per the docs, as it is not feasible to implement them as sub-registers.
			      The new registers have been assigned register numbers from 32 -> 39 (for reference).
			*/
			struct {
				// General registers.
				RegisterIndex_t Index;        	// r0:  Index that specifies TLB entry for reading for writing.
				RegisterRandom_t Random;       	// r1:  Pseudo-random index for TLB replacement.
				RegisterEntryLo0_t EntryLo0;    // r2:  Low half of TLB entry (for even PFN).
				RegisterEntryLo1_t EntryLo1;    // r3:  Low half of TLB entry (for odd PFN).
				RegisterContext_t Context;      // r4:  Pointer to PTE table.
				RegisterPageMask_t PageMask;    // r5:  Most significant part of the TLB entry (page size mark).
				RegisterWired_t Wired;        	// r6:  Number of wired TLB entries.
				RegisterReserved_t reserved0;  	// r7:  Reserved.
				RegisterBadVAddr_t BadVAddr;    // r8:  Bad virtual address value (for exceptions).
				RegisterCount_t Count;        	// r9:  Timer Compare.
				RegisterEntryHi_t EntryHi;      // r10: High half (Virtual page number and ASID) of TLB entry.
				RegisterCompare_t Compare;      // r11: Timer reference value.
				RegisterStatus_t Status;        // r12: Processor Status Register.
				RegisterCause_t Cause;          // r13: Result of last exception taken.
				RegisterEPC_t EPC;          	// r14: Exception Program Counter.
				RegisterPRId_t PRId;         	// r15: Processor Revision Identifier.
				RegisterConfig_t Config;       	// r16: Configuration Register.
				RegisterReserved_t reserved1; 	// r17: Reserved.
				RegisterReserved_t reserved2;  	// r18: Reserved.
				RegisterReserved_t reserved3; 	// r19: Reserved.
				RegisterReserved_t reserved4;  	// r20: Reserved.
				RegisterReserved_t reserved5; 	// r21: Reserved.
				RegisterReserved_t reserved6;  	// r22: Reserved.
				RegisterBadPAddr_t BadPAddr;   	// r23: Bad Physical Address value (for exceptions).
												// r24: See below for r24.
												// r25: See below for r25.
				RegisterReserved_t reserved7;  	// r26: Reserved.
				RegisterReserved_t reserved8;  	// r27: Reserved.
				RegisterTagLo_t TagLo;          // r28: Low bits of the Cache Tag.
				RegisterTagHi_t TagHi;        	// r29: High bits of the Cache Tag.
				RegisterErrorEPC_t ErrorEPC;    // r30: Error Exception Program Counter.
				RegisterReserved_t reserved9;  	// r31: Reserved.

				// Debug registers.
				RegisterBPC_t BPC;        		// r24: Registers related to debug function.
				RegisterIAB_t IAB;				// r32: Instruction address breakpoint settings.
				RegisterIABM_t IABM;			// r33: Instruction address breakpoint settings.
				RegisterDAB_t DAB;				// r34: Data address breakpoint settings.
				RegisterDABM_t DABM;			// r35: Data address breakpoint settings.
				RegisterDVB_t DVB;				// r36: Data value breakpoint settings.
				RegisterDVBM_t DVBM;			// r37: Data value breakpoint settings.

				// Performance registers.
				RegisterPCCR_t PCCR;         	// r25: Performance counter and control register.
				RegisterPCR0_t PCR0;         	// r38: Performance counter.
				RegisterPCR1_t PCR1;         	// r39: Performance counter.
			} Registers;

		};

	} // namespace EE
} // namespace PS2