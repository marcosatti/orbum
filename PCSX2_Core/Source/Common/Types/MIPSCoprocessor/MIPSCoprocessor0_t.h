#pragma once

#include "Common/Types/MIPSCoprocessor/MIPSCoprocessor_t.h"
#include "Common/Types/MIPSCoprocessor/MIPSOperatingContext_t.h"

/*
Represents a MIPS co-processor 0 base class (aka COP0).
COP0 is used widely in MIPS systems, as the system control registers.

The MFC0, MTC0 MIPS instructions move data to and from these registers, by specifying an array index from 0 -> 31.
It is up to the user to define the array contents.
*/
class MIPSCoprocessor0_t : public MIPSCoprocessor_t
{
public:
	MIPSCoprocessor0_t();
	virtual ~MIPSCoprocessor0_t();

	/*
	Used to check the operating context - Kernel mode, Supervisor mode, or User mode.
	Set to a virtual function as the COP0 register formats are not always compatible.
	*/
	virtual	MIPSOperatingContext_t getCPUOperatingContext() const = 0;
};

