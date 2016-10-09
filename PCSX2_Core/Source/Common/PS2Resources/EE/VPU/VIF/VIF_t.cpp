#include "stdafx.h"

#include "Common/PS2Resources/EE/VPU/VIF/VIF_t.h"
#include "Common/PS2Resources/Types/MappedMemory/MappedMemory32_t.h"
#include "Common/PS2Resources/Types/MappedMemory/DeadMMemory_t.h"

VIF_t::VIF_t(const PS2Resources_t* const PS2Resources) :
	PS2ResourcesSubobject(PS2Resources),

	// VIF0 Registers.
	VIF0_REGISTER_STAT(std::make_shared<MappedMemory32_t>("VIF0: VIF0_STAT", 0x10003800)),
	VIF0_REGISTER_FBRST(std::make_shared<MappedMemory32_t>("VIF0: VIF0_FBRST", 0x10003810)),
	VIF0_REGISTER_ERR(std::make_shared<MappedMemory32_t>("VIF0: VIF0_ERR", 0x10003820)),
	VIF0_REGISTER_MARK(std::make_shared<MappedMemory32_t>("VIF0: VIF0_MARK", 0x10003830)),
	VIF0_REGISTER_CYCLE(std::make_shared<MappedMemory32_t>("VIF0: VIF0_CYCLE", 0x10003840)),
	VIF0_REGISTER_MODE(std::make_shared<MappedMemory32_t>("VIF0: VIF0_MODE", 0x10003850)),
	VIF0_REGISTER_NUM(std::make_shared<MappedMemory32_t>("VIF0: VIF0_NUM", 0x10003860)),
	VIF0_REGISTER_MASK(std::make_shared<MappedMemory32_t>("VIF0: VIF0_MASK", 0x10003870)),
	VIF0_REGISTER_CODE(std::make_shared<MappedMemory32_t>("VIF0: VIF0_CODE", 0x10003880)),
	VIF0_REGISTER_ITOPS(std::make_shared<MappedMemory32_t>("VIF0: VIF0_ITOPS", 0x10003890)),
	VIF0_REGISTER_38a0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38a0 (reserved)", 0x100038a0)),
	VIF0_REGISTER_38b0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38b0 (reserved)", 0x100038b0)),
	VIF0_REGISTER_38c0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38c0 (reserved)", 0x100038c0)),
	VIF0_REGISTER_ITOP(std::make_shared<MappedMemory32_t>("VIF0: VIF0_ITOP", 0x100038d0)),
	VIF0_REGISTER_38e0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38e0 (reserved)", 0x100038e0)),
	VIF0_REGISTER_38f0(std::make_shared<DeadMMemory_t>(0x10, "VIF0: VIF0_38f0 (reserved)", 0x100038f0)),
	VIF0_REGISTER_R0(std::make_shared<MappedMemory32_t>("VIF0: VIF0_R0", 0x10003900)),
	VIF0_REGISTER_R1(std::make_shared<MappedMemory32_t>("VIF0: VIF0_R1", 0x10003910)),
	VIF0_REGISTER_R2(std::make_shared<MappedMemory32_t>("VIF0: VIF0_R2", 0x10003920)),
	VIF0_REGISTER_R3(std::make_shared<MappedMemory32_t>("VIF0: VIF0_R3", 0x10003930)),
	VIF0_REGISTER_C0(std::make_shared<MappedMemory32_t>("VIF0: VIF0_C0", 0x10003940)),
	VIF0_REGISTER_C1(std::make_shared<MappedMemory32_t>("VIF0: VIF0_C1", 0x10003950)),
	VIF0_REGISTER_C2(std::make_shared<MappedMemory32_t>("VIF0: VIF0_C2", 0x10003960)),
	VIF0_REGISTER_C3(std::make_shared<MappedMemory32_t>("VIF0: VIF0_C3", 0x10003970)),
	VIF0_REGISTER_3980(std::make_shared<DeadMMemory_t>(0x280, "VIF0: VIF0_3980 (reserved)", 0x10003980)),

	// VIF1 Registers.
	VIF1_REGISTER_STAT(std::make_shared<MappedMemory32_t>("VIF1: VIF1_STAT", 0x10003c00)),
	VIF1_REGISTER_FBRST(std::make_shared<MappedMemory32_t>("VIF1: VIF1_FBRST", 0x10003c10)),
	VIF1_REGISTER_ERR(std::make_shared<MappedMemory32_t>("VIF1: VIF1_ERR", 0x10003c20)),
	VIF1_REGISTER_MARK(std::make_shared<MappedMemory32_t>("VIF1: VIF1_MARK", 0x10003c30)),
	VIF1_REGISTER_CYCLE(std::make_shared<MappedMemory32_t>("VIF1: VIF1_CYCLE", 0x10003c40)),
	VIF1_REGISTER_MODE(std::make_shared<MappedMemory32_t>("VIF1: VIF1_MODE", 0x10003c50)),
	VIF1_REGISTER_NUM(std::make_shared<MappedMemory32_t>("VIF1: VIF1_NUM", 0x10003c60)),
	VIF1_REGISTER_MASK(std::make_shared<MappedMemory32_t>("VIF1: VIF1_MASK", 0x10003c70)),
	VIF1_REGISTER_CODE(std::make_shared<MappedMemory32_t>("VIF1: VIF1_CODE", 0x10003c80)),
	VIF1_REGISTER_ITOPS(std::make_shared<MappedMemory32_t>("VIF1: VIF1_ITOPS", 0x10003c90)),
	VIF1_REGISTER_BASE(std::make_shared<MappedMemory32_t>("VIF1: VIF1_BASE", 0x10003ca0)),
	VIF1_REGISTER_OFST(std::make_shared<MappedMemory32_t>("VIF1: VIF1_OFST", 0x10003cb0)),
	VIF1_REGISTER_TOPS(std::make_shared<MappedMemory32_t>("VIF1: VIF1_TOPS", 0x10003cc0)),
	VIF1_REGISTER_ITOP(std::make_shared<MappedMemory32_t>("VIF1: VIF1_ITOP", 0x10003cd0)),
	VIF1_REGISTER_TOP(std::make_shared<MappedMemory32_t>("VIF1: VIF1_TOP", 0x10003ce0)),
	VIF1_REGISTER_3cf0(std::make_shared<DeadMMemory_t>(0x10, "VIF1: VIF1_3cf0 (reserved)", 0x10003cf0)),
	VIF1_REGISTER_R0(std::make_shared<MappedMemory32_t>("VIF1: VIF1_R0", 0x10003d00)),
	VIF1_REGISTER_R1(std::make_shared<MappedMemory32_t>("VIF1: VIF1_R1", 0x10003d10)),
	VIF1_REGISTER_R2(std::make_shared<MappedMemory32_t>("VIF1: VIF1_R2", 0x10003d20)),
	VIF1_REGISTER_R3(std::make_shared<MappedMemory32_t>("VIF1: VIF1_R3", 0x10003d30)),
	VIF1_REGISTER_C0(std::make_shared<MappedMemory32_t>("VIF1: VIF1_C0", 0x10003d40)),
	VIF1_REGISTER_C1(std::make_shared<MappedMemory32_t>("VIF1: VIF1_C1", 0x10003d50)),
	VIF1_REGISTER_C2(std::make_shared<MappedMemory32_t>("VIF1: VIF1_C2", 0x10003d60)),
	VIF1_REGISTER_C3(std::make_shared<MappedMemory32_t>("VIF1: VIF1_C3", 0x10003d70)),
	VIF1_REGISTER_3d80(std::make_shared<DeadMMemory_t>(0x280, "VIF1: VIF1_3d80 (reserved)", 0x10003d80))
{
}
