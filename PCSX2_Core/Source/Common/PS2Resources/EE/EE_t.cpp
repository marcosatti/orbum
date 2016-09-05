#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/Types/PS2DeadStorageObject/PS2DeadStorageObject_t.h"
#include "Common/PS2Resources/EE/Types/EERegisters_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"

EE_t::EE_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	EECore(std::make_shared<EECore_t>(getRootResources())),

	// Registers.
	EE_REGISTER_SIO(std::make_shared<EERegisterSIO_t>()),

	EE_REGISTER_F400(std::make_shared<PS2StorageObject_t>(0x10, "Undocumented: F400", 0x1000F400)),
	EE_REGISTER_F410(std::make_shared<PS2DeadStorageObject_t>(0x10, "Undocumented: F410", 0x1000F410)),
	EE_REGISTER_F420(std::make_shared<PS2StorageObject_t>(0x10, "Undocumented: F420", 0x1000F420)),
	EE_REGISTER_MCH(std::make_shared<EERegisterMCH_t>()),
	EE_REGISTER_F450(std::make_shared<PS2StorageObject_t>(0xB0, "Undocumented: F450", 0x1000F450)),

	EE_REGISTER_F500(std::make_shared<PS2DeadStorageObject_t>(0x20, "Undocumented: F500", 0x1000F500)),
	EE_REGISTER_D_ENABLER(std::make_shared<PS2StorageObject_t>(0x10, "DMAC: D_ENABLER", 0x1000F520)),
	EE_REGISTER_F530(std::make_shared<PS2DeadStorageObject_t>(0x50, "DMAC: F530 (reserved)", 0x1000F530)),
	EE_REGISTER_D_ENABLEW(std::make_shared<PS2StorageObject_t>(0x10, "DMAC: D_ENABLEW", 0x1000F590)),
	EE_REGISTER_F5A0(std::make_shared<PS2DeadStorageObject_t>(0x50, "DMAC: F5A0 (reserved)", 0x1000F5A0))
{
}
