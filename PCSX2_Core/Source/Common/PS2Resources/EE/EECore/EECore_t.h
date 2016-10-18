#pragma once

#include <memory>

#include "Common/Interfaces/PS2ResourcesSubobject.h"

/*
TODO: finish off documentation when all components are ready.
EECore_t declares the R5900 structure, co-processors, etc. (forming the EE Core).
For reference documentation, see:
 - (primarily) The EE Core Users Manual (SCE).
 - R5900_t.h, EECoreCOP0_t.h, EECoreFPU_t.h, etc, for the component inners.
*/

class R5900_t;
class EECoreCOP0_t;
class EECoreFPU_t;
class MappedMemory_t;
class EECoreExceptions_t;
class EECoreTLB_t;

class EECore_t : public PS2ResourcesSubobject
{
public:
	explicit EECore_t(const PS2Resources_t* const PS2Resources);

	// R5900 CPU.
	std::shared_ptr<R5900_t> R5900;

	// COP0 coprocessor.
	std::shared_ptr<EECoreCOP0_t> COP0;

	// FPU (COP1) coprocessor.
	std::shared_ptr<EECoreFPU_t> FPU;

	// VPU0 (COP2) coprocessor. Points to same object as EE::VPU0.
	// VPU_t VPU0;

	// Scratchpad memory.
	std::shared_ptr<MappedMemory_t> ScratchpadMemory;

	// Exception/Interrupt State.
	std::shared_ptr<EECoreExceptions_t> Exceptions;

	// TLB state.
	std::shared_ptr<EECoreTLB_t> TLB;

};
