#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Constants/PS2Constants.h"

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual.
*/

class BitfieldRegister32_t;
class RegisterReserved_t;
class RegisterIndex_t;
class RegisterRandom_t;
class RegisterEntryLo0_t;
class RegisterEntryLo1_t;
class RegisterContext_t;
class RegisterPageMask_t;
class RegisterWired_t;
class RegisterBadVAddr_t;
class RegisterCount_t;
class RegisterEntryHi_t;
class RegisterCompare_t;
class RegisterStatus_t;
class RegisterCause_t;
class RegisterEPC_t;
class RegisterPRId_t;
class RegisterConfig_t;
class RegisterBadPAddr_t;
class RegisterTagLo_t;
class RegisterTagHi_t;
class RegisterErrorEPC_t;
class RegisterBPC_t;
class RegisterIAB_t;
class RegisterIABM_t;
class RegisterDAB_t;
class RegisterDABM_t;
class RegisterDVB_t;
class RegisterDVBM_t;
class RegisterPCCR_t;
class RegisterPCR0_t;
class RegisterPCR1_t;

class COP0_t : public PS2ResourcesSubobject
{
public:
	explicit COP0_t(const PS2Resources_t* const PS2Resources);

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
	std::shared_ptr<RegisterIndex_t>	Index;	   // r0:  Index that specifies TLB entry for reading for writing.
	std::shared_ptr<RegisterRandom_t>	Random;	   // r1:  Pseudo-random index for TLB replacement.
	std::shared_ptr<RegisterEntryLo0_t> EntryLo0;  // r2:  Low half of TLB entry (for even PFN).
	std::shared_ptr<RegisterEntryLo1_t> EntryLo1;  // r3:  Low half of TLB entry (for odd PFN).
	std::shared_ptr<RegisterContext_t>	Context;   // r4:  Pointer to PTE table.
	std::shared_ptr<RegisterPageMask_t> PageMask;  // r5:  Most significant part of the TLB entry (page size mark).
	std::shared_ptr<RegisterWired_t>	Wired;     // r6:  Number of wired TLB entries.
	std::shared_ptr<RegisterReserved_t> reserved0; // r7:  Reserved.
	std::shared_ptr<RegisterBadVAddr_t> BadVAddr;  // r8:  Bad virtual address value (for exceptions).
	std::shared_ptr<RegisterCount_t>	Count;     // r9:  Timer Compare.
	std::shared_ptr<RegisterEntryHi_t>	EntryHi;   // r10: High half (Virtual page number and ASID) of TLB entry.
	std::shared_ptr<RegisterCompare_t>	Compare;   // r11: Timer reference value.
	std::shared_ptr<RegisterStatus_t>	Status;    // r12: Processor Status Register.
	std::shared_ptr<RegisterCause_t>	Cause;	   // r13: Result of last exception taken.
	std::shared_ptr<RegisterEPC_t>		EPC;       // r14: Exception Program Counter.
	std::shared_ptr<RegisterPRId_t>		PRId;      // r15: Processor Revision Identifier.
	std::shared_ptr<RegisterConfig_t>	Config;    // r16: Configuration Register.
	std::shared_ptr<RegisterReserved_t> reserved1; // r17: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved2; // r18: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved3; // r19: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved4; // r20: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved5; // r21: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved6; // r22: Reserved.
	std::shared_ptr<RegisterBadPAddr_t> BadPAddr;  // r23: Bad Physical Address value (for exceptions).
												   // r24: See below for r24.
												   // r25: See below for r25.
	std::shared_ptr<RegisterReserved_t> reserved7; // r26: Reserved.
	std::shared_ptr<RegisterReserved_t> reserved8; // r27: Reserved.
	std::shared_ptr<RegisterTagLo_t>	TagLo;     // r28: Low bits of the Cache Tag.
	std::shared_ptr<RegisterTagHi_t>	TagHi;     // r29: High bits of the Cache Tag.
	std::shared_ptr<RegisterErrorEPC_t> ErrorEPC;  // r30: Error Exception Program Counter.
	std::shared_ptr<RegisterReserved_t> reserved9; // r31: Reserved.

	// Debug registers.
	std::shared_ptr<RegisterBPC_t>		BPC;       // r24: Registers related to debug function.
	std::shared_ptr<RegisterIAB_t>		IAB;       // r32: Instruction address breakpoint settings.
	std::shared_ptr<RegisterIABM_t>		IABM;      // r33: Instruction address breakpoint settings.
	std::shared_ptr<RegisterDAB_t>		DAB;	   // r34: Data address breakpoint settings.
	std::shared_ptr<RegisterDABM_t>		DABM;	   // r35: Data address breakpoint settings.
	std::shared_ptr<RegisterDVB_t>		DVB;	   // r36: Data value breakpoint settings.
	std::shared_ptr<RegisterDVBM_t>		DVBM;	   // r37: Data value breakpoint settings.

	// Performance registers.
	std::shared_ptr<RegisterPCCR_t>		PCCR;	   // r25: Performance counter and control register.
	std::shared_ptr<RegisterPCR0_t>		PCR0;      // r38: Performance counter.
	std::shared_ptr<RegisterPCR1_t>		PCR1;      // r39: Performance counter.

	// Array of above registers (needed by some EECore instructions to access by index). Generally you will never access registers through this, only the PS2 OS will.
	std::shared_ptr<BitfieldRegister32_t> Registers[PS2Constants::EE::EECore::COP0::NUMBER_REGISTERS];

	// Array of PCR0/PCR1, used by the MFPC/MTPC instructions.
	std::shared_ptr<BitfieldRegister32_t> PCRRegisters[PS2Constants::EE::EECore::COP0::NUMBER_PCR_REGISTERS];

	/*
	Operating mode functionality (User, Supervisor or Kernel). See EE Core Users Manual page 74 (truth table at bottom). Thanks to gregory38 @ PCSX2 for helping me!
	*/
	bool isOperatingUserMode() const;
	bool isOperatingSupervisorMode() const;
	bool isOperatingKernelMode() const;

	/*
	Checks if the COP0 coprocessor is usable. Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCOP0Usable() const;
};
