#include "stdafx.h"

#include <fstream>

#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"
#include "Common/PS2Constants/PS2Constants.h"

BootROM_t::BootROM_t() :
	ROMappedMemory_t(PS2Constants::EE::BootROM::SIZE_BOOT_ROM, "Boot ROM", PS2Constants::EE::BootROM::PADDRESS_BOOT_ROM)
{
}

void BootROM_t::loadBIOS(const std::string& biosPath) const
{
	char * memoryBase = reinterpret_cast<char*>(getClientMemoryAddress());
	std::ifstream file(biosPath, std::ifstream::binary);
	if (file.fail())
		throw std::runtime_error("initaliseBootROM(): tried to open BIOS file, but it failed! Check file exists and has read permissions.");
	file.seekg(std::ifstream::beg);
	file.read(memoryBase, PS2Constants::EE::BootROM::SIZE_BOOT_ROM);
}
