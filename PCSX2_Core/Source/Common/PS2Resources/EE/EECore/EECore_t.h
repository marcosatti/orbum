#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish off documentation when all components are ready.
EECore_t declares the R5900 structure, co-processors, etc. (forming the EE Core).
For reference documentation, see:
 - (primarily) The EE Core Users Manual (SCE).
 - R5900_t.h, COP0_t.h, COP1_t.h, etc, for the component inners.
*/

class R5900_t;
class COP0_t;
class COP1_t;
class StorageObject_t;
class Exceptions_t;
class MMU_t;

class EECore_t : public PS2ResourcesSubobject
{
public:
	explicit EECore_t(const PS2Resources_t* const PS2Resources);

	// R5900 CPU
	std::shared_ptr<R5900_t> R5900;

	// COP0 coprocessor
	std::shared_ptr<COP0_t> COP0;

	// COP1 coprocessor
	std::shared_ptr<COP1_t> COP1;

	/*
	COP2 refers to VPU0. As the Sony doc's include it with the EE Core, it is also included here.
	HOWEVER, it is always referenced in PCSX2 as VPU0, rather than COP2. When reading through the docs, just remember they are the same thing.
	See EE Core Users Manual for more information.
	*/
	// TODO: Implement. As there is VPU0/VPU1, need to develop a VPU_t.h file and reuse it here.
	// VPU_t VPU0;

	// Scratchpad memory
	std::shared_ptr<StorageObject_t> ScratchpadMemory;

	// Exception/Interrupt State. The INTC etc will communicate through here.
	std::shared_ptr<Exceptions_t> Exceptions;

	// PS2 MMU Implementation (TLB, virtual address translation, etc).
	std::shared_ptr<MMU_t> MMU;

};