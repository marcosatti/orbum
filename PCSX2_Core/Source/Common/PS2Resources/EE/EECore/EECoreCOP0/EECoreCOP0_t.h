#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/MIPSCoprocessor0_t.h"

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual page 62 onwards.
*/

class COP0RegisterPRId_EECore_t;
class COP0RegisterBadPAddr_t;
class COP0RegisterBPC_t;
class COP0RegisterIAB_t;
class COP0RegisterIABM_t;
class COP0RegisterDAB_t;
class COP0RegisterDABM_t;
class COP0RegisterDVB_t;
class COP0RegisterDVBM_t;
class COP0RegisterPCCR_t;
class COP0RegisterPCR0_t;
class COP0RegisterPCR1_t;

class EECoreCOP0_t : public MIPSCoprocessor0_t, public PS2ResourcesSubobject
{
public:
	explicit EECoreCOP0_t(const PS2Resources_t* const PS2Resources);

	/*
	Checks if the EECore COP0 coprocessor is usable. 
	Can be used by the component calling this to raise a EECoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable() const override;

	/*
	Initalises the COP0 registers.
	*/
	void initalise() override;

	/*
	EECore COP0 register implementations. Follows EE Core Users Manual.
	Note: Registers r24 and r25 have been split up into 7 and 3 registers respectively as per the docs, 
	       as it is not feasible to implement them as sub-registers.
	The new registers have been assigned register numbers from 32 -> 39 (for PCSX2 reference).
	*/
	std::shared_ptr<COP0RegisterPRId_EECore_t> PRId;
	std::shared_ptr<COP0RegisterBadPAddr_t> BadPAddr;  // r23: Bad Physical Address value (for exceptions).
													   // r24: See below for r24.
													   // r25: See below for r25.

	// Debug registers.
	std::shared_ptr<COP0RegisterBPC_t>		BPC;       // r24: Registers related to debug function.
	std::shared_ptr<COP0RegisterIAB_t>		IAB;       // r32: Instruction address breakpoint settings.
	std::shared_ptr<COP0RegisterIABM_t>		IABM;      // r33: Instruction address breakpoint settings.
	std::shared_ptr<COP0RegisterDAB_t>		DAB;	   // r34: Data address breakpoint settings.
	std::shared_ptr<COP0RegisterDABM_t>		DABM;	   // r35: Data address breakpoint settings.
	std::shared_ptr<COP0RegisterDVB_t>		DVB;	   // r36: Data value breakpoint settings.
	std::shared_ptr<COP0RegisterDVBM_t>		DVBM;	   // r37: Data value breakpoint settings.

	// Performance registers.
	std::shared_ptr<COP0RegisterPCCR_t>		PCCR;	   // r25: Performance counter and control register.
	std::shared_ptr<COP0RegisterPCR0_t>		PCR0;      // r38: Performance counter.
	std::shared_ptr<COP0RegisterPCR1_t>		PCR1;      // r39: Performance counter.

	// Array of above registers (needed by some EECore instructions to access by index). 
	// Generally you will never access registers directly through this, only the PS2 OS will.
	std::shared_ptr<BitfieldRegister32_t> Registers[PS2Constants::EE::EECore::COP0::NUMBER_REGISTERS];

	// Array of PCR0/PCR1, used by the MFPC/MTPC instructions.
	std::shared_ptr<BitfieldRegister32_t> PCRRegisters[PS2Constants::EE::EECore::COP0::NUMBER_PCR_REGISTERS];


};
