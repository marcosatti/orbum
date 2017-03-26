#pragma once

#include "Common/Types/MIPSInstruction/MIPSInstruction_t.h"

/*
Extends the MIPS instruction type with additional fields available, needed to support the VU0 (COP2) instruction lookup.
*/
struct EECoreInstruction_t : MIPSInstruction_t
{
	/*
	Gets the various VU instruction fields required. Prefixed with getV*.
	- I    @ bits 0.
	- BC   @ bits 0-1.
	- Dest @ bits 21-24.
	- CO   @ bits 25.
	*/
	u8 getVI() const;
	u8 getVBC() const;
	u8 getVDest() const;
	u8 getVCO() const;
};