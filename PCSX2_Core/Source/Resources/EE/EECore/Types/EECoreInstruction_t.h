#pragma once

#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"

/*
Extends the MIPS instruction type with additional fields available, needed to support the VU0 (COP2) instruction lookup.
*/
class EECoreInstruction_t : public MIPSInstruction_t
{
public:
	/*
	Initialise an Instruction object with the specified 32-bit MIPS instruction. Defaults to 0.
	*/
	EECoreInstruction_t(const u32 instructionValue = 0);

	/*
	Gets the various VU instruction fields required. Prefixed with getV*.
	- I    @ Bit 0.
	- BC   @ Bits 0-1.
	- Dest @ Bits 21-24.
	- CO   @ Bit 25.
	*/
	u8 getVI() const;
	u8 getVBC() const;
	u8 getVDest() const;
	u8 getVCO() const;
};