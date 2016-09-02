#include "stdafx.h"

#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/EECore/R5900/R5900_t.h"
#include "Common/PS2Resources/EE/EECore/COP0/COP0_t.h"
#include "Common/PS2Resources/EE/EECore/COP1/COP1_t.h"
#include "Common/PS2Resources/EE/EECore/Exceptions/Exceptions_t.h"
#include "Common/PS2Resources/EE/EECore/MMU/MMU_t.h"
#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"

EECore_t::EECore_t(const PS2Resources_t* const PS2Resources): PS2ResourcesSubobject(PS2Resources)
{
	// Initalise Class.
	R5900 = std::make_shared<R5900_t>(getRootResources());
	COP0 = std::make_shared<COP0_t>(getRootResources());
	COP1 = std::make_shared<COP1_t>(getRootResources());
	ScratchpadMemory = std::make_shared<PS2StorageObject_t>(PS2Constants::EE::EECore::ScratchpadMemory::SIZE_SCRATCHPAD_MEMORY, "Scratchpad Memory", PS2Constants::EE::EECore::ScratchpadMemory::PADDRESS_SCRATCHPAD_MEMORY);
	Exceptions = std::make_shared<Exceptions_t>(getRootResources());
	MMU = std::make_shared<MMU_t>(getRootResources());
}
