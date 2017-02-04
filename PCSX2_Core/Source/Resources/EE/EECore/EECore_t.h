#pragma once

#include <memory>

class EECoreR5900_t;
class EECoreCOP0_t;
class EECoreFPU_t;
class Memory_t;
class EECoreTLB_t;

/*
TODO: finish off documentation when all components are ready.
EECore_t declares the R5900 structure, co-processors, etc. (forming the EE Core).
For reference documentation, see:
- (primarily) The EE Core Users Manual (SCE).
- EECoreR5900_t.h, EECoreCOP0_t.h, EECoreFPU_t.h, etc, for the component inners.
*/
class EECore_t
{
public:
	explicit EECore_t();

	/*
	R5900 CPU.
	*/
	std::shared_ptr<EECoreR5900_t> R5900;

	/*
	COP0 coprocessor.
	*/
	std::shared_ptr<EECoreCOP0_t> COP0;

	/*
	FPU (COP1) coprocessor.
	*/
	std::shared_ptr<EECoreFPU_t> FPU;

	/*
	Scratchpad memory.
	*/
	std::shared_ptr<Memory_t> ScratchpadMemory;

	/*
	TLB state.
	*/
	std::shared_ptr<EECoreTLB_t> TLB;

};
