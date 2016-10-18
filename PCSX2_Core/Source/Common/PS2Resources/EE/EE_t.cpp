#include "stdafx.h"

#include "Common/Global/Globals.h"

#include "Common/PS2Resources/EE/EE_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"
#include "Common/PS2Resources/EE/Types/EE_Registers_t.h"
#include "Common/PS2Resources/EE/Types/BootROM_t.h"
#include "Common/PS2Resources/EE/EECore/EECore_t.h"
#include "Common/PS2Resources/EE/DMAC/DMAC_t.h"
#include "Common/PS2Resources/EE/INTC/INTC_t.h"
#include "Common/PS2Resources/EE/Timers/Timers_t.h"
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
	MainMemory(std::make_shared<MappedMemory_t>(PS2Constants::EE::MainMemory::SIZE_MAIN_MEMORY, "Main Memory", PS2Constants::EE::MainMemory::PADDRESS_MAIN_MEMORY)),
	BootROM(std::make_shared<BootROM_t>()),

	// Registers.
	EE_REGISTER_VIF0_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF0_FIFO", 0x10004000)),
	EE_REGISTER_VIF1_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: VIF1_FIFO", 0x10005000)),
	EE_REGISTER_GIF_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: GIF_FIFO", 0x10006000)),
	EE_REGISTER_IPU_out_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_out_FIFO", 0x10007000)),
	EE_REGISTER_IPU_in_FIFO(std::make_shared<MappedMemory_t>(0x10, "FIFO: IPU_in_FIFO", 0x10007010)),
	EE_REGISTER_SIO(std::make_shared<EERegisterSIO_t>()),
	EE_REGISTER_SB_SMFLG(std::make_shared<MappedMemory32_t>("SIF: SB_SMFLG", 0x1000f230)),
	EE_REGISTER_F400(std::make_shared<MappedMemory32_t>("Undocumented: F400", 0x1000f400)),
	EE_REGISTER_F410(std::make_shared<DeadMMemory_t>(0x04, "Undocumented: F410", 0x1000f410)),
	EE_REGISTER_F420(std::make_shared<MappedMemory32_t>("Undocumented: F420", 0x1000f420)),
	EE_REGISTER_MCH(std::make_shared<EERegisterMCH_t>()),
	EE_REGISTER_F450(std::make_shared<MappedMemory_t>(0xB0, "Undocumented: F450", 0x1000f450))
{
}
