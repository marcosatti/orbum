#pragma once

#include <memory>

#include "PS2Constants/PS2Constants.h"
#include "Common/Types/MIPSCoprocessor/MIPSCoprocessor0_t.h"
#include "Common/Types/Registers/BitfieldRegister32_t.h"

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual page 62 onwards.

TODO: Finish implementing 'COP0RegisterReserved_t' registers? IOP COP0 registers that are unused within the emulator have been left as reserved, since there is no need for them. Probably will never need to.
*/

class IOPCoreCOP0Register_Context_t;
class IOPCoreCOP0Register_Status_t;
class IOPCoreCOP0Register_Cause_t;
class COP0RegisterEPC_t;
class IOPCoreCOP0Register_PRId_t;
class COP0RegisterReserved_t;

class IOPCoreCOP0_t : public MIPSCoprocessor0_t
{
public:
	explicit IOPCoreCOP0_t();

	/*
	Checks if the IOP COP0 coprocessor is usable. 
	Can be used by the component calling this to raise a IOPCoreException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable() const override;

	/*
	Initalises the IOP COP0 registers.
	*/
	void initalise() override;

	/*
	Functions to determine the CPU context. Uses the Status register.
	*/
	bool isOperatingUserMode() const override;
	bool isOperatingSupervisorMode() const override; // Not supported on the IOP - throws exception if called.
	bool isOperatingKernelMode() const override;

	/*
	IOP COP0 register implementations. 
	*/
	std::shared_ptr<COP0RegisterReserved_t> INDX;           // r0: INDX.
	std::shared_ptr<COP0RegisterReserved_t> RAND;           // r1: RAND.
	std::shared_ptr<COP0RegisterReserved_t> TLBL;           // r2: TLBL.
	std::shared_ptr<COP0RegisterReserved_t> BPC;            // r3: BPC.
	std::shared_ptr<IOPCoreCOP0Register_Context_t> Context; // r4: Context.
	std::shared_ptr<COP0RegisterReserved_t> BDA;            // r5: BDA.
	std::shared_ptr<COP0RegisterReserved_t> PIDMASK;        // r6: PIDMASK.
	std::shared_ptr<COP0RegisterReserved_t> DCIC;           // r7: DCIC.
	std::shared_ptr<COP0RegisterReserved_t> BADV;           // r8: BADV.
	std::shared_ptr<COP0RegisterReserved_t> BDAM;           // r9: BDAM.
	std::shared_ptr<COP0RegisterReserved_t> TLBH;           // r10: TLBH.
	std::shared_ptr<COP0RegisterReserved_t> BPCM;           // r11: BPCM.
	std::shared_ptr<IOPCoreCOP0Register_Status_t> Status;   // r12: Status.
	std::shared_ptr<IOPCoreCOP0Register_Cause_t> Cause;     // r13: Cause.
	std::shared_ptr<COP0RegisterEPC_t> EPC;                 // r14: EPC.
	std::shared_ptr<IOPCoreCOP0Register_PRId_t> PRId;       // r15: PRId.
	std::shared_ptr<COP0RegisterReserved_t> ERREG;          // r16: ERREG.


	// Array of above registers (needed by some IOP instructions to access by index). 
	// Generally you will never access registers directly through this, only the PS2 OS will.
	std::shared_ptr<BitfieldRegister32_t> Registers[PS2Constants::IOP::IOPCore::COP0::NUMBER_REGISTERS];

};
