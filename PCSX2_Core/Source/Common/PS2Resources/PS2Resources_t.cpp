#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Constants/PS2Constants.h"
#include "Common/PS2Resources/Types/PS2StorageObject/PS2StorageObject_t.h"
#include "Common/PS2Resources/EE/EE_t.h"

PS2Resources_t::PS2Resources_t() :
	EE(std::make_shared<EE_t>(this)),
	MainMemory(std::make_shared<PS2StorageObject_t>(PS2Constants::MainMemory::SIZE_MAIN_MEMORY, "Main Memory", PS2Constants::MainMemory::PADDRESS_MAIN_MEMORY)),
	BootROM(std::make_shared<PS2StorageObject_t>(PS2Constants::BootROM::SIZE_BOOT_ROM, "Boot ROM", PS2Constants::BootROM::PADDRESS_BOOT_ROM))
{
}
