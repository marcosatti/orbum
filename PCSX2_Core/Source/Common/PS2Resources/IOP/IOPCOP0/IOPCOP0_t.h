#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/MIPSCoprocessor/MIPSCoprocessor0_t.h"

/*
COP0 refers to the system control coprocessor (used for manipulating the memory management and exception handling facilities of the processor, etc).
See EE Core Users Manual page 62 onwards.
*/

class COP0RegisterPRId_IOP_t;
class COP0RegisterReserved_t;

class IOPCOP0_t : public MIPSCoprocessor0_t, public PS2ResourcesSubobject
{
public:
	explicit IOPCOP0_t(const PS2Resources_t* const PS2Resources);

	/*
	Checks if the IOP COP0 coprocessor is usable. 
	Can be used by the component calling this to raise a IOPException_t(coprocessor unusable) if not available.
	*/
	bool isCoprocessorUsable() const override;

	/*
	Initalises the IOP COP0 registers.
	*/
	void initalise() override;

	/*
	IOP COP0 register implementations. 
	*/
	std::shared_ptr<COP0RegisterPRId_IOP_t> PRId;
	std::shared_ptr<COP0RegisterReserved_t> Reserved7; // IOP COP0 #7 register is undefined, but is accessed by BIOS (treat as unknown).

	// Array of above registers (needed by some IOP instructions to access by index). 
	// Generally you will never access registers directly through this, only the PS2 OS will.
	std::shared_ptr<BitfieldRegister32_t> Registers[PS2Constants::IOP::COP0::NUMBER_REGISTERS];

};
