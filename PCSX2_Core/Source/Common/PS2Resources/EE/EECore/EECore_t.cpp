#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreCOP0/EECoreCOP0_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreFPU/EECoreFPU_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreExceptions/EECoreExceptions_t.h"
#include "Common/PS2Resources/EE/EECore/EECoreTLB/EECoreTLB_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"

EECore_t::EECore_t(const PS2Resources_t* const PS2Resources) : 
	PS2ResourcesSubobject(PS2Resources),
	R5900(std::make_shared<R5900_t>(getRootResources())),
	COP0(std::make_shared<EECoreCOP0_t>(getRootResources())),
	FPU(std::make_shared<EECoreFPU_t>(getRootResources())),
	ScratchpadMemory(std::make_shared<MappedMemory_t>(PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "EE Core Scratchpad Memory", PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY)),
	Exceptions(std::make_shared<EECoreExceptions_t>(getRootResources())),
	TLB(std::make_shared<EECoreTLB_t>(getRootResources()))
{
}
