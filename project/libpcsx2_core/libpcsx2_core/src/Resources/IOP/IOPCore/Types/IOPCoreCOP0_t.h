#pragma once

#include <memory>

#include "Common/Global/Globals.h"
#include "Common/Types/MIPS/MIPSCoprocessor0_t.h"
#include "Common/Types/MIPS/MIPSOperatingContext_t.h"

class Register32_t;
class IOPCoreCOP0Register_Context_t;
class IOPCoreCOP0Register_Status_t;
class IOPCoreCOP0Register_Cause_t;
class IOPCoreCOP0Register_PRId_t;

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual page 62 onwards.

TODO: Finish implementing 'Register32_t' registers? IOP COP0 registers that are unused within the emulator have been left as reserved, since there is no need for them. Probably will never need to.
*/
class IOPCoreCOP0_t : public MIPSCoprocessor0_t
{
public:
	IOPCoreCOP0_t();

	/*
	Checks if the IOP COP0 coprocessor is usable. 
	Can be used by the component calling this to raise a IOPCoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable(const Context_t context) const override;

	/*
	Initialises the IOP COP0 registers.
	*/
	void initialise() override;

	/*
	Determine the CPU context. Uses the Status register.
	*/
	MIPSCPUOperatingContext_t getCPUOperatingContext(const Context_t context) const override;

	/*
	IOP COP0 register implementations. 
	*/
	std::shared_ptr<Register32_t>                  INDX;    // r0: INDX.
	std::shared_ptr<Register32_t>                  RAND;    // r1: RAND.
	std::shared_ptr<Register32_t>                  TLBL;    // r2: TLBL.
	std::shared_ptr<Register32_t>                  BPC;     // r3: BPC.
	std::shared_ptr<IOPCoreCOP0Register_Context_t> Context; // r4: Context.
	std::shared_ptr<Register32_t>                  BDA;     // r5: BDA.
	std::shared_ptr<Register32_t>                  PIDMASK; // r6: PIDMASK.
	std::shared_ptr<Register32_t>                  DCIC;    // r7: DCIC.
	std::shared_ptr<Register32_t>                  BADV;    // r8: BADV.
	std::shared_ptr<Register32_t>                  BDAM;    // r9: BDAM.
	std::shared_ptr<Register32_t>                  TLBH;    // r10: TLBH.
	std::shared_ptr<Register32_t>                  BPCM;    // r11: BPCM.
	std::shared_ptr<IOPCoreCOP0Register_Status_t>  Status;  // r12: Status.
	std::shared_ptr<IOPCoreCOP0Register_Cause_t>   Cause;   // r13: Cause.
	std::shared_ptr<Register32_t>                  EPC;     // r14: EPC.
	std::shared_ptr<IOPCoreCOP0Register_PRId_t>    PRId;    // r15: PRId.
	std::shared_ptr<Register32_t>                  ERREG;   // r16: ERREG.


	// Array of above registers (needed by some IOP instructions to access by index). 
	// Generally you will never access registers directly through this, only the PS2 OS will.
	std::shared_ptr<Register32_t> Registers[Constants::IOP::IOPCore::COP0::NUMBER_REGISTERS];

};
