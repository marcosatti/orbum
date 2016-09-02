#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/Types/PS2DeadStorageObject/PS2DeadStorageObject_t.h"
#include "Common/PS2Resources/EE/Types/EERegisters_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"

EE_t::EE_t(const PS2Resources_t* const PS2Resources):
	PS2ResourcesSubobject(PS2Resources),
	EECore(std::make_shared<EECore_t>(getRootResources())),
	EE_REGISTER_SIO(std::make_shared<EERegisterSIO_t>()),
	EE_REGISTER_MCH(std::make_shared<EERegisterMCH_t>()),
	EE_REGISTER_DMAC_EXT(std::make_shared<PS2StorageObject_t>(PS2Constants::EE::EE_REGISTER_DMAC_EXT::SIZE_EE_REGISTER_DMAC_EXT, "DMAC EXT (F500)", PS2Constants::EE::EE_REGISTER_DMAC_EXT::PADDRESS_EE_REGISTER_DMAC_EXT)),
	EE_REGISTER_F410(std::make_shared<PS2DeadStorageObject_t>(0x10, "F410", 0x1000F410)) // Unknown register named "F410". Used by the BIOS.
{
}
