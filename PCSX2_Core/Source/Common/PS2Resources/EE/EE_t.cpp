#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/ImageMappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/BusErrorMMemory_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/PhysicalMMU/PhysicalMMU_t.h"
#include "Common/PS2Resources/PS2Resources_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/Timers/Timers_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/INTC/INTC_t.h"
#include "Common/PS2Resources/EE/IPU/IPU_t.h"
#include "Common/PS2Resources/EE/GIF/GIF_t.h"
#include "Common/PS2Resources/EE/VPU/VPU_t.h"


EE_t::EE_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),
	EECore(std::make_shared<EECore_t>(getRootResources())),
	DMAC(std::make_shared<DMAC_t>(getRootResources())),
	INTC(std::make_shared<INTC_t>(getRootResources())),
	Timers(std::make_shared<Timers_t>(getRootResources())),
	IPU(std::make_shared<IPU_t>(getRootResources())),
	GIF(std::make_shared<GIF_t>(getRootResources())),
	VPU(std::make_shared<VPU_t>(getRootResources())),
	PhysicalMMU(std::make_shared<PhysicalMMU_t>(Constants::SIZE_4GB, Constants::SIZE_4MB, Constants::SIZE_16B)),
	MainMemory(std::make_shared<MappedMemory_t>(PS2Constants::EE::MainMemory::SIZE_MAIN_MEMORY, "Main Memory", PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY)),
	BootROM(std::make_shared<BootROM_t>()),
	UNKNOWN_1A000000(std::make_shared<DeadMMemory_t>(0x10000, "Unknown: 1A00", 0x1A000000)),

	// Registers.
	EE_FIFO_VIF0(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF0_FIFO", 0x10004000)),
	EE_FIFO_VIF1(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF1_FIFO", 0x10005000)),
	EE_FIFO_GIF(std::make_shared<MappedMemory_t>(0x10, "FIFO: GIF_FIFO", 0x10006000)),
	EE_FIFO_IPU_out(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_out_FIFO", 0x10007000)),
	EE_FIFO_IPU_in(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_in_FIFO", 0x10007010)),

	EE_MEMORY_SIO(std::make_shared<EERegisterSIO_t>()),
	EE_REGISTER_SB_SMFLG(std::make_shared<Register32_t>()),
	EE_REGISTER_F400(std::make_shared<Register32_t>()),
	EE_MEMORY_F410(std::make_shared<DeadMMemory_t>(0x04, "Undocumented: F410", 0x1000f410)),
	EE_REGISTER_F420(std::make_shared<Register32_t>()),
	EE_MEMORY_MCH(std::make_shared<EERegisterMCH_t>()),
	EE_MEMORY_F450(std::make_shared<MappedMemory_t>(0xB0, "Undocumented: F450", 0x1000f450))
{
}
