#include "stdafx.h"

#include "Common/PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "Common/PS2Resources/Types/Registers/Register32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

VIF_t::VIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// VIF0 Registers.
	VIF0_REGISTER_STAT(std::make_shared<Register32_t>()),
	VIF0_REGISTER_FBRST(std::make_shared<Register32_t>()),
	VIF0_REGISTER_ERR(std::make_shared<Register32_t>()),
	VIF0_REGISTER_MARK(std::make_shared<Register32_t>()),
	VIF0_REGISTER_CYCLE(std::make_shared<Register32_t>()),
	VIF0_REGISTER_MODE(std::make_shared<Register32_t>()),
	VIF0_REGISTER_NUM(std::make_shared<Register32_t>()),
	VIF0_REGISTER_MASK(std::make_shared<Register32_t>()),
	VIF0_REGISTER_CODE(std::make_shared<Register32_t>()),
	VIF0_REGISTER_ITOPS(std::make_shared<Register32_t>()),
	VIF0_MEMORY_38a0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38a0 (reserved)", 0x100038a0)),
	VIF0_MEMORY_38b0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38b0 (reserved)", 0x100038b0)),
	VIF0_MEMORY_38c0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38c0 (reserved)", 0x100038c0)),
	VIF0_REGISTER_ITOP(std::make_shared<Register32_t>()),
	VIF0_MEMORY_38e0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38e0 (reserved)", 0x100038e0)),
	VIF0_MEMORY_38f0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38f0 (reserved)", 0x100038f0)),
	VIF0_REGISTER_R0(std::make_shared<Register32_t>()),
	VIF0_REGISTER_R1(std::make_shared<Register32_t>()),
	VIF0_REGISTER_R2(std::make_shared<Register32_t>()),
	VIF0_REGISTER_R3(std::make_shared<Register32_t>()),
	VIF0_REGISTER_C0(std::make_shared<Register32_t>()),
	VIF0_REGISTER_C1(std::make_shared<Register32_t>()),
	VIF0_REGISTER_C2(std::make_shared<Register32_t>()),
	VIF0_REGISTER_C3(std::make_shared<Register32_t>()),
	VIF0_MEMORY_3980(std::make_shared<DeadMMemory_t>(0x280, "VIF0: VIF0_3980 (reserved)", 0x10003980)),

	// VIF1 Registers.
	VIF1_REGISTER_STAT(std::make_shared<Register32_t>()),
	VIF1_REGISTER_FBRST(std::make_shared<Register32_t>()),
	VIF1_REGISTER_ERR(std::make_shared<Register32_t>()),
	VIF1_REGISTER_MARK(std::make_shared<Register32_t>()),
	VIF1_REGISTER_CYCLE(std::make_shared<Register32_t>()),
	VIF1_REGISTER_MODE(std::make_shared<Register32_t>()),
	VIF1_REGISTER_NUM(std::make_shared<Register32_t>()),
	VIF1_REGISTER_MASK(std::make_shared<Register32_t>()),
	VIF1_REGISTER_CODE(std::make_shared<Register32_t>()),
	VIF1_REGISTER_ITOPS(std::make_shared<Register32_t>()),
	VIF1_REGISTER_BASE(std::make_shared<Register32_t>()),
	VIF1_REGISTER_OFST(std::make_shared<Register32_t>()),
	VIF1_REGISTER_TOPS(std::make_shared<Register32_t>()),
	VIF1_REGISTER_ITOP(std::make_shared<Register32_t>()),
	VIF1_REGISTER_TOP(std::make_shared<Register32_t>()),
	VIF1_MEMORY_3cf0(std::make_shared<DeadMMemory_t>(0x10, "VIF1: VIF1_3cf0 (reserved)", 0x10003cf0)),
	VIF1_REGISTER_R0(std::make_shared<Register32_t>()),
	VIF1_REGISTER_R1(std::make_shared<Register32_t>()),
	VIF1_REGISTER_R2(std::make_shared<Register32_t>()),
	VIF1_REGISTER_R3(std::make_shared<Register32_t>()),
	VIF1_REGISTER_C0(std::make_shared<Register32_t>()),
	VIF1_REGISTER_C1(std::make_shared<Register32_t>()),
	VIF1_REGISTER_C2(std::make_shared<Register32_t>()),
	VIF1_REGISTER_C3(std::make_shared<Register32_t>()),
	VIF1_MEMORY_3d80(std::make_shared<DeadMMemory_t>(0x280, "VIF1: VIF1_3d80 (reserved)", 0x10003d80))
{
}
