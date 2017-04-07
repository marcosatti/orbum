#include "stdafx.h"

#include "Common/Global/Globals.h"
#include "Common/Types/Memory/ByteMemory_t.h"
#include "Common/Types/Memory/ROByteMemory_t.h"
#include "Common/Types/Memory/ConstantByteMemory_t.h"
#include "Common/Types/Register/Register32_t.h"
#include "Common/Types/ByteMMU/ByteMMU_t.h"

#include "Resources/Resources_t.h"
#include "Resources/EE/EE_t.h"
#include "Resources/EE/Types/EERegisters_t.h"
#include "Resources/EE/EECore/EECore_t.h"
#include "Resources/EE/Timers/EETimers_t.h"
#include "Resources/EE/DMAC/EEDmac_t.h"
#include "Resources/EE/INTC/EEIntc_t.h"
#include "Resources/EE/IPU/IPU_t.h"
#include "Resources/EE/GIF/GIF_t.h"
#include "Resources/EE/VPU/VPU_t.h"

EE_t::EE_t() :
	EECore(std::make_shared<EECore_t>()),
	DMAC(std::make_shared<EEDmac_t>()),
	INTC(std::make_shared<EEIntc_t>()),
	Timers(std::make_shared<EETimers_t>()),
	IPU(std::make_shared<IPU_t>()),
	GIF(std::make_shared<GIF_t>()),
	VPU(std::make_shared<VPU_t>()),
	MMU(std::make_shared<ByteMMU_t>(32, 16, 2)), // Number of page index bits optimised for minimum memory usage (Marco Satti).
	MainMemory(std::make_shared<ByteMemory_t>("EE MainMem", false, false, Constants::EE::MainMemory::SIZE_MAIN_MEMORY)),
	BootROM(std::make_shared<ROByteMemory_t>("EE BootROM", false, false, Constants::EE::ROM::SIZE_BOOT_ROM)),
	ROM1(std::make_shared<ROByteMemory_t>("EE ROM1", false, false, Constants::EE::ROM::SIZE_ROM1)),
	EROM(std::make_shared<ROByteMemory_t>("EE EROM", false, false, Constants::EE::ROM::SIZE_EROM)),
	ROM2(std::make_shared<ROByteMemory_t>("EE ROM2", false, false, Constants::EE::ROM::SIZE_ROM2)),
	UNKNOWN_1A000000(std::make_shared<ConstantByteMemory_t>("EE 1A00", false, false, 0x10000)),

	// Registers.
	MEMORY_SIO(std::make_shared<EERegister_SIO_t>("EE SIO", false, false)),
	REGISTER_F400(std::make_shared<Register32_t>("EE F400", false, false)),
	MEMORY_F410(std::make_shared<ConstantByteMemory_t>("EE F410", false, false, 0x04)),
	REGISTER_F420(std::make_shared<Register32_t>("EE F420", false, false)),
	MEMORY_MCH(std::make_shared<EERegister_MCH_t>("EE MCH", false, false)),
	MEMORY_F450(std::make_shared<ByteMemory_t>("EE F450", false, false, 0xB0))
{
}