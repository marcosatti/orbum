#include "stdafx.h"

#include <memory>

#include "Resources/EE/VPU/VIF/Types/VIFUnits_t.h"
#include "Resources/EE/VPU/VIF/Types/VIFUnitRegisters_t.h"

VifUnit_t::VifUnit_t(const u32 & unitID) :
	mUnitID(unitID),
	R0(std::make_shared<Register32_t>()),
	R1(std::make_shared<Register32_t>()),
	R2(std::make_shared<Register32_t>()),
	R3(std::make_shared<Register32_t>()),
	C0(std::make_shared<Register32_t>()),
	C1(std::make_shared<Register32_t>()),
	C2(std::make_shared<Register32_t>()),
	C3(std::make_shared<Register32_t>()),
	CYCLE(std::make_shared<VifUnitRegister_CYCLE_t>()),
	MASK(std::make_shared<VifUnitRegister_MASK_t>()),
	MODE(std::make_shared<VifUnitRegister_MODE_t>()),
	ITOP(std::make_shared<VifUnitRegister_ITOP_t>()),
	ITOPS(std::make_shared<VifUnitRegister_ITOPS_t>()),
	BASE(std::make_shared<VifUnitRegister_BASE_t>()),
	OFST(std::make_shared<VifUnitRegister_OFST_t>()),
	TOP(std::make_shared<VifUnitRegister_TOP_t>()),
	TOPS(std::make_shared<VifUnitRegister_TOPS_t>()),
	MARK(std::make_shared<VifUnitRegister_MASK_t>()),
	NUM(std::make_shared<VifUnitRegister_NUM_t>()),
	CODE(std::make_shared<VifUnitRegister_CODE_t>()),
	STAT(std::make_shared<VifUnitRegister_STAT_t>()),
	FBRST(std::make_shared<VifUnitRegister_FBRST_t>()),
	ERR(std::make_shared<VifUnitRegister_ERR_t>())
{
}

VifUnit_VIF0_t::VifUnit_VIF0_t() :
	VifUnit_t(UNIT_ID)
{
}

VifUnit_VIF1_t::VifUnit_VIF1_t() :
	VifUnit_t(UNIT_ID)
{
}
