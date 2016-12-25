#include "stdafx.h"

#include "PS2Resources/EE/EECore/EECore_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreR5900_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreCOP0_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreFPU_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreExceptions_t.h"
#include "PS2Resources/EE/EECore/Types/EECoreTLB_t.h"
#include "Common/Types/Memory/Memory_t.h"

EECore_t::EECore_t(const PS2Resources_t* PS2Resources) : 
	PS2ResourcesSubcategory(PS2Resources),
	R5900(std::make_shared<EECoreR5900_t>()),
	COP0(std::make_shared<EECoreCOP0_t>()),
	FPU(std::make_shared<EECoreFPU_t>(COP0)),
	ScratchpadMemory(std::make_shared<Memory_t>(PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "EE Core Scratchpad Memory")),
	Exceptions(std::make_shared<EECoreExceptions_t>(COP0)),
	TLB(std::make_shared<EECoreTLB_t>())
{
}