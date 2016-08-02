#pragma once

#include "Common/PS2 Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2 Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2 Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2 Resources/EE/EECore/ScratchpadMemory/ScratchpadMemory.h"

/*
TODO: finish off documentation when all components are ready.
EECore_t declares the R5900 structure, co-processors, etc. (forming the EE Core).
For reference documentation, see:
 - (primarily) The EE Core Users Manual (SCE).
 - R5900_t.h, COP0_t.h, COP1_t.h for the component inners.
*/

class EECore_t {
public:
	// R5900 CPU
	R5900_t R5900;

	// COP0 coprocessor
	COP0_t COP0;

	// COP1 coprocessor
	COP1_t COP1;

	/*
	COP2 refers to VPU0. As the Sony doc's include it with the EE Core, it is also included here.
	HOWEVER, it is always referenced in PCSX2 as VPU0, rather than COP2. When reading through the docs, just remember they are the same thing.
	See EE Core Users Manual for more information.
	*/
	// TODO: Implement. As there is VPU0/VPU1, need to develop a VPU_t.h file and reuse it here.
	// VPU_t VPU0;

	// Scratchpad memory
	ScratchpadMemory_t ScratchpadMemory;

};
