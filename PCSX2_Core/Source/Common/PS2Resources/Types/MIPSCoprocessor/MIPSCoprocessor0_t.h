#pragma once

#include <memory>
#include "Common/PS2Resources/Types/MIPSCoprocessor/MIPSCoprocessor_t.h"

/*
Represents a MIPS co-processor 0 base class (aka COP0).
COP0 is used widely in MIPS systems, as the system control registers.

The MFC0, MTC0 MIPS instructions move data to and from these registers, by specifying an array index from 0 -> 31.
This class defines some common COP0 registers, but it is up to the user to define the array contents.
*/

class BitfieldRegister32_t;
class COP0RegisterReserved_t;
class COP0RegisterIndex_t;
class COP0RegisterRandom_t;
class COP0RegisterEntryLo0_t;
class COP0RegisterEntryLo1_t;
class COP0RegisterContext_t;
class COP0RegisterPageMask_t;
class COP0RegisterWired_t;
class COP0RegisterBadVAddr_t;
class COP0RegisterCount_t;
class COP0RegisterEntryHi_t;
class COP0RegisterCompare_t;
class COP0RegisterStatus_t;
class COP0RegisterCause_t;
class COP0RegisterEPC_t;
class COP0RegisterPRId_EECore_t;
class COP0RegisterConfig_t;
class COP0RegisterTagLo_t;
class COP0RegisterTagHi_t;
class COP0RegisterErrorEPC_t;

class MIPSCoprocessor0_t : public MIPSCoprocessor_t
{
public:
	MIPSCoprocessor0_t();
	virtual ~MIPSCoprocessor0_t();

	/*
	Below functions can be used to check the operating context - Kernel mode, Supervisor mode, or User mode.
	These use the Status register below to determine the context.
	*/
	virtual	bool isOperatingUserMode() const;
	virtual bool isOperatingSupervisorMode() const;
	virtual bool isOperatingKernelMode() const;

	/*
	Common register implementations (for PS2 emulator purposes).
	The registers listed below are used by COP0 for various functions relating to system management
	Comments are provided for each register. See EE Core Users Manual, pg 62 for more information, and other MIPS manuals.

	All bitfield registers are subclassed off the BitfieldRegister32_t class.
	*/
	std::shared_ptr<COP0RegisterIndex_t>	Index;	   // Index that specifies TLB entry for reading for writing.
	std::shared_ptr<COP0RegisterRandom_t>	Random;	   // Pseudo-random index for TLB replacement.
	std::shared_ptr<COP0RegisterEntryLo0_t> EntryLo0;  // Low half of TLB entry (for even PFN).
	std::shared_ptr<COP0RegisterEntryLo1_t> EntryLo1;  // Low half of TLB entry (for odd PFN).
	std::shared_ptr<COP0RegisterContext_t>	Context;   // Pointer to PTE table.
	std::shared_ptr<COP0RegisterPageMask_t> PageMask;  // Most significant part of the TLB entry (page size mark).
	std::shared_ptr<COP0RegisterWired_t>	Wired;     // Number of wired TLB entries.
	std::shared_ptr<COP0RegisterBadVAddr_t> BadVAddr;  // Bad virtual address value (for exceptions).
	std::shared_ptr<COP0RegisterCount_t>	Count;     // Timer Compare.
	std::shared_ptr<COP0RegisterEntryHi_t>	EntryHi;   // High half (Virtual page number and ASID) of TLB entry.
	std::shared_ptr<COP0RegisterCause_t>	Cause;	   // Result of last exception taken. [Listed before Cause due to dependency.]
	std::shared_ptr<COP0RegisterCompare_t>	Compare;   // Timer reference value.
	std::shared_ptr<COP0RegisterStatus_t>	Status;    // Processor Status Register.
	std::shared_ptr<COP0RegisterEPC_t>		EPC;       // Exception Program Counter.
	std::shared_ptr<COP0RegisterConfig_t>	Config;    // Configuration Register.
	std::shared_ptr<COP0RegisterTagLo_t>	TagLo;     // Low bits of the Cache Tag.
	std::shared_ptr<COP0RegisterTagHi_t>	TagHi;     // High bits of the Cache Tag.
	std::shared_ptr<COP0RegisterErrorEPC_t> ErrorEPC;  // Error Exception Program Counter.
};

