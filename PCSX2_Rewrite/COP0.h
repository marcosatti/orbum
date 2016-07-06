#pragma once

#include "Globals.h"
#include "PS2Types.h"

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
			*/
			struct {
				Register32 Index, // r0:  Index that specifies TLB entry for reading for writing.
					Random,       // r1:  Pseudo-random index for TLB replacement.
					EntryLo0,     // r2:  Low half of TLB entry (for even PFN).
					EntryLo1,     // r3:  Low half of TLB entry (for odd PFN).
					Context,      // r4:  Pointer to PTE table.
					PageMask,     // r5:  Most significant part of the TLB entry (page size mark).
					Wired,        // r6:  Number of wired TLB entries.
					reserved0,    // r7:  Reserved.
					BadVAddr,     // r8:  Bad virtual address value (for exceptions).
					Count,        // r9:  Timer Compare.
					EntryHi,      // r10: High half (Virtual page number and ASID) of TLB entry.
					Compare,      // r11: Timer reference value.
					Status,       // r12: Processor Status Register.
					Cause,        // r13: Result of last exception taken.
					EPC,          // r14: Exception Program Counter.
					PRId,         // r15: Processor Revision Identifier.
					Config,       // r16: Configuration Register.
					reserved1,    // r17: Reserved.
					reserved2,    // r18: Reserved.
					reserved3,    // r19: Reserved.
					reserved4,    // r20: Reserved.
					reserved5,    // r21: Reserved.
					reserved6,    // r22: Reserved.
					BadPAddr,     // r23: Bad Physical Address value (for exceptions).
					Debug,        // r24: Registers related to debug function.
					unused0,      // r25: **SPECIAL**: Unused. This is normally the Perf register, however PCSX2 deviates from this due to it not being constrained by hardware. 
								  //                   Instead r32, r33, r34 are used as the PCCR, PCR0 and PCR1 respectively. See EE Core Users Manual, pg 143-145 for descriptions on how it is normally accessed.
					reserved7,    // r26: Reserved.
					reserved8,    // r27: Reserved.
					TagLo,        // r28: Low bits of the Cache Tag.
					TagHi,        // r29: High bits of the Cache Tag.
					ErrorEPC,     // r30: Error Exception Program Counter.
					reserved9,    // r31: Reserved.
					PCCR,         // r32: Performance counter control register. See note from r25.
					PCR0,         // r33: Counter register PCR0. See note from r25.
					PCR1;         // r34: Counter register PCR1. See note from r25.
			} Registers;

		};

	} // namespace EE
} // namespace PS2